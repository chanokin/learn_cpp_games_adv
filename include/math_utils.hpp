#ifndef MATH_UTILS_HPP
#define MATH_UTILS_HPP
static const float EPSILON = 0.000001f;
static const float INF = 100000000.0f;

bool eq_float(float left, float right, float thresh=EPSILON);
bool geq_float(float left, float right, float thresh=EPSILON);
bool leq_float(float left, float right, float thresh=EPSILON);


#endif // !MATH_UTILS_HPP
