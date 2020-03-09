#ifndef COMPANY_STRUCTURE_TEST_COMPANYSTRUCTURE_H
#define COMPANY_STRUCTURE_TEST_COMPANYSTRUCTURE_H

#include <vector>
#include <memory>
#include "Stateful.h"

namespace models {
    class Department;

    class CompanyStructure : public Stateful {
        friend class Department;

        enum ChangeType {
            DEP_ADD,
            DEP_REMOVE,
            DEP_CHANGE
        };

        struct Change {
            ChangeType Type;
            std::shared_ptr<Department> Dep;
            unsigned RemovedDepIndex;
        };

        std::vector<std::shared_ptr<Department>> departments;
        std::vector<Change> changes;
        unsigned currentStateIndex = 0;

        void departmentChanged(Department *department);

        void removeFirstState();

    public:
        CompanyStructure() {}

        CompanyStructure(CompanyStructure const &) = delete;

        CompanyStructure &operator=(CompanyStructure const &) = delete;

        std::vector<std::shared_ptr<Department>> &GetDepartments();

        void AddDepartment(std::shared_ptr<Department> department, bool track_history = true);

        bool RemoveDepartament(std::shared_ptr<Department> department);

        bool PreviousState() override;

        bool NextState() override;

        bool IsFirstState() override;

        bool IsLastState() override;
    };
}

#endif //COMPANY_STRUCTURE_TEST_COMPANYSTRUCTURE_H
