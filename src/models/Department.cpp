#include <algorithm>
#include "Department.h"
#include "Employee.h"

using namespace models;

Department::Department(const std::string &name) : name(name) {}

const std::string &Department::GetName() const {
    return name;
}

void Department::SetName(const std::string &new_name) {
    auto change = std::unique_ptr<Change>(new DepChange{{ChangeType::DEP_CHANGE}, name, new_name});
    addChange(std::move(change));
    name = new_name;
}

unsigned int Department::GetEmployeesNum() const {
    return employees_num;
}

float Department::GetAvgSalary() const {
    return avg_salary;
}

void Department::AddEmployee(const std::shared_ptr<Employee> &employee, bool track_history) {
    employee->department = this;
    employees.push_back(employee);
    employees_num++;
    salary_sum += employee->GetSalary();
    avg_salary = salary_sum / employees_num;

    if (!track_history) {
        return;
    }
    auto change = std::unique_ptr<Change>(new EmpChange{ChangeType::EMP_ADD, employee, 0});
    addChange(std::move(change));
}

bool Department::RemoveEmployee(const std::shared_ptr<Employee> &employee) {
    auto find_it = std::find(employees.begin(), employees.end(), employee);
    if (find_it == employees.end()) {
        return false;
    }
    auto change = std::unique_ptr<Change>(
            new EmpChange{ChangeType::EMP_REMOVE, employee, static_cast<unsigned int>(find_it - employees.begin())});
    addChange(std::move(change));

    salary_sum -= employee->GetSalary();
    employees_num--;
    avg_salary = salary_sum / employees_num;
    employees.erase(find_it);
    return true;
}

void Department::addChange(std::unique_ptr<Change> change) {
    if (currentStateIndex < changes.size()) {
        changes.resize(currentStateIndex);
    }
    changes.push_back(std::move(change));
    currentStateIndex++;
    companyStructure->departmentChanged(this);
}

bool Department::PreviousState() {
    if (currentStateIndex == 0) {
        return false;
    }

    currentStateIndex--;
    auto change = changes[currentStateIndex].get();
    switch (change->Type) {
        case ChangeType::EMP_REMOVE: {
            auto emp_change = static_cast<EmpChange *>(change);
            employees.insert(employees.begin() + emp_change->RemovedEmpIndex, emp_change->Emp);
            break;
        }

        case ChangeType::EMP_ADD: {
            employees.pop_back();
            break;
        }

        case ChangeType::EMP_CHANGE: {
            auto emp_change = static_cast<EmpChange *>(change);
            emp_change->Emp->PreviousState();
            break;
        }

        case ChangeType::DEP_CHANGE: {
            auto dep_change = static_cast<DepChange *>(change);
            name = dep_change->OldName;
            break;
        }

        default:
            throw std::runtime_error("Disaster happened");
    }
    return true;
}

bool Department::NextState() {
    if (currentStateIndex == changes.size()) {
        return false;
    }

    auto change = changes[currentStateIndex].get();
    switch (change->Type) {
        case ChangeType::EMP_REMOVE: {
            auto emp_change = static_cast<EmpChange *>(change);
            employees.erase(employees.begin() + emp_change->RemovedEmpIndex);
            break;
        }

        case ChangeType::EMP_ADD: {
            auto emp_change = static_cast<EmpChange *>(change);
            employees.push_back(emp_change->Emp);
            break;
        }

        case ChangeType::EMP_CHANGE: {
            auto emp_change = static_cast<EmpChange *>(change);
            emp_change->Emp->NextState();
            break;
        }

        case ChangeType::DEP_CHANGE: {
            auto dep_change = static_cast<DepChange *>(change);
            name = dep_change->NewName;
            break;
        }

        default:
            throw std::runtime_error("Disaster happened");
    }
    currentStateIndex++;
    return true;
}

bool Department::IsFirstState() {
    return currentStateIndex == 0;
}

bool Department::IsLastState() {
    return currentStateIndex == changes.size();
}

void Department::removeFirstState() {
    auto change = changes[0].get();
    if (change->Type == ChangeType::EMP_CHANGE) {
        static_cast<EmpChange *>(change)->Emp->removeFirstState();
    }
    changes.erase(changes.begin());
    currentStateIndex--;
}

void Department::employeeChanged(Employee *employee) {
    auto find_it = std::find_if(employees.begin(), employees.end(),
                                [employee](auto &emp) { return emp.get() == employee; });
    if (find_it == employees.end()) {
        throw std::runtime_error("Disaster happened");
    }
    auto change = std::unique_ptr<Change>(new EmpChange{ChangeType::EMP_CHANGE, *find_it, 0});
    addChange(std::move(change));
}

std::shared_ptr<Department> Department::getSharedPtrToThis() const {
    auto &departments = companyStructure->GetDepartments();
    auto find_it = std::find_if(departments.begin(), departments.end(),
                                [this](auto &dep) { return dep.get() == this; });
    if (find_it == departments.end()) {
        throw std::runtime_error("Disaster happened");
    }
    return *find_it;
}

std::vector<std::shared_ptr<Employee>> &Department::GetEmployees() {
    return employees;
}