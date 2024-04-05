#include <vector>
#include <algorithm>
#include <math.h>
#include <functional>
#include <iostream>

#include "linearize.hpp"

void linearize(std::vector<double>& x_points, std::vector<double>& y_points, std::function<double(double)> get_new_y){
    std::vector<std::pair<int, int>> stack;
    stack.reserve(x_points.size());
    for(int i=0; i<x_points.size()-1; i++){
        stack.push_back(std::make_pair(i, i+1));
    }
    while (!stack.empty())
    {
        auto [left, right] = stack.back();
        stack.pop_back();

        double& x_1 = x_points[left];
        double& x_2 = x_points[right];
        double& y_1 = y_points[left];
        double& y_2 = y_points[right];

        double interval = (x_2 - x_1)/2;
        if (interval < 1e-15){
            break;
        }
        
        double x_point = x_1 + interval;
        double y_point = get_new_y(x_point);
        double interp_y = y_1 + (y_2 - y_1)*(x_point - x_1)/(x_2 - x_1);

        double abs_diff = abs(y_point - interp_y);
        double rel_diff = (y_point != 0) ? abs(abs_diff/y_point) : 0;


        if (abs_diff>0.1 || rel_diff>0.001){
            x_points.push_back(x_point);
            y_points.push_back(y_point);
            stack.push_back(std::make_pair(left, x_points.size()-1));
            stack.push_back(std::make_pair(x_points.size()-1, right));
        }
    }
    std::vector<std::pair<double, double>> data;
    data.resize(x_points.size());
    for (size_t i = 0; i < x_points.size(); i++){
        data[i] = std::make_pair(x_points[i], y_points[i]);
    }
    std::sort(data.begin(), data.end());
    for (size_t i = 0; i<x_points.size(); i++){
        x_points[i] = data[i].first;
        y_points[i] = data[i].second;
    }
}