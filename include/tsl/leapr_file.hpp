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
        std::vector<bool> pos_temp;
        bool unique_temperatures;
        std::vector<double> temps;
        std::vector<double> deltas;
        std::vector<int> nis;
        std::vector<std::vector<double>> rhos;
        std::vector<double> twts;
        std::vector<double> cs;
        std::vector<double> tbetas;
        std::vector<int> nds;
        std::vector<std::vector<double>> osc_eners;
        std::vector<std::vector<double>> osc_weights;
        std::vector<int> nkas;
        std::vector<double> dkas;
        std::vector<std::vector<double>> skappas;
        std::vector<double> cfracs;

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
        void get_all_cards_10_19__();
        void get_card_10__();
        void get_card_11__();
        void get_card_12__();
        void get_card_13__();
        void get_card_14__();
        void get_card_15__();
        void get_card_16__();
        void get_card_17__();
        void get_card_18__();
        void get_card_19__();
        
        void write_formatted_vector__(std::ofstream &file, const std::vector<double> &vec, const int width);
        void set_leapr_file_write_temps__();
};

#endif