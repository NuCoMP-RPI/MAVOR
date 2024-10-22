#ifndef MAVOR_LEAPR_FILE_H
#define MAVOR_LEAPR_FILE_H

#include <iostream>
#include <vector>
#include <fstream>

class LeaprFile{
    public:
        int nout;
        std::string title;
        int ntemp;
        int iprint;
        int nphon;
        int material_number;
        int za;
        int isabt;
        int ilog;
        double smin;
        double awr;
        double spr;
        int npr;
        int iel;
        int ncold;
        int nsk;
        int nss;
        int b7;
        double aws;
        double sps;
        int mss;
        int nalpha;
        int nbeta;
        int lat;
        std::vector<double> alphas;
        std::vector<double> betas;

        std::vector<bool> pos_temp_ps;
        bool unique_temperatures_ps;
        std::vector<double> temps_ps;
        std::vector<double> deltas_ps;
        std::vector<int> nis_ps;
        std::vector<std::vector<double>> rhos_ps;
        std::vector<double> twts_ps;
        std::vector<double> cs_ps;
        std::vector<double> tbetas_ps;
        std::vector<int> nds_ps;
        std::vector<std::vector<double>> osc_eners_ps;
        std::vector<std::vector<double>> osc_weights_ps;
        std::vector<int> nkas_ps;
        std::vector<double> dkas_ps;
        std::vector<std::vector<double>> skappas_ps;
        std::vector<double> cfracs_ps;

        std::vector<bool> pos_temp_ss;
        bool unique_temperatures_ss;
        std::vector<double> temps_ss;
        std::vector<double> deltas_ss;
        std::vector<int> nis_ss;
        std::vector<std::vector<double>> rhos_ss;
        std::vector<double> twts_ss;
        std::vector<double> cs_ss;
        std::vector<double> tbetas_ss;
        std::vector<int> nds_ss;
        std::vector<std::vector<double>> osc_eners_ss;
        std::vector<std::vector<double>> osc_weights_ss;
        std::vector<int> nkas_ss;
        std::vector<double> dkas_ss;
        std::vector<std::vector<double>> skappas_ss;
        std::vector<double> cfracs_ss;

        // Constructor 
        LeaprFile(const std::string & file_path);

        void write_leapr_file(const double temperature, const int file_number = 0);
        void write_leapr_files();

    private:
        std::ifstream file;
        std::string line;
        std::vector<double> endf_numbers;

        bool get_line_single_item__();
        std::vector<std::string> expand_leapr_numbers__(std::vector<std::string> items);
        bool get_line_all_numbers__();
        std::vector<double> get_leapr_array__(int num_items);
        void find_file_start__();
        void get_card_1__();
        void get_card_2__();
        void get_card_3__();
        void get_card_4__();
        void get_card_5__();
        void get_card_6__();
        void get_card_7__();
        void get_card_8__();
        void get_card_9__();
        void get_all_cards_10_19_ps__();
        void get_card_10_ps__();
        void get_card_11_ps__();
        void get_card_12_ps__();
        void get_card_13_ps__();
        void get_card_14_ps__();
        void get_card_15_ps__();
        void get_card_16_ps__();
        void get_card_17_ps__();
        void get_card_18_ps__();
        void get_card_19_ps__();

        void get_all_cards_10_19_ss__();
        void get_card_10_ss__();
        void get_card_11_ss__();
        void get_card_12_ss__();
        void get_card_13_ss__();
        void get_card_14_ss__();
        void get_card_15_ss__();
        void get_card_16_ss__();
        void get_card_17_ss__();
        void get_card_18_ss__();
        void get_card_19_ss__();
        
        void write_formatted_vector__(std::ofstream &file, const std::vector<double> &vec, const int width = 4, const int precision = 6);
        void set_leapr_file_write_temps__();
};

#endif