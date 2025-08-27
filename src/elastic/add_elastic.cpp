#include <filesystem>

#include <highfive/highfive.hpp>

#include "ENDFtk/tree/Tape.hpp"
#include "ENDFtk/tree/fromFile.hpp"
#include "ENDFtk/section/7/2.hpp"

#include "runtime_variables.hpp"

#include "add_elastic.hpp"

using Tape = njoy::ENDFtk::tree::Tape;
using MF7MT2 = njoy::ENDFtk::section::Type<7,2>;
using ScatteringLaw = MF7MT2::ScatteringLaw;
using CoherentElastic = MF7MT2::CoherentElastic;
using IncoherentElastic = MF7MT2::IncoherentElastic;
using MixedElastic = MF7MT2::MixedElastic;

void add_coherent_elastic__(HighFive::Group elastic_group, const MF7MT2::CoherentElastic &coherent_elastic_data){
    HighFive::Group coherent_group = elastic_group.createGroup("Coherent");

    std::vector<double> temperatures{coherent_elastic_data.temperatures().begin(), 
                                     coherent_elastic_data.temperatures().end()};
    coherent_group.createDataSet("TEMPERATURES", temperatures);

    std::vector<int> temperature_intepolants{coherent_elastic_data.temperatureInterpolants().begin(),
                                             coherent_elastic_data.temperatureInterpolants().end()};
    coherent_group.createDataSet("INTERPOLATION_LAWS", temperature_intepolants);

    std::vector<double> energies{coherent_elastic_data.energies().begin(),
                                 coherent_elastic_data.energies().end()};
    coherent_group.createDataSet("ENERGIES", energies);

    auto s_val_matrix = coherent_elastic_data.thermalScatteringValues();
    std::vector<double> flatend_s_vals;
    for (auto s_val_vec:s_val_matrix){
        flatend_s_vals.insert(flatend_s_vals.end(), s_val_vec.data(), s_val_vec.data() + s_val_vec.size());
    }
    coherent_group.createDataSet("S_VALS", flatend_s_vals);
}

void add_incoherent_elastic__(HighFive::Group elastic_group, const MF7MT2::IncoherentElastic &incoherent_elastic_data){
    HighFive::Group incoherent_group = elastic_group.createGroup("Incoherent");

    std::vector<double> temperatures{incoherent_elastic_data.temperatures().begin(), 
                                     incoherent_elastic_data.temperatures().end()};
    incoherent_group.createDataSet("TEMPERATURES", temperatures);
    
    incoherent_group.createAttribute("INTERPOLATION_LAW", incoherent_elastic_data.interpolants()[0]);
    
    std::vector<double> debye_wallers{incoherent_elastic_data.debyeWallerValues().begin(),
                                      incoherent_elastic_data.debyeWallerValues().end()};
    incoherent_group.createDataSet("DEBYE_WALLERS", debye_wallers);
}

void scattering_data(){
    // Copy the OTF coefficient file to the final desired file
    const auto copy_options = std::filesystem::copy_options::overwrite_existing;
    if (!std::filesystem::copy_file(elastic_otf_file, elastic_full_otf_file, copy_options)){
        throw std::runtime_error("Unable to copy OTF coefficient file to full otf file.");
    }

    // Add in elastic data to the copied OTF coefficient file
    HighFive::File h5_file(elastic_full_otf_file, HighFive::File::ReadWrite);

    Tape tape = njoy::ENDFtk::tree::fromFile(elastic_endf_file);
    
    int endf_mat = tape.materialNumbers()[0];
    int otf_mat = h5_file.getAttribute("MAT").read<int>();
    if (endf_mat != otf_mat){throw std::runtime_error("Material numbers do not match for the given OTF and ENDF files.");}

    if (tape.materials().front().hasSection(7,2)){
        HighFive::Group elastic = h5_file.createGroup("Elastic");
        MF7MT2 mt2 = tape.materials().front().section(7,2).parse<7,2>();
        ScatteringLaw scat_law = mt2.scatteringLaw();
        int lthr = mt2.LTHR();
        if (lthr == 1){add_coherent_elastic__(elastic, std::get<CoherentElastic>(scat_law));}
        else if (lthr == 2){add_incoherent_elastic__(elastic, std::get<IncoherentElastic>(scat_law));}
        else if (lthr == 3){
            const MixedElastic& me = std::get<MixedElastic>(scat_law);
            add_coherent_elastic__(elastic, me.coherent());
            add_incoherent_elastic__(elastic, me.incoherent());
        }
        else{throw std::runtime_error("Unexpected LTHR value found in ENDF file.");}
    }
   
    else{
        if (!silence){std::cout << "No elastic data found in ENDF file." << std::endl;}
    }
}