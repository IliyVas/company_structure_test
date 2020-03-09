#ifndef COMPANY_STRUCTURE_TEST_COMPANYSTRUCTURESTORE_H
#define COMPANY_STRUCTURE_TEST_COMPANYSTRUCTURESTORE_H


#include <memory>
#include "tinyxml2.h"
#include "../models/CompanyStructure.h"
#include "../models/Department.h"
#include "../models/Employee.h"

namespace data_access {
    using namespace models;
    using namespace tinyxml2;

    class CompanyStructureStore {
        std::unique_ptr<CompanyStructure> companyStructure;

        std::unique_ptr<CompanyStructure> parseCompanyStructure(XMLElement *departments);

        std::shared_ptr<Department> parseDepartment(XMLElement *department);

        std::shared_ptr<Employee> parseEmployee(XMLElement *xml_employee);

        XMLElement *getElement(XMLElement *root, const char *elem_name);

    public:
        void LoadXML(std::string file_path);

        std::unique_ptr<CompanyStructure> &GetCompanyStructure();
    };
}

#endif //COMPANY_STRUCTURE_TEST_COMPANYSTRUCTURESTORE_H
