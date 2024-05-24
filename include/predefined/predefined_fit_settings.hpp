#ifndef MAVOR_PREDEFINED_FIT_SETTINGS_H
#define MAVOR_PREDEFINED_FIT_SETTINGS_H

#include <map>
#include <vector>
#include <iostream>

#include "fitting_function.hpp"

typedef std::tuple<bool, double, double, FitFunction> FitSettings;

typedef std::pair<std::string, FitSettings> PredefinedFitSettings;
typedef std::map<int, PredefinedFitSettings> PredefinedFitSettingsMap;

typedef std::pair<PredefinedFitSettings, int> PredefinedFit;

typedef std::map<int, std::tuple<PredefinedFit, PredefinedFit, PredefinedFit>> MatPredefinedFitMap;

extern PredefinedFitSettingsMap predefined_fit_settings;
extern MatPredefinedFitMap material_predefined_fits;

#endif