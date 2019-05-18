#include "math_utils.hpp"
#include <cmath>

bool eq_float(float left, float right, float thresh){
    return ( fabs(left - right) <= thresh );
}

bool geq_float(float left, float right, float thresh){
    return ( (left > right) || eq_float(left, right, thresh));

}

bool leq_float(float left, float right, float thresh){
    return ( (left < right) || eq_float(left, right, thresh));
}
