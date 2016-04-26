#include "stdlib.h"
#include "stdint.h"
#include "string.h"
#include "stdio.h"

#include "MK64F12.h"
#include "UUID.h"

static char unitUuid[37] = { 0 };

static void uuid_unpack (const uuid_t in, struct uuid *uu) {
	
	const __u8	*ptr = in;
	__u32		tmp;

	tmp = *ptr++;
	tmp = (tmp << 8) | *ptr++;
	tmp = (tmp << 8) | *ptr++;
	tmp = (tmp << 8) | *ptr++;
	uu->time_low = tmp;

	tmp = *ptr++;
	tmp = (tmp << 8) | *ptr++;
	uu->time_mid = tmp;
	
	tmp = *ptr++;
	tmp = (tmp << 8) | *ptr++;
	uu->time_hi_and_version = tmp;

	tmp = *ptr++;
	tmp = (tmp << 8) | *ptr++;
	uu->clock_seq = tmp;

	memcpy (uu->node, ptr, 6);
}

/**
 * Convert a 16 octet (that is, 16 byte) UUID to a 36 byte null-terminated string.
 * 
 * Since the resulting 36 byte string is null-terminated, the string must be 
 * declared as a 37 byte string so the null character can be stored after the 
 * UUID string. 
 */
static void uuid_unparse (const uuid_t uu, char *out) {
	
	struct uuid uuid;

	uuid_unpack (uu, &uuid);
	sprintf (out,
		"%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
		uuid.time_low, uuid.time_mid, uuid.time_hi_and_version,
		uuid.clock_seq >> 8, uuid.clock_seq & 0xFF,
		uuid.node[0], uuid.node[1], uuid.node[2],
		uuid.node[3], uuid.node[4], uuid.node[5]);
}

void Initialize_Unit_UUID () {
	
	unsigned char unitUuidBytes[16] = { 0 };
	
	unitUuidBytes[0]  = (SIM_UIDH >> 24) & 0xFF;
	unitUuidBytes[1]  = (SIM_UIDH >> 16) & 0xFF;
	unitUuidBytes[2]  = (SIM_UIDH >>  8) & 0xFF;
	unitUuidBytes[3]  = (SIM_UIDH >>  0) & 0xFF;
	
	unitUuidBytes[4]  = (SIM_UIDMH >> 24) & 0xFF;
	unitUuidBytes[5]  = (SIM_UIDMH >> 16) & 0xFF;
	unitUuidBytes[6]  = (SIM_UIDMH >>  8) & 0xFF;
	unitUuidBytes[7]  = (SIM_UIDMH >>  0) & 0xFF;
	
	unitUuidBytes[8]  = (SIM_UIDML >> 24) & 0xFF;
	unitUuidBytes[9]  = (SIM_UIDML >> 16) & 0xFF;
	unitUuidBytes[10] = (SIM_UIDML >>  8) & 0xFF;
	unitUuidBytes[11] = (SIM_UIDML >>  0) & 0xFF;
	
	unitUuidBytes[12] = (SIM_UIDL >> 24) & 0xFF;
	unitUuidBytes[13] = (SIM_UIDL >> 16) & 0xFF;
	unitUuidBytes[14] = (SIM_UIDL >>  8) & 0xFF;
	unitUuidBytes[15] = (SIM_UIDL >>  0) & 0xFF;
	
	uuid_unparse (unitUuidBytes, unitUuid);
}

char* Get_Unit_UUID () {
	return unitUuid;
}
