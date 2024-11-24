#include "GroupServer.h"
#include "Server.h"

// constructors
// GroupServer::GroupServer(Waitlist &wl, DischargeList &dl) : Server::Server(wl, dl) {};
// GroupServer::GroupServer(int max_caseload, Waitlist &wl, DischargeList &dl) : Server::Server(max_caseload,
//                                                                                             wl,
//                                                                                             dl) {};
GroupServer::GroupServer(int path, int path_len, int max_caseload,
        float group_size_effect,
        Waitlist &wl, DischargeList &dl) : Server::Server(max_caseload, wl, dl) {

    GroupServer::set_path(path);
    GroupServer::set_path_len(rint(path_len * (1 + group_size_effect)));
    GroupServer::set_n_appts(path_len);
};

// setter methods
void GroupServer::set_path(int p){path = p;}
void GroupServer::set_path_len(int pl){path_len = pl;}
void GroupServer::set_n_appts(int n){n_appts = n;}
void GroupServer::reset_n_appts(){n_appts = path_len;}

// incrementer/decrementer methods
void GroupServer::decrement_n_appts(){n_appts -= 1;}

void GroupServer::discharge_patients(int epoch){
    while (caseload.size() > 0) {
            Patient p = caseload.front();
            caseload.pop_front();
            p.set_discharge_time(epoch);
            discharge_list.add_patient(p);
            n_patients -= 1;
    }
}

// redefine process epoch
void GroupServer::process_epoch(int epoch) {
    // add new batch of patients
    if (n_patients == 0){
        while (caseload.size() < max_caseload & waitlist.check_class_availability(path, epoch)) {
            Server::add_from_waitlist(epoch);
        }
        GroupServer::reset_n_appts();
    }
    int capacity = n_patients;
    while (capacity > 0) {
        Patient p = caseload.front();
        caseload.pop_front();
        std::array<int, 2> results = p.process_patient(epoch);
        capacity -= 1;  // capacity used even if patient advance canceled
        caseload.push_back(p);
    }
    GroupServer::decrement_n_appts(); // decrement remaining appts by 1
    if (n_appts == 0) { // if group finished -> discharge all
        GroupServer::discharge_patients(epoch);
    }
}
