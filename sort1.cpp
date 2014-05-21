#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int num[1000000];
int n;
int ans,pos,L,R;
int SORT(int *p,int l,int r)
{
if(l>=r)
return 0;
ans=p[l],pos=l,L=l,R=r;
while(L<R)
{
while(p[R]>=ans&&L<=R)
R--;
p[pos]=p[R];
pos=R;
R--;
while(p[L]<=ans&&L<=R)
L++;
p[pos]=p[L];
pos=L;
L++;
}
p[pos]=ans;
SORT(p,l,pos-1);
SORT(p,pos+1,r);
return 0;
}
int main()
{
int i;
int count,ans;
while(scanf("%d",&n)!=EOF)
{
count=1;
ans=0;
for(i=0;i<n;i++)
scanf("%d",&num[i]);
SORT(num,0,n-1);
/*for(i=0;i<n;i++)
cout<<num[i]<<' ';
cout<<endl;*/
for(i=1;i<n;i++)
{
if(num[i]==num[i-1])
count++;
else
count=1;
if(count>=n/2+1)
{ 
printf("%d\n",num[i]); 
break;
}
}
}
return 0;
}

