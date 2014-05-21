#include<iostream>
using namespace std;
#define MAX 51000
typedef struct
{
int left;
int right;
int sum;
point *next;
}point;
point tree[MAX*4];
int nCount=1;
/*void build(int l,int r,int root)//cong ling kai shi jian li 
{
tree[root].left
}*/
void BuildTree(CNode * pRoot,int L, int R)
{
	pRoot->L = L;
	pRoot->R = R;
	pRoot->sum= 0;
	if( L == R)
		return;
	nCount ++;
	pRoot->pLeft = Tree + nCount;
	nCount ++;
	pRoot->pRight = Tree + nCount;
	BuildTree(pRoot->pLeft,L,(L+R)/2);
	BuildTree(pRoot->pRight,(L+R)/2+1,R);
}
int main()
{

}
