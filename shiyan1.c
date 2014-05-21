#include<stdio.h>
#include<iostream>
using namespace std;
char map[100][100];
int N,M,T;
int flag;
void DFS(int x,int y,int t)
{

//printf("Yes %d %d %d\n",x,y,t);
if(map[x][y]=='D'&&t==T)
{ flag=1;/* printf("OK :%d\n",t);*/return ;}
if(t>=T)
return ;
char old=map[x][y];
map[x][y]='X';
if(x-1>=0&&map[x-1][y]!='X')
DFS(x-1,y,t+1); 
if(y+1<M&&map[x][y+1]!='X')
DFS(x,y+1,t+1);
if(x+1<N&&map[x+1][y]!='X')
DFS(x+1,y,t+1);
if(y-1>=0&&map[x][y-1]!='X')
DFS(x,y-1,t+1);
map[x][y]=old;
}
int main()
{
int i,j,k;
int s_i,s_j;
while(scanf("%d%d%d",&N,&M,&T))
{
flag=0;
if(N==0&&M==0&&T==0)
break;
for(i=0;i<N;i++)
for(j=0;j<M;j++)
{
 cin>>map[i][j]; if(map[i][j]=='S') { s_i=i;s_j=j;}
}
//printf("haha :%d %d",s_i,s_j);
//map[s_i][s_j]='';
DFS(s_i,s_j,0);
if(flag==1)
printf("YES\n");
else
printf("NO\n");
}
return 0;
}
