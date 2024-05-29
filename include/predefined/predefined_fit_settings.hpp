#ifndef MAVOR_PREDEFINED_FIT_SETTINGS_H
#define MAVOR_PREDEFINED_FIT_SETTINGS_H

#include <map>
#include <vector>
#include <iostream>

typedef double(*FuncPointer)(const double &, const int);
typedef std::pair<std::string, FuncPointer> FitFunction;
typedef std::tuple<bool, double, double, FitFunction> FitSettings;
typedef std::pair<std::string, FitSettings> PredefinedFitSettings;

typedef std::pair<PredefinedFitSettings, int> PredefinedFit;
typedef std::tuple<PredefinedFit, PredefinedFit, PredefinedFit> MatPredefinedFits;

typedef std::map<int, FitFunction> MapFittingFunctions;
extern MapFittingFunctions fitting_functions;

typedef std::map<int, PredefinedFitSettings> PredefinedFitSettingsMap;
extern PredefinedFitSettingsMap predefined_fit_settings;

typedef std::map<int, MatPredefinedFits> MatPredefinedFitMap;
extern MatPredefinedFitMap material_predefined_fits;

extern PredefinedFit default_fit;

#endif