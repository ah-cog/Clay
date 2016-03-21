/*
 * AddressSerialization.h
 *
 *  Created on: Mar 2, 2016
 *      Author: thebh_000
 */

#ifndef SOURCES_MESSAGE_ADDRESSSERIALIZATION_H_
#define SOURCES_MESSAGE_ADDRESSSERIALIZATION_H_

#include "PE_Types.h"

////defines ///////////////////////////////////////////////////////
#define CLAY_MESSAGE_TYPE_STRING_MAX_LENGTH     16

///Copied definitions from lwip/inet.h, sockets.h
#define AF_INET    2

#define htons(x) lwip_htons(x)
#define ntohs(x) lwip_ntohs(x)
#define htonl(x) lwip_htonl(x)
#define ntohl(x) lwip_ntohl(x)

#define lwip_htons(x) LWIP_PLATFORM_HTONS(x)
#define lwip_ntohs(x) LWIP_PLATFORM_HTONS(x)
#define lwip_htonl(x) LWIP_PLATFORM_HTONL(x)
#define lwip_ntohl(x) LWIP_PLATFORM_HTONL(x)

#define LWIP_PLATFORM_HTONS(_n)  ((u16_t)((((_n) & 0xff) << 8) | (((_n) >> 8) & 0xff)))
#define LWIP_PLATFORM_HTONL(_n)  ((u32_t)( (((_n) & 0xff) << 24) | (((_n) & 0xff00) << 8) | (((_n) >> 8)  & 0xff00) | (((_n) >> 24) & 0xff) ))

////Typedefs  /////////////////////////////////////////////////////

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

typedef enum
{
   MESSAGE_TYPE_UDP,
   MESSAGE_TYPE_TCP,
   MESSAGE_TYPE_COMMAND,
   MESSAGE_TYPE_INFO,
   MESSAGE_TYPE_MAX
} Message_Type;

////Globals   /////////////////////////////////////////////////////
//max 16 chars
extern uint8_t* message_strings[];
extern const char * address_terminator;

////Prototypes/////////////////////////////////////////////////////
extern void Deserialize_Address(uint8_t* Source, uint32_t SourceLength, struct sockaddr_in * Destination, Message_Type *type);
extern uint32_t Serialize_Address(struct sockaddr_in * Source,
                                  uint8_t* Destination,
                                  uint32_t DestinationLength,
                                  Message_Type ConnectionTypeStr);

extern bool Get_Message_Type_Str(Message_Type type, uint8_t *returnStr);
extern Message_Type Get_Message_Type_From_Str(uint8_t*typeString);

extern uint8_t * inet_ntoa(const in_addr_t * addr);
extern int inet_aton(const uint8_t * cp, in_addr_t * addr);

#endif /* SOURCES_MESSAGE_ADDRESSSERIALIZATION_H_ */
