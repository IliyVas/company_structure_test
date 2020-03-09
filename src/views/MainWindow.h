#ifndef COMPANY_STRUCTURE_TEST_MAINWINDOW_H
#define COMPANY_STRUCTURE_TEST_MAINWINDOW_H

#include <nana/gui.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/treebox.hpp>


#include "DepartmentEdit.h"
#include "EmployeeEdit.h"
#include "View.h"
#include "TreeMenu.h"
#include "../viewmodels/CompanyStructureVM.h"

namespace views {
    using namespace nana;
    using namespace viewmodels;

    class MainWindow : public form, public View {
        place layout;
        menubar topMenubar;
        label helloLbl, infoLbl;
        treebox companyStructureTree;
        DepartmentEdit departmentEdit;
        EmployeeEdit employeeEdit;

        menu companyStructureMenu;
        TreeMenu departmentMenu, employeeMenu;

        CompanyStructureVM companyStructureVM;

        void initMenubar();

        void initMenus();

        void initTree();

        void recreateTreeStructure();

    public:
        MainWindow();

        void Update(ViewModel *view_model, ChangeType change_type = ChangeType::DUMMY) override;

    };
}

#endif //COMPANY_STRUCTURE_TEST_MAINWINDOW_H
