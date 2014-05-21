#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//#include<conio.h>
using namespace std;
char *name1[25]={"大堤口","中山路","凤凰山","螃蟹甲","小东门","民主路小东门","何家垅","洪山体育馆","中南路","丁字桥","洪山","街道口","珞狮路","武工大","黄家湾","马房山","珞狮南路","幸福村","北港村","傅家嘴","南湖山庄","澳新学院","壕沟","周家湾","狮子山"};
char *name2[30]={"余家头","杨园","四美塘","徐家棚","赵家墩","三家路","三层楼","积玉桥","中山路","司门口","汉阳门","平湖门","彭刘杨路","阅马场","傅家坡","丁字桥","洪山","街道口","广埠屯","卓刀泉","虎泉","元宝山","桂元路","珞狮南路","幸福村","文秀街","图书城","文治街","建安街","江南村"};
char *name3[29]={"烽火科技","烽火路","大黄村","叶麻店","关山口","新屋熊","珞喻路鲁巷","吴家湾","东湖开发区","马家庄","卓刀泉","东湖村","东湖新村","广八路","珞珈山","劝业场","珞狮路","武工大","黄家湾","马房山","珞狮南路","幸福村","北港村","傅家嘴","南湖山庄","澳新学院","壕沟"," 周家湾","狮子山"};
char *name4[22]={"中华路","司门口东站","民主路胭脂路","武警医院","宜家装饰广场","民主路小东门","何家垅","洪山体育馆","中南路","丁字桥","洪山","街道口","广埠屯","卓刀泉","马家庄","东湖开发区","吴家湾","珞喻路鲁巷","新屋熊","关山口","汽发社区","关山街"};
char *name5[20]={"大堤口","中山路","凤凰山","螃蟹甲","小东门","大东门","傅家坡","丁字桥","洪山","街道口","广埠屯","卓刀泉","马家庄","东湖开发区","吴家湾","珞喻路鲁巷","新屋熊","关山口","汽发社区","关山街"};
char *name6[30]={"平湖门","彭刘杨路","阅马场","大东门","傅家坡","丁字桥","洪山","街道口","广埠屯","卓刀泉","马家庄","东湖开发区","吴家湾","珞喻路鲁巷","新屋熊","关山口","叶麻店","大黄村","森林公园","油篓口","长山","高坡店","王家店","九峰","土桥","苏家墩","金鸡山","新店","左家岭","上街村"};
char *name7[24]={"武东","张家铺","龚家岭","彭家岭","黄家大湾","雁中嘴","梅园","猴山","游泳池","风光村","东湖村","东湖新村","广八路","珞珈山","省邮电干校","小洪山","八一路","洪山体育馆","何家垅","民主路小东门","武警医院","民主路胭脂路","司门口东站","汉阳门"};
char name[200][30];
bool is_line_have;
int bbb,ddd;
int count_of_station;//记录车站的总数
struct point
{
	bool flag;
	int num_of_public_car;//记录公交车的标号
	int num1;
	int num2;
}map[200][200],line[100];//这个是一个临接矩阵，记录两个车站之间是否有直接连线
int beg(int n,char **p)//把所有车站设置进这个数组name中，没有重复，相当于是为这个车站编号，号码就是这个数组元素对应的下标
{//注意这里的编号是从零开始的
	int i,j;
	bool flag;
	static int k=0;//注意这个要设置成静态的
	for(i=0;i<n;i++)
	{
		flag=true;
	for(j=0;j<k;j++)
	{
		if(strcmp(name[j],p[i])==0)
		{
			flag=!flag;
			break;
		}
	}
	if(flag)
	{
		strcpy(name[k],p[i]);
		k++;
	}
	}
	return k;
}
int init()//把武汉的所有车站全部初始化进入这个name数组中
{
	beg(25,name1);
	beg(30,name2);
	beg(29,name3);
	beg(22,name4);
	beg(20,name5);
	beg(30,name6);
	return beg(24,name7);//最后返回的是所有车站的数目
}
int get_num(char *p)//返回这个车站对应的标号
{
	int i;
	for(i=0;i<count_of_station;i++)
	{
		if(strcmp(p,name[i])==0)
			return i;
	}
return 0;
}

int beg_map(int n,char **p,int num)//参数分别是每条路的车站数目，那一条路线，还有就是公交汽车标号
{//函数作用，初始化车站之间的路线
	int i,k,h;
	k=get_num(p[0]);
	for(i=1;i<n;i++)
	{
		h=get_num(p[i]);
		if(k!=h)
		{
	    map[k][h].flag=true;
        map[k][h].num_of_public_car=num;
		map[k][h].num1=k;
		map[k][h].num1=h;
		}
    	k=h;//这一步相当于是一种优化，就是减少计算的
	}
return 0;
}
int kkk=1;
int DFS(int count,int m,int n)//count 车站目前的数目，m这一步的起始位置，n这一站相通的下一个位置
{ 
	if(count>=count_of_station)
		return 0;
    	int i,k=m;
    	bool flag;
	int num_change=0;//记录转车的次数
	 
//	cout<<"DFS   "<<kkk++<<endl;
	    
			line[count].num1=m;
			line[count].num2=n;
			line[count].num_of_public_car=map[m][n].num_of_public_car;
	if(n==ddd)
	{   
		is_line_have=false;
		cout<<name[bbb]<<"-->"<<name[ddd]<<"的第"<<kkk++<<"条乘车路线："<<endl;
		cout<<"乘坐第"<<line[1].num_of_public_car<<"路公交车:"<<' ';
		cout<<name[line[0].num2]<<' '<<name[line[1].num2]<<' ';
		for(i=2;i<=count;i++)
		{
			if(line[i].num_of_public_car!=line[i-1].num_of_public_car)
			{   num_change++;
				cout<<"***请换乘"<<line[i].num_of_public_car<<"路公交***"<<' ';
			}
			cout<<name[line[i].num2]<<' ';
		}
		cout<<endl;
		cout<<"该条路线的转车次数为:";num_change==0?(cout<<" 0 \n属性 ： 直达"<<endl): (cout<<num_change<<"次。"<<endl);
		cout<<"乘车路线总长度为"<<count<<endl;
		cout<<"乘坐此路线需要总的费用是:"<<(num_change+1)*2<<"元钱"<<endl;
		cout<<endl;
	}
	for(i=0;i<count_of_station;i++)
	{
		if(map[n][i].flag)//如果可以由m到i那么就走走看
		{   
			flag=true;
			if(map[i][n].flag)
			{
				flag=false;
			}
			map[i][n].flag=false;//注意这里要调过来，这样就可以保证回不去了，防止循环
            map[n][i].flag=false;//这条路先不能通，防止循环
			DFS(count+1,n,i);
		    map[n][i].flag=true;//回溯
			if(flag==false)//这个是防止开始就是false 那你还变成true，那不是平白无故增加出一条路了吗？
			{
			map[i][n].flag=true;
			}

		}
	}
	return 0;
}
			
		




int init_map()
{
	beg_map(25,name1,576);
	beg_map(30,name2,804);
	beg_map(29,name3,591);
	beg_map(22,name4,521);
	beg_map(20,name5,15);
	beg_map(30,name6,25);
	beg_map(24,name7,515);
	return 0;
}
char des[30];
char start[30];
int main()
{
	cout<<"----------------欢迎使用武汉公交线路查询系统------------------"<<endl;
	cout<<"                 版权所有，全体计科四班学员"<<endl;
	cout<<"         请按任意键进入系统..........."<<endl;
	getch();
	count_of_station=init();
	int i,j;
/*	for(i=0;i<count_of_station;i++)
	{
		cout<<name[i]<<' ';
	}
	*/
	memset(map,0,sizeof(map));
	init_map();
/*for(i=0;i<35;i++)
	{
		for(j=0;j<35;j++)
		{
			cout<<map[i][j].flag<<' ';
		}
		cout<<endl;
	}*/

/*while(cin>>start>>des)
{
	cout<<map[get_num(start)][get_num(des)].flag<<' '<<map[get_num(start)][get_num(des)].num_of_public_car<<' '<<endl;
}*/
	while(1)
	{
		is_line_have=true;
		cout<<"请输入起始站点:"<<endl;
loop:
		cin>>start;
		for(i=0;i<count_of_station;i++)
		{
			if(strcmp(name[i],start)==0)
				break;
		}
		if(i==count_of_station)
		{
			cout<<"对不起，您所输入的起始站点不存在请重新输入:"<<endl;
			goto loop;
		}
loop1:
		cout<<"请输入终点站:"<<endl;
		cin>>des;
		for(i=0;i<count_of_station;i++)
		{
			if(strcmp(name[i],des)==0)
				break;
		}
		if(i==count_of_station)
		{
			cout<<"对不起，您所输入的终点站点不存在请重新输入:"<<endl;
			goto loop1;
		}
		bbb=get_num(start);
		cout<<bbb<<endl;
		ddd=get_num(des);
		cout<<ddd<<endl;
		kkk=1;
		DFS(0,bbb,bbb);
		if(is_line_have)
		{
			cout<<"您所查找的路线不存在，转车也无法达到，建议您坐出租车"<<endl<<"请按任意键继续查询....."<<endl;
		}
		else
		{
		cout<<"所有的直达线路还有转车线路如上面所给出"<<endl<<"请按任意键继续查询....."<<endl;
		}
		getch();
	}
return 0;
}
