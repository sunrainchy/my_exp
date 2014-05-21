#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <iostream>
#include <list>
using namespace std;
template <typename T1,typename T> void PRINT(T1 &co,T &value){
	typename T::iterator it;
	for(it=value.begin();it!=value.end();it++)
		co<<*it<<endl;
}
int all;
class pr{
	public:
		pr(int n):num(n){
		}
		int print(int l,int m){
			cout<<num<<' '<<l<<' '<<m<<endl;
		}
	private:
		int num;
};
class print{
	public:
		bool operator()(int a){
			cout<<a<<endl;
		}
};
class seq{
	public:
		int operator()(){
			return 2;
		}
};
int find_ans(int a){
	return a*a;
}
int main(){
	list<int> l;
	for(int i=0;i<10;i++) l.push_back(i);
	PRINT(cout,l);
	seq q;
	generate_n(back_inserter(l),4,q);
	PRINT(cout,l);
	return 0;
}
