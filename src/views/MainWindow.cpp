#include "MainWindow.h"
#include <nana/gui/filebox.hpp>
#include <iostream>

using namespace views;

MainWindow::MainWindow() :
        form(API::make_center(800, 500), appear::decorate<appear::sizable>()),
        layout(*this),
        topMenubar(*this),
        helloLbl(*this),
        infoLbl(*this),
        companyStructureTree(*this, true),
        departmentEdit(*this),
        employeeEdit(*this) {
    initMenubar();
    initMenus();
    initTree();

    helloLbl.format(true).caption("<size=14 center>Use File->Open() to open a xml file</>");
    infoLbl.format(true).caption("<size=12 center>Choose department or employee</>");

    layout.div("vertical <weight=28 menubar>"
               "<<><fit hello_msg><> hello>"
               "<<weight=30% margin=5 company_tree>"
               "<margin=10 info <><fit info_msg><>>"
               "<margin=5 department_edit>"
               "<margin=5 employee_edit>>");
    layout["menubar"] << topMenubar;
    layout["hello_msg"] << helloLbl;
    layout["info_msg"] << infoLbl;
    layout["company_tree"] << companyStructureTree;
    layout["employee_edit"] << employeeEdit;
    layout["department_edit"] << departmentEdit;
    layout.field_display("company_tree", false);
    layout.field_display("department_edit", false);
    layout.field_display("employee_edit", false);
    layout.field_display("info", false);
    layout.collocate();

    companyStructureVM.AddViewObserver(this);
}

void MainWindow::initTree() {
    companyStructureTree.events().expanded([this](const nana::arg_treebox &tb_msg) {
        if (!tb_msg.operated) return;
        if (tb_msg.item.level() == 1) {
            companyStructureVM.SetExpanded(tb_msg.item.expanded());
        }

        if (auto emp_vm_ptr = tb_msg.item.value_ptr<EmployeeVM *>()) {
            (*emp_vm_ptr)->SetExpanded(tb_msg.item.expanded());
        }

        if (auto dep_vm_ptr = tb_msg.item.value_ptr<DepartmentVM *>()) {
            (*dep_vm_ptr)->SetExpanded(tb_msg.item.expanded());
        }
    });

    companyStructureTree.events().selected([this](const nana::arg_treebox &tb_msg) {
        if (!tb_msg.operated) return;
        if (tb_msg.item.level() == 1) return;

        if (auto emp_vm_ptr = tb_msg.item.value_ptr<EmployeeVM *>()) {
            employeeEdit.SetViewModel(*emp_vm_ptr);
            layout.field_display("employee_edit", true);
            layout.field_display("department_edit", false);
            layout.field_display("info", false);
            layout.collocate();
        }

        if (auto dep_vm_ptr = tb_msg.item.value_ptr<DepartmentVM *>()) {
            departmentEdit.SetViewModel(*dep_vm_ptr);
            layout.field_display("employee_edit", false);
            layout.field_display("department_edit", true);
            layout.field_display("info", false);
            layout.collocate();
        }
    });

    companyStructureTree.events().mouse_down([this](const nana::arg_mouse &am) {
        if (!am.right_button) return;

        auto hovered = companyStructureTree.hovered(false);
        if (hovered.empty()) return;

        if (hovered.level() == 1) {
            companyStructureMenu.popup_await(am.window_handle, am.pos.x, am.pos.y);
            return;
        }

        if (hovered.level() == 2) {
            departmentMenu.Item = &hovered;
            departmentMenu.DepVM = hovered.value<DepartmentVM *>();
            departmentMenu.popup_await(am.window_handle, am.pos.x, am.pos.y);
            return;
        }

        if (hovered.level() == 3) {
            employeeMenu.Item = &hovered;
            employeeMenu.EmpVM = hovered.value<EmployeeVM *>();
            employeeMenu.DepVM = hovered.owner().value<DepartmentVM *>();
            employeeMenu.popup_await(am.window_handle, am.pos.x, am.pos.y);
            return;
        }
    });
}

void MainWindow::initMenubar() {
    topMenubar.push_back("&File");
    topMenubar.at(0).append("Open", [this](menu::item_proxy &ip) {
        filebox fbox(*this, true);
        fbox.add_filter("Xml", "*.xml");
        fbox.add_filter("All Files", "*.*");
        auto files = fbox.show();
        if (!files.empty()) {
            companyStructureVM.OpenFile(files.front());
            layout.field_display("hello", false);
            layout.field_display("company_tree", true);
            layout.field_display("info", true);
            layout.collocate();
        }
    });
    topMenubar.push_back("&Edit");
    topMenubar.at(1).append("Undo", [this](menu::item_proxy &ip) {
        companyStructureVM.Undo();
    });
    topMenubar.at(1).append("Redo", [this](menu::item_proxy &ip) {
        companyStructureVM.Redo();
    });

    topMenubar.at(1).enabled(0, false);
    topMenubar.at(1).enabled(1, false);
}

void MainWindow::Update(ViewModel *view_model, ChangeType change_type) {
    companyStructureTree.auto_draw(false);
    if (auto *cs = dynamic_cast<CompanyStructureVM *>(view_model)) {
        recreateTreeStructure();
    } else if (auto *dep_vm = dynamic_cast<DepartmentVM *>(view_model)) {
        if (change_type == ChangeType::DEP_CHANED) {
            auto selected = companyStructureTree.selected();
            selected.key(dep_vm->GetName()).text(dep_vm->GetName());
        } else {
            recreateTreeStructure();
        }
    } else if (auto *emp_vm = dynamic_cast<EmployeeVM *>(view_model)) {
        if (change_type == ChangeType::EMP_CHANGED) {
            auto selected = companyStructureTree.selected();
            selected.key(emp_vm->GetFullName()).text(emp_vm->GetFullName());
        }
    }
    companyStructureTree.auto_draw(true);
    topMenubar.at(1).enabled(0, companyStructureVM.HasUndoActions());
    topMenubar.at(1).enabled(1, companyStructureVM.HasRedoActions());
}

void MainWindow::initMenus() {
    companyStructureMenu.append("Add department", [&](menu::item_proxy &ip) {
        companyStructureVM.CreateDepartment();
    });

    departmentMenu.append("Add employee", [&](menu::item_proxy &ip) {
        departmentMenu.DepVM->AddEmployee();
    });
    departmentMenu.append("Remove department", [&](menu::item_proxy &ip) {
        companyStructureVM.RemoveDepartment(departmentMenu.DepVM);
    });

    employeeMenu.append("Remove employee", [&](menu::item_proxy &ip) {
        employeeMenu.DepVM->RemoveEmployee(employeeMenu.EmpVM);
    });
}

void MainWindow::recreateTreeStructure() {
    companyStructureTree.erase("Company structure");
    auto root = companyStructureTree.insert("Company structure", "Company structure");
    root.expand(companyStructureVM.IsExpanded());

    bool dep_edit_vm_exists = false, emp_edit_vm_exists = false;
    for (auto &dep : companyStructureVM.GetDepartments()) {
        auto dep_node = companyStructureTree.insert(root, dep->GetName(), dep->GetName());
        dep_node.expand(dep->IsExpanded());
        dep_node.value(dep.get());
        if (dep->GetObservers().size() == 0) {
            dep->AddViewObserver(&departmentEdit);
            dep->AddViewObserver(this);
        }

        if (dep_edit_vm_exists || dep.get() == departmentEdit.GetDepartmentVM()) {
            dep_edit_vm_exists = true;
        }

        for (auto &emp : dep->GetEmployees()) {
            auto emp_node = companyStructureTree.insert(dep_node, emp->GetFullName(), emp->GetFullName());
            emp_node.expand(emp->IsExpanded());
            emp_node.value(emp.get());
            if (emp->GetObservers().size() == 0) {
                emp->AddViewObserver(&employeeEdit);
                emp->AddViewObserver(this);
            }

            if (emp_edit_vm_exists || emp.get() == employeeEdit.GetEmployeeVM()) {
                emp_edit_vm_exists = true;
            }
        }
    }
    if (!dep_edit_vm_exists) {
        layout.field_visible("department_edit", false);
        layout.field_display("info", true);
    }
    if (!emp_edit_vm_exists) {
        layout.field_display("employee_edit", false);
        layout.field_display("info", true);
    }
}
