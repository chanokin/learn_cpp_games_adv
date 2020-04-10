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

float ms_to_s(uint32_t ms){
    return static_cast<float>(ms) * 0.001;
}
