/*
 * AddressSerialization.h
 *
 *  Created on: Mar 2, 2016
 *      Author: thebh_000
 */

#ifndef SOURCES_MESSAGE_ADDRESSSERIALIZATION_H_
#define SOURCES_MESSAGE_ADDRESSSERIALIZATION_H_

#include "PE_Types.h"

///Copied typedefs from lwip/inet.h, sockets.h
typedef uint8_t u8_t;
typedef int8_t s8_t;
typedef uint16_t u16_t;
typedef int16_t s16_t;
typedef uint32_t u32_t;
typedef int32_t s32_t;

/* If your port already typedef's in_addr_t, define IN_ADDR_T_DEFINED
 to prevent this code from redefining it. */
#if !defined(in_addr_t) && !defined(IN_ADDR_T_DEFINED)
typedef u32_t in_addr_t;
#endif

/** For compatibility with BSD code */
struct in_addr
{
      in_addr_t s_addr;
};

#if !defined(sa_family_t) && !defined(SA_FAMILY_T_DEFINED)
typedef u8_t sa_family_t;
#endif

/* If your port already typedef's in_port_t, define IN_PORT_T_DEFINED
 to prevent this code from redefining it. */
#if !defined(in_port_t) && !defined(IN_PORT_T_DEFINED)
typedef u16_t in_port_t;
#endif

/* members are in network byte order */
struct sockaddr_in
{
      u8_t sin_len;
      sa_family_t sin_family;
      in_port_t sin_port;
      struct in_addr sin_addr;
#define SIN_ZERO_LEN 8
      char sin_zero[SIN_ZERO_LEN];
};
///End copied typedefs from lwip/inet.h, sockets.h

uint32_t Serialize_Address(struct sockaddr_in * Source, uint8_t* Destination, uint32_t DestinationLength);
void Deserialize_Address(uint8_t* Source, uint32_t SourceLength, struct sockaddr_in * Destination);

#endif /* SOURCES_MESSAGE_ADDRESSSERIALIZATION_H_ */
