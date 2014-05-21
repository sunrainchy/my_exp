#include<stdio.h>
#include<string.h>
int num[262145];
int order[262145];
int main()
{
int i,j,k;
int T,N,K,t;
int count;
int ans;
scanf("%d",&T);
for(t=0;t<T;t++)
{
ans=0;
scanf("%d%d",&N,&K);
for(i=0;i<=N;i++)
num[i]=i;
for(i=0;i<K;i++)
{
count=0;
scanf("%d",&order[i]);
for(j=0;j<i;j++)
if(order[j] <= order[i])
count++;
order[i]+=count;
ans+=num[order[i]];
}

printf("Case %d: %d\n",t+1,ans);
}
return 0;
}

