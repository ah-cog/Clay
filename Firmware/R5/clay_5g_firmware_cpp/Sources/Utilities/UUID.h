#ifndef UUID_H
#define UUID_H

#include "PE_Types.h"
#include "PE_LDD.h"

typedef unsigned char uuid_t[16];

#define SIZEOF_INT 4
#define SIZEOF_SHORT 2

#if (SIZEOF_INT == 4)
typedef	unsigned int	__u32;
#elif (SIZEOF_LONG == 4)
typedef	unsigned long	__u32;
#endif

#if (SIZEOF_INT == 2)
typedef	int		__s16;
typedef	unsigned int	__u16;
#elif (SIZEOF_SHORT == 2)
typedef	short		__s16;
typedef	unsigned short	__u16;
#endif

typedef unsigned char __u8;

struct uuid {
	__u32	time_low;
	__u16	time_mid;
	__u16	time_hi_and_version;
	__u16	clock_seq;
	__u8	node[6];
};

extern void Initialize_Unit_UUID ();

extern char* Get_Unit_UUID ();

#endif /* UUID_H */
