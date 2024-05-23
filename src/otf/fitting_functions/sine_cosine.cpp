#include <math.h>

#include "sine_cosine.hpp"

#include "constants.hpp"

double eval_sine_cosine_order(double const & x, int const order){
    if (order==0) {return 1;}
    else if (order%2 == 0) {return sin(int(order/2)*2*PI*x);}
    else {return cos(int(order/2)*2*PI*x);}
}