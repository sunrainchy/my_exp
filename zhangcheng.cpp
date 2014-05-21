#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <iostream>
#include <cmath>
using namespace std;
const int maxn =100000;
int len,down;
char str[maxn];
unsigned short rec[maxn],my_map[10];
int init(){
	int i,j,k;
	scanf("%s",str);
	for(i=0;str[i];i++){
		if(str[i]=='A') str[i]=1;
		else if(str[i]=='G') str[i]=2;
		else if(str[i]=='C') str[i]=3;
		else str[i]=4;
	}
	len=i;
	for(i=0;i<6;i++)
	map[i]=pow(5,i);
	return 0;
}
int find_one(int low){//处理长度为1的情况	
	int num=1;
	for(int i=1;i<len;i++){
		if(str[i]==str[i-1]) num++;
		else{
			if(num>=low){
				printf("%c: %d %d\n",str[i-1],num,i-num);//string num pos
			}
			num=1;
		}
	}
	return 0;
}
int find_ans(int length,int low){
	int i,j,k,num;
	rec[0]=0;
	for(int i=0;i<len;i+=length){
		rec[i]=0;
		for(j=0;j<length;j++)
			rec[i]=rec[i]*5+str[i+j];
		for(j=1;j<length;j++){
			k=i+j;
			rec[k]=rec[k-1];
			rec[k]-=str[k-1]*my_map[length-1];
			rec[k]=rec[k]*5+str[k+length-1];
		}
	}
	for(i=0;i<length;i++){
		num=1;
		for(j=i+length+length;j<len;j++){
			if(rec[j]==rec[j-length]) num++;
			else {
				if(num>=low){
					for(k=0;k<length;k++)
					putchar(str[j-length+k]);
					printf(": %d %d\n",num,j-num*length);
				}
				else num=1;
			}
		}
	}
	return 0;
}
int main(){
	scanf("%d\n",&down);
	return 0;
}
