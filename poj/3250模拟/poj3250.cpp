#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
#include<cmath>
using namespace std;
int n,tall[80005],dp[80005];

int main()
{
    scanf("%d",&n);
    memset(dp,0,sizeof(dp));
    for(int i=n;i>=1;i--)
      scanf("%d",&tall[i]);
    int d=1;
    for(int i=2;i<=n;i++)
      {
      	d=1;
      	while(tall[i]>tall[i-d]&&i-d>0)
      	  {
      	  	dp[i]+=dp[i-d]+1;
      	  	d+=dp[i-d]+1;
      	  }
      }
    long long ans=0;
    for(int i=1;i<=n;i++)
      ans+=dp[i];
    printf("%lld",ans);
    return 0;
}