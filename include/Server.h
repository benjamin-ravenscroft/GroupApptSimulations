#ifndef SERVER_H
#define SERVER_H

#include <deque>
#include "Patient.h"
#include "Waitlist.h"
#include "DischargeList.h"

class Server{
    public:
        Server(Waitlist &wl, DischargeList &dl);
        Server(int max_caseload, Waitlist &wl, DischargeList &dl);

        void add_patient(Patient &patient);
        void add_from_waitlist(int epoch);
        void process_extension(Patient patient, int epoch);
        void process_epoch(int epoch);

        // setters
        void set_max_caseload(int max_caseload);

        void print_patients();

    private:
        std::deque<Patient> caseload = std::deque<Patient>();
        int n_patients = 0;
        Waitlist& waitlist;
        DischargeList& discharge_list;
        int max_caseload = 1; // max allowable caseload -> impacts freq (i.e., 1 = weekly, 2 = bi-weekly, 4 = monthly, etc.)
        bool logging = false; // variable to use to report if patients are on waitlist or not

};
#endif