#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int num[1000000];
int n;
void quicksort(int a[],int l,int r)
{
//cout<<"a";
bool flag=true;
if(l>=r)
return ;
int pos=l,L=l,R=r,ans=a[l];
while(L<R)
{
if(flag==true)
{
while(R>L&&a[R]>=a[pos])
R--;
if(R>L)
{
a[pos]=a[R];
pos=R;
flag=false;
}
}
else
{
while(L<R&&a[L]<=a[pos])
L++;
if(L<R)
{
a[pos]=a[l];
pos=L;
flag=true;
}
}
}
a[pos]=ans;
quicksort(a,l,pos-1);
quicksort(a,pos+1,r);
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
quicksort(num,0,n-1);
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
