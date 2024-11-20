#include "Waitlist.h"

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include "Patient.h"
#include "DischargeList.h"

// Waitlist::Waitlist(){};

Waitlist::Waitlist(int n_classes, double max_ax_age, 
                std::mt19937 &gen, DischargeList& dl) : discharge_list(dl) {
    rng = gen;
    set_max_ax_age(max_ax_age);
    for (int i = 0; i < n_classes; i++){
        classes.push_back(i);
        waitlist.push_back(std::deque<std::pair<Patient, int>>());
    }
}

Waitlist::Waitlist(int n_classes, double max_ax_age, 
                bool priority_wlist, std::vector<int> (&p_order),
                std::mt19937 &gen, DischargeList& dl) : priority_order(p_order), discharge_list(dl) {
    rng = gen;
    set_max_ax_age(max_ax_age);
    set_priority_wlist(priority_wlist);
    for (int i = 0; i < n_classes; i++){
        if (priority_wlist) {
            classes.push_back(p_order[i]);
        } else {
            classes.push_back(i);
        }
        waitlist.push_back(std::deque<std::pair<Patient, int>>());
    }
}

// setter methods
void Waitlist::set_max_ax_age(double m){max_ax_age = m;}
void Waitlist::set_priority_wlist(bool p){priority_wlist = p;}

int Waitlist::len_waitlist(){
    int len = 0;
    for (int i = 0; i < waitlist.size(); i++){
        len += waitlist[i].size();
    }
    return len;
}

void Waitlist::add_patient(Patient &patient, int epoch){
    waitlist[patient.get_pathway()].push_back((std::pair<Patient, int>) {patient, epoch});
}

int Waitlist::len_reassignments(){
    return reassignment_list.size();
}

void Waitlist::add_reassignment(Patient patient){
    reassignment_list.push_back(patient);
}

bool Waitlist::check_availability(int epoch){
    for (auto & i : classes){
        bool ret_val = check_class_availability(i, epoch);
        if (ret_val){return true;}
    }
    return false;
}

bool Waitlist::check_class_availability(int c, int epoch){
    while (waitlist[c].size() > 0) {
        if (waitlist[c].front().first.get_age(epoch) < max_ax_age) {
            return true;
        } else {
            std::pair<Patient, int> pair = waitlist[c].front();
            pair.first.set_discharge_time(epoch);
            pair.first.set_age_out(1);
            // std::cout << "Getting discharge list size: " << discharge_list.get_n_patients() << std::endl;
            // std::cout << "Discharging patient from waitlist..." << std::endl;
            discharge_list.add_patient(pair.first);
            // std::cout << "Successfully discharged patient from waitlist." << std::endl;
            waitlist[c].pop_front();
        }
    }
    return false;
}

std::pair<Patient, int> Waitlist::get_patient(int epoch){
    if (!priority_wlist) {
        std::shuffle(classes.begin(), classes.end(), rng);
    }
    for (auto & i : classes){
        if (waitlist[i].size() > 0){
            std::pair<Patient, int> pair = waitlist[i].front();
            waitlist[i].pop_front();
            if (pair.first.get_age(epoch) > max_ax_age){
                pair.first.set_discharge_time(epoch);
                pair.first.set_age_out(1);
                discharge_list.add_patient(pair.first);
            } else {
                return pair;
            }
        }
    }
}