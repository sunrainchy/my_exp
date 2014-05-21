#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
using namespace std;
struct node
{
node *next[128];
int num;
node()
{
memset(next,0,sizeof(next));
num=0;
}
}re_root;
int count;
char global_name[100];
int insert_trie(node *root,char *name)
{
if(name[0]==0)
{
root->num++;
return 0;
}
if(root->next[name[0]]!=NULL)
insert_trie(root->next[name[0]],name+1);
else
{
root->next[name[0]]=new node();
insert_trie(root->next[name[0]],name+1);
}
return 0;
}
int tri_reverse(node *root,int k)
{
if(root->num>0)
{
global_name[k]=0;
printf("%s %.4lf\n",global_name,100*double(root->num)/count);
}
int i;
for(i=0;i<128;i++)
if(root->next[i]!=NULL)
{
global_name[k]=i;
tri_reverse(root->next[i],k+1);
}
return 0;
}
int main()
{
char name[31];
count=0;
while(gets(name)!=NULL)
{
count++;
insert_trie(&re_root,name);
}
if(count==0)
return 0;
tri_reverse(&re_root,0);
return 0;
}
