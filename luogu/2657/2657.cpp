#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll A,B,dp[20][3][3][12],ans;
int a[20],n;

void change(ll x)
{
    n=0;
    while(x)
    { 
	a[++n]=x%10;
	x/=10;
    }
}

ll dfs(int len,int cur,int start,int last)
{
	if(dp[len][cur][start][last]) return dp[len][cur][start][last];
    if(len==0) return dp[len][cur][start][last]=1;

    ll res=0;
    for(int i=0;i<10;i++)
    {
	if(cur&&i>a[len]) break;
	int nstart,ncnt;
	ncnt=(cur&&(i==a[len]));
	nstart=(start||i!=0);
	if(len!=n&&start&&abs(i-last)<=1) continue;
	res+=dfs(len-1,ncnt,nstart,i);
    }

    return dp[len][cur][start][last]=res;
}

int main()
{
    cin>>A>>B;
    change(B);
    ans+=dfs(n,1,0,0);
    memset(dp,0,sizeof(dp));
    change(A-1);
    ans-=dfs(n,1,0,0);
    printf("%lld",ans);
    return 0;
}
