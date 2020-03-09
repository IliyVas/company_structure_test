#ifndef COMPANY_STRUCTURE_TEST_DEPARTMENTVM_H
#define COMPANY_STRUCTURE_TEST_DEPARTMENTVM_H

#include <memory>
#include "ViewModel.h"
#include "EmployeeVM.h"
#include "../models/Department.h"

namespace viewmodels {
    using namespace viewmodels;

    class DepartmentVM : public ViewModel {
        std::shared_ptr<models::Department> department;
        std::vector<std::unique_ptr<EmployeeVM>> employees;
        bool expanded;

        static unsigned newEmployeeNum;

    public:
        DepartmentVM(std::shared_ptr<models::Department> &department);

        float GetAvgSalary() const;

        unsigned GetEmployeesNum() const;

        const std::string &GetName() const;

        void SetName(const std::string &val);

        void AddEmployee();

        const std::vector<std::unique_ptr<EmployeeVM>> &GetEmployees() const;

        void RemoveEmployee(EmployeeVM *emp_vm);

        const std::shared_ptr<models::Department> &GetDepartment() const;

        bool IsExpanded() const;

        void SetExpanded(bool expanded);
    };
}


#endif //COMPANY_STRUCTURE_TEST_DEPARTMENTVM_H
