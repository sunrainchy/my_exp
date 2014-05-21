#include<iostream>
#include<stdio.h>
using namespace std;
int a,b;
int num[100001];
int ans;
bool flag;
int init()
{
for(int i=0;i<100001;i++)
num[i]=i;
return 0;
}
/*
int find(int i)
{
    return num[i] == i ? i : find(num[i]);
}
int find(int x) 
{   
      if(num[x] == x)  
      {        return x;    }
      return num[x] = find(num[x]);
}*/
//非递归版路径压缩
int find (int n) {//r->root   
       int r = n;    
       while (r != num[r]) {//寻找根结点        
       r = num[r];  
       }    
        int x = n, y;    
        while (x != r) {//压缩路径，全部赋值为根结点的值        
         y = num[x];      
         num[x] = r;     
         x = y;    
       }   
     return r;
}

int merge(int x,int y)
{
    int fx,fy;
    fx = find(x);
    fy = find(y);
    if(fx != fy)
        num[fx] = fy;
return 0;
}
int main()
{
int n,m;
int u,v,w;
ans=0;
while(scanf("%d%d",&n,&m))
{
flag=true;
while(m--)
{
scanf("%d%d%d",&u,&v,&w);
merge(u,v);
ans+=w;
if(flag&&find(u)==find(v))
{
cout<<"YES"<<endl;
flag=false;
}

}
if(flag)
cout<<ans<<endl;
}
return 0;
}
