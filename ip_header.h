#include <stdio.h>
#include<stdint.h>
#include <string.h>
#include <stdlib.h>
#include"TCP_header.h"
/*********************Data tyope ******************
uint8_t == 8 byte integer 
uint16_t == 16 byte integer
uint32_t == 32 byte integer
******************************************************/

struct ip_header 
{
    uint8_t   header_ver_len;   /* Header version 4 bit and header length 4. */ 
    uint8_t   service_esn;    /*DSCP(6) and ECN(2) Service type. */
    uint16_t  total_length;     /*total Length of datagram (16bytes). */
    uint16_t  ident;      /* Unique packet identification no (16bytes). */
    uint16_t  flag_offset;   /* Flags(2); Fragment offset(14) . */
    uint8_t   ttl; /* Packet time to live(8) (in network). */
    uint8_t   protocol;   /* Upper level protocol(8) (ipv4,UDP, TCP). */
    uint16_t  checksum;   /* IP header checksum(16). */
    uint32_t  src_addr;   /* Source IP address(32). */
    uint32_t  dest_addr;  /* Destination IP address(32). */

    //may not be used options are actually 32 byts not 32 bit
//    uint32_t  options;    /* options field(32) */
};

#define IP_VER_HLEN     0x45   //what is this
#define IP_HEADER_LEN   sizeof(ip_header)

#define MTU 1024
// we have to put the value of MTU
#define IP_DATA_LEN   (MTU - IP_HEADER_LEN)

//IP packet
struct ip_packet
{
    struct ip_header ipHdr;
    struct tcp_packet *tcp_packet;
};
