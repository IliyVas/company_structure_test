#include <algorithm>
#include "Employee.h"

Employee::Employee(const std::string &firstName, const std::string &surname, const std::string &middleName,
                   const std::string &function, unsigned int salary)
        : firstName(firstName), surname(surname), middleName(middleName), function(function), salary(salary) {}

const std::string &Employee::GetFirstName() const {
    return firstName;
}

const std::string &Employee::GetSurname() const {
    return surname;
}

const std::string &Employee::GetMiddleName() const {
    return middleName;
}

const std::string &Employee::GetFunction() const {
    return function;
}

unsigned int Employee::GetSalary() const {
    return salary;
}

std::shared_ptr<Department> Employee::GetDepartment() const {
    return department->getSharedPtrToThis();
}

void Employee::saveCurrentState(bool notify_department) {
    if ((int) currentStateIndex < ((int) states.size() - 1)) {
        states.resize(currentStateIndex + 1);
    } else {
        auto cur_state = std::make_unique<Employee>(firstName, surname, middleName, function, salary);
        cur_state->department = department;
        states.push_back(std::move(cur_state));
    }
    currentStateIndex++;
    if (notify_department) {
        department->employeeChanged(this);
    }
}

void Employee::setState(const std::unique_ptr<Employee> &employee) {
    firstName = employee->firstName;
    surname = employee->surname;
    middleName = employee->middleName;
    function = employee->function;
    salary = employee->salary;
    department = employee->department;
}

bool Employee::PreviousState() {
    if (currentStateIndex == 0) {
        return false;
    }
    if (currentStateIndex == states.size()) {
        saveCurrentState(false);
        currentStateIndex--;
    }
    currentStateIndex--;
    auto &previous_state = states[currentStateIndex];
    setState(previous_state);
    return true;
}

bool Employee::NextState() {
    if (currentStateIndex == states.size()) {
        return false;
    }
    currentStateIndex++;
    auto &next_state = states[currentStateIndex];
    setState(next_state);

    if ((int) currentStateIndex == ((int) states.size() - 1)) {
        states.resize(currentStateIndex);
    }
    return true;
}

bool Employee::IsFirstState() {
    return currentStateIndex == 0;
}

bool Employee::IsLastState() {
    return currentStateIndex == states.size();
}

void Employee::removeFirstState() {
    states.erase(states.begin());
    currentStateIndex--;
}

bool Employee::SetFields(const std::string &first_name, const std::string &surname, const std::string &middle_name,
                         const std::string &function, unsigned salary) {
    if (Employee::firstName == first_name &&
        Employee::surname == surname &&
        Employee::middleName == middle_name &&
        Employee::function == function &&
        Employee::salary == salary) {
        return false;
    }

    saveCurrentState();
    Employee::firstName = first_name;
    Employee::surname = surname;
    Employee::middleName = middle_name;
    Employee::function = function;
    Employee::salary = salary;
    return true;
}
