#include<sys/types.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/socket.h>
#include<stdio.h>
#define MY_PORT 4000
extern int errno;
struct sockaddr_in my_addr;
int main()
{
int net;
if(net=socket(AF_INET,SOCK_STREAM,0)==-1)
printf("errno happen\n");
my_addr.sin_family=AF_INET;
my_addr.sin_port=htons(5678);
my_addr.sin_addr.s_addr=htonl(INADDR_ANY);//0;//inet_addr("192.168.1.122");
bzero(&(my_addr.sin_zero),8);
if(bind(net,(struct sockaddr*)&my_addr,sizeof(struct sockaddr))==-1)
printf("bind errno \n");//perror(errno);}

if(close(net)==-1)
printf("close errno \n");
//perror(errno);
printf("socket yes\n");
return 0;
}
