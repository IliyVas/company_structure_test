#ifndef COMPANY_STRUCTURE_TEST_DEPARTMENTEDIT_H
#define COMPANY_STRUCTURE_TEST_DEPARTMENTEDIT_H

#include <nana/gui.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/panel.hpp>
#include "View.h"
#include "../viewmodels/ViewModel.h"
#include "../viewmodels/DepartmentVM.h"

namespace views {
    using namespace nana;
    using namespace viewmodels;

    class DepartmentEdit : public panel<false>, public View {
        place layout;
        label title, avgSalary, employeesNum, nameLbl;
        textbox name;
        button save;

        DepartmentVM *departmentVM;

        void initSaveEvent();

    public:
        DepartmentEdit(window wd);

        void SetViewModel(DepartmentVM *dep_vm);

        DepartmentVM *GetDepartmentVM() const;

        void Update(ViewModel *view_model, ChangeType change_type = ChangeType::DUMMY) override;
    };
}

#endif //COMPANY_STRUCTURE_TEST_DEPARTMENTEDIT_H
