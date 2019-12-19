#include<stdio.h>
#include<netinet/tcp.h>
#include<netinet/ip.h>
#include"ip_header.h"
#include<sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
   
    int ip_len=5,tcp_len=5;
    int ident_no=1;
    int source_port=5000,dest_port=80;
    int port_no;


    /********IP Packet filling ***************/
    struct ip_packet *packet;
    packet->ipHdr.header_ver_len = IP_VER_HLEN;
    packet->ipHdr.service_esn=0x00;
    packet->ipHdr.total_length=htons(ip_len);
    packet->ipHdr.ident=htons(ident_no);
    packet->ipHdr.flag_offset=0x00;
    packet->ipHdr.ttl=0x10;
    packet->ipHdr.protocol=IPPROTO_TCP;
    packet->ipHdr.checksum=14536;
    packet->ipHdr.src_addr=inet_addr("10.55.1.39");
    packet->ipHdr.dest_addr=inet_addr("127.0.0.1");

    /***************Tcp packet filling *****************/
    packet->tcp_packet->header.source_port=htons(source_port);
    packet->tcp_packet->header.dest_port=htons(dest_port);
    packet->tcp_packet->header.sequ_number=1;
    packet->tcp_packet->header.ack_number=2;
    packet->tcp_packet->header.header_len=htons(tcp_len);
    packet->tcp_packet->header.flag_bit=2;
    packet->tcp_packet->header.window_size=htons(512);
    packet->tcp_packet->header.checksum=8889;/**tcp checksum***/
    packet->tcp_packet->header.urgent_pointer=0;


     int tcp_socket=socket(AF_INET,SOCK_RAW,IPPROTO_RAW);
     struct sockaddr_in addr;
     addr.sin_family=AF_INET;
     addr.sin_port=htons(port_no);
     addr.sin_addr.s_addr =inet_addr("127.0.0.1");


     sendto(tcp_socket,&packet,sizeof(packet),0,(struct sockaddr *)&addr,sizeof(addr));

}
