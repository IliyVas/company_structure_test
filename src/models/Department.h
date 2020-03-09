#ifndef COMPANY_STRUCTURE_TEST_DEPARTMENT_H
#define COMPANY_STRUCTURE_TEST_DEPARTMENT_H

#include <string>
#include <vector>
#include "CompanyStructure.h"
#include "Stateful.h"

namespace models {
    class Employee;

    class Department : public Stateful {
        friend class CompanyStructure;

        friend class Employee;

        enum ChangeType {
            EMP_ADD,
            EMP_REMOVE,
            EMP_CHANGE,
            DEP_CHANGE
        };

        struct Change {
            ChangeType Type;
        };

        struct DepChange : public Change {
            std::string OldName;
            std::string NewName;
        };

        struct EmpChange : public Change {
            std::shared_ptr<Employee> Emp;
            unsigned RemovedEmpIndex;
        };

        std::string name;
        unsigned employees_num = 0;
        unsigned salary_sum = 0;
        float avg_salary = 0;

        CompanyStructure *companyStructure;
        std::vector<std::shared_ptr<Employee>> employees;

        unsigned currentStateIndex = 0;
        std::vector<std::unique_ptr<Change>> changes;

        void addChange(std::unique_ptr<Change> change);

        void employeeChanged(Employee *employee);

        void removeFirstState();

        std::shared_ptr<Department> getSharedPtrToThis() const;

    public:
        Department(const std::string &name);

        Department(Employee const &) = delete;

        Department &operator=(Department const &) = delete;

        Department() = delete;

        const std::string &GetName() const;

        void SetName(const std::string &new_name);

        unsigned int GetEmployeesNum() const;

        float GetAvgSalary() const;

        void AddEmployee(const std::shared_ptr<Employee> &employee, bool track_history = true);

        bool RemoveEmployee(const std::shared_ptr<Employee> &employee);

        std::vector<std::shared_ptr<Employee>> &GetEmployees();

        bool PreviousState() override;

        bool NextState() override;

        bool IsFirstState() override;

        bool IsLastState() override;
    };
}

#endif //COMPANY_STRUCTURE_TEST_DEPARTMENT_H
