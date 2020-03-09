#include <algorithm>
#include "DepartmentVM.h"

using namespace viewmodels;

unsigned DepartmentVM::newEmployeeNum = 1;

const std::string &DepartmentVM::GetName() const {
    return department->GetName();
}

DepartmentVM::DepartmentVM(std::shared_ptr<models::Department> &department) : department(department), expanded(false) {
    for (auto &emp : department->GetEmployees()) {
        employees.push_back(std::make_unique<EmployeeVM>(emp));
    }
}

const std::vector<std::unique_ptr<EmployeeVM>> &DepartmentVM::GetEmployees() const {
    return employees;
}

void DepartmentVM::SetName(const std::string &val) {
    department->SetName(val);
    NotifyViews(ChangeType::DEP_CHANED);
}

const std::shared_ptr<models::Department> &DepartmentVM::GetDepartment() const {
    return department;
}

void DepartmentVM::AddEmployee() {
    auto new_emp_name = std::string("New Employee ") + std::to_string(newEmployeeNum);
    newEmployeeNum++;

    auto new_emp = std::make_shared<models::Employee>("", new_emp_name, "", "", 0);
    department->AddEmployee(new_emp);
    employees.push_back(std::make_unique<EmployeeVM>(new_emp));

    NotifyViews(ChangeType::EMP_ADDED);
}

bool DepartmentVM::IsExpanded() const {
    return expanded;
}

void DepartmentVM::SetExpanded(bool expanded) {
    DepartmentVM::expanded = expanded;
}

void DepartmentVM::RemoveEmployee(EmployeeVM *emp_vm) {
    auto find_it = std::find_if(employees.begin(), employees.end(), [&emp_vm](auto &emp_uniq_ptr) {
        return emp_uniq_ptr.get() == emp_vm;
    });
    if (find_it == employees.end()) {
        throw std::runtime_error("Disaster happened");
    }
    department->RemoveEmployee((*find_it)->GetEmployee());
    employees.erase(find_it);
    NotifyViews(ChangeType::EMP_REMOVED);
}

float DepartmentVM::GetAvgSalary() const {
    return department->GetAvgSalary();
}

unsigned DepartmentVM::GetEmployeesNum() const {
    return department->GetEmployeesNum();
}
