
#include <string>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;
int get_string(char *first,char del)
/*函数接受以del结尾的一串字符并返回实际接收的字符数目*/
{
int num=0;
char ch;
while(1)
{
ch=getchar();
if(ch==del)
{ 
first[num]=0;
return num;
}
else
first[num++]=ch;
}
return 0;
}
int change_case(char * first,int b)
/****改变字母大小写，b==0小写转换成大写，b==1大写转换成小写****/
{
int len=0;
if(b==1)
while(first[len])
{
if(first[len]>='A' && first[len]<='Z')
first[len]+=32;
len++;
}
else
while(first[len])
{
if(first[len]>='a' && first[len]<='z')
first[len]-=32;
len++;
}
return 0;
}
int my_lower(char *first)
/*把所有字母转换成为小写*/
{
return change_case(first,1);
}
int my_upper(char *first)
/****所有能转换成大写的小写字母转换成大写****/
{
return change_case(first,0);
}
int is_space(char ch)
/*判断字符是不是'\n':10 '\t':9 ' '*/ 
{
if(ch==10||ch==9||ch==' ')
return 1;
else 
return 0;
printf("%s","\b\b");
}
/** 判断字符是不是 {} [] <> , = 前后空格要去除的符号 **/
int is_marry(char ch)
{
switch(ch)
{
case '=':
case ',':
case '(':
case ')':
case '}':
case '{':
case ']':
case '[':
case '<':
case '>': return 1;
default :return 0;
}
return 0;
}
int compress(char *first)
/*把所有回车 tab还有多余的空格压缩变换还有功能就是在符号后面出现的空格也会删除这里的符号主要是',',因为查询语句里面出现的都是','分割符*/
{
int len=0,real_len=0;
while(is_space(first[len])) len++;
first[real_len++]=first[len++];
for(len;first[len];len++)
{
if((is_space(first[len])&&is_space(first[len-1]))||((first[len-1]==','||is_marry(first[len-1]))&&is_space(first[len])))
continue;
/*
 * 前面是空格后面也是就去掉一个，前面是','后面是空格那个去掉空格
 */
if(is_space(first[len]))
first[len]=' ';
first[real_len++]=first[len];
}
first[real_len]=0;
real_len--;
/*检查去除串最后是空字符\n tab ' '等*/
while(is_space(first[real_len]))
real_len--;
first[real_len+1]=0;
/*
 *上面的操作完成的是把所有(){}<>[],后面的空格消除，还剩下的就是这些符号前面的一个空格，下面开始清除
 */
real_len=0;
for(len=0;first[len];len++)
{
if(is_space(first[len])&&is_marry(first[len+1]))
continue;
first[real_len++]=first[len];
}
first[real_len]=0;
return 0;
}
/*检查语法错误之匹配错误*/
int check_syntax_for_match(const char *ch)
{
char *sta;
int len=strlen(ch);
sta=(char*)malloc(len+1);
int i,j,k,s=0;
/* '39 "34 (40 )41 {123 }125 [91 ]93 <60 >62*/
for(i=0;i<len;i++)
{
if(ch[i]<=0)
{
printf("无法识别 0xa1\n",ch[i]);
return 50;
}
k=(int)ch[i];
/* < { [ ( */
if(ch[i]=='<'||ch[i]=='{'||ch[i]=='['||ch[i]=='(')
{ 
sta[s++]=ch[i];
continue;
}
/* > } ] ) */
if(ch[i]=='>'||ch[i]=='}'||ch[i]==']'||ch[i]==')')
{
/*如果在第一个位置出现该字符或者出现后前面无匹配则发生错误*/
if(i==0||(ch[i]=='>'&&sta[s-1]!='<')||(ch[i]==')'&&sta[s-1]!='(')||(ch[i]=='}'&&sta[s-1]!='{')||(ch[i]==']'&&sta[s-1]!='['))
{ 
printf("匹配错误%c不匹配\n",ch[i]);
free(sta);
return 50;
}
else
s--;
continue;
}
/* ' " */
if(k==39||k==34)
{
if(i==0||s==0)/*第一个位置出现 或者当stack为空的时候出现*/
{
sta[s++]=ch[i];
continue;
}
if(k==(int)sta[s-1])
{
s--;
continue;
}
else
sta[s++]=ch[i];
}
}
free(sta);
if(s>0)
{ 
printf("匹配错误\n");
return 50;
}
return 0;
}

int my_split(const char *src,char *dec,char del,int k)
/****分离一个以del为分割符的第k个字段存放在dec中 ****/
{
/*如果第0个一下一定是传参数错误,让dec为一个空串就OK 了*/
dec[0]=0;
int i,j,p,q;
k--;
p=0;
q=0;
for(i=0;src[i]&&p<k;i++)
{
if(src[i]==del)
p++;
}
for( ;src[i]&&src[i]!=del;i++)
{
dec[q++]=src[i];
}
dec[q]=0;
return 0;
}

int is_name(char *name)
/*
 *判断一个给定的字符串能否为名称，也就是只能由数字，字母和下划线组成
 *成功返回1，失败返回0
 */
{
int i=0;
if(name[0]==0)
return 0;
if(!((name[i]>='a'&&name[i]<='z')||(name[i]>='A'&&name[i]<='Z')||name[i]=='_'))//首字母不是下划线或者字母不符合条件
return 0;
for(i=1;name[i];i++)
{
if(!((name[i]>='a'&&name[i]<='z')||(name[i]>='A'&&name[i]<='Z')||(name[i]>='0'&&name[i]<='9')||name[i]=='_'))
return 0;
}
return 1;
}

int my_split_end(const char *src,char *dec,char del,int k,int flag)
/*
 *这个函数实现找到第k个del位置之后的字符串全部放在dec中，参数与my_split相同
 */
{
int i,p=0;
dec[0]=0;
for(i=0;src[i];i++)
{
if(src[i]==del)
p++;
if(p==k)
{
if(flag==0)
strcpy(dec,src+i+1);
else
{
strncpy(dec,src,i);
}
return 0;
}
}
return 0;
}
   

struct select_info
{
char name[50];
select_info *next;
};
select_info *head;
char table_name[100];
int main()
{
int offset=0;
int k;
select_info *name;
name=new select_info;
head=name;
name->next=NULL;
char sql_command[200];
char next[200];
char sp[200];
get_string(sql_command,';');
compress(sql_command);
cout<<sql_command<<endl;
my_split_end(sql_command,sp,' ',1,0);
my_split_end(sp,next,' ',1,1);
while(next[offset])
{
k=0;
while(next[offset]!=','&&next[offset])
{
name->name[k++]=next[offset];
offset++;
}
name->name[k]=0;
if(next[offset])
{
name->next=new select_info;
name=name->next;
name->next=NULL;
}
else
break;
offset++;
}
name=head;
while(name)
{
cout<<name->name<<endl;
name=name->next;
}
my_split_end(sp,table_name,' ',2,0);
cout<<table_name<<endl;
return 0;
}
