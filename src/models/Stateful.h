#ifndef COMPANY_STRUCTURE_TEST_STATEFUL_H
#define COMPANY_STRUCTURE_TEST_STATEFUL_H

namespace models {
    class Stateful {
    protected:
        static unsigned maxStateNum;

    public:
        virtual ~Stateful() {}

        virtual bool PreviousState() = 0;

        virtual bool NextState() = 0;

        virtual bool IsFirstState() = 0;

        virtual bool IsLastState() = 0;

        unsigned GetMaxStateNum() {
            return maxStateNum;
        }

        void SetMaxStateNum(unsigned state_num) {
            maxStateNum = state_num;
        }
    };
}


#endif //COMPANY_STRUCTURE_TEST_STATEFUL_H
