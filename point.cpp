#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
using namespace std;
#define MAX 110000
struct node
{
double x;
double y;
int index;
}X[MAX],Y[MAX];
bool cmp_x(const node &a,const node &b)
{
return a.x < b.x;
}
bool cmp_y(const node &a,const node &b)
{
return a.y < b.y;
}
double dis(node *a,node *b)
{
return sqrt((a->x-b->x)*(a->x-b->x)+(a->y-b->y)*(a->y-b->y));
}
double find_min(int a,int b,node *po)
{
double ans=1e10;
double v;
if(a+1==b)
{
v=dis(&po[a],&po[b]);
if(ans>v)
ans=v;
return ans;
}
if(a+2==b)
{
v=dis(&po[a],&po[b]);
if(ans>v)
ans=v;
v=dis(&po[a],&po[a+1]);
if(ans>v)
ans=v;
v=dis(&po[a+1],&po[b]);
if(ans>v)
ans=v;
return ans;
}
int mid=(a+b)/2;
node *XL,*XR;
XL=new node [mid-a+1];
XR=new node [b-mid];
int i,cntl=0,cntr=0;
for(i=0;i<=b-a;i++)
{
if(po[i].index<=mid)
XL[cntl++]=po[i];
else
XR[cntr++]=po[i];
}
ans=min(find_min(a,mid,XL),find_min(mid+1,b,XR));
double line=X[mid].x;
int ind,j;
for(i = 0, ind = 0; i <= b-a; ++i)
if (fabs(po[i].x - line) < ans)
po[ind++] = po[i];
for (i = 0; i < ind - 1; ++i)
{
for (j = i+1; j <= i+7 && j < ind; ++j)
{
double temp =dis(&po[i], &po[j]);
if (ans > temp)
ans = temp;
}
}

return ans;
}
int main()
{
int n,i,j,k;
while(scanf("%d",&n),n)
{
for(i=0;i<n;i++)
scanf("%lf%lf",&X[i].x,&X[i].y);
sort(X,X+n,cmp_x);
memcpy(Y,X,sizeof(X[0])*n);
sort(Y,Y+n,cmp_y);
printf("%.2lf\n",find_min(0,n-1,Y)/2);
}
return 0;
}
