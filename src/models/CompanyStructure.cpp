#include <algorithm>
#include "CompanyStructure.h"
#include "Department.h"

using namespace models;

std::vector<std::shared_ptr<Department>> &CompanyStructure::GetDepartments() {
    return departments;
}

void CompanyStructure::AddDepartment(std::shared_ptr<Department> department, bool track_history) {
    department->companyStructure = this;
    departments.push_back(department);
    if (!track_history) {
        return;
    }

    changes.push_back(Change{
            ChangeType::DEP_ADD,
            department,
            0
    });
    currentStateIndex++;

    if (changes.size() > maxStateNum) {
        removeFirstState();
    }
}

bool CompanyStructure::RemoveDepartament(std::shared_ptr<Department> department) {
    auto find_it = std::find(departments.begin(), departments.end(), department);
    if (find_it == departments.end()) {
        return false;
    }

    departments.erase(find_it);
    changes.push_back(Change{
            ChangeType::DEP_REMOVE,
            department,
            static_cast<unsigned int>(find_it - departments.begin())
    });
    currentStateIndex++;

    if (changes.size() > maxStateNum) {
        removeFirstState();
    }

    return true;
}

bool CompanyStructure::PreviousState() {
    if (currentStateIndex == 0) {
        return false;
    }

    currentStateIndex--;
    auto &change = changes[currentStateIndex];
    switch (change.Type) {
        case ChangeType::DEP_REMOVE: {
            departments.insert(departments.begin() + change.RemovedDepIndex, change.Dep);
            break;
        }

        case ChangeType::DEP_ADD: {
            departments.pop_back();
            break;
        }

        case ChangeType::DEP_CHANGE: {
            change.Dep->PreviousState();
            break;
        }

        default:
            throw std::runtime_error("Disaster happened");
    }
    return true;
}

bool CompanyStructure::NextState() {
    if (currentStateIndex == changes.size()) {
        return false;
    }

    auto &change = changes[currentStateIndex];
    switch (change.Type) {
        case ChangeType::DEP_REMOVE: {
            departments.erase(departments.begin() + change.RemovedDepIndex);
            break;
        }

        case ChangeType::DEP_ADD: {
            departments.push_back(change.Dep);
            break;
        }

        case ChangeType::DEP_CHANGE: {
            change.Dep->NextState();
            break;
        }

        default:
            throw std::runtime_error("Disaster happened");
    }
    currentStateIndex++;
    return true;
}

bool CompanyStructure::IsFirstState() {
    return currentStateIndex == 0;
}

bool CompanyStructure::IsLastState() {
    return currentStateIndex == changes.size();
}

void CompanyStructure::removeFirstState() {
    if (changes.size() == 0) {
        return;
    }

    auto &change = changes[0];
    if (change.Type == ChangeType::DEP_CHANGE) {
        change.Dep->removeFirstState();
    }
    changes.erase(changes.begin());
}

void CompanyStructure::departmentChanged(Department *department) {
    auto find_it = std::find_if(departments.begin(), departments.end(),
                                [department](auto &dep) { return dep.get() == department; });
    if (find_it == departments.end()) {
        throw std::runtime_error("Disaster happened");
    }
    changes.push_back(Change{
            ChangeType::DEP_CHANGE,
            *find_it,
            0
    });
    currentStateIndex++;
}