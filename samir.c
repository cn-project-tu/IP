#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<errno.h>
#include<netinet/tcp.h>
#include<netinet/ip.h>
#include"samir.c"

#define PORT_NO 
#define SOURCE_IP



/** IP structure header **/

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

/** TCP structure header **/ 
struct tcp_header
{
 uint16_t source_port;  //source port(16)
 unit16_t dest_port;  //Destination port(16)
 unit32_t sequ_number;  //dequence number(32)
 unit32_t ack_number; //acknowledgement number(32)
 unit8_t header_len;  //(4)header length-(4)reserved bit
 //unit3_t res; //reserved bit
 unit8_t flag_bit ;//2 bit reserved URG,ACK,PSH,RSH,SYN,FIN each are of 1 bit
 unit16_t window_size; //receiver advertise window size(16)
 unit16_t checksum;  //checksum(16) to be computed
 unit16_t urgent_pointer;//points to urgent data byte(16) if URG flag_bit set to 1

/*it may be possible option file be required */

 //unit32_t options;//option field may not be 32 so to compromise the remaining
                   //bits we can use padding
};



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

    struct sockaddr_in sin;

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
         

    