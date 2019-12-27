#include<netinet/tcp.h>
#include<netinet/ip.h>
#include"ip_header.h"
#include"check_sum.h"
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<error.h>
#include"packet.h"
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

#define PORT_NO 5002
#define SOURCE_IP "127.0.0.1"




int main(int argc,char **argv)
{
    int one=1;
    const int *val =&one;
    struct sockaddr_in sin;
    int s=socket(AF_INET,SOCK_RAW,IPPROTO_TCP);    //create a raw socket
    if (s==-1)
    {
        printf("socket creation failed ");
        exit(1);
    }
    char datagram[4096],sorce_ip[32],*data;     //datagram to represent the packet
    memset(datagram,0,4096);
    struct ip_header *iph = (struct ip_header *)datagram;

    struct tcp_header *tcph = (struct tcp_header *)(datagram + sizeof(iph));


    //Data part
    data = datagram + sizeof(struct ip_header) + sizeof(struct tcp_header);

    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORT_NO);
    sin.sin_addr.s_addr = inet_addr(SOURCE_IP);

    //fill the IP header

    //Fill the TCP header

    if(setsockopt(s,IPPROTO_IP,IP_HDRINCL,val,sizeof(one))<0)
    {
        printf("Error in setsocket ");
        exit(1);
    } 
    int buffer[100];
    int addrlen = sizeof(struct sockaddr_in);
    if(recvfrom(s,buffer,sizeof(buffer),0,(struct sockaddr *)&sin ,&addrlen)>0)
    {
        printf("Connection established ");
    }
    

}
         

    