#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
   /*1)创建socket, TCP协议*/
   int sockfd = socket(AF_INET, SOCK_STREAM, 0);
   /*2)准备地址,需要连接到服务器端的地址*/
   struct sockaddr_in addr;
   addr.sin_family = AF_INET;
   addr.sin_port = htons(10222);
   addr.sin_addr.s_addr = inet_addr("127.0.0.1");
   /*3)连接到服务器*/
   if(connect(sockfd, (struct sockaddr*)&addr, sizeof(addr))==-1)perror("连接服务器失败"),exit(-1);
   /*4)通信*/
  // write(sockfd, "Hello Server", strlen("Hello Server")+1);//
   char buf[100] = {};
 //  read(sockfd, buf, sizeof(buf));//
   printf("%s\n", buf);
   /*5)关闭*/
   close(sockfd);
}
