
#ifndef IMP_TIMER_H_
#define IMP_TIMER_H_

#include"CommonFunc.h"

class ImpTimer
{
    public:
        ImpTimer();
        ~ImpTimer();
        void start();
        void stop();
        void paused();
        void unpaused();

        int get_ticks();

        bool is_paused();
        bool is_started();


    private:
        int start_tick_;
        int paused_tick_;

        bool is_paused_;
        bool is_started_;

};


#endif