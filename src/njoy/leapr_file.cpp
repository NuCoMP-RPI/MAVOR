#include <fstream>
#include <algorithm>

#include "file_reading.hpp"
#include "runtime_variables.hpp"

#include "leapr_file.hpp"



LeaprFile::LeaprFile(const std::string &file_path) :
    // Set Default values here
    ntemp(0), 
    iprint(1), 
    nphon(100), 
    isabt(0),
    ilog(1), 
    smin(1e-75), 
    iel(0), 
    ncold(0), 
    nsk(0),
    nss(0), 
    lat(0),
    file(file_path)
    {
        if (!file.is_open()) {throw std::runtime_error("Failed to open file: " + file_path);}
        try
        {
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
        get_all_cards_10_19__();
        }
        catch(const std::exception& e)
        {
            std::cout << line << std::endl;
            std::cerr << e.what() << '\n';
        }
        file.close();
}

bool LeaprFile::get_line_single_item__(){
    // bool result = debug_getline(file, line);
    bool result = static_cast<bool>(std::getline(file, line));
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
    // std::cout << "Finished reading leapr array" << std::endl;
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
    // std::cout << "Reading Card 1" << std::endl;
    get_line_single_item__();
    nout = std::stoi(line);
}

void LeaprFile::get_card_2__(){
    // std::cout << "Reading Card 2" << std::endl;
    get_line_single_item__();
    title = line;
}

void LeaprFile::get_card_3__(){
    // std::cout << "Reading Card 3" << std::endl;
    get_line_all_numbers__();
    if (endf_numbers.size() > 0) {ntemp = static_cast<int>(endf_numbers[0]);}
    if (endf_numbers.size() > 1) {iprint = static_cast<int>(endf_numbers[1]);}
    if (endf_numbers.size() > 2) {nphon = static_cast<int>(endf_numbers[2]);}
}

void LeaprFile::get_card_4__(){
    // std::cout << "Reading Card 4" << std::endl;
    get_line_all_numbers__();
    material_number = static_cast<int>(endf_numbers[0]);
    za = static_cast<int>(endf_numbers[1]);
    if (endf_numbers.size() > 2){isabt = static_cast<int>(endf_numbers[2]);}
    if (endf_numbers.size() > 3){ilog = static_cast<int>(endf_numbers[3]);}
    if (endf_numbers.size() > 4){smin = endf_numbers[4];}
}

void LeaprFile::get_card_5__(){
    // std::cout << "Reading Card 5" << std::endl;
    get_line_all_numbers__();
    awr = endf_numbers[0];
    spr = endf_numbers[1];
    npr = static_cast<int>(endf_numbers[2]);
    if (endf_numbers.size() > 3) {iel = static_cast<int>(endf_numbers[3]);}
    if (endf_numbers.size() > 4) {ncold = static_cast<int>(endf_numbers[4]);}
    if (endf_numbers.size() > 5) {nsk = static_cast<int>(endf_numbers[5]);}
}

void LeaprFile::get_card_6__(){
    // std::cout << "Reading Card 6" << std::endl;
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
    // std::cout << "Reading Card 7" << std::endl;
    get_line_all_numbers__();
    nalpha = static_cast<int>(endf_numbers[0]);
    nbeta = static_cast<int>(endf_numbers[1]);
    if (endf_numbers.size() > 2) {lat = static_cast<int>(endf_numbers[2]);}
}

void LeaprFile::get_card_8__(){
    // std::cout << "Reading Card 8" << std::endl;
    alphas = get_leapr_array__(nalpha);
}

void LeaprFile::get_card_9__(){
    // std::cout << "Reading Card 9" << std::endl;
    betas = get_leapr_array__(nbeta);
}

void LeaprFile::get_all_cards_10_19__(){
    for (int i = 0; i < ntemp; ++i) {
        // std::cout << "Temperature Number: "<< i << std::endl;
        get_card_10__();
        get_card_11__();
        get_card_12__();
        get_card_13__();
        get_card_14__();
        get_card_15__();
        get_card_16__();
        get_card_17__();
        get_card_18__();
        get_card_19__();
    }
}

void LeaprFile::get_card_10__(){
    // std::cout << "Reading Card 10" << std::endl;
    get_line_single_item__();
    double temp = ENDF_float(line);
    pos_temp.push_back(temp > 0);
    temps.push_back(std::abs(temp));
}

void LeaprFile::get_card_11__(){
    // std::cout << "Reading Card 11" << std::endl;
    if (pos_temp.back()) {
        get_line_all_numbers__();
        deltas.push_back(endf_numbers[0]);
        nis.push_back(static_cast<int>(endf_numbers[1]));
    }
    else {
        deltas.push_back(deltas.back());
        nis.push_back(nis.back());
    }
}

void LeaprFile::get_card_12__(){
    // std::cout << "Reading Card 12" << std::endl;
    if (pos_temp.back()) {
        rhos.push_back(get_leapr_array__(nis.back()));
    } 
    else {
        rhos.push_back(rhos.back());
    }
}

void LeaprFile::get_card_13__(){
    // std::cout << "Reading Card 13" << std::endl;
    if (pos_temp.back()) {
        get_line_all_numbers__();
        twts.push_back(endf_numbers[0]);
        cs.push_back(endf_numbers[1]);
        tbetas.push_back(endf_numbers[2]);
    }
    else {
        twts.push_back(twts.back());
        cs.push_back(cs.back());
        tbetas.push_back(tbetas.back());
    }
}

void LeaprFile::get_card_14__(){
    // std::cout << "Reading Card 14" << std::endl;
    if (pos_temp.back()) {
        get_line_single_item__();
        nds.push_back(static_cast<int>(ENDF_float(line)));
    } else {
        nds.push_back(nds.back());
    }
}

void LeaprFile::get_card_15__(){
    // std::cout << "Reading Card 15" << std::endl;
    if (pos_temp.back()) {
        osc_eners.push_back(get_leapr_array__(nds.back()));
    } else {
        osc_eners.push_back(osc_eners.back());
    }
}

void LeaprFile::get_card_16__(){
    // std::cout << "Reading Card 16" << std::endl;
    if (pos_temp.back()) {
        osc_weights.push_back(get_leapr_array__(nds.back()));
    } else {
        osc_weights.push_back(osc_weights.back());
    }
}

void LeaprFile::get_card_17__(){
    // std::cout << "Reading Card 17" << std::endl;
    if (nsk != 0){
        if (pos_temp.back()) {
            get_line_all_numbers__();
            nkas.push_back(endf_numbers[0]);
            dkas.push_back(endf_numbers[1]);
        } else {
            nkas.push_back(nkas.back());
            dkas.push_back(dkas.back());
        }
    }
}

void LeaprFile::get_card_18__(){
    // std::cout << "Reading Card 18" << std::endl;
    if (nsk != 0){
        if (pos_temp.back()) {
            skappas.push_back(get_leapr_array__(nkas.back()));
        } else {
            skappas.push_back(skappas.back());
        }
    }
}

void LeaprFile::get_card_19__(){
    // std::cout << "Reading Card 19" << std::endl;
    if (nsk == 2){
        if (pos_temp.back()) {
            get_line_single_item__();
            cfracs.push_back(ENDF_float(line));
        } else {
            cfracs.push_back(0.0);
        }
    }
}

