#ifndef MAVOR_PREDEFINED_FIT_SETTINGS_H
#define MAVOR_PREDEFINED_FIT_SETTINGS_H

#include <functional>
#include <map>
#include <vector>
#include <iostream>

/// @brief Typedef for a function pointer to a basis function.
/// The function takes a `const double &` and an `int` as input and returns a `double`.
using FuncPointer = std::function<double(const double&, const int)>;

/// @brief A pair representing a basis function with its name and associated function pointer.
typedef std::pair<std::string, FuncPointer> BasisFunction;

/// @brief A map that associates an integer identifier with a `BasisFunction`.
typedef std::map<int, BasisFunction> BasisFunctionMap;

/// @brief A tuple representing settings for a basis function:
/// - `bool` indicating if the evaluation point of the basis function needs to be scaled into a specific range.
/// - `double` minimum value for the applicable range.
/// - `double` maximum value for the applicable range.
/// - `BasisFunction` associated function and name.
typedef std::tuple<bool, double, double, BasisFunction> BasisFunctionSettings;

/// @brief A pair representing a fitting function:
/// - `std::string` name of the fitting function.
/// - `BasisFunctionSettings` settings associated with the fitting function.
typedef std::pair<std::string, BasisFunctionSettings> FittingFunction;

/// @brief A map that associates an integer identifier with a `FittingFunction`.
typedef std::map<int, FittingFunction> FittingFunctionMap;

/// @brief A pair representing a single fit:
/// - `FittingFunction` the fitting function details.
/// - `int` the associated order or configuration index.
typedef std::pair<FittingFunction, int> Fit;

/// @brief Represents a fit for alpha values.
typedef Fit AlphaFit;

/// @brief Represents a fit for beta values.
typedef Fit BetaFit;

/// @brief Represents a fit for cross-section values.
typedef Fit XSFit;

/// @brief A tuple grouping fits for cross-sections, beta values, and alpha values.
typedef std::tuple<XSFit, BetaFit, AlphaFit> MaterialFit;

/// @brief A pair representing settings for a specific material:
/// - `std::string` name of the material.
/// - `MaterialFit` fits associated with the material.
typedef std::pair<std::string, MaterialFit> MaterialFitSettings;

/// @brief A predefined map of fitting functions for various materials.
///
/// This map associates a unique integer identifier with a pair containing:
/// - A string representing the material name.
/// - A set of fitting functions associated with that material.
///
/// Each key-value pair in the map corresponds to a specific material and its fitting functions.
///
/// Example usage:
/// @code
/// auto mat_fits = PredefinedMaterialFitsMap[1]; // Access the fits for "HinH2O"
/// std::string material = grid.first;     // Material name: "HinH2O"
/// MaterialFit fits = grid.second; // Fitting functions
/// @endcode
///
/// The materials and their identifiers are as follows:
/// - 27: "BeinBeO" (Beryllium in Beryllium Oxide)
/// - 44: "CinSiC" (Carbon in Silicon Carbide)
/// - 30: "crystalline_graphite"
/// - 11: "DinD2O" (Deuterium in Heavy Water)
/// - 37: "HinCH2" (Hydrogen in Polyethylene)
/// - 1: "HinH2O" (Hydrogen in Water)
/// - 10: "HinIcelh" (Hydrogen in Ice)
/// - 5: "HinYH2" (Hydrogen in Yttrium Hydride)
/// - 7: "HinZrH" (Hydrogen in Zirconium Hydride)
/// - 71: "NinUN" (Nitrogen in Uranium Nitride)
/// - 46: "OinBeO" (Oxygen in Beryllium Oxide)
/// - 51: "OinD2O" (Oxygen in Heavy Water)
/// - 50: "OinIcelh" (Oxygen in Ice)
/// - 75: "OinUO2" (Oxygen in Uranium Dioxide)
/// - 31: "reactor_graphite_10P" (Reactor Graphite with 10% Porosity)
/// - 32: "reactor_graphite_30P" (Reactor Graphite with 30% Porosity)
/// - 43: "SiinSiC" (Silicon in Silicon Carbide)
/// - 72: "UinUN" (Uranium in Uranium Nitride)
/// - 48: "UinUO2" (Uranium in Uranium Dioxide)
/// - 55: "YinYH2" (Yttrium in Yttrium Hydride)
/// - 58: "ZrinZrH" (Zirconium in Zirconium Hydride)
typedef std::map<int, MaterialFitSettings> PredefinedMaterialFitsMap;

/// @brief A map that associates an integer identifier with a group of predefined material fits.
typedef std::map<int, PredefinedMaterialFitsMap> PredefinedFitGroups;

/// @brief Map of predefined basis functions.
extern BasisFunctionMap basis_functions;

/// @brief Map of predefined fitting functions.
extern FittingFunctionMap fitting_functions;

/// @brief Default fit configuration.
extern Fit default_fit;

/// @brief Map of the best fits for various materials.
extern PredefinedMaterialFitsMap best_material_fits;

/// @brief Map of the optimal fits for various materials.
extern PredefinedMaterialFitsMap optimal_material_fits;

/// @brief Groups of predefined material fits for various configurations.
extern PredefinedFitGroups predefined_material_fits_groups;


// // Function pointer for basis functions
// using FuncPointer = std::function<double(const double&, const int)>;

// // Basis function representation
// struct BasisFunction {
//     std::string name;
//     FuncPointer function;
// };

// // Map of basis functions
// using BasisFunctionMap = std::map<int, BasisFunction>;

// // Basis function settings
// struct BasisFunctionSettings {
//     bool needs_scaling;
//     double min_value;
//     double max_value;
//     BasisFunction basis_function;
// };

// // Fitting function representation
// struct FittingFunction {
//     std::string name;
//     BasisFunctionSettings settings;
// };

// // Map of fitting functions
// using FittingFunctionMap = std::map<int, FittingFunction>;

// // Fit representation
// struct Fit {
//     FittingFunction fitting_function;
//     int order;
// };

// // Material fit containing all three fits
// struct MaterialFit {
//     Fit xs_fit;
//     Fit beta_fit;
//     Fit alpha_fit;
// };

// // Material fit settings
// struct MaterialFitSettings {
//     std::string material_name;
//     MaterialFit material_fit;
// };

// // Predefined material fit map
// using PredefinedMaterialFitsMap = std::map<int, MaterialFitSettings>;

// // Groups of predefined fits
// using PredefinedFitGroups = std::map<int, PredefinedMaterialFitsMap>;

#endif