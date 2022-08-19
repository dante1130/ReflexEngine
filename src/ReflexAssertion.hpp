#pragma once

#include <iostream>

#ifndef NDEBUG
#define REFLEX_ASSERT(Expr, Msg) \
	reflex_assert(#Expr, Expr, __FILE__, __LINE__, Msg)
#else
#define REFLEX_ASSERT(Expr, Msg) ;
#endif

inline void reflex_assert(const char* expr_str, bool expr, const char* file,
                          int line, const char* msg) {
	if (!expr) {
		std::cerr << "Assert failed:\t" << msg << "\n"
		          << "Expected:\t" << expr_str << "\n"
		          << "Source:\t\t" << file << ", line " << line << "\n";
		std::terminate();
	}
}
