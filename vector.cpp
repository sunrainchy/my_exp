#include <stdio.h>
#include <deque>
#include <iostream>
using namespace std;
int main()
{
deque<int> d;
d.push_back(1);
d.push_back(2);
d.push_back(3);
//d.push_front(100);
//d.push_front(200);
cout<<d[0]<<' '<<d[1]<<' '<<d[2]<<endl;

}
