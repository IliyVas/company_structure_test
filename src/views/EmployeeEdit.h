#ifndef COMPANY_STRUCTURE_TEST_EMPLOYEEEDIT_H
#define COMPANY_STRUCTURE_TEST_EMPLOYEEEDIT_H

#include <nana/gui.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/panel.hpp>
#include "View.h"
#include "../viewmodels/EmployeeVM.h"
#include "../viewmodels/ViewModel.h"

namespace views {
    using namespace nana;
    using namespace viewmodels;

    class EmployeeEdit : public panel<false>, public View {
        place layout;
        label title, firstNameLbl, surnameLbl, middleNameLbl, functionLbl, salaryLbl;
        textbox firstName, surname, middleName, function, salary;
        button save;
        EmployeeVM *employeeVM;

        void initSaveEvent();

    public:
        EmployeeEdit(window wd);

        void SetViewModel(EmployeeVM *emp_vm);

        EmployeeVM *GetEmployeeVM() const;

        void Update(ViewModel *view_model, ChangeType change_type = ChangeType::DUMMY) override;

    };
}

#endif //COMPANY_STRUCTURE_TEST_EMPLOYEEEDIT_H
