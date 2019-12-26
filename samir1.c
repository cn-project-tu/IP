#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>

int main()
{
 int sockfd;
 struct sockaddr_in sin;
 int one=1;

 memset(datagram,0,4096);
 sockfd=socket(PF_INET,SOCK_RAW,IPPROTO_TCP);
 if(sockfd<0)
 {
  printf("Creation failed");
 }
 else
 {
  printf("Socket created");
 }
 
 
 sin.sin_family = AF_INET;
 sin.sin_port = htons(DES_PORT);
 sin.sin_addr.s_addr = inet_addr(IP_ADD);

 if(setsocketopt(sockfd, IPPROTO_IP, IP_HDRINCL,&one,sizeof(one)) ==-1)
 {
  printf("setsockopt() is failed");
  exit(1);
 }

 
 recv(sockfd,datagram,sizeof(datagram),0);
 printf("Receiving data");
 
}