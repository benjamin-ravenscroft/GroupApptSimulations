#ifndef WAITLIST_H
#define WAITLIST_H

#include <iostream>
#include <vector>
#include <deque>
#include "Patient.h"
#include "DischargeList.h"

class Waitlist{
    public:
        std::vector<int> classes;
        std::vector<std::deque<std::pair<Patient, int>>> waitlist;
        std::deque<Patient> reassignment_list;
        std::mt19937 rng;

        Waitlist();
        Waitlist(int n_classes, double max_ax_age,
                std::mt19937 &gen, DischargeList &dl);
        Waitlist(int n_classes, double max_ax_age,
                bool priority_wlist, std::vector<int> (&p_order),
                std::mt19937 &gen, DischargeList &dl);

        int len_waitlist();
        void add_patient(Patient &patient, int epoch);
        int len_reassignments();
        void add_reassignment(Patient patient);
        std::pair<Patient, int> get_patient(int epoch);
        bool check_availability(int epoch);
        bool check_class_availability(int c, int epoch);
    
    private:
        DischargeList& discharge_list;
        double max_ax_age;
        bool priority_wlist = false;    // flag to determine if priority waitlist is used
        std::vector<int> priority_order; // order of priority for waitlist

        // setter methods
        void set_max_ax_age(double max_ax_age);
        void set_priority_wlist(bool priority_wlist);

};
#endif