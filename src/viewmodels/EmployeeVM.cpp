#include <sstream>
#include "EmployeeVM.h"

using namespace viewmodels;

EmployeeVM::EmployeeVM(const std::shared_ptr<models::Employee> &employee) : employee(employee), expanded(false) {}

const std::string &EmployeeVM::GetFirstName() const {
    return employee->GetFirstName();
}

const std::string &EmployeeVM::GetSurname() const {
    return employee->GetSurname();
}

const std::string &EmployeeVM::GetMiddleName() const {
    return employee->GetMiddleName();
}

const std::string &EmployeeVM::GetFunction() const {
    return employee->GetFunction();
}

unsigned int EmployeeVM::GetSalary() const {
    return employee->GetSalary();
}

const std::string EmployeeVM::GetFullName() const {
    std::stringstream ss;
    ss << GetSurname() << ' ' << GetFirstName() << ' ' << GetMiddleName();
    return ss.str();
}

bool EmployeeVM::IsExpanded() const {
    return expanded;
}

void EmployeeVM::SetExpanded(bool expanded) {
    EmployeeVM::expanded = expanded;
}

bool EmployeeVM::SetFields(const std::string &first_name, const std::string &surname, const std::string &middle_name,
                           const std::string &function, unsigned salary) {
    bool changed = employee->SetFields(first_name, surname, middle_name, function, salary);
    if (changed) {
        NotifyViews(ChangeType::EMP_CHANGED);
    }
    return changed;
}

const std::shared_ptr<models::Employee> &EmployeeVM::GetEmployee() const {
    return employee;
}
