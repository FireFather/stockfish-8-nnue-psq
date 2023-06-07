// disable specific compiler warnings
#pragma once
#ifdef _MSC_VER
#pragma warning(disable: 4127) // conditional expression is constant
#pragma warning(disable: 4146) // unary minus operator applied to unsigned type
#pragma warning(disable: 4189) // local variable is initialized but not referenced
#pragma warning(disable: 4244) // 'initializing' : conversion from '' to '', possible loss of data
#pragma warning(disable: 4458) // declaration of 'depth' hides class member
#pragma warning(disable: 4706) // assignment within conditional expression
#pragma warning(disable: 6031) // Return value ignored: 'sscanf'
#pragma warning(disable: 6326) // Potential comparison of a constant with another constant
#pragma warning(disable: 6386) // Buffer overrun while writing to 'this->kingSquare'
#else
#pragma GCC diagnostic ignored "-Wimplicit-fallthrough"
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wcast-qual"
#pragma GCC diagnostic ignored "-Wunused-function"
#endif

