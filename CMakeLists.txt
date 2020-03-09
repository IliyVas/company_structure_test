cmake_minimum_required(VERSION 3.15)
project(company_structure_test)

set(CMAKE_CXX_STANDARD 17)

include_directories(lib/tinyxml2)
include_directories(lib/nana/include)
link_directories("lib/nana/mingw_x64")

add_executable(company_structure_test
        src/main.cpp
        src/models/CompanyStructure.cpp
        src/models/Department.cpp
        src/models/Employee.cpp
        src/data_access/CompanyStructureStore.cpp
        lib/tinyxml2/tinyxml2.cpp
        src/models/Stateful.cpp
        src/views/MainWindow.cpp
        src/views/DepartmentEdit.cpp
#        src/viewmodels/ViewModel.h
        src/viewmodels/CompanyStructureVM.cpp
        src/viewmodels/DepartmentVM.cpp
        src/viewmodels/EmployeeVM.cpp
        src/views/EmployeeEdit.cpp)
target_compile_definitions(company_structure_test PUBLIC NANA_FILESYSTEM_FORCE)
target_link_libraries(company_structure_test nana)