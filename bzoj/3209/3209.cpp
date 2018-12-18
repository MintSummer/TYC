#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int p=1e7+7;
ll n,sum[51],dp[51][2][51][51];
int cnt,a[51];
//数位dp+快速幂 

ll dfs(int now,int cur,int num,int tot)
{
	//从二进制最高为到低位填，now表示该填第几位，cur表示是否贴着上限；
	//num表示当前填了几个1，tot表示总共应该填的1的个数 
	if(!now) return num==tot;
	if(~dp[now][cur][num][tot])
		return dp[now][cur][num][tot];
	ll res=0;
	int up=cur?a[now]:1;
	for(int i=0;i<=up;i++)
		res+=dfs(now-1,cur&&(i==a[now]),num+i,tot);//不要取模 
	return dp[now][cur][num][tot]=res;
}

ll qpow(ll x,ll tim)
{
	ll ans=1;
	for(;tim;tim>>=1,x=x*x%p)
		if(tim&1) ans=ans*x%p;
	return ans;
}

int main()
{
	memset(dp,-1,sizeof(dp));
	scanf("%lld",&n);
	ll nn=n;
	while(n) a[++cnt]=(n&1),n>>=1;//因为n为1e15，故最多也就不到50个二进制位 
	ll ans=1;
	for(int i=1;i<=50&&(1<<(i-1))<=nn;i++)
	{
		//枚举这个二进制数中1的个数，运用数位dp计算1有i个的数的个数 
		sum[i]=dfs(cnt,1,0,i);
		ans=ans*qpow(i,sum[i])%p;//快速幂求出1个数为i个的总乘积 
		//注意一下！！！指数不可以取模，即pow(a,b)%p!=pow(a,b%p)%p 
		//故求sum时不可以取模 
	}
	printf("%lld",ans);
} 
