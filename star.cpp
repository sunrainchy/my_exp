#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
int map[11][11];
int count_now;//本次消灭个数
int total_score;//当前总分
int last_have;//最后剩余未消个数
int target_score;//本关目标分数
int level;//等级
int cal_score(int t)//根据消除的个数决定分数
{
	return t*(t*5);
}
int cal_target_score(int l)
{
	if(l<=5)
		target_score+=2000;
	else if(l<=10)
		target_score+=3000;
	else if(l<=15)
		target_score+=3500;
	else 
		target_score+=4000;
	return 0;
}
int cal_bonous(int t)
{
	if(t>=10)
		return 0;
	else
		return 2000-t*t*20;
}
bool check_one(int (*p)[11],int i,int j)//检查单个点是否符合消除的条件
{
	bool flag=false;
	if(i<0||i>=10||j<0||j>=10||map[i][j]==-1)
		return false;
	if(i-1>=0&&map[i-1][j]==map[i][j])
		flag=true;
	if(flag||(j+1<10&&map[i][j+1]==map[i][j]))
		flag=true;
	if(flag||(i+1<10&&map[i+1][j]==map[i][j]))
		flag=true;
	if(flag||(j-1>=0&&map[i][j-1]==map[i][j]))
		flag=true;
	return flag;
}
bool check_all(int (*p)[11])
{
	int i,j;
	for(i=9;i>=0;i--)
		for(j=0;j<10;j++)
			if(check_one(p,i,j))
				return true;
	return false;
}
int init()///////////////////////////////////////////////init
{
	int i,j;
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			map[i][j]=rand()%4;
	return 0;
}
int show(int (*map)[11])//////////////////////////////////print
{
	int i,j;
	for(i=0;i<10;i++)
	{
		printf("        %d ",9-i);
		for(j=0;j<10;j++)
			switch(map[i][j])
			{
				case -1:putchar(' ');putchar(' ');break;
				case 0:putchar('$');putchar(' ');break;
				case 1:putchar('&');putchar(' ');break;
				case 2:putchar('@');putchar(' ');break;
				case 3:putchar('#');putchar(' ');break;
			}
		putchar('\n');
	}
	printf("        + ");
	for(j=0;j<10;j++)
		printf("%d ",j);
	putchar('\n');
	return 0;
}
int clean(int (*p)[11],int i,int j ,int real)
{
	if(i<0||i>=10||j<0||j>=10)//其实没必要，但是效率要高一些
		return 0;
	//printf("OK:%d  %d\n",i,j);
	if(i-1>=0&&map[i-1][j]==real)
	{  count_now++;map[i-1][j]=-1; clean(p,i-1,j,real); }
	if((j+1<10&&map[i][j+1]==real))
	{count_now++; map[i][j+1]=-1; clean(p,i,j+1,real); }
	if((i+1<10&&map[i+1][j]==real))
	{count_now++; map[i+1][j]=-1; clean(p,i+1,j,real); }
	if((j-1>=0&&map[i][j-1]==real))
	{ count_now++; map[i][j-1]=-1; clean(p,i,j-1,real); }
	return 0;
}
int down(int (*p)[11])//上面的下来
{
	int i,j,c;
	for(j=0;j<10;j++)
	{
		c=0;
		for(i=9;i>=0;i--)
		{
			if(p[i][j]==-1)
				c++;
			else
				p[i+c][j]=p[i][j];
		}
		for(i=0;i<c;i++)
			p[i][j]=-1;
	}
	return 0;
}
int left(int (*p)[11])////向左看齐
	//在向下对齐之后向右就简单了
{
	int i=9,j=0,c=0;
	int x;
	for(j=0;j<10;j++)
	{
		if(p[i][j]==-1)
			c++;
		else
			for(x=0;x<10;x++)
				p[x][j-c]=p[x][j];
	}
	for(j=0;j<c;j++)
		for(i=0;i<10;i++)
			p[i][10-j-1]=-1;
	return 0;
}
int play_game(int(*p)[11])//////////////////////////////play
{
	int i,j;
	show(p);
	printf("请输入消除坐标:");
	char ch_i[20],ch_j[20];
	scanf("%s%s",ch_j,ch_i);
	if(strlen(ch_j)>1||strlen(ch_i)>1)
	{ printf("输入不合法，不符合条件\n"); return 0;} 
	else 
	{
		i=int(ch_i[0]-'0');
		j=int(ch_j[0]-'0');
	}
	i=9-i;
	if(check_one(p,i,j))
	{  printf("输入OK\n"); clean(p,i,j,p[i][j]);down(p); left(p); } 
	else 
		printf("输入不合法，不符合条件\n");
	return 0;
}
int main()
{
	bool flag_go_on=true;//判断是否继续
	target_score=1000;
	level=1;
	while(flag_go_on)
	{
		printf("begin new !\n\n\n\n");
		init();
		last_have=100;
		while(1)
		{
			count_now=0;
			play_game(map); 
			total_score+=cal_score(count_now);
			last_have-=count_now;
			if(!check_all(map))
			{
				total_score+=cal_bonous(count_now);
				if(total_score>=target_score)
				{ 
					printf("congrulations you win !\n");
					flag_go_on=true;
					level++;
					cal_target_score(level);
				}
				else
				{ 
					flag_go_on=false; printf("loser ! hahahahahahahahah...................\n");
				}
				printf("last_have:%d ,bonus:%d,total:%d\n",last_have,cal_bonous(last_have),total_score);

				break;
			}
			printf("clean star num:%d ,add:%d ,total:%d\n,level:%d ,target score:%d\n",count_now,cal_score(count_now),total_score,level,target_score);
		}
		show(map);
		sleep(10);
	}
	return 0;
}
