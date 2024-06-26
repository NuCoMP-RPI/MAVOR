#ifndef MAVOR_PREDEFINED_FIT_SETTINGS_H
#define MAVOR_PREDEFINED_FIT_SETTINGS_H

#include <map>
#include <vector>
#include <iostream>

// typedef double(*FuncPointer)(const double &, const int);
// typedef std::pair<std::string, FuncPointer> FitFunction;
// typedef std::tuple<bool, double, double, FitFunction> FitSettings;
// typedef std::pair<std::string, FitSettings> PredefinedFitSettings;

// typedef std::pair<PredefinedFitSettings, int> PredefinedFit;
// typedef std::tuple<PredefinedFit, PredefinedFit, PredefinedFit> MatPredefinedFits;

// typedef std::map<int, FitFunction> MapFittingFunctions;
// extern MapFittingFunctions fitting_functions;

// typedef std::map<int, PredefinedFitSettings> PredefinedFitSettingsMap;
// extern PredefinedFitSettingsMap predefined_fit_settings;

// typedef std::map<int, MatPredefinedFits> MatPredefinedFitMap;
// extern MatPredefinedFitMap material_predefined_fits;

// extern PredefinedFit default_fit;

typedef double(*FuncPointer)(const double &, const int);
typedef std::pair<std::string, FuncPointer> BasisFunction;
typedef std::map<int, BasisFunction> BasisFunctionMap;
typedef std::tuple<bool, double, double, BasisFunction> BasisFunctionSettings;
typedef std::pair<std::string, BasisFunctionSettings> FittingFunction;
typedef std::map<int, FittingFunction> FittingFunctionMap;
typedef std::pair<FittingFunction, int> Fit;
typedef Fit AlphaFit;
typedef Fit BetaFit;
typedef Fit XSFit;
typedef std::tuple<XSFit, BetaFit, AlphaFit> MaterialFit;
typedef std::pair<std::string, MaterialFit> MaterialFitSettings;
typedef std::map<int, MaterialFitSettings> PredefinedMaterialFitsMap;
typedef std::map<int, PredefinedMaterialFitsMap> PredefinedFitGroups;

extern BasisFunctionMap basis_functions;
extern FittingFunctionMap fitting_functions;
extern Fit default_fit;

extern PredefinedMaterialFitsMap best_material_fits;
extern PredefinedMaterialFitsMap optimal_material_fits;

extern PredefinedFitGroups predefined_material_fits_groups;

#endif

// 27 BeinBeO
// 44 CinSiC
// 30 crystalline_graphite
// 11 DinD2O
// 37 HinCH2
// 1  HinH2O
// 10 HinIcelh
// 5  HinYH2
// 7  HinZrH
// 71 NinUN
// 46 OinBeO
// 51 OinD2O
// 50 OinIcelh
// 75 OinUO2
// 31 reactor_graphite_10P
// 32 reactor_graphite_30P
// 43 SiinSiC
// 72 UinUN
// 48 UinUO2
// 55 YinYH2
// 58 ZrinZrH
