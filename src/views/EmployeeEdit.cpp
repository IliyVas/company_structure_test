//
// Created by vasil on 09/03/2020.
//

#include "EmployeeEdit.h"

using namespace views;

EmployeeEdit::EmployeeEdit(window wd) :
        panel<false>(wd),
        layout(*this),
        title(*this),
        firstNameLbl(*this),
        surnameLbl(*this),
        middleNameLbl(*this),
        functionLbl(*this),
        salaryLbl(*this),
        firstName(*this),
        surname(*this),
        middleName(*this),
        function(*this),
        salary(*this),
        save(*this, "Save") {
    title.format(true).caption("<size=20 top>Employee</>");
    firstNameLbl.format(true).caption("<bottom>First name:</>");
    surnameLbl.format(true).caption("Surname:");
    middleNameLbl.format(true).caption("Middle name:");
    functionLbl.format(true).caption("Function:");
    salaryLbl.format(true).caption("Salary:");
    firstName.tip_string("First name").multi_lines(false);
    surname.tip_string("Surname").multi_lines(false);
    middleName.tip_string("Middle name").multi_lines(false);
    function.tip_string("Function").multi_lines(false);
    salary.tip_string("Salary").multi_lines(false);
    salary.set_accept([this](wchar_t key) {
        // 8 - backspace, 127 - del
        if (key == 8 || key == 127) return true;
        if (salary.text().size() >= 7) return false;
        if (salary.text().size() == 0 && key == '0') return false;
        return (key >= '0' && key <= '9');
    });

    initSaveEvent();
    layout.div("vertical <weight=50 margin=5 title>"
               "<margin=[5,10,0] weight=30 first_name_lbl>"
               "<margin=[2,10,5] weight=35 first_name>"

               "<margin=[5,10,0] weight=30 surname_lbl>"
               "<margin=[2,10,5] weight=35 surname>"

               "<margin=[5,10,0] weight=30 middle_name_lbl>"
               "<margin=[2,10,5] weight=35 middle_name>"

               "<margin=[5,10,0] weight=30 function_lbl>"
               "<margin=[2,10,5] weight=35 function>"

               "<margin=[5,10,0] weight=30 salary_lbl>"
               "<margin=[2,10,5] weight=35 salary>"

               "<>"
               "<weight=35 margin=5 save>");
    layout["title"] << title;
    layout["first_name_lbl"] << firstNameLbl;
    layout["first_name"] << firstName;
    layout["surname_lbl"] << surnameLbl;
    layout["surname"] << surname;
    layout["middle_name_lbl"] << middleNameLbl;
    layout["middle_name"] << middleName;
    layout["function_lbl"] << functionLbl;
    layout["function"] << function;
    layout["salary_lbl"] << salaryLbl;
    layout["salary"] << salary;
    layout["save"] << save;
    layout.collocate();
}

void EmployeeEdit::initSaveEvent() {
    save.events().click([&]() {
        employeeVM->SetFields(firstName.text(), surname.text(), middleName.text(), function.text(), salary.to_int());
    });
}

void EmployeeEdit::SetViewModel(EmployeeVM *emp_vm) {
    firstName.caption(emp_vm->GetFirstName());
    surname.caption(emp_vm->GetSurname());
    middleName.caption(emp_vm->GetMiddleName());
    function.caption(emp_vm->GetFunction());
    salary.from((int) emp_vm->GetSalary());
    employeeVM = emp_vm;
}

void EmployeeEdit::Update(ViewModel *view_model, ChangeType change_type) {}

EmployeeVM *EmployeeEdit::GetEmployeeVM() const {
    return employeeVM;
}
