#include<iostream>
using namespace std;
#define size 262145
struct T
{
	int L,R;
	int count;
}tree[4*size];
int mun;
void build_tree(int k,int l,int r)
{
        tree[k].L=l;tree[k].R=r;
        tree[k].count=(r-l+1);
        if(l==r)
            return ;
            int mid=(l+r)>>1;
            build_tree(2*k,l,mid);
            build_tree(2*k+1,mid+1,r);
}
void delt(int k,int p)
{
    if(tree[k].L==tree[k].R)
        {
            mun=tree[k].R;
            tree[k].count--;
            return ;
            }
            if(p<=tree[2*k].count)
                delt(2*k,p);
                else
                delt(2*k+1,p-tree[2*k].count);
                tree[k].count--;
}
int main()
{
    int T,N,n,x;
   long long sum;
    while(cin>>T)
    {
        for(int i=1;i<=T;++i)
        {
            cin>>N>>n;
            sum=0;
            build_tree(1,1,N);
            for(int j=1;j<=n;++j)
            {
               cin>>x;
                delt(1,x);
                sum+=mun;
                }
                cout<<"Case "<<i<<": "<<sum<<endl;
            }
        }
    return 0;
    }
