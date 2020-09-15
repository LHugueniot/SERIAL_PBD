#ifndef UTILITIES_H
#define UTILITIES_H

// c++11 std lib includes 
#include <map>
#include <cmath>
#include <string>
#include <memory>
#include <vector>
#include <random>
#include <chrono>
#include <cassert>
#include <iostream>
#include <algorithm>

template<class T>
const T& clamp( const T& v, const T& lo, const T& hi )
{
    assert( !(hi < lo) );
    return (v < lo) ? lo : (hi < v) ? hi : v;
}

// Window management
#include <SDL2/SDL.h>

// Graphics drawing
#include <GL/glew.h>

// Eigen includes
#include <Eigen/Eigen>
#include <Eigen/Core>
#include <Eigen/Geometry>

using namespace Eigen;

#define M_RAD_RATIO 0.01745329251
#define TO_RAD(deg) deg * M_RAD_RATIO

#define cot(x) cos(x)/sin(x)

#endif /* UTILITIES_H */