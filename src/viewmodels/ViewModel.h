#ifndef COMPANY_STRUCTURE_TEST_VIEWMODEL_H
#define COMPANY_STRUCTURE_TEST_VIEWMODEL_H

#include <vector>
#include "../views/View.h"
#include "ChangeType.h"

namespace viewmodels {
    class ViewModel {
        std::vector<views::View *> views;
    public:
        virtual void AddViewObserver(views::View *view) {
            views.push_back(view);
        }

        virtual const std::vector<views::View *> GetObservers() const {
            return views;
        }

        virtual void NotifyViews(ChangeType change_type = ChangeType::DUMMY) {
            for (auto view: views) {
                view->Update(this, change_type);
            }
        }

        virtual ~ViewModel() {}
    };
}

#endif //COMPANY_STRUCTURE_TEST_VIEWMODEL_H
