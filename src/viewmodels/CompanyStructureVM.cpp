#include "CompanyStructureVM.h"

using namespace viewmodels;

unsigned CompanyStructureVM::newDepartmentNum = 1;

void CompanyStructureVM::OpenFile(const std::filesystem::path &path) {
    csstore.LoadXML(path.string());
    for (auto &dep : csstore.GetCompanyStructure()->GetDepartments()) {
        departments.push_back(std::make_unique<DepartmentVM>(dep));
    }
    NotifyViews();
}

const std::vector<std::unique_ptr<DepartmentVM>> &CompanyStructureVM::GetDepartments() const {
    return departments;
}

bool CompanyStructureVM::HasUndoActions() {
    return !csstore.GetCompanyStructure()->IsFirstState();
}

bool CompanyStructureVM::HasRedoActions() {
    return !csstore.GetCompanyStructure()->IsLastState();
}

void CompanyStructureVM::CreateDepartment() {
    auto new_dep_name = std::string("New Department ") + std::to_string(newDepartmentNum);
    newDepartmentNum++;

    auto new_dep = std::make_shared<models::Department>(new_dep_name);
    csstore.GetCompanyStructure()->AddDepartment(new_dep);
    departments.push_back(std::make_unique<DepartmentVM>(new_dep));

    NotifyViews();
}

void CompanyStructureVM::RemoveDepartment(DepartmentVM *dep_vm) {
    auto find_it = std::find_if(departments.begin(), departments.end(), [&dep_vm](auto &dep_uniq_ptr) {
        return dep_uniq_ptr.get() == dep_vm;
    });
    if (find_it == departments.end()) {
        throw std::runtime_error("Disaster happened");
    }
    csstore.GetCompanyStructure()->RemoveDepartament((*find_it)->GetDepartment());
    departments.erase(find_it);
    NotifyViews();
}

bool CompanyStructureVM::IsExpanded() const {
    return expanded;
}

void CompanyStructureVM::SetExpanded(bool expanded) {
    CompanyStructureVM::expanded = expanded;
}

void CompanyStructureVM::Undo() {
    bool changed = csstore.GetCompanyStructure()->PreviousState();
    if (changed) {
        updateDepartmentsVM();
    }
}

void CompanyStructureVM::Redo() {
    bool changed = csstore.GetCompanyStructure()->NextState();
    if (changed) {
        updateDepartmentsVM();
    }
}

void CompanyStructureVM::updateDepartmentsVM() {
    std::vector<std::unique_ptr<DepartmentVM>> new_departments;
    for (auto &dep : csstore.GetCompanyStructure()->GetDepartments()) {
        new_departments.push_back(std::make_unique<DepartmentVM>(dep));
    }

    for (int i = 0; i < departments.size() && i < new_departments.size(); i++) {
        if (departments[i]->GetDepartment() != new_departments[i]->GetDepartment()) continue;
        new_departments[i]->SetExpanded(departments[i]->IsExpanded());
    }
    departments = std::move(new_departments);
    NotifyViews();
}
