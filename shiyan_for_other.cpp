#include <iostream>
#include <string.h>
#include <stdio.h>
int is_load;
using namespace std;
template <typename T> class linklist//单向链表类模板
{
	//这里没设置为私有的原因是不需要对链表进行隐藏，我们隐藏的是patient和medical_rec的信息
	public:
		T temp;
		linklist<T> *next;
		linklist();
		int insert_after_head(linklist<T> &node);//将node节点插到头节点之后，也就是插入完成之后变成病历链表第二个节点
};
/* 
 *病历
 */
class medical_rec//病历
{
	private:
		char name[30];//name
		char date[30];//日期 格式为2013-06-25
		char subject[30];//科别，字符串表示
		char check[100];//体检信息，未知
		char other[500];//些其它信息，方便扩展
	public:
		medical_rec();
		int write_file(FILE *fd)
		{
			fprintf(fd,"%s %s %s %s ",name,date,subject,check);
			return 0;
		}
		int load_file(FILE *fd)
		{
			fscanf(fd,"%s %s %s %s ",name,date,subject,check);
			return 0;
		}
		friend ostream &operator<<(ostream &out,const medical_rec &me);//重载输出运算符
		friend istream &operator>>(istream &in,medical_rec &me);//重载输入运算符
		char* get_name(){ return name;}
};

/*
 *patient
 */
class patient
{
	private:
		static int num;// 静态成员变量记录病人的总数量；
		int num_case;//记录该病人病历的条数
		char name[30];//name
		int age;//age
		int sex;//0 man 1 women
		char adress[200];//这个记录家庭住址，因为字数不限制，所以要动态申请
	public:
		linklist<medical_rec> med;//这个是表示每个病人可能会有多个病历
		patient();
		static int add_num(){ num++; return 0;};
		static int get_num(){ return num;}
		static int set_num(int k){ num=k;return 0;}
		int add_case_num(){ num_case++; return 0;}
		int get_num_case(){return num_case;}
		int write_file(FILE *fd)
		{
			fprintf(fd,"%d %s %d %d %s ",num_case,name,age,sex,adress);
			return 0;
		}
		int load_file(FILE *fd)
		{
			fscanf(fd,"%d%s%d%d%s ",&num_case,name,&age,&sex,adress);
			return 0;
		}
		char* get_name(){ return name;}
		friend ostream &operator<<(ostream &out,const patient &pa);//重载输入操作符
		friend istream &operator>>(istream &in,patient &pa);//重载输入操作符
		int show_patient();
		int insert_after_head(linklist<medical_rec> &node) { med.insert_after_head(node); return 0;}
};
/**********************************************************patient***************************************************/
int patient::num=0;

patient::patient():num_case(0),age(0),sex(0)
{
	med.next=NULL;
	name[0]=0;//初始化为空
	adress[0]=0;//初始化为空
}

ostream &operator<<(ostream &out,const patient &pa)
{
	out<<"病人姓名："<<pa.name<<endl;
	out<<"性别："<<(pa.sex==0 ? "男" : "女")<<endl;
	out<<"该病人病历条数目："<<pa.num_case<<endl;
	out<<"年龄："<<pa.age<<endl;
	if(strlen(pa.adress)>0)
		out<<"家庭住址："<<pa.adress<<endl;
	return out;
}

istream &operator>>(istream &in,patient &pa)
{
	cout<<"请输入姓名:";
	in>>pa.name;
	cout<<"请输入性别(0 man 1 women):";
	in>>pa.sex;
	cout<<"请输入年龄:";
	in>>pa.age;
	cout<<"请输入家庭住址:";
	in>>pa.adress;
	return in;
}
int patient::show_patient()
{
	cout<<*this;
	return 0;
}

/*************************************************medical_rec*********************************************************/

medical_rec:: medical_rec()
{
	name[0]=0;
	strcmp(date,"1700-01-01");//设置默认时间
	subject[0]=0;
	check[0]=0;
	other[0]=0;
}

ostream &operator<<(ostream &out,const medical_rec &me)
{
	out<<"姓名："<<me.name<<endl;
	out<<"日期："<<me.date<<endl;
	out<<"科目："<<me.subject<<endl;
	out<<"体检信息："<<me.check<<endl;
	if(strlen(me.other)>0)
		cout<<"其他信息："<<me.other<<endl;
	return out;
}

istream &operator>>(istream &in,medical_rec &me)
{
	cout<<"请输入日期：";//这里病历不需要输入姓名，因为姓名已经有了！
	in>>me.date;
	cout<<"请输入科目：";
	in>>me.subject;
	cout<<"请输入体检信息：";
	in>>me.check;
	return in;
}
/************************************************linklist****************************************************************/
template <typename T> linklist<T>::linklist()
{
	next=NULL;
}
template <typename T> int linklist<T>::insert_after_head(linklist<T> &node)
{
	node.next=next;
	next=&node;
	return 0;
}
/***********************************************function*****************************************************************/
linklist<patient> pati;//定义一个病人的链表，每个病人内部内嵌一个病历链表
int init()
{
	is_load=0;
	return 0;
}
int function_1()
{
	linklist<patient> *pa=new linklist<patient>();
	cin>>pa->temp;
	pati.insert_after_head(*pa);
	return 0;
}
linklist<patient> * find_patient_name(linklist<patient> &pa,char *name);
int function_7()
{
	linklist<patient> *head;
	char name[50];
	cout<<"请输入你要添加病历的患者姓名:";
	cin>>name;
	head=find_patient_name(pati,name);
	head->temp.add_case_num();
	if(head==NULL)
	{ 
		cout<<"病人"<<name<<"不存在"<<endl;
		return 0;
	}
	linklist<medical_rec> *rec=new linklist<medical_rec>();
	cin>>rec->temp;
	head->temp.insert_after_head(*rec);
	return 0;
}
linklist<patient> * find_patient_name(linklist<patient> &pa,char *name)
{
	linklist<patient> *head;
	head=pa.next;
	while(head)
	{
		if(strcmp(name,head->temp.get_name())==0)
			return head;
		head=head->next;

	}
	return NULL;
}
int show_patient(linklist<patient> &pa)
{
	linklist<patient> *head=&pa;
	head=head->next;//注意这里head一定有next，因为第一个是头，第二个才是正式信息
	while(head)
	{
		head->temp.show_patient();
		head=head->next;
	}
	return 0;
}
int function_8(char *name)//显示名为name的病人的所有相关信息
{
	linklist<patient> *head;
	linklist<medical_rec> *head_rec;
	head=find_patient_name(pati,name);
	if(head==NULL)
	{
		cout<<"病人"<<name<<"不存在"<<endl;
		return 0;
	}
	head_rec=head->temp.med.next;
	cout<<head->temp;
	cout<<"病历:"<<endl;
	if(head_rec==NULL)
	{
		cout<<"无此人任何病历"<<endl;
	}
	while(head_rec)
	{
		cout<<head_rec->temp;
		head_rec=head_rec->next;
	}
	return 0;
}
int function_2()//显示所有病人的信息
{
	linklist<patient> *head=pati.next;
	if(head==NULL)
	{
		cout<<"暂时还没任何病人"<<endl;
		return 0;
	}
	while(head)
	{
		function_8(head->temp.get_name());
		head=head->next;
	}
	return 0;
}
int function_3()//把pati中的内容全部写入文件中
{
	FILE *fd;
	fd=fopen("data.txt","w+");
	if(fd==NULL)
	{
		cout<<"文件打开失败\n";
		return 0;
	}
	linklist<patient> *head=pati.next;
	linklist<medical_rec> *head_rec;
	fprintf(fd,"%d ",patient::get_num());//输入一共有多少病人
	while(head)
	{
		head->temp.write_file(fd);
		head_rec=head->temp.med.next;
		while(head_rec)
		{
			head_rec->temp.write_file(fd);
			head_rec=head_rec->next;
		}
		head=head->next;
	}
	cout<<"文件存储成功\n";
	fclose(fd);
	return 0;
}
int function_4()//文件读取
{
	int k;
	if(is_load==0)
		is_load=1;
	else
	{
		//printf("装载成功\n");//这里保证整个程序运行过程中只有一次装载，目的是内存和文件分开
		return 0;
	}
	FILE *fd;
	fd=fopen("data.txt","r+");
	if(fd==NULL)
	{
		cout<<"文件打开错误"<<endl;
		return 0;
	}
	if(feof(fd)==0)
	{
		cout<<"数据文件为空"<<endl;
		return 0;
	}

	int num,j,i;
	fscanf(fd,"%d",&num);
	patient::set_num(num);
	linklist<patient> *pa;//=new linklist<patient>();
	linklist<medical_rec> *rec;//=new linklist<medical_rec>();
	for(i=0;i<num;i++)
	{
		pa=new linklist<patient>();
		pa->temp.load_file(fd);
		pati.insert_after_head(*pa);
		for(j=0;j<pa->temp.get_num_case();j++)
		{
			rec=new linklist<medical_rec>();
			rec->temp.load_file(fd);
			pa->temp.insert_after_head(*rec);
		}
	}
	return 0;
}
int function_6()
{
	linklist<patient> *head;
	char name[50];
	cout<<"请输入你要修改的患者姓名:";
	cin>>name;
	head=find_patient_name(pati,name);
	if(head==NULL)
	{
		cout<<"病人"<<name<<"不存在"<<endl;
		return 0;
	}
	cout<<"现在开始输入新信息:";
	cin>>head->temp;
	cout<<"信息修改成功\n"<<endl;
	return 0;
}
int main()
{
	int function;
	char name[50];
	init();
	while(1)
	{
		cout<<"请选择功能:"<<endl;
		cout<<"0、退出"<<endl;
		cout<<"1、添加一个病人 "<<endl<<"2、显示 "<<endl<<"3、存储 "<<endl<<"4、装入 "<<endl<<"5、查询 "<<endl;
		cout<<"6、修改 输入要修改病人的名称 "<<endl<<"7、添加病历 输入添加病历患者名称"<<endl;
		cout<<"8、显示 输入你要显示信息的病人的名称"<<endl;
		cin>>function;
		switch(function)
		{
			case 0: cout<<"欢迎下次使用\n"; return 0;
			case 1: patient::add_num(); function_1();function_4();show_patient(pati);break;
			case 2: function_2();break;
			case 4: function_4();cout<<"文件装入成功\n";break;
			case 3: function_3();break;
			case 5: cout<<"查询功能见8"<<endl;break;
			case 6: function_6(); break;
			case 7: function_7();break;
			case 8:
					cout<<"请输入病人名称:";
					cin>>name;
					function_8(name);break;
			default:
					cout<<"选择功能不存在\n";
		}
	}
	return 0;
}
