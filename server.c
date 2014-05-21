#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#define LOCALPORT 4567


int   main(int argc,char *argv[])
{
    int s,len;
    struct sockaddr_in addr;
    int addr_len;
    char msg[256];
    int i=0;

    if (( s= socket(AF_INET, SOCK_DGRAM, 0) )<0)
    {
        perror("error");
        exit(1);
    }
    else
    {
        printf("socket created .\n");
        printf("socked id: %d \n",s);

        printf("remote port: %d \n",LOCALPORT);
    }

    len=sizeof(struct sockaddr_in);
	bzero(&addr,sizeof(addr));
	addr.sin_family=AF_INET;
    addr.sin_port=htons(LOCALPORT);
    addr.sin_addr.s_addr=htonl(INADDR_ANY);
    if(bind(s,(struct sockaddr *)&addr,sizeof(addr))<0){
		perror("connect...");
		exit(1);
	}
	else{
		printf("bind ok. \n");
		printf("local port:%d \n",LOCALPORT);
	}
    while (1){
		bzero(msg,sizeof(msg));
        len =sizeof(struct sockaddr_in);
        if ((i=recvfrom(s,msg,sizeof(msg),0,(struct sockaddr *)&addr,&len))==-1){
			printf("error receiving! \n");
			exit(1);
		}
		printf("The mseeage you recving is:%s \n",msg);
		if(msg[0]=='e'){return 0;}
		sendto(s,msg,sizeof(msg),0,(struct sockaddr *)&addr,len);
	}
}
