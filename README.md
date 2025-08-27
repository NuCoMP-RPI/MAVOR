# MAVOR  
*A Tool for Continuous, On-The-Fly Thermal Neutron Scattering Data*  

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](LICENSE)  

MAVOR is an open-source C++ tool for generating fully continuous, linearized, temperature on-the-fly (OTF) thermal neutron scattering distributions.  
It replaces the role of NJOY’s THERMR module by building compact, regression-based fits of scattering distributions across temperature, enabling direct Monte Carlo sampling at arbitrary temperatures without interpolation or heavy memory overhead.  

If you use MAVOR in your research, please cite our paper:  

> Camden Blake, Hunter Belanger, and Wei Ji,  
> *MAVOR: A Tool to Create Fully Continuous, Linearized, Temperature On-The-Fly Thermal Neutron Sampling Distributions*,  
> [Journal Reference / DOI — add here once available].  

---

## Key Features  
- Implements the direct S(α, β, T) method for compact scattering representation.  
- Generates continuous OTF sampling distributions across arbitrary temperature grids.  
- Provides both direct sampling and regression-based coefficient outputs.  
- Automates end-to-end workflows for processing ENDF thermal scattering evaluations.  
- Produces output in HDF5 format, directly usable in Monte Carlo neutron transport codes.  
- Validated against ACE libraries with excellent agreement, while drastically reducing storage requirements.  

---

## Dependencies (auto-fetched)  
MAVOR automatically fetches and builds required libraries:  

- [HDF5](https://www.hdfgroup.org/solutions/hdf5/)  
- [HighFive](https://github.com/BlueBrain/HighFive)  
- [CLI11](https://github.com/CLIUtils/CLI11)  
- [Eigen](https://eigen.tuxfamily.org/)  
- [GoogleTest](https://github.com/google/googletest)  
- [ENDFtk](https://github.com/njoy/ENDFtk)  
- [NJOY2016.76](https://github.com/njoy/NJOY2016) (built automatically)  

---

## Installation  
```bash
git clone https://github.com/NuCoMP-RPI/MAVOR.git
cd MAVOR
mkdir build && cd build
cmake ..
make -j
