#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
struct time_lrc
{
int t;
char *lrc;
}music[100];
int main()
{
int fd;
int num,i,j,k;
int all_time[100];
int time_long,len_lrc;
char var[15];
int min,sec,macro;
char buffer[10000];
fd=open("music.lrc",O_RDONLY,10175);
num=read(fd,buffer,1500);
buffer[num]=0;
printf("%d %s",num,buffer);
i=0;
j=0;
while(buffer[i])
{
if(buffer[i]=='\n')
buffer[i]=0;
if(buffer[i]=='[')
{
strncpy(var,buffer+i,10);
var[10]=0;
sscanf(var,"[%d:%d.%d]",&min,&sec,&macro);
printf("%d %d %d\n",min,sec,macro);
music[j].t=min*1000*60+sec*1000+macro*10;
music[j].lrc=buffer+i+10;
j++;
}
i++;
}
for(i=0;i<j;i++)
if(music[i].t)
break;
usleep(music[i].t*1000);
for( ;i<j;i++)
{
if(music[i].t)
printf("time is %d   lrc is %s\n",music[i].t,music[i].lrc);
}
for(i=0;i<j;i++)
if(music[i].t)
break;
printf("%s",music[10].lrc);
for(i;i<j-1;i++)
{
time_long=music[i+1].t-music[i].t;
len_lrc=strlen(music[i].lrc);
time_long/=len_lrc;
printf("             ");
for(k=0;k<len_lrc;k++)
{
usleep(time_long*1000);
printf("%c",music[i].lrc[k]);
fflush(stdout);
}
printf("\n");
}
len_lrc=strlen(music[j-1].lrc);
for(k=0;k<len_lrc;k++)
{
usleep(time_long*1000);
printf("%c",music[i].lrc[k]);
fflush(stdout);
}
close(fd);
return 0;
}
