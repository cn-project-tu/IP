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
#define DATAGRAM_LEN 4096
#define OPT_SIZE 20

#define URG_PACKET 0
#define ACK_PACKET 1
#define PSH_PACKET 2
#define RST_PACKET 3
#define SYN_PACKET 4
#define FIN_PACKET 5


void create_raw_datagram(char *pck, int *pcklen, int type,
		struct sockaddr_in *src, struct sockaddr_in *dst, 
		char *databuf, int len)
{
	uint32_t seq, ack;
	int poff, pldlen = 0;
	int16_t mss;

	/* Reserve empty space for storing the datagram. (memory already filled with zeros) */
	char *pld, *dgrm = calloc(DATAGRAM_LEN, sizeof(char));

	/* Required structs for the IP- and TCP-header */
	struct ip_* iph = (struct iphdr *)(dgrm);
	struct tcphdr* tcph = (struct tcphdr *)(dgrm + sizeof(struct iphdr));

	/* If the passes data-buffer contains more than the seq- and ack-numbers */
	if(len > 8) {
		/* The length of the pld is the length of the whole buffer */
		/* without the seq- and ack-numbers. */
		pldlen = len - 8;
	}

	/* Configure the IP-header */
	setup_ip_hdr(iph, src, dst, pldlen);

	/* Configure the TCP-header */
	setup_tcp_hdr(tcph, src->sin_port, dst->sin_port);

	/* Configure the datagram, depending on the type */
	switch(type) {
		case(URG_PACKET):
			break;
		
		case(ACK_PACKET):
			/* Set packet-flags */
			tcph->ack = 1;

			/* Set seq- and ack-numbers */
			memcpy(&seq, databuf, 4);
			memcpy(&ack, databuf + 4, 4);
			tcph->seq = htonl(seq);
			tcph->ack_seq = htonl(ack);
			break;
		
		case(PSH_PACKET):
			/* Set datagram-flags */
			tcph->psh = 1;
			tcph->ack = 1;

			/* Set pld according to the preset message */
			pld = dgrm + sizeof(struct iphdr) + sizeof(struct tcphdr) + OPT_SIZE;
			memcpy(pld, databuf + 8, len - 8);

			/* Set seq- and ack-numbers */
			memcpy(&seq, databuf, 4);
			memcpy(&ack, databuf + 4, 4);
			tcph->seq = htonl(seq);
			tcph->ack_seq = htonl(ack);
			break;
		
		case(RST_PACKET):
			break;
				
		case(SYN_PACKET):
			/* Set datagram-flags */
			tcph->syn = 1;

			poff = sizeof(struct ethhdr);

			/* TCP options are only set in the SYN packet */
			/* Set the Maximum Segment Size(MMS) */
			dgrm[poff + 40] = 0x02;
			dgrm[poff + 41] = 0x04;
			mss = htons(48);
			memcpy(dgrm + poff + 42, &mss, sizeof(int16_t));
			/* Enable SACK */
			dgrm[poff + 44] = 0x04;
			dgrm[poff + 45] = 0x02;
			break;

		case(FIN_PACKET):
			/* Set the datagram-flags */
			tcph->ack = 1;
			tcph->fin = 1;

			/* Set seq- and ack-numbers */
			memcpy(&seq, databuf, 4);
			memcpy(&ack, databuf + 4, 4);
			tcph->seq = htonl(seq);
			tcph->ack_seq = htonl(ack);
			break;
	}

	/* Calculate the checksum for both the IP- and TCP-header */
	tcph->check = in_cksum_tcp(tcph, src, dst, pldlen);
	iph->check = in_cksum((char*)dgrm, iph->tot_len);

	/* Convert the length of IP-header to big endian. */
	/* iph->tot_len = htons(iph->tot_len); */

	/* Return the created datagram */
	memcpy(pck, dgrm, DATAGRAM_LEN);
	*pcklen = iph->tot_len;
}




int main(int argc,char *argv[])
{
    if(argc !=5)
    {
        printf("less argument ");
        exit(-1);
    }
    // use for buffer containing the raw data gram for both when it recived and sent
    
    
    char *packet_buffer;
    int pck_len;
    struct ip_header ip_hdr;
    struct tcp_header tcp_hdr;
    // reserve memory for payload
    char *databuf;
    packet_buffer=calloc(PACK_LEN,sizeof(cahr));
    // initialize data buffer
    databuf=malloc(520);


    cahr *pld;
    int pldlen;
    pld=malloc(512);
    strcpy(pld,"DAta send");
    pldlen(strlen(pld)/sizeof(char))


    int ip_len=sizeof(struct ip_header)+sizeof(struct tcp_packet);
    int tcp_len=5;
    int ident_no=10;
    int source_port=htons(atoi(argv[2])),dest_port=htons(atoi(argv[4]));
    int port_no=80;
    int one=1;
    
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
    char buffer[PACK_LEN];
    struct ip_packet *packet=(struct ip_packet *)buffer;                   
    
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
    

    // configuration succefull
    memset(pckbuf, 0, DATAGRAM_LEN);
	create_raw_datagram(pckbuf, &pckbuflen, SYN_PACKET, &srcaddr, &dstaddr, NULL, 0);
    
    
    packet->ipHdr.header_ver_len = IP_VER_HLEN;
    packet->ipHdr.service_esn=0x00;         
    packet->ipHdr.total_length=htons(ip_len);
    packet->ipHdr.ident=htons(ident_no);          
    packet->ipHdr.flag_offset=0x0;                 
    packet->ipHdr.ttl=0x10;                 
    packet->ipHdr.protocol=0x06;            
    packet->ipHdr.checksum=0; 
    packet->ipHdr.src_addr=inet_addr(argv[1]);
    packet->ipHdr.dest_addr=inet_addr(argv[1]);
    
    
//  *************** TCP header filling ********************                                                            
    
    
    packet->tcp_packet.header.source_port=htons(atoi(argv[2]));
    packet->tcp_packet.header.dest_port=htons(atoi(argv[4]));
    packet->tcp_packet.header.sequ_number=htonl(1);               
    packet->tcp_packet.header.ack_number=0;           
    packet->tcp_packet.header.header_len=tcp_len;
    packet->tcp_packet.header.flag_bit=2;    //  check krna hai
    packet->tcp_packet.header.window_size=htons(1024);
    packet->tcp_packet.header.checksum=0;    //  tcp checksum Done by kernel
    packet->tcp_packet.header.urgent_pointer=0;
    
  // ******************* Ip header calculation *******************                     
    packet->ipHdr.checksum=ip_check_sum((uint16_t *)buffer,(sizeof(struct ip_header)+sizeof(struct tcp_header)));
    
    
    
  // **********************************************************
    
    
    
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
