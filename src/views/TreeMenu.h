#ifndef COMPANY_STRUCTURE_TEST_TREEMENU_H
#define COMPANY_STRUCTURE_TEST_TREEMENU_H

#include <nana/gui/widgets/menu.hpp>
#include <nana/gui/widgets/treebox.hpp>
#include "../viewmodels/ViewModel.h"

namespace views {
    using namespace nana;
    struct TreeMenu : public menu {
        viewmodels::DepartmentVM *DepVM = nullptr;
        viewmodels::EmployeeVM *EmpVM = nullptr;
        treebox::item_proxy *Item;
    };
}

#endif //COMPANY_STRUCTURE_TEST_TREEMENU_H
