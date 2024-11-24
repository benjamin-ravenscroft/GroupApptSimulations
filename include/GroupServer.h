#ifndef GROUPSERVER_H
#define GROUPSERVER_H

#include "Server.h"
#include "Waitlist.h"
#include "DischargeList.h"

class GroupServer : public Server {
    public:
        // GroupServer(Waitlist &wl, DischargeList &dl);
        // GroupServer(int max_caseload, Waitlist &wl, DischargeList &dl);
        GroupServer(int path, int path_len, int max_caseload,
            float group_size_effect, 
            Waitlist &wl, DischargeList &dl);

        ~GroupServer(){};

        virtual void process_epoch(int epoch);

    private:
        int path; // indexes the pathway the server serves
        int path_len; // holds the number of appointments the groups need
        int n_appts; // tracks appointments delivered to current group

        void set_path(int path);
        void set_path_len(int path_len);
        void set_n_appts(int n_appts);
        void reset_n_appts();   // resets n_appts to path_len

        void decrement_n_appts(); // decrements n_appts by 1

        void discharge_patients(int epoch); // discharges all current patients
};
#endif