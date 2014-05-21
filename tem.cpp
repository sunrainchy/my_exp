#include<iostream>
#include<ostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;
/*template <typename  T> class myclass
{
private:
T x;
T y;
public:
myclass(T a,T b):x(a),y(b)
{
cout<<"this is construct function"<<endl;
}
T print();
~myclass()
{
cout<<"xigou function"<<endl;
}
};
template <typename T1> T1 myclass<T1>::print()
{
cout<<x<<' '<<y<<endl;
return T1(0);
}

int main()
{
int a;
myclass<int> c(0,0);
c.print();
return 0;
}*/
int main()
{
vector<string> v;
string tem;
while(getline(cin,tem))
v.push_back(tem);
sort(v.begin(),v.end());
copy(v.begin(),v.end(),ostream_iterator<string>(cout,"\n"));
return 0;
}
