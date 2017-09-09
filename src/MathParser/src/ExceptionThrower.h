/**
 * @file   ExceptionThrower.h
 * 
 * @brief Macro for exception throwing.
 * 
 * @since 10.08.2017
 * @author agor
 */

#ifndef EXCEPTIONTHROWER_H
#define	EXCEPTIONTHROWER_H


// @TODO delete this, will be given as a compiler flag
#define DEBUG

#ifdef DEBUG
	#define THROW(ex, msg, ctx) throw ex(msg, string(ctx) + "\n Function: " + __func__ + "; \n File: " + __FILE__ + "(" + to_string(__LINE__) + ")")
#else
	#define THROW(ex, msg, ctx) throw ex(msg, ctx)
#endif

#endif	/* EXCEPTIONTHROWER_H */

