#ifndef GROUPSERVER_H
#define GROUPSERVER_H

#include "Server.h"
#include "Waitlist.h"
#include "DischargeList.h"

class GroupServer : public Server {
    public:
        // GroupServer(Waitlist &wl, DischargeList &dl);
        // GroupServer(int max_caseload, Waitlist &wl, DischargeList &dl);
        GroupServer(int path, int path_len, int max_caseload, Waitlist &wl, DischargeList &dl);

        ~GroupServer(){};

        virtual void process_epoch(int epoch);

    private:
        int path;
        int path_len;
        int n_appts; // tracks appointments delivered to current group

        void set_path(int path);
        void set_path_len(int path_len);
        void set_n_appts(int n_appts);
        void reset_n_appts();

        void decrement_n_appts();

        void discharge_patients(int epoch);
};
#endif