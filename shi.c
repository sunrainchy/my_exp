#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <set>
#include <queue>
#include <math.h>
using namespace std;
const int MOD=1000000007;
long long f[110];
void init()
{
    f[1]=0;
    f[2]=1;
    for(int i=3;i<=100;i++)
    {
        f[i]=f[i-1]+f[i-2];
        f[i]%=MOD;
        f[i]*=(i-1);
        f[i]%=MOD;
    }
}
int main()
{
    init();
    int n;
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        printf("%I64d\n",f[n]);
    }
    return 0;
}
