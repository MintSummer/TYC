#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=15;
int num[MAXN];
ll a,b,dp[MAXN][2][2][MAXN];

ll dfs(int len,int cur,int zero,int sum,int d)
{
    if(dp[len][cur][zero][sum]!=-1) return dp[len][cur][zero][sum];
    if(len==0) return sum;
    ll res=0;
    for(int i=0;i<10;i++)
    {
		if(cur&&num[len]<i) break;
		int nsum=sum+((!zero||i)&&(i==d));//当d==0的时候要排除前导零的情况
		res+=dfs(len-1,cur&&(i==num[len]),zero&&(i==0),nsum,d);
    }
    return dp[len][cur][zero][sum]=res;
}

ll solve(ll x,int d)
{
    int len=0;
    while(x)
    {
		num[++len]=x%10;
		x/=10;
    }
    memset(dp,-1,sizeof(dp));
    return dfs(len,1,1,0,d);
}

int main()
{
    scanf("%lld%lld",&a,&b);
    for(int i=0;i<10;i++)
		printf("%lld ",solve(b,i)-solve(a-1,i));
    return 0;
}
