#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;
#define N 500010
char str[1000010], keyword[51];
int head, tail;

struct node
{
	node *fail;
	node *next[26];
	int count;
	node() //init
	{
		fail = NULL;
		count = 0;
		for(int i = 0; i < 26; ++i)
			next[i] = NULL;
	}
}*q[N];
node *root;

void insert(char *str) //建立Trie
{
	int temp, len;
	node *p = root;
	len = strlen(str);
	for(int i = 0; i < len; ++i)
	{
		temp = str[i] - 'a';
		if(p->next[temp] == NULL)
			p->next[temp] = new node();
		p = p->next[temp];
	}
	p->count++;
}

void build_ac() //初始化fail指针，BFS
{
	q[tail++] = root;
	while(head != tail)
	{
		node *p = q[head++]; //弹出队头
		node *temp = NULL;
		for(int i = 0; i < 26; ++i)
		{
			if(p->next[i] != NULL)
			{
				if(p == root) //第一个元素fail必指向根
					p->next[i]->fail = root;
				else
				{
					temp = p->fail; //失败指针
					while(temp != NULL) //2种情况结束：匹配为空or找到匹配
					{
						if(temp->next[i] != NULL) //找到匹配
						{
							p->next[i]->fail = temp->next[i];
							break;
						}
						temp = temp->fail;
					}
					if(temp == NULL) //为空则从头匹配
						p->next[i]->fail = root;
				}
				q[tail++] = p->next[i]; //入队
			}
		}
	}
}

int query() //扫描
{
	int index, len, result;
	node *p = root; //Tire入口
	result = 0;
	len = strlen(str);
	for(int i = 0; i < len; ++i)
	{
		index = str[i] - 'a';
		while(p->next[index] == NULL && p != root) //跳转失败指针
			p = p->fail;
		p = p->next[index];
		if(p == NULL)
			p = root;
		node *temp = p; //p不动，temp计算后缀串
		while(temp != root && temp->count != -1)
		{
			result += temp->count;
			temp->count = -1;
			temp = temp->fail;
		}
	}
	return result;
}

int main()
{
	int ncase, num;
	scanf("%d", &ncase);
	while(ncase--)
	{
		head= tail = 0;
		root = new node();
		scanf("%d", &num);
		getchar();
		for(int i = 0; i < num; ++i)
		{
			gets(keyword);
			insert(keyword);
		}
		build_ac();
		scanf("%s", str);
		printf("%d\n", query());
	}
	return 0;
}
