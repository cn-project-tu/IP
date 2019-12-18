#include<stdio.h>
#include"ip_header.h"
#include"TCP_header.h"



int main()
{
    /********IP Packet filling ***************/
    struct ip_packet packet;
    packet->ipHdr.header_ver_len = IP_VER_HLEN;
    packet->ipHdr.service_esn=0x00;
    packet->ipHdr.total_length=htons(len);
    packet->ipHdr.ident=htons(ident_no);
    packet->ipHdr.flag_offset=0x00;
    packet->ipHdr.ttl=0x10;
    packet->ipHdr.protocol=IPPROTO_TCP;
    packet->ipHdr.checksum=14536;
    packet->ipHdr.src_addr=inet_addr("Enter your ip");
    packet->ipHdr.dest_addr=inet_addr("127.0.0.1");

    /***************Tcp packet filling *****************/
    packet->tcpHdr.source_port=htons(source_port);
    packet->tcpHdr.dest_port=htons(dest_port);
    packet->tcpHdr.sequ_number=1;
    packet->tcpHdr.ack_number=2;
    packet->tcpHdr.header_len=
    packet->tcpHdr.flag_bit=2;
    packet->tcpHdr.window_size=htons(512);
    packet->tcpHdr.checksum=8889;/**tcp checksum***/
    packet->tcpHdr.urgent_pointer=0;
    

    



}