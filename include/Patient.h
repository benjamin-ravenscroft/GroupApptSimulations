#ifndef PATIENT_H
#define PATIENT_H

#include <vector>
#include <array>
#include <random>

class Patient{
    public:
        std::mt19937 rng;
        std::uniform_real_distribution<double> dis;

        Patient(int arrival_time, double arrival_age, int pathway, int base_duration,
                double wait_ext_beta, double modality_ext_beta, double modality_policy,
                const std::array<std::array<double, 4>, 2> &att_probs,
                std::mt19937 &gen);

        void add_appt(int epoch);
        void add_wait(int add_t);
        std::array<int, 2> process_patient(int epoch);

        // setters
        void set_arrival_time(int t);
        void set_arrival_age(double a);
        void set_pathway(int p);
        void set_base_duration(int d);
        void set_service_duration(int d);
        void set_base_ext_p(double p);
        void set_wait_ext_beta(double b);
        void set_discharge_time(int epoch);
        void set_extended(int c);
        void set_discharge_duration(int d);
        void set_modality_effect(double m);
        void set_age_out(int a);
        void set_modality_policy(double p);
        void set_modality_dstb(std::uniform_real_distribution<> dstb);

        // getter methods
        int get_pathway();
        int get_base_duration();
        int get_arrival_t();
        float get_age(int epoch);
        float get_arrival_age();
        int get_first_appt();
        int get_n_appts();
        int get_n_ext();
        int get_discharge_time();
        int get_sojourn_time();
        int get_total_wait_time();
        int get_discharge_duration();
        int get_age_out();
        float get_pct_face();
        int get_modality_sum();

    private:
        int arrival_time;
        double arrival_age;
        int pathway;
        int base_duration;
        int service_duration;
        double serv_red_beta;
        int serv_red_cap;
        std::vector<int> appt_epochs;
        int modality_sum = 0;
        int extended = 0;
        double ext_prob_cap;
        double base_ext_p;
        double wait_ext_beta;
        double queue_ext_beta;
        int discharge_time = 0;
        int total_wait_time = 0;
        int ext_cap = 1;
        int discharge_duration = 0;
        double modality_effect = 0.5;
        double modality_policy = 1.0;
        int age_out = 0;
        std::uniform_real_distribution<> modality_dstb;
        const std::array<std::array<double, 4>, 2> att_probs;

        float calculate_wait_effect();
        void add_wait_effect();
        float calculate_modality_effect();
        void add_modality_effect();
        int check_complete(int epoch);
        int check_attendance(int modality);

        // Incrementer methods
        void increment_modality_sum(int m);

        // Setter methods
        
};
#endif