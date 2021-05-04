#ifndef UBaseTypes_H
#define UBaseTypes_H

#include "ToolsStable.h"

namespace Tools
{

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef PI
#define PI 3.14159265358979
#endif


/** Boolean type */

typedef bool BOOL;


/** Unsigned integer types */

typedef uint8_t U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;


/** Signed integer types */

typedef int8_t S8;
typedef int16_t S16;
typedef int32_t S32;
typedef int64_t S64;


/** Floating-point types */

typedef float F32;
typedef double F64;


/** Complex numbers */

typedef struct
{
    F32 f32Re;
    F32 f32Im;
} C32;

typedef struct
{
    F64 f64Re;
    F64 f64Im;
} C64;

} /* End of namespace Tools */
#endif // UBaseTypes_H
