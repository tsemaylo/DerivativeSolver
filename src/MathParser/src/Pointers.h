/**
 * @file Pointers.h
 * 
 * Definitions pointer types and operations over pointers.
 * 
 * The purpose is to encapsulate library definitions, like shared_ptr, in one place 
 * in order to be a bit more flexible by changing the library implementation of the
 * smart pointer. Or probably implementing custom memory management tools.
 * 
 * @author  agor
 * @since 05.09.2017
 */

#ifndef POINTERS_H
#define POINTERS_H

#include <memory>

/**
 *  Wrapper for pointers (aka smart pointer).
 */
template <typename T>
using SPointer = std::shared_ptr<T>;

/**
 * Wrapper to allow "this" pointers.
 * 
 * @TODO the place for refactoring, since clients still using STL API methods instead of wraped.
 */
template <typename T>
using EnableSPointerFromThis = std:: enable_shared_from_this<T>;

/**
 * Casting from one Spointer type to an other.
 * 
 * The appliocation case: casting from SPointer<Generic> to SPointer<Concrete>.
 * The function is made inline to avoid unnecessary reference counting (SIC!).
 * 
 * The 
 * @param T Concrete target type of the object.
 * @param p Pointer to the object of generic type.
 * 
 * @return The casted pointer to the object.
 */
template <typename T, typename T1>
inline  SPointer<T> SPointerCast(const SPointer<T1> p){
    return std::dynamic_pointer_cast<T>(p);
}

/**
 * 
 * @param _args
 * 
 * @return 
 */
template <typename T, typename... _Args >
inline  SPointer<T> MakeSPointer(_Args&&... _args){
    return (std::make_shared<T>(_args...));
}

#endif /* POINTERS_H */

