// Header File Guard
#ifndef STD_TYPES_H_
#define STD_TYPES_H_

typedef unsigned char           u8;
typedef unsigned short int      u16;
typedef unsigned long int       u32;
typedef unsigned long long int  u64;
typedef signed char             s8;
typedef signed short int        s16;
typedef signed long int         s32;
typedef signed long long int    s64;
typedef float                   f32;
typedef double                  f64;
typedef long double             f128;


typedef unsigned char * 			pu8;
typedef signed char *			     ps8;
typedef unsigned short int *	     pu16;
typedef signed short int * 		     ps16;
typedef unsigned int *			     pu32;
typedef signed int *			     ps32;
typedef unsigned long long int *     pu64;
typedef signed long long int *	     ps64;
typedef float *					     pf32;
typedef double *					 pf64;
typedef long double *			     pf128;

#define NULL						0x00000000
#endif /* STD_TYPES_H_ */
