#include<iostream>
#include<algorithm>
using namespace std;
template <typename T> class vector
{
private:
	T *vec;
	int num_of_elem;
	int size;
public:
	vector();
	vector(int s);//ŽŽœšÒ»žö³õÊŒvectorŽóÐ¡ÎªsµÄÊý×é
	vector(const vector<T> &copy);
	~vector();
	T back() const;//·µ»Ø×îºóÒ»žöÔªËØ
	bool push_back(const T &elem);
	int print() const;
	int get_size() const;
	T at(const int &inx) const;//Ž«»ØË÷ÒýidxËùÖžµÄÊýŸÝ£¬Èç¹ûidxÔœœç
	int clear() ;//Çå¿ÕÊý×éÔªËØ£¬µ«ÊÇ¿ÕŒä±£Áô
	bool empty() const;//ÅÐ¶ÏvectorÊÇ·ñÎª¿Õ
	int erase(const int &pos);//ÉŸ³ýposÎ»ÖÃµÄÊýŸÝ£¬Ž«»ØÏÂÒ»žöÊýŸÝµÄÎ»ÖÃ¡£
	int erase(const int &beg,const int &end);
	int pop_back();// ÉŸ³ý×îºóÒ»žöÔªËØ
	int reverse(int beg,int end);//·Ž×ªÏÂ±êbegºÍendÖ®ŒäµÄÔªËØ
	int reverse();//·Ž×ªËùÓÐÔªËØ
	int sort();//ÔªËØÅÅÐò
};
template <typename T> vector<T>::vector<T>():size(5),num_of_elem(0)
{
	cout<<"vector construct without argument "<<endl;
	vec=new T [5];
	return ;
}
template <typename T> vector<T>::vector<T>(int s):size(s),num_of_elem(0)
{
	cout<<"vector construct without one argument "<<endl;
	if(size<=0)
		size=5;
    vec=new T [size];
	return ;
}
template <typename T> vector<T>::vector(const vector<T> &copy)
{
size=copy.size;
vec=new T [size];
num_of_elem=copy.num_of_elem;
for(int i=0;i<num_of_elem;i++)
vec[i]=copy.vec[i];
}
template <typename T> vector<T>::~vector()
{
	delete [] vec;
}
template <typename T> int vector<T>::get_size() const
{
	return size;
}
template <typename T>bool vector<T>::push_back(const T &elem) 
{
	if(num_of_elem < size )
	{
		vec[num_of_elem]=elem;
		num_of_elem++;
	}
	else 
	{
		T *new_vec;
		new_vec=new T [size*2];//Èç¹û²»¹»ŸÍÖØÐÂÉêÇëÁœ±¶µÄ¿ÕŒä£¬Ä¿µÄÊÇÓÃ¿ÕŒä»»Ê±Œä£¬·ÀÖ¹ÖØžŽÉêÇë
        size*=2;
        for(int i=0;i<num_of_elem;i++)
		new_vec[i]=vec[i];
		new_vec[num_of_elem]=elem;
		num_of_elem++;
		delete [] vec;
		vec=new_vec;
	}
	return true;
}
template <typename T>int vector<T>::print() const
{
cout<<"size is:"<<size<<endl;
cout<<"num_of_elem is:"<<num_of_elem<<endl;
for(int i=0;i<num_of_elem;i++)
cout<<vec[i]<<' ';// ÕâÀïÄ¬ÈÏTÖ§³Ö<<
cout<<endl;
return 0;
}
template <typename T>T vector<T>::back() const
{
	if(num_of_elem<=0)
		return T(0);
	return vec[num_of_elem-1];
}
template <typename T> T vector<T>::at(const int &inx) const
{
if(inx<num_of_elem && inx>=0)
return vec[inx];
else 
return T(0);
}
template <typename T> int vector<T>::clear() 
{
	num_of_elem=0;
    return 0;
}
template <typename T> bool vector<T>::empty() const
{
	return num_of_elem==0;
}
template <typename T> int vector<T>::erase(const int &pos)
{
if(pos > num_of_elem || pos < 0 )
return 0;
if(pos==num_of_elem-1)
{
	num_of_elem--;
	return 0;
}
num_of_elem--;//Ò»¶šÒªÏÈŒõ
for(int i=pos;i<num_of_elem;i++)
vec[i]=vec[i+1];
if(pos==num_of_elem)
return 0;
else 
return pos;
}
template <typename T> int vector<T>::erase(const int &beg,const int &end)
{
if(beg>end||beg<0||end>=num_of_elem)
return 1;
for(int i=beg,j=end+1;j<num_of_elem;i++,j++)
vec[i]=vec[j];
num_of_elem-=(end-beg+1);
return 0;
}
template <typename T> int vector<T>::pop_back()
{
	if(num_of_elem>0)
		num_of_elem--;
	else
		 num_of_elem=0;
	return 0;
}
template <typename T> int vector<T>::reverse(int beg,int end)
{
T temp;
for(beg;beg<end;beg++,end--)
{
	temp=vec[beg];
	vec[beg]=vec[end];
	vec[end]=temp;
}
return 0;
}
template <typename T> int vector<T>::reverse()
{
	reverse(0,num_of_elem-1);
	return 0;
}
template <typename T> int my_cmp(const void *a,const void *b)
{
	return (*(T*)a) > (*(T*)a) ? 1 :-1;
}
int cmp ( const void *a , const void *b )
{
return *(int *)a - *(int *)b;
}
template <typename T> int vector<T>::sort()
{
qsort(vec,num_of_elem,sizeof(T),cmp);
return 0;
}
int main()
{
	vector<int>v;
	v.print();
	for(int i=0;i<10;i++)
		v.push_back(i);
		v.print();
		v.push_back(10000);
		v.print();
		cout<<"¿œ±Ž¹¹Ôìº¯Êý²âÊÔ"<<endl;
		vector<int> v1(v);
		v1.print();
		cout<<"v1×îºóÒ»žöÔªËØÊÇ:"<<v1.back()<<endl;
		cout<<"v1µÄµÚ8žöÔªËØÊÇ:"<<v1.at(7)<<endl;
		cout<<"erase(3,5)²âÊÔ:"<<endl;
		v1.erase(3,5);
		v1.print();
		cout<<"erase(3)²âÊÔ:"<<endl;
		v1.erase(3);
		v1.print();
		v1.clear();
		v1.print();
		v1.push_back(999);
		cout<<"v1.empty: "<<v1.empty()<<endl;
		v1.clear();
	    cout<<"v1.empty: "<<v1.empty()<<endl;
		cout<<"reverse(3,7)²âÊÔ:"<<endl;
		v.reverse(3,7);
		v.print();
		cout<<"reverse()²âÊÔ:"<<endl;
		v.print();
		v.reverse();
		v.print();
		cout<<"sort() ²âÊÔ:"<<endl;
        v.sort();
		v.print();
	    return 0;
}
