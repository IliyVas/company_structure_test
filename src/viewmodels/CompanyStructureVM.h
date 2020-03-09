//
// Created by vasil on 08/03/2020.
//

#ifndef COMPANY_STRUCTURE_TEST_COMPANYSTRUCTUREVM_H
#define COMPANY_STRUCTURE_TEST_COMPANYSTRUCTUREVM_H

#include <nana/filesystem/filesystem.hpp>
#include "ViewModel.h"
#include "DepartmentVM.h"
#include "../data_access/CompanyStructureStore.h"

namespace viewmodels {
    using namespace viewmodels;
    using namespace data_access;
    class CompanyStructureVM: public ViewModel {
        CompanyStructureStore csstore;
        std::vector<std::unique_ptr<DepartmentVM>> departments;
        bool expanded = false;

        static unsigned newDepartmentNum;

        void updateDepartmentsVM();

    public:
        void OpenFile(const std::filesystem::path &path);

        bool HasUndoActions();
        bool HasRedoActions();
        void Undo();
        void Redo();
        void CreateDepartment();
        void RemoveDepartment(DepartmentVM* dep_vm);
        const std::vector<std::unique_ptr<DepartmentVM>> &GetDepartments() const;

        bool IsExpanded() const;

        void SetExpanded(bool expanded);
    };
}

#endif //COMPANY_STRUCTURE_TEST_COMPANYSTRUCTUREVM_H
