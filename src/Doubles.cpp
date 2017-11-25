/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file Doubles.cpp
 * 
 * Implementation of operations with double precision numbers (Doubles.h).
 *
 * @since 25.11.2017
 * @author agor
 */

#include <cmath>
#include <algorithm>

bool equal(double a, double b){
    double eps = 0.00000001;
    double max = std::max( { std::fabs(a), std::fabs(b), 1.0 } );
    return std::fabs(a - b) <= max * eps;
}