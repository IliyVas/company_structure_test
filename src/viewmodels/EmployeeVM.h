#ifndef COMPANY_STRUCTURE_TEST_EMPLOYEEVM_H
#define COMPANY_STRUCTURE_TEST_EMPLOYEEVM_H

#include "ViewModel.h"
#include "../models/Employee.h"

namespace viewmodels {
    class EmployeeVM : public ViewModel {
        std::shared_ptr<models::Employee> employee;
        bool expanded;
    public:
        EmployeeVM(const std::shared_ptr<models::Employee> &employee);

        const std::string &GetFirstName() const;

        const std::string &GetSurname() const;

        const std::string &GetMiddleName() const;

        const std::string GetFullName() const;

        const std::string &GetFunction() const;

        unsigned int GetSalary() const;

        const std::shared_ptr<models::Employee> &GetEmployee() const;

        bool IsExpanded() const;

        void SetExpanded(bool expanded);

        bool SetFields(const std::string &first_name, const std::string &surname, const std::string &middle_name,
                       const std::string &function,
                       unsigned salary);
    };
}


#endif //COMPANY_STRUCTURE_TEST_EMPLOYEEVM_H
