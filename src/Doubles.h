/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file Doubles.h
 * 
 * Definitions of operations with double precision numbers.
 *
 * @since 25.11.2017
 * @author agor
 */

#ifndef DOUBLES_H
#define DOUBLES_H

const double PI=3.14159265358979323846;

/**
 * Check whether two doubles are equal with certain precision.
 * 
 * @param a Value of first double.
 * @param b Value of second double.
 * @return true/false
 */
bool equal(double a, double b);

#endif /* DOUBLES_H */

