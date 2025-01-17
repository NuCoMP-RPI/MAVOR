#ifndef MAVOR_PREDEFINED_ENERGY_GRIDS_H
#define MAVOR_PREDEFINED_ENERGY_GRIDS_H

#include <map>
#include <vector>
#include <iostream>

/// @brief A predefined map of energy grids for various materials.
///
/// This map associates a unique integer identifier with a pair containing:
/// - A string representing the material name.
/// - A vector of doubles representing the energy grid associated with that material.
///
/// Each key-value pair in the map corresponds to a specific material and its associated energy grid.
///
/// Example usage:
/// @code
/// auto grid = predefined_energy_grids[1]; // Access the energy grid for "HinH2O"
/// std::string material = grid.first;     // Material name: "HinH2O"
/// std::vector<double> energies = grid.second; // Energy grid values
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
///
/// @see predefined_energy_grids
extern std::map<int, std::pair<std::string, std::vector<double>>> predefined_energy_grids;

#endif