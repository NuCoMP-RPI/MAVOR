#include <fstream>
#include <algorithm>
#include <numeric>
#include <filesystem>
#include <iomanip>

#include "file_reading.hpp"
#include "runtime_variables.hpp"
#include "interpolation.hpp"
#include "linspace.hpp"
#include "arange.hpp"

#include "leapr_file.hpp"

LeaprFile::LeaprFile(const std::string &file_path) :
    // Set Default values here
    ntemp(0), 
    iprint(1), 
    nphon(100), 
    isabt(0),
    ilog(0), 
    smin(1e-75), 
    iel(0), 
    ncold(0), 
    nsk(0),
    nss(0), 
    lat(0),
    file(file_path)
    {
        if (!file.is_open()) {throw std::runtime_error("Failed to open file: " + file_path);}
        find_file_start__();
        get_card_1__();
        get_card_2__();
        get_card_3__();
        get_card_4__();
        get_card_5__();
        get_card_6__();
        get_card_7__();
        get_card_8__();
        get_card_9__();
        get_all_cards_10_19_ps__();
        if (nss > 0 && b7 == 0){
            get_all_cards_10_19_ss__();
        }
        file.close();
        int unique_temps_ps = std::accumulate(pos_temp_ps.begin(), pos_temp_ps.end(), 0);
        unique_temperatures_ps = (unique_temps_ps > 1) ? true : false;
        int unique_temps_ss = std::accumulate(pos_temp_ss.begin(), pos_temp_ss.end(), 0);
        unique_temperatures_ss = (unique_temps_ss > 1) ? true : false;
        if (!silence) {std::cout << "Number of Unique Temperatures | " << unique_temps_ps << std::endl;}
        if (!silence && nss == 1) {std::cout << "Number of Unique Temperatures for Secondary Scatterers | " << unique_temps_ss << std::endl;}
}

bool LeaprFile::get_line_single_item__(){
    bool result = debug_getline(file, line);
    // bool result = static_cast<bool>(std::getline(file, line));
    line = split(line, '/').at(0);
    line.erase(0, line.find_first_not_of(" \t\n\r"));
    line.erase(line.find_last_not_of(" \t\n\r") + 1);
    return result;
}

std::vector<std::string> LeaprFile::expand_leapr_numbers__(std::vector<std::string> items){
    std::vector<std::string> new_items;
    for (const std::string item: items){
        if (item.find("*") != std::string::npos){
            std::vector<std::string> sub_items = split(item, '*');
            int count = static_cast<int>(std::stod(sub_items.at(0)));
            if (sub_items.size() > 2){throw std::runtime_error("More than one '*' found in string.");}
            for (int i = 0; i < count; ++i) {
                new_items.push_back(sub_items.at(1));
            }
        }
        else{
            new_items.push_back(item);
        }
    }
    return new_items;
}

bool LeaprFile::get_line_all_numbers__(){
    bool result = get_line_single_item__();
    auto items = split(line);
    // Erase all empty strings in items
    items.erase(std::remove_if(items.begin(), items.end(), [](const std::string& s) { return s.empty(); }), items.end());
    items = expand_leapr_numbers__(items);
    endf_numbers.clear();
    std::transform(items.begin(), items.end(), std::back_inserter(endf_numbers), ENDF_float);
    return result;
}

std::vector<double> LeaprFile::get_leapr_array__(int num_items) {
    std::vector<double> array;
    array.reserve(num_items);

    int count = 0;
    std::string line;
    while (count < num_items && get_line_all_numbers__()) {
        for (const auto &number : endf_numbers) {
            array.push_back(number);
            count++;
            if (count == num_items) break;
        }
    }
    std::cout << "Finished reading leapr array" << std::endl;
    return array;
}

void LeaprFile::find_file_start__(){
        while (get_line_single_item__()) {
            if (line.find("leapr") != std::string::npos) {
                break;
            }
        }
    }

void LeaprFile::get_card_1__(){
    std::cout << "Reading Card 1" << std::endl;
    get_line_single_item__();
    nout = std::stoi(line);
}

void LeaprFile::get_card_2__(){
    std::cout << "Reading Card 2" << std::endl;
    get_line_single_item__();
    title = line;
}

void LeaprFile::get_card_3__(){
    std::cout << "Reading Card 3" << std::endl;
    get_line_all_numbers__();
    if (endf_numbers.size() > 0) {ntemp = static_cast<int>(endf_numbers[0]);}
    if (endf_numbers.size() > 1) {iprint = static_cast<int>(endf_numbers[1]);}
    if (endf_numbers.size() > 2) {nphon = static_cast<int>(endf_numbers[2]);}
}

void LeaprFile::get_card_4__(){
    std::cout << "Reading Card 4" << std::endl;
    get_line_all_numbers__();
    material_number = static_cast<int>(endf_numbers[0]);
    za = static_cast<int>(endf_numbers[1]);
    if (endf_numbers.size() > 2){isabt = static_cast<int>(endf_numbers[2]);}
    if (endf_numbers.size() > 3){ilog = static_cast<int>(endf_numbers[3]);}
    if (endf_numbers.size() > 4){smin = endf_numbers[4];}
}

void LeaprFile::get_card_5__(){
    std::cout << "Reading Card 5" << std::endl;
    get_line_all_numbers__();
    awr = endf_numbers[0];
    spr = endf_numbers[1];
    npr = static_cast<int>(endf_numbers[2]);
    if (endf_numbers.size() > 3) {iel = static_cast<int>(endf_numbers[3]);}
    if (endf_numbers.size() > 4) {ncold = static_cast<int>(endf_numbers[4]);}
    if (endf_numbers.size() > 5) {nsk = static_cast<int>(endf_numbers[5]);}
}

void LeaprFile::get_card_6__(){
    std::cout << "Reading Card 6" << std::endl;
    get_line_all_numbers__();
    nss = static_cast<int>(endf_numbers[0]);
    if (nss == 1) {
        b7 = static_cast<int>(endf_numbers[1]);
        aws = endf_numbers[2];
        sps = endf_numbers[3];
        mss = static_cast<int>(endf_numbers[4]);
    }
}

void LeaprFile::get_card_7__(){
    std::cout << "Reading Card 7" << std::endl;
    get_line_all_numbers__();
    nalpha = static_cast<int>(endf_numbers[0]);
    nbeta = static_cast<int>(endf_numbers[1]);
    if (endf_numbers.size() > 2) {lat = static_cast<int>(endf_numbers[2]);}
}

void LeaprFile::get_card_8__(){
    std::cout << "Reading Card 8" << std::endl;
    alphas = get_leapr_array__(nalpha);
}

void LeaprFile::get_card_9__(){
    std::cout << "Reading Card 9" << std::endl;
    betas = get_leapr_array__(nbeta);
}

void LeaprFile::get_all_cards_10_19_ps__(){
    for (int i = 0; i < ntemp; ++i) {
        std::cout << "Primary Scatterer Temperature Number: "<< i << std::endl;
        get_card_10_ps__();
        get_card_11_ps__();
        get_card_12_ps__();
        get_card_13_ps__();
        get_card_14_ps__();
        get_card_15_ps__();
        get_card_16_ps__();
        get_card_17_ps__();
        get_card_18_ps__();
        get_card_19_ps__();
    }
}

void LeaprFile::get_card_10_ps__(){
    std::cout << "Primary Scatterer Reading Card 10" << std::endl;
    get_line_single_item__();
    double temp = ENDF_float(line);
    pos_temp_ps.push_back(temp > 0);
    temps_ps.push_back(std::abs(temp));
}

void LeaprFile::get_card_11_ps__(){
    std::cout << "Primary Scatterer Reading Card 11" << std::endl;
    if (pos_temp_ps.back()) {
        get_line_all_numbers__();
        deltas_ps.push_back(endf_numbers[0]);
        nis_ps.push_back(static_cast<int>(endf_numbers[1]));
    }
    else {
        deltas_ps.push_back(deltas_ps.back());
        nis_ps.push_back(nis_ps.back());
    }
}

void LeaprFile::get_card_12_ps__(){
    std::cout << "Primary Scatterer Reading Card 12" << std::endl;
    if (pos_temp_ps.back()) {
        rhos_ps.push_back(get_leapr_array__(nis_ps.back()));
    } 
    else {
        rhos_ps.push_back(rhos_ps.back());
    }
}

void LeaprFile::get_card_13_ps__(){
    std::cout << "Primary Scatterer Reading Card 13" << std::endl;
    if (pos_temp_ps.back()) {
        get_line_all_numbers__();
        twts_ps.push_back(endf_numbers[0]);
        cs_ps.push_back(endf_numbers[1]);
        tbetas_ps.push_back(endf_numbers[2]);
    }
    else {
        twts_ps.push_back(twts_ps.back());
        cs_ps.push_back(cs_ps.back());
        tbetas_ps.push_back(tbetas_ps.back());
    }
}

void LeaprFile::get_card_14_ps__(){
    std::cout << "Primary Scatterer Reading Card 14" << std::endl;
    if (pos_temp_ps.back()) {
        get_line_single_item__();
        nds_ps.push_back(static_cast<int>(ENDF_float(line)));
    } else {
        nds_ps.push_back(nds_ps.back());
    }
}

void LeaprFile::get_card_15_ps__(){
    std::cout << "Primary Scatterer Reading Card 15" << std::endl;
    if (pos_temp_ps.back()) {
        osc_eners_ps.push_back(get_leapr_array__(nds_ps.back()));
    } else {
        osc_eners_ps.push_back(osc_eners_ps.back());
    }
}

void LeaprFile::get_card_16_ps__(){
    std::cout << "Primary Scatterer Reading Card 16" << std::endl;
    if (pos_temp_ps.back()) {
        osc_weights_ps.push_back(get_leapr_array__(nds_ps.back()));
    } else {
        osc_weights_ps.push_back(osc_weights_ps.back());
    }
}

void LeaprFile::get_card_17_ps__(){
    std::cout << "Primary Scatterer Reading Card 17" << std::endl;
    if (nsk != 0){
        if (pos_temp_ps.back()) {
            get_line_all_numbers__();
            nkas_ps.push_back(endf_numbers[0]);
            dkas_ps.push_back(endf_numbers[1]);
        } else {
            nkas_ps.push_back(nkas_ps.back());
            dkas_ps.push_back(dkas_ps.back());
        }
    }
}

void LeaprFile::get_card_18_ps__(){
    std::cout << "Primary Scatterer Reading Card 18" << std::endl;
    if (nsk != 0){
        if (pos_temp_ps.back()) {
            skappas_ps.push_back(get_leapr_array__(nkas_ps.back()));
        } else {
            skappas_ps.push_back(skappas_ps.back());
        }
    }
}

void LeaprFile::get_card_19_ps__(){
    std::cout << "Primary Scatterer Reading Card 19" << std::endl;
    if (nsk == 2){
        if (pos_temp_ps.back()) {
            get_line_single_item__();
            cfracs_ps.push_back(ENDF_float(line));
        } else {
            cfracs_ps.push_back(0.0);
        }
    }
}

void LeaprFile::get_all_cards_10_19_ss__(){
    for (int i = 0; i < ntemp; ++i) {
        std::cout << "Secondary Scatterer Temperature Number: "<< i << std::endl;
        get_card_10_ss__();
        get_card_11_ss__();
        get_card_12_ss__();
        get_card_13_ss__();
        get_card_14_ss__();
        get_card_15_ss__();
        get_card_16_ss__();
        get_card_17_ss__();
        get_card_18_ss__();
        get_card_19_ss__();
    }
}

void LeaprFile::get_card_10_ss__(){
    std::cout << "Secondary Scatterer Reading Card 10" << std::endl;
    get_line_single_item__();
    double temp = ENDF_float(line);
    pos_temp_ss.push_back(temp > 0);
    temps_ss.push_back(std::abs(temp));
}

void LeaprFile::get_card_11_ss__(){
    std::cout << "Secondary Scatterer Reading Card 11" << std::endl;
    if (pos_temp_ss.back()) {
        get_line_all_numbers__();
        deltas_ss.push_back(endf_numbers[0]);
        nis_ss.push_back(static_cast<int>(endf_numbers[1]));
    }
    else {
        deltas_ss.push_back(deltas_ss.back());
        nis_ss.push_back(nis_ss.back());
    }
}

void LeaprFile::get_card_12_ss__(){
    std::cout << "Secondary Scatterer Reading Card 12" << std::endl;
    if (pos_temp_ss.back()) {
        rhos_ss.push_back(get_leapr_array__(nis_ss.back()));
    } 
    else {
        rhos_ss.push_back(rhos_ss.back());
    }
}

void LeaprFile::get_card_13_ss__(){
    std::cout << "RSecondary Scatterer eading Card 13" << std::endl;
    if (pos_temp_ss.back()) {
        get_line_all_numbers__();
        twts_ss.push_back(endf_numbers[0]);
        cs_ss.push_back(endf_numbers[1]);
        tbetas_ss.push_back(endf_numbers[2]);
    }
    else {
        twts_ss.push_back(twts_ss.back());
        cs_ss.push_back(cs_ss.back());
        tbetas_ss.push_back(tbetas_ss.back());
    }
}

void LeaprFile::get_card_14_ss__(){
    std::cout << "Secondary Scatterer Reading Card 14" << std::endl;
    if (pos_temp_ss.back()) {
        get_line_single_item__();
        nds_ss.push_back(static_cast<int>(ENDF_float(line)));
    } else {
        nds_ss.push_back(nds_ps.back());
    }
}

void LeaprFile::get_card_15_ss__(){
    std::cout << "Secondary Scatterer Reading Card 15" << std::endl;
    if (pos_temp_ss.back()) {
        osc_eners_ss.push_back(get_leapr_array__(nds_ss.back()));
    } else {
        osc_eners_ss.push_back(osc_eners_ss.back());
    }
}

void LeaprFile::get_card_16_ss__(){
    std::cout << "Secondary Scatterer Reading Card 16" << std::endl;
    if (pos_temp_ss.back()) {
        osc_weights_ss.push_back(get_leapr_array__(nds_ss.back()));
    } else {
        osc_weights_ss.push_back(osc_weights_ss.back());
    }
}

void LeaprFile::get_card_17_ss__(){
    std::cout << "Secondary Scatterer Reading Card 17" << std::endl;
    if (nsk != 0){
        if (pos_temp_ss.back()) {
            get_line_all_numbers__();
            nkas_ss.push_back(endf_numbers[0]);
            dkas_ss.push_back(endf_numbers[1]);
        } else {
            nkas_ss.push_back(nkas_ss.back());
            dkas_ss.push_back(dkas_ss.back());
        }
    }
}

void LeaprFile::get_card_18_ss__(){
    std::cout << "Secondary Scatterer Reading Card 18" << std::endl;
    if (nsk != 0){
        if (pos_temp_ss.back()) {
            skappas_ss.push_back(get_leapr_array__(nkas_ss.back()));
        } else {
            skappas_ss.push_back(skappas_ss.back());
        }
    }
}

void LeaprFile::get_card_19_ss__(){
    std::cout << "Secondary Scatterer Reading Card 19" << std::endl;
    if (nsk == 2){
        if (pos_temp_ss.back()) {
            get_line_single_item__();
            cfracs_ss.push_back(ENDF_float(line));
        } else {
            cfracs_ss.push_back(0.0);
        }
    }
}

void LeaprFile::write_leapr_file(const double temperature, const int file_number){
    std::cout << "Writing input for MAT number " << material_number << " at " << temperature << "K\n";
    std::filesystem::create_directory(tsl_leapr_write_dir);
    std::filesystem::path location_path(tsl_leapr_write_dir);
    std::filesystem::path file_path = location_path / (std::to_string(material_number) + "_" + std::to_string(file_number) + ".leapr");
    std::ofstream file(file_path);
    if (!file.is_open()) {throw std::runtime_error("Error opening file for writing");}

    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    file << "leapr / \n";
    file << "20 / \n";
    file << "MAT Number " << material_number << " at " << temperature << "K - Created " << std::put_time(&tm, "%d-%m-%Y") << " by MAVOR / \n";
    file << "1 1 " << nphon << " / \n";
    file << material_number << " " << za << " " << isabt << " " << ilog << " " << smin << " / \n";
    file << awr << " " << spr << " " << npr << " " << iel << " " << ncold << " " << nsk << " / \n";

    if (nss == 0){
        file << nss << " / \n";
    }
    else {
        file << nss << " " << b7 << " " << aws << " " << sps << " " << mss << " / \n";
    }

    file << nalpha << " " << nbeta << " " << lat << " / \n";
    write_formatted_vector__(file, alphas, 4);
    write_formatted_vector__(file, betas, 4);

    // Handle primary scatterer
    file << temperature << " / \n";

    double temp_delta_ps = deltas_ps[0]; 
    int temp_ni_ps = nis_ps[0]; 
    std::vector<double> temp_rhos_ps = rhos_ps[0]; 
    double temp_twt_ps = twts_ps[0]; 
    double temp_c_ps = cs_ps[0]; 
    double temp_tbeta_ps = tbetas_ps[0]; 
    int temp_nd_ps = nds_ps[0]; 
    std::vector<double> temp_osc_eners_ps;
    std::vector<double> temp_osc_weights_ps;
    if (temp_nd_ps != 0){
        temp_osc_eners_ps = osc_eners_ps[0]; 
        temp_osc_weights_ps = osc_weights_ps[0]; 
    }
    int temp_nka_ps;
    double temp_dka_ps;
    std::vector<double> temp_skappas_ps;
    if (nsk != 0){
        temp_nka_ps = nkas_ps[0]; 
        temp_dka_ps = dkas_ps[0]; 
        temp_skappas_ps = skappas_ps[0]; 
    }
    double temp_cfrac_ps;
    if (nsk == 2){
        temp_cfrac_ps = cfracs_ps[0]; 
    }

    if (unique_temperatures_ps){
        auto tb_ps = findInterpolationIndexes(temps_ps.begin(), temps_ps.end(), temperature);
        double t_low_ps = temps_ps[tb_ps.first];
        double t_high_ps = temps_ps[tb_ps.second];
        temp_ni_ps = ENDF_interp(t_low_ps, t_high_ps, nis_ps[tb_ps.first], nis_ps[tb_ps.second], temperature);
        temp_rhos_ps = ENDF_interp_vector(t_low_ps, t_high_ps, rhos_ps[tb_ps.first], rhos_ps[tb_ps.second], temperature);
        temp_twt_ps = ENDF_interp(t_low_ps, t_high_ps, twts_ps[tb_ps.first], twts_ps[tb_ps.second], temperature);
        temp_c_ps = ENDF_interp(t_low_ps, t_high_ps, cs_ps[tb_ps.first], cs_ps[tb_ps.second], temperature);
        temp_tbeta_ps = ENDF_interp(t_low_ps, t_high_ps, tbetas_ps[tb_ps.first], tbetas_ps[tb_ps.second], temperature);
        temp_nd_ps = ENDF_interp(t_low_ps, t_high_ps, nds_ps[tb_ps.first], nds_ps[tb_ps.second], temperature);
        if (temp_nd_ps != 0){
            temp_osc_eners_ps = ENDF_interp_vector(t_low_ps, t_high_ps, osc_eners_ps[tb_ps.first], osc_eners_ps[tb_ps.second], temperature);
            temp_osc_weights_ps = ENDF_interp_vector(t_low_ps, t_high_ps, osc_weights_ps[tb_ps.first], osc_weights_ps[tb_ps.second], temperature);
        }
        if (nsk != 0){
            temp_nka_ps = ENDF_interp(t_low_ps, t_high_ps, nkas_ps[tb_ps.first], nkas_ps[tb_ps.second], temperature);
            temp_dka_ps = ENDF_interp(t_low_ps, t_high_ps, dkas_ps[tb_ps.first], dkas_ps[tb_ps.second], temperature);
            temp_skappas_ps = ENDF_interp_vector(t_low_ps, t_high_ps, skappas_ps[tb_ps.first], skappas_ps[tb_ps.second], temperature);
        }
        if (nsk == 2){
            temp_cfrac_ps = ENDF_interp(t_low_ps, t_high_ps, cfracs_ps[tb_ps.first], cfracs_ps[tb_ps.second], temperature);
        }
    }

    file << temp_delta_ps << " " << temp_ni_ps << " / \n";
    write_formatted_vector__(file, temp_rhos_ps, 4);
    file << temp_twt_ps << " " << temp_c_ps << " " << temp_tbeta_ps << " / \n";
    file << temp_nd_ps << " / \n";
    if (temp_nd_ps != 0){
        write_formatted_vector__(file, temp_osc_eners_ps, temp_osc_eners_ps.size());
        write_formatted_vector__(file, temp_osc_weights_ps, temp_osc_weights_ps.size());
    }
    if (nsk != 0){
        file << temp_nka_ps << " " << temp_dka_ps << " / \n";
        write_formatted_vector__(file, temp_skappas_ps, temp_skappas_ps.size());
    }
    if (nsk == 2){
        file << temp_cfrac_ps << " / \n";
    }

    // Handle secondary scatterer
    if (nss > 0 && b7 == 0){
        file << temperature << " / \n";

        double temp_delta_ss = deltas_ss[0]; 
        int temp_ni_ss = nis_ss[0]; 
        std::vector<double> temp_rhos_ss = rhos_ss[0]; 
        double temp_twt_ss = twts_ss[0]; 
        double temp_c_ss = cs_ss[0]; 
        double temp_tbeta_ss = tbetas_ss[0]; 
        int temp_nd_ss = nds_ss[0]; 
        std::vector<double> temp_osc_eners_ss;
        std::vector<double> temp_osc_weights_ss;
        if (temp_nd_ss != 0){
            temp_osc_eners_ss = osc_eners_ss[0]; 
            temp_osc_weights_ss = osc_weights_ss[0]; 
        }
        int temp_nka_ss;
        double temp_dka_ss;
        std::vector<double> temp_skappas_ss;
        if (nsk != 0){
            temp_nka_ss = nkas_ss[0]; 
            temp_dka_ss = dkas_ss[0]; 
            temp_skappas_ss = skappas_ss[0]; 
        }
        double temp_cfrac_ss;
        if (nsk == 2){
            temp_cfrac_ss = cfracs_ss[0]; 
        }

        if (unique_temperatures_ss){
            auto tb_ss = findInterpolationIndexes(temps_ss.begin(), temps_ss.end(), temperature);
            double t_low_ss = temps_ss[tb_ss.first];
            double t_high_ss = temps_ss[tb_ss.second];
            temp_ni_ss = ENDF_interp(t_low_ss, t_high_ss, nis_ss[tb_ss.first], nis_ss[tb_ss.second], temperature);
            temp_rhos_ss = ENDF_interp_vector(t_low_ss, t_high_ss, rhos_ss[tb_ss.first], rhos_ss[tb_ss.second], temperature);
            temp_twt_ss = ENDF_interp(t_low_ss, t_high_ss, twts_ss[tb_ss.first], twts_ss[tb_ss.second], temperature);
            temp_c_ss = ENDF_interp(t_low_ss, t_high_ss, cs_ss[tb_ss.first], cs_ss[tb_ss.second], temperature);
            temp_tbeta_ss = ENDF_interp(t_low_ss, t_high_ss, tbetas_ss[tb_ss.first], tbetas_ss[tb_ss.second], temperature);
            temp_nd_ss = ENDF_interp(t_low_ss, t_high_ss, nds_ss[tb_ss.first], nds_ss[tb_ss.second], temperature);
            if (temp_nd_ss != 0){
                temp_osc_eners_ss = ENDF_interp_vector(t_low_ss, t_high_ss, osc_eners_ss[tb_ss.first], osc_eners_ss[tb_ss.second], temperature);
                temp_osc_weights_ss = ENDF_interp_vector(t_low_ss, t_high_ss, osc_weights_ss[tb_ss.first], osc_weights_ss[tb_ss.second], temperature);
            }
            if (nsk != 0){
                temp_nka_ss = ENDF_interp(t_low_ss, t_high_ss, nkas_ss[tb_ss.first], nkas_ss[tb_ss.second], temperature);
                temp_dka_ss = ENDF_interp(t_low_ss, t_high_ss, dkas_ss[tb_ss.first], dkas_ss[tb_ss.second], temperature);
                temp_skappas_ss = ENDF_interp_vector(t_low_ss, t_high_ss, skappas_ss[tb_ss.first], skappas_ss[tb_ss.second], temperature);
            }
            if (nsk == 2){
                temp_cfrac_ss = ENDF_interp(t_low_ss, t_high_ss, cfracs_ss[tb_ss.first], cfracs_ss[tb_ss.second], temperature);
            }
        }

        file << temp_delta_ss << " " << temp_ni_ss << " / \n";
        write_formatted_vector__(file, temp_rhos_ss, 4);
        file << temp_twt_ss << " " << temp_c_ss << " " << temp_tbeta_ss << " / \n";
        file << temp_nd_ss << " / \n";
        if (temp_nd_ss != 0){
            write_formatted_vector__(file, temp_osc_eners_ss, temp_osc_eners_ss.size());
            write_formatted_vector__(file, temp_osc_weights_ss, temp_osc_weights_ss.size());
        }
        if (nsk != 0){
            file << temp_nka_ss << " " << temp_dka_ss << " / \n";
            write_formatted_vector__(file, temp_skappas_ss, temp_skappas_ss.size());
        }
        if (nsk == 2){
            file << temp_cfrac_ss << " / \n";
        }
    }

    file << "/ \nstop\n";

    file.close();
}

void LeaprFile::write_leapr_files(){
    if (std::filesystem::exists(tsl_leapr_write_dir)){
        if (std::filesystem::is_directory(tsl_leapr_write_dir)){
            if (!force_run){
                std::string response;
                std::cout << "Are you sure you want to delete the directory '" << tsl_leapr_write_dir << "' and all its contents? (yes/no): ";
                std::cin >> response;
                std::transform(response.begin(), response.end(), response.begin(), ::tolower);
                if (response == "no"){
                    throw std::runtime_error("Operation cancelled.");
                }
            }
            std::filesystem::remove_all(tsl_leapr_write_dir);
        }
    }
    set_leapr_file_write_temps__();
    if (!silence){std::cout << "Number of files to write | " << tsl_leapr_temps.size() << std::endl;}
    for (int i = 0; i<tsl_leapr_temps.size(); ++i){
        write_leapr_file(tsl_leapr_temps[i], i);
    }
}

void LeaprFile::write_formatted_vector__(std::ofstream &file, const std::vector<double> &vec, const int width, const int precision){
    // ostringstream is used to avoid formatting effecting file
    std::ostringstream oss;
    for (size_t i = 0; i < vec.size(); ++i) {
        if (i % width == 0 && i != 0) {
            oss << '\n';
        }
        oss << std::scientific << std::setprecision(precision) << vec[i] << " ";
    }
    oss << "/ \n";
    file << oss.str();
}

void LeaprFile::set_leapr_file_write_temps__(){
    if (tsl_leapr_use_temp_delta){
        tsl_leapr_temps = arange(temps_ps.front(), temps_ps.back(), tsl_leapr_delta_temp);
        if (tsl_leapr_temps.back() != temps_ps.back()){
            tsl_leapr_temps.push_back(temps_ps.back());
        }
    }
    if (tsl_leapr_use_num_temps){
        tsl_leapr_temps = linspace(temps_ps.front(), temps_ps.back(), tsl_leapr_num_temps);
    }
    if (tsl_leapr_temps.empty()){
        tsl_leapr_temps.push_back(temps_ps[0]);
    }
}
