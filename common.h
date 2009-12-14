#ifndef _COMMON_H_
#define _COMMON_H_
/*
* Copyright (c) 2009 Heung-Keung Chai
* You can redistribute it and/or modify it under the same terms as FreeBSD
*/
typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned int    uint32_t;
typedef unsigned long long uint64_t;

typedef char   int8_t;
typedef short  int16_t;
typedef int    int32_t;
typedef long long int64_t;

/*
 * Status code for functions
 */

#define OK           (0)
#define ERROR        (-1)

#define OFF          (0)

/*
 *  Verbosity levels for debugging purposes
 */

#define V_MAX        (1<<31)
#define V_ENTER_EXIT (1<<30)
#define V_DEBUG_3    (1<<14)
#define V_DEBUG_2    (1<<13)
#define V_DEBUG_1    (1<<12)
#define V_DEBUG      (1<<11)
#define V_INFO       (1<<10)
#define V_WARNING    (1<<8)
#define V_ERROR      (1<<6)
#define V_IMPORTANT  (1<<5)
#define V_FATAL      (1<<4)
#define V_CRITICAL   (1<<2)
#define V_SILENT     (1<<1)
#define V_MIN        (0)


/*
 * Any X_S will show all messages with verbosity level equal or smaller than it
 * E.g. V_CRITICAL_S will show all V_SILENT, V_CRITICAL, and V_FATAL statements
 */
#define V_MAX_S        (0xFFFFFFFF)   // All 32 bits included. Super-sized deal
#define V_ENTER_EXIT_S (V_ENTER_EXIT | V_DEBUG_S)
#define V_DEBUG_S      (V_DEBUG | V_INFO_S)
#define V_INFO_S       (V_INFO | V_WARNING_S)
#define V_WARNING_S    (V_WARNING | V_ERROR_S)
#define V_ERROR_S      (V_ERROR | V_IMPORTANT_S)
#define V_IMPORTANT_S  (V_IMPORTANT | V_FATAL_S)
#define V_FATAL_S      (V_FATAL | V_CRITICAL_S)
#define V_CRITICAL_S   (V_CRITICAL | V_SILENT_S)
#define V_SILENT_S     (V_SILENT)                    // Dummy, for uniformity...

#define VPRINT(level, F, args...)\
do{\
	if(level & global_verbose_level)\
	{\
		printf("\n\r%s: " F, __func__, ##args);\
	}\
}while(0)

#define VENTER() VPRINT(V_INFO, "Enter\n\r");

#define VEXIT() VPRINT(V_INFO, "Exit\n\r");

//
// VPRINT_PLAIN will not print the invoking function name
//
#define VPRINT_PLAIN(level, F, args...)\
do{\
	if(level & global_verbose_level)\
	{\
		printf(F, ##args);\
	}\
}while(0)

#define VCHECK_VOID(F) \
do{\
	if(F == OK)\
	{\
    		VPRINT(V_DEBUG, "%s is ok\n\r", #F);\
	}\
	else\
	{\
    		VPRINT(V_ERROR, "****ERROR: Didn't return OK: %s\n\r", #F);\
		return;\
	}\
}while(0)

#define VASSERT(F) \
do{\
	if((F))\
	{\
    		VPRINT(V_DEBUG, "%s is ok\n\r", #F);\
	}\
	else\
	{\
    		VPRINT(V_ERROR, "****ERROR: This statement has failed assertion: %s\n\r", #F);\
		return ERROR;\
	}\
}while(0)

#define VASSERT_INT(F)\
do{\
	if((F))\
	{\
    		VPRINT(V_DEBUG, "%s is ok\n\r", #F);\
	}\
	else\
	{\
    		VPRINT(V_ERROR, "****ERROR: This statement has failed assertion: %s\n\r", #F);\
		return ERROR;\
	}\
}while(0)

#define VASSERT_VOID(F)\
do{\
	if((F))\
	{\
    		VPRINT(V_DEBUG, "%s is ok\n\r", #F);\
	}\
	else\
	{\
    		VPRINT(V_ERROR, "****ERROR: This statement has failed assertion: %s\n\r", #F);\
		return;\
	}\
}while(0)

#define VCHECK(F) \
  do{\
	if(F == OK)\
	{\
    		VPRINT(V_DEBUG, "%s is ok\n\r", #F);\
	}\
	else\
	{\
    		VPRINT(V_ERROR, "****ERROR: Didn't return OK: %s\n\r", #F);\
		return ERROR;\
	}\
  }while(0)

/*
 * (hkc) The following definitions are side-effect safe. I believe typeof is a GCC extension
 */
#define MAX(a, b) ({ typeof(a) _a = (a), _b = (b); _a > _b? _a:_b; })
#define MIN(a, b) ({ typeof(a) _a = (a), _b = (b); _a < _b? _a:_b; })
#define ABS(a) ({ typeof(a) _a = (a); (_a > 0) ? _a: -_a; })
#define SQR(a) ({ typeof(a) _a = (a); _a*_a; })
#define SQR_SUM(a,b) ({SQR(a) + SQR(b);})

#endif //_COMMON_H_

