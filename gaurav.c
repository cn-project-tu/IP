#include<netinet/tcp.h>
#include<netinet/ip.h>
#include"ip_header.h"
#include"check_sum.h"
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<error.h>

//#include <linux/if_packet.h>
#include <net/ethernet.h>

#include <sys/types.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include<sys/ioctl.h>
#include<net/if.h>

#include<netpacket/packet.h>
#include<getopt.h>

#include<time.h>

#define PACK_LEN 8192
int main(int argc,char *argv[])
{
    if(argc !=5)
    {
        printf("less argument ");
        exit(-1);
    }
    // use for buffer containing the raw data gram for both when it recived and sent

    int ip_len=sizeof(struct ip_header)+sizeof(struct tcp_packet);
    int tcp_len=5;
    int ident_no=10;
    int source_port=htons(atoi(argv[2])),dest_port=htons(atoi(argv[4]));
    int port_no=80;
    int one=1;
    struct ifreq ifr;
    struct sockaddr_ll sll;
    memset(&sll,0,sizeof(sll));
    
    int tcp_socket;
    tcp_socket=socket(PF_INET,SOCK_RAW,IPPROTO_UDP);
    if(tcp_socket<0)
    {
        perror("Error in creating socket......");
        exit(-1);
    }
    else
    {
        printf("Raw Socket created...%d.......\n",tcp_socket);
    }
  //  ********IP Packet filling *************** /
    struct ip_packet *packet;                   
    
    memset(buffer,0,PACK_LEN);
    //configure source address
    struct sockaddr_in source_addr,dest_addr;
    source_addr.sin_family=AF_INET;
    source_addr.sin_port=source_port; 
    source_addr.sin_addr.s_addr =inet_addr(argv[1]);
    if(inet_pton(AF_INET,argv[1],&source_addr.sin_addr)!=1){
        perror("Error in src-ip");
        exit(-1);
       }else{ printf("source address ok:\n"); }
    // configure destination address
    dest_addr.sin_family=AF_INET;
    dest_addr.sin_port=dest_port; 
    dest_addr.sin_addr.s_addr =inet_addr(argv[1]);
    if(inet_pton(AF_INET,argv[3],&source_addr.sin_addr)!=1){
        perror("Error in dest-ip");
        exit(-1);
    }
    else
    { printf("dest address ok:\n"); }
    
    // configuration succefull
    
    
    
    packet->ipHdr->header_ver_len = IP_VER_HLEN;
    packet->ipHdr->service_esn=16;         
    packet->ipHdr->total_length=sizeof(struct ip_header)+sizeof(struct tcp_packet);
    packet->ipHdr->ident=htons(54321);          
    packet->ipHdr->flag_offset=0;                 
    packet->ipHdr->ttl=64;                 
    packet->ipHdr->protocol=6;            
    packet->ipHdr->checksum=0; 
    packet->ipHdr->src_addr=inet_addr(argv[1]);
    packet->ipHdr->dest_addr=inet_addr(argv[3]);
    
    
//  *************** TCP header filling ********************                                                            
    
    
    packet->tcpHdr->source_port=htons(atoi(argv[2]));
    packet->tcpHdr->dest_port=htons(atoi(argv[4]));
    packet->tcpHdr->sequ_number=htonl(1);               
    packet->tcpHdr->ack_number=0;           
    packet->tcpHdr->header_len=tcp_len;
    packet->tcpHdr->bit_sin=1;
    packet->tcpHdr->bit_fin=0;
    packet->tcpHdr->window_size=htons(1024);
    packet->tcpHdr->checksum=0;    //  tcp checksum Done by kernel
    packet->tcpHdr->urgent_pointer=0;
    
  // ******************* Ip header calculation *******************                     
    packet->ipHdr->checksum=ip_check_sum((uint16_t *)buffer,(sizeof(struct ip_header)+sizeof(struct tcp_header)));
    
    fgets(packet->data,1024,stdin);
    
  // **********************************************************
    
    printf("configure socket\n");
    int setsock_no=setsockopt(tcp_socket,IPPROTO_IP,IP_HDRINCL,&one,sizeof(one));
    if(setsock_no<0)
    {
        perror("Error..........in setsockopt()\n");
        exit(-1);
    }
    else
    {
        printf("setsockopt() is OK......:\n");
    }
    
    
    
//    ***************************************************************
    
    
    
    
    int send_no=sendto(tcp_socket,&packet,sizeof(packet),0,(struct sockaddr *)&source_addr,sizeof(source_addr));
    if(send_no<0)
    {
        perror("errro in sending........:\n");
        exit(-1);
    }
    else
    {
        printf("message sending succes.....:\n");
        sleep(2);
    }
    
    close(tcp_socket);
    return 0;
}