#ifndef MAVOR_PREDEFINED_FIT_SETTINGS_H
#define MAVOR_PREDEFINED_FIT_SETTINGS_H

#include <map>
#include <vector>
#include <iostream>

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