#ifndef SPAG_COMMON_H
#define SPAG_COMMON_H

/// @file common.cuh
/// @brief TO COMPLETE

// Standard lib includes
#include <set>
#include <cmath>
#include <array>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <unordered_set>

//OpenGL includes
#include <GL/glew.h>

//Eigen includes
#include <Eigen/Eigen>
#include <Eigen/Core>
#include <Eigen/Geometry>

using uint = unsigned int;

namespace spag{

#define M_RAD_RATIO 0.01745329251
#define TO_RAD(deg) deg * M_RAD_RATIO

#define cot(x) cos(x)/sin(x)

enum Dim : unsigned char{
	X = 0,
	Y = 1,
	Z = 2
};

inline Dim operator ++(Dim &id, int)
{
   Dim currId = id;

   id = static_cast<Dim>( id + 1 );

   return currId;
}


#define ASSERT_MSG(condition, message) do { \
if (!(condition)) { std::cout<<message; } \
assert ((condition)); } while(false)


// Debug functions for those of us in the middle ages who dont use a debugger.

#define DEBUG_MODE 0

#if DEBUG_MODE
#   define DEBUG() std::cout<<"BREAK POINT: LINE "<<__LINE__<<" IN "<<__FILE__<<std::endl;
#   define DEBUG_VAR(var) std::cout<<"BREAK POINT: LINE "<<__LINE__<<" IN "<<__FILE__<<" FOR VAR: "<<#var<<" = "<<var<<std::endl;
#   define DEBUG_MSG(msg) std::cout<<"BREAK POINT: LINE "<<__LINE__<<" IN "<<__FILE__<<" ~ WITH MSG: "<<msg<<std::endl;
#   define DEBUG_ASS(Expr, Msg) \
    __M_Assert(#Expr, Expr, __FILE__, __LINE__, Msg)
#else
#   define DEBUG(...) do {} while (0)
#   define DEBUG_VAR(var) do {} while (0)
#   define DEBUG_MSG(msg) do {} while (0)
#   define DEBUG_ASS(Expr, Msg) do {} while (0)
#endif

template<typename T>
void __M_Assert(const char* expr_str, bool expr, const char* file, int line, T msg){
    if (!expr){
        std::cerr << "Assert failed:\t" << msg << "\n"
            << "Expected:\t" << expr_str << "\n"
            << "Source:\t\t" << file << ", line " << line << "\n";
        abort();
    }
}

} /* namespace spag */

#endif /* SPAG_COMMON_H */