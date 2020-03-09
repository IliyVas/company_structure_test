#include "DepartmentEdit.h"
#include <sstream>
#include <iomanip>

using namespace views;
using namespace viewmodels;

DepartmentEdit::DepartmentEdit(window wd) :
        panel<false>(wd),
        layout(*this),
        title(*this),
        avgSalary(*this),
        employeesNum(*this),
        nameLbl(*this),
        name(*this),
        save(*this, "Save") {
    title.format(true).caption("<size=20 top>Department</>");
    nameLbl.format(true).caption("<bottom>Department name:</>");
    name.tip_string("Department name").multi_lines(false);
    initSaveEvent();
    layout.div("vertical <weight=50 margin=5 title>"
               "<weight=30 margin=[5,10,5] avg_salary>"
               "<weight=30 margin=[5,10,5] emp_num>"
               "<weight=30 margin=[5,10,0] name_lbl>"
               "<margin=[2,10,5] weight=35 name>"
               "<>"
               "<weight=35 margin=5 save>");
    layout["title"] << title;
    layout["emp_num"] << employeesNum;
    layout["avg_salary"] << avgSalary;
    layout["name_lbl"] << nameLbl;
    layout["name"] << name;
    layout["save"] << save;
    layout.collocate();
}

void views::DepartmentEdit::Update(ViewModel *view_model, ChangeType change_type) {}

void DepartmentEdit::SetViewModel(DepartmentVM *dep_vm) {
    name.caption(dep_vm->GetName());
    std::stringstream ss;
    ss << "Average salary: " << std::fixed << std::setprecision(2) << dep_vm->GetAvgSalary();
    avgSalary.caption(ss.str());
    employeesNum.caption("Employees: " + std::to_string(dep_vm->GetEmployeesNum()));
    departmentVM = dep_vm;
}

void DepartmentEdit::initSaveEvent() {
    save.events().click([&]() {
        departmentVM->SetName(name.text());
    });
}

DepartmentVM *DepartmentEdit::GetDepartmentVM() const {
    return departmentVM;
}
