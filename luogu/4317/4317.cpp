#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int p=1e7+7;
ll n,sum[51],dp[51][2][51][51];
int cnt,a[51];
//��λdp+������ 

ll dfs(int now,int cur,int num,int tot)
{
	//�Ӷ��������Ϊ����λ�now��ʾ����ڼ�λ��cur��ʾ�Ƿ��������ޣ�
	//num��ʾ��ǰ���˼���1��tot��ʾ�ܹ�Ӧ�����1�ĸ��� 
	if(!now) return num==tot;
	if(~dp[now][cur][num][tot])
		return dp[now][cur][num][tot];
	ll res=0;
	int up=cur?a[now]:1;
	for(int i=0;i<=up;i++)
		res+=dfs(now-1,cur&&(i==a[now]),num+i,tot);//��Ҫȡģ 
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
	while(n) a[++cnt]=(n&1),n>>=1;//��ΪnΪ1e15�������Ҳ�Ͳ���50��������λ 
	ll ans=1;
	for(int i=1;i<=50&&(1<<(i-1))<=nn;i++)
	{
		//ö���������������1�ĸ�����������λdp����1��i�������ĸ��� 
		sum[i]=dfs(cnt,1,0,i);
		ans=ans*qpow(i,sum[i])%p;//���������1����Ϊi�����ܳ˻� 
		//ע��һ�£�����ָ��������ȡģ����pow(a,b)%p!=pow(a,b%p)%p 
		//����sumʱ������ȡģ 
	}
	printf("%lld",ans);
} 
