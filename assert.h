#ifndef ASSERTION
#define ASSERTION
#ifndef NDEBUG
#include <stdexcept>
#include <iostream>
#define assert(X) ((void)(!(X) ? __assert(#X, __FILE__, __func__, __LINE__) : (void)(X)))

extern inline void __assert (const char* msg, const char* file, const char* func, int line) {
	std::cerr << "assertion: " << msg << "\n\t failed at: " << file << ", " << func <<  "(), line: " << line << std::endl;
	throw std::logic_error("Assertion failed.");
}

#else
#define assert(X) ((void)(X))
#endif
#endif