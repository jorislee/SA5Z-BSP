#include <stdio.h> 
#include <string.h> 

//8 x 2 --> 16
#define MAKEUINT8(v1)             ((uint8_t)(v1))      //v1,v2 is UINT8
#define MAKEUINT16(v1,v2)         ((((uint16_t)(v1))<<8)|(uint16_t)(v2))      //v1,v2 is UINT8
//8 x 4 --> 32
#define MAKEUINT32(v1,v2,v3,v4)   ((((uint32_t)(v1))<<24)| \
                                  (((uint32_t)(v2)) <<16)| \
                                  (((uint32_t)(v3))  <<8)| \
                                  (uint32_t)(v4))

#define MAKEPUINT8(v1)          MAKEUINT8(*(v1))
#define MAKEPUINT16(v1)         MAKEUINT16(*(v1), *(v1 + 1))
#define MAKEPUINT32(v1)         MAKEUINT32(*(v1), *(v1 + 1), *(v1 + 2), *(v1 + 3))

#define MAKEUINT8P(p, v)     do { *((uint8_t*)(p)) = (v); } while(0)
#define MAKEUINT16P(p, v)    do { *((uint16_t*)(p)) = (v); } while(0)
#define MAKEUINT32P(p, v)    do { *((uint32_t*)(p)) = (v); } while(0)

//16 --> 8 x 2
#define HIBYTE(v1)              ((uint8_t)((v1)>>8))                      //v1 is UINT16
#define LOBYTE(v1)              ((uint8_t)((v1)&0xFF))
//32 --> 16 x 2
#define YBYTE1(v1)              ((uint16_t)((v1)>>16)&0xFFFF)                    //v1 is UINT32
#define YBYTE0(v1)              ((uint16_t)((v1)&0xFFFF))
//32 --> 8 x 4
#define TBYTE3(v1)              ((uint8_t)((v1)>>24)&0xFF)                     //v1 is UINT32
#define TBYTE2(v1)              ((uint8_t)((v1)>>16)&0xFF)
#define TBYTE1(v1)              ((uint8_t)((v1)>>8)&0xFF) 
#define TBYTE0(v1)              ((uint8_t)((v1)&0xFF))

#ifndef HEX2STR4
#define HEX2STR4(a) (a)[0], (a)[1], (a)[2], (a)[3]
#define HEXSTR4 "%02x%02x%02x%02"
#endif

#ifndef HEX2STR6
#define HEX2STR6(a) (a)[0], (a)[1], (a)[2], (a)[3], (a)[4], (a)[5]
#define HEXSTR6 "%02x%02x%02x%02x%02x%02x"

#endif
#ifndef HEX2STR16
#define HEX2STR16(a)  (a)[0], (a)[1], (a)[2], (a)[3], (a)[4], (a)[5], (a)[6],\
    (a)[7], (a)[8], (a)[9], (a)[10], (a)[11], (a)[12], (a)[13],\
    (a)[14],(a)[15]
#define HEXSTR16 "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x"
#endif

#ifndef MAC2STR
#define MAC2STR HEX2STR6
#define MACSTR "%02x:%02x:%02x:%02x:%02x:%02x"
#endif

#ifndef SM42STR
#define SM42STR HEX2STR16
#define SM4STR HEXSTR16
#endif

#ifndef IP4_2STR
#define U32IP4_2STR(a) TBYTE3(a), TBYTE2(a), TBYTE1(a), TBYTE0(a)
#define IP4_2STR HEX2STR4
#define IP4_STR "%u.%u.%u.%u"
#endif

#ifndef IP6_2STR
#define IP6_2STR HEX2STR16
#define IP6_STR "%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x"
#endif

#ifndef PORT2STR
#define PORT2STR MAKEPUINT16
#define PORT_STR "%u"
#endif
