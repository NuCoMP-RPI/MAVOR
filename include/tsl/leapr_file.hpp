#ifndef MAVOR_LEAPR_FILE_H
#define MAVOR_LEAPR_FILE_H

#include <iostream>
#include <vector>
#include <fstream>

/// @brief Class that reads in Leapr input files from NJOY and stores the results.  
/// Has methods to write Leapr input files at desired temperatures.
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

        /// Constructor 
        /// @brief Constructor to initialize and read in a Leapr file
        /// @param file_path Path to the Leapr file to be read
        LeaprFile(const std::string & file_path);

        /// @brief Writes a Leapr file at the desired tempearture and append the file_number to the MAT number as the name.
        /// @param temperature Temperature to generate the file
        /// @param file_number File number to append to MAT number
        void write_leapr_file(const double temperature, const int file_number = 0);

        /// @brief Writes Leapr files for a series of temperatures controlled by the command line arguments.
        /// Uses the private method "set_leapr_file_write_temps__""
        void write_leapr_files();

    private:
        std::ifstream file;
        std::string line;
        std::vector<double> endf_numbers;

        /// @brief Reads a line of the Leapr file into the "line" private variable trimming comments and whitespace
        /// @return True if the line reading was successful
        bool get_line_single_item__();

        /// @brief Expands ENDF repeat notation for numbers.  Ex. "1 2 3*4 5" -> "1 2 4 4 4 5"
        /// @param items Vector of strings to expand if the "*" character is found, does nothing if no "*"
        /// @return Vector of strings where ENDF repeat notation is expanded
        std::vector<std::string> expand_leapr_numbers__(std::vector<std::string> items);

        /// @brief Reads a line of the Leapr file into the "endf_numbers" private variable delineated by whitespace
        /// @return True if the line reading was successful
        bool get_line_all_numbers__();

        /// @brief Reads an array from the Leapr file
        /// @param num_items Number of items to read from the file
        /// @return Array elements
        std::vector<double> get_leapr_array__(int num_items);

        /// @brief Find the start of the Leapr file
        void find_file_start__();

        /// @brief Read card 1 of the Leapr file
        void get_card_1__();

        /// @brief Read card 2 of the Leapr file
        void get_card_2__();

        /// @brief Read card 3 of the Leapr file
        void get_card_3__();

        /// @brief Read card 4 of the Leapr file
        void get_card_4__();

        /// @brief Read card 5 of the Leapr file
        void get_card_5__();

        /// @brief Read card 6 of the Leapr file
        void get_card_6__();

        /// @brief Read card 7 of the Leapr file
        void get_card_7__();

        /// @brief Read card 8 of the Leapr file
        void get_card_8__();

        /// @brief Read card 9 of the Leapr file
        void get_card_9__();

        /// @brief Read cards 10 to 19 for the primary scatterer of the Leapr file
        void get_all_cards_10_19_ps__();

        /// @brief Read card 10 for the primary scatterer of the Leapr file
        void get_card_10_ps__();

        /// @brief Read card 11 for the primary scatterer of the Leapr file
        void get_card_11_ps__();

        /// @brief Read card 12 for the primary scatterer of the Leapr file
        void get_card_12_ps__();

        /// @brief Read card 13 for the primary scatterer of the Leapr file
        void get_card_13_ps__();

        /// @brief Read card 14 for the primary scatterer of the Leapr file
        void get_card_14_ps__();

        /// @brief Read card 15 for the primary scatterer of the Leapr file
        void get_card_15_ps__();

        /// @brief Read card 16 for the primary scatterer of the Leapr file
        void get_card_16_ps__();

        /// @brief Read card 17 for the primary scatterer of the Leapr file
        void get_card_17_ps__();

        /// @brief Read card 18 for the primary scatterer of the Leapr file
        void get_card_18_ps__();

        /// @brief Read card 19 for the primary scatterer of the Leapr file
        void get_card_19_ps__();


        /// @brief Read cards 10 to 19 for the secondary scatterer of the Leapr file
        void get_all_cards_10_19_ss__();

        /// @brief Read card 10 for the secondary scatterer of the Leapr file
        void get_card_10_ss__();

        /// @brief Read card 11 for the secondary scatterer of the Leapr file
        void get_card_11_ss__();

        /// @brief Read card 12 for the secondary scatterer of the Leapr file
        void get_card_12_ss__();

        /// @brief Read card 14 for the secondary scatterer of the Leapr file
        void get_card_13_ss__();

        /// @brief Read card 14 for the secondary scatterer of the Leapr file
        void get_card_14_ss__();

        /// @brief Read card 15 for the secondary scatterer of the Leapr file
        void get_card_15_ss__();

        /// @brief Read card 16 for the secondary scatterer of the Leapr file
        void get_card_16_ss__();

        /// @brief Read card 17 for the secondary scatterer of the Leapr file
        void get_card_17_ss__();

        /// @brief Read card 18 for the secondary scatterer of the Leapr file
        void get_card_18_ss__();

        /// @brief Read card 19 for the secondary scatterer of the Leapr file
        void get_card_19_ss__();
        
        /// @brief Writes a vector to a text file
        /// @param file Object to the write the data to
        /// @param vec Vector of data to write to file
        /// @param width Number of items per row
        /// @param precision Precision of the written data
        void write_formatted_vector__(std::ofstream &file, const std::vector<double> &vec, const int width = 4, const int precision = 6);

        /// @brief Sets the temperatures to generate Leapr files controlled by the command line arguments.
        /// Is used by the public method "write_leapr_files"
        void set_leapr_file_write_temps__();
};

#endif