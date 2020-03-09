#ifndef COMPANY_STRUCTURE_TEST_VIEW_H
#define COMPANY_STRUCTURE_TEST_VIEW_H

#include "../viewmodels/ChangeType.h"

namespace viewmodels {
    class ViewModel;
}

namespace views {
    using namespace viewmodels;

    class View {
    public:
        virtual ~View() {}

        virtual void Update(ViewModel *view_model, ChangeType change_type) = 0;
    };
}

#endif //COMPANY_STRUCTURE_TEST_VIEW_H
