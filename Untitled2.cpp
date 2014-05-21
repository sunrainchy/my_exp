/*
题目大意：在一条水平线上有N个建筑物，建筑物都是长方形的，且可以互相遮盖。给出每个建筑物的左右坐标值Ai,Bi以及每个建筑物的高度Hi，
		：需要计算出这些建筑物总共覆盖的面积。
题目解答：由于Ai，Bi∈[1,1000000000]，直接将线段[Ai,Bi]插入线段树空间消耗太大，
		：可以将这n条线段的2n个端点离散化到一个数组X[0...2n-1]，

Source Code

Problem: 3277  User: wawadimu
Memory: 4188K  Time: 282MS
Language: C++  Result: Accepted

Source Code
*/
#include<iostream>
#include<algorithm>
using namespace std;

#define maxn 40010

struct Node  //区间[l,r]内 h = 房子的最高值
{
	int l,r,h;
}tree[7*maxn];//开小了就运行出错，不知为什么3倍不行

struct XX   //原始数据(左右坐标，高度)
{
	int ai,bi,h;
}res[maxn];

int t[2*maxn];//原始坐标
int hash[maxn];//离散化坐标--空间压缩
void built(int num,int L ,int R);//建立线段树
void insert(int num,int L ,int R,int H);//维护线段树
int query(int L, int R ,int t);//查找离散化的区间
long long  Count(int num);//统计面积

int cmp ( XX a, XX b)//按告诉从小到大排列
{
	return a.h < b.h;
}

int main()
{
	//freopen("3277.txt","r",stdin);
	int n , len , i , j , k ;
	int ai , bi , h ;
	int cnt;
	while(scanf("%d",&n)!=EOF)
	{
		k=0;
		for(i=0; i<n; i++)
		{
			scanf("%d%d%d",&ai,&bi,&h);
			t[k++]=ai; t[k++]=bi;
			res[i].ai=ai; res[i].bi=bi; res[i].h=h;
		}
		sort( t , t+k );//排序
		sort( res, res+ n ,  cmp);//高度排序
		cnt=0;
		hash[cnt++]=t[0];
		for(i=1 ; i<k ;i++)//离散化
		{
			if(t[i] != t[i-1]) hash[cnt++]=t[i];
		}
		cnt--;
		//for(i=1;i<=cnt;i++)   cout<<hash[i]<<" ";cout<<endl;
		built(1,0,cnt);
		for(i=0; i <n ; i++)
		{
			int l=query(0, cnt , res[i].ai),
				r=query(l, cnt , res[i].bi);
			insert(1,l,r,res[i].h);//更新区间[l,r]的数据 h
		}
		long long  ans=Count(1);
		printf("%lld/n",ans);

	}
	return 0;
}
void built(int num,int L, int R)
{

	tree[num].l=L ; tree[num].r=R;//cout<<L<<":"<<R<<"  ";
	tree[num].h=-1;//区间未覆盖
	if(L+1 == R) {  return ;}
	else
	{
		int M=(L+R)>>1;
		built(2*num,L,M);
		built(2*num+1,M,R);
	}
}
void insert(int num, int L, int R ,int H)
{
	//cout<<L<<":"<<R<<"="<<H<<"->"<<tree[num].l<<tree[num].r<<" "<<tree[num].h<<"   ";
	if(H <= tree[num].h) return;
	if(L==tree[num].l && R==tree[num].r ) { tree[num].h=H; return;}
	if(tree[num].h >=0 && tree[num].l +1 != tree[num].r)
	{    tree[2*num].h=tree[2*num+1].h=tree[num].h;  tree[num].h=-1; }
	int M=(tree[num].l+tree[num].r)>>1;
	if( R <= M)      {  insert( 2*num   , L , R , H ); }
	else if( L >=M ) {  insert( 2*num+1 , L , R , H ); }
	else             {  insert( 2*num   , L , M , H );
						insert( 2*num+1 , M , R , H ); }
}
int query(int L, int R ,int d)
{
	int mid,l=L,r=R;
	while( l<= r)
	{
		mid=(l+r)>>1;
		if( d==hash[mid] ) return mid;
		else if(hash[mid] > d) r=mid-1;
		else l=mid+1;
	}
	return -1;
}
long long Count(int num)
{
	if(tree[num].l +1 == tree[num].r && tree[num].h < 0) return 0;
	if(tree[num].h >0) return tree[num].h*(long long )(hash[tree[num].r]-hash[tree[num].l]);
	else return Count(2*num) + Count(2*num+1);
}
