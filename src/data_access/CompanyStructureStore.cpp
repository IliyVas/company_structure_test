#include "CompanyStructureStore.h"
#include "../models/CompanyStructure.h"

#include <sstream>

using namespace tinyxml2;

void data_access::CompanyStructureStore::LoadXML(std::string file_path) {
    XMLDocument doc;
    doc.LoadFile(file_path.c_str());
    auto xml_departments = doc.RootElement(); // check
    companyStructure = parseCompanyStructure(xml_departments);
}

XMLElement *data_access::CompanyStructureStore::getElement(XMLElement *root, const char *elem_name) {
    auto elem = root->FirstChildElement(elem_name);
    if (elem == nullptr) {
        std::stringstream ss;
        ss << "Invalid XML. Expected \"" << elem_name << "\" child in \"" << root->Name() << "\" xml element";
        throw std::runtime_error(ss.str());
    }
    return elem;
}

std::shared_ptr<Employee> data_access::CompanyStructureStore::parseEmployee(XMLElement *xml_employee) {
    auto xml_name = getElement(xml_employee, "name");
    auto xml_surname = getElement(xml_employee, "surname");
    auto xml_middle_name = getElement(xml_employee, "middleName");
    auto xml_function = getElement(xml_employee, "function");
    auto xml_salary = getElement(xml_employee, "salary");

    std::string first_name = xml_name->GetText();
    std::string surname = xml_surname->GetText();
    std::string middle_name = xml_middle_name->GetText();
    std::string function = xml_function->GetText();
    uint64_t salary;
    XMLError error = xml_salary->QueryUnsigned64Text(&salary);
    // if (error)

    return std::make_shared<Employee>(first_name, surname, middle_name, function, salary);
}

std::unique_ptr<CompanyStructure> data_access::CompanyStructureStore::parseCompanyStructure(XMLElement *departments) {
    auto res = std::make_unique<CompanyStructure>();
    auto xml_department = getElement(departments, "department");
    while (xml_department) {
        auto department = parseDepartment(xml_department);
        res->AddDepartment(department, false);
        xml_department = xml_department->NextSiblingElement("department");
    }
    return res;
}

std::shared_ptr<Department> data_access::CompanyStructureStore::parseDepartment(XMLElement *department) {
    std::string name = department->Attribute("name");
    auto res = std::make_shared<Department>(name);
    auto xml_employments = getElement(department, "employments");
    auto xml_employment = getElement(xml_employments, "employment");
    std::vector<std::shared_ptr<Employee>> employees;
    while (xml_employment) {
        auto employee = parseEmployee(xml_employment);
        res->AddEmployee(employee, false);
        xml_employment = xml_employment->NextSiblingElement("employment");
    }
    return res;
}

std::unique_ptr<CompanyStructure> &data_access::CompanyStructureStore::GetCompanyStructure() {
    return companyStructure;
}
