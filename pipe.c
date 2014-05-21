#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<errno.h>
#include<stdlib.h>
int main()
{
char buffer[256];
pid_t pid;
int num;
int fd[2];
pipe(fd);
pid=fork();
if(pid==0)
{
printf("this is child %d\n my father is %d\n",getpid(),getppid());
close(fd[1]);
num=read(fd[0],buffer,sizeof(buffer));
printf("read %s   %d\n",buffer,num);
sleep(2);
}
else 
{
close(fd[0]);
printf("this is father %d\n",getpid());
num=write(fd[1],"hello chy ",strlen("hello chy ")+1);

printf("write %s    %d\n",buffer,num);
}
return 0;
}
