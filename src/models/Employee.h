//
// Created by vasil on 03/03/2020.
//

#ifndef COMPANY_STRUCTURE_TEST_EMPLOYEE_H
#define COMPANY_STRUCTURE_TEST_EMPLOYEE_H


#include <string>
#include <memory>
#include "Stateful.h"
#include "Department.h"

using namespace models;

namespace models {
    class Employee : public Stateful {
        friend class Department;

        std::string firstName;
        std::string surname;
        std::string middleName;
        std::string function;
        unsigned salary;
        Department *department;

        unsigned currentStateIndex = 0;
        std::vector<std::unique_ptr<Employee>> states;

        void saveCurrentState(bool notify_department = true);

        void setState(const std::unique_ptr<Employee> &employee);

        void removeFirstState();

    public:
        Employee(const std::string &firstName, const std::string &surname, const std::string &middleName,
                 const std::string &function, unsigned int salary);

        Employee(Employee const &) = delete;

        Employee &operator=(Employee const &) = delete;

        Employee() = delete;

        const std::string &GetFirstName() const;

        const std::string &GetSurname() const;

        const std::string &GetMiddleName() const;

        const std::string &GetFunction() const;

        unsigned int GetSalary() const;

        std::shared_ptr<Department> GetDepartment() const;

        bool SetFields(const std::string &first_name, const std::string &surname, const std::string &middle_name,
                       const std::string &function,
                       unsigned salary);

        friend void Department::AddEmployee(const std::shared_ptr<Employee> &employee, bool track_history);

        bool PreviousState() override;

        bool NextState() override;

        bool IsFirstState() override;

        bool IsLastState() override;
    };
}

#endif //COMPANY_STRUCTURE_TEST_EMPLOYEE_H
