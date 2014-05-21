#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <time.h>

int sockfd;
void close_sock(int signo){
   close(sockfd);
   printf("服务器退出\n");
   exit(0);
}
int main()
{
   /*1)创建socket, TCP协议*/
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   printf("服务开始启动,退出请按CTRL+C\n");
   signal(SIGINT, close_sock);
   /*2)准备地址,服务器端的地址*/
   struct sockaddr_in addr;
   addr.sin_family = AF_INET;
   addr.sin_port = htons(10222);
   addr.sin_addr.s_addr = inet_addr("127.0.0.1");
   /*3)绑定地址*/
   if(bind(sockfd, (struct sockaddr*)&addr, sizeof(addr))==-1)perror("绑定失败"),exit(-1);
   printf("绑定成功\n");
   /*4)监听*/
   if(listen(sockfd, 20))perror("监听失败"),exit(-1);
   printf("监听成功\n");
   while(1){
      /*5)响应(等待)客户端连接*/
      struct sockaddr_in fromaddr = {};
      socklen_t len = sizeof(fromaddr);//此就是要初始化
      //返回一个socket，并且和客户有连接关系
      int fd = accept(sockfd, (struct sockaddr*)&fromaddr, &len);
      if(fd==-1)perror("获取客户端连接失败");
      /*6)通信*/
      char buf[100] = {};
      if(read(fd, buf, sizeof(buf))<0)perror("读取数据出错");
      else printf("%s说:%s\n", inet_ntoa(fromaddr.sin_addr),buf);
      /*增加一个时间服务功能*/
      time_t cur = time(NULL);
      struct tm* cur_tm = localtime(&cur);
      char datebuf[20] = {};
      sprintf(datebuf, "%04d-%02d-%02d %02d:%02d:%02d",
              cur_tm->tm_year+1900,
              cur_tm->tm_mon+1,
              cur_tm->tm_mday,
              cur_tm->tm_hour,
              cur_tm->tm_min,
              cur_tm->tm_sec);
      char msg[100] = {};
      strcpy(msg, "现在时间是:");
      strcat(msg, datebuf);
      //if(write(fd, msg, strlen(msg)+1)<0)perror("发送数据错误");//
      /*7)关闭客户端socket*/
	  sleep(1);
      close(fd);
   }
   /*8)关闭服务器socket*/
}
