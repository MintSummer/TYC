#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const ll p=998244353;
	const int N=505;
	const int M=7;
	int n;char str[N];

	inline void Mod(ll &x) {x=(x>=p?x-p:x);}

	struct Matrix
	{
		ll m[M][M];
		Matrix(){memset(m,0,sizeof(m));}

		Matrix operator +(const Matrix &t)
		{
			Matrix ans;
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)
					Mod(ans.m[i][j]=m[i][j]+t.m[i][j]);
			return ans;
		}

		Matrix operator *(const Matrix &t) 
		{
			Matrix ans;
			for(int i=1;i<=n;i++)
				for(int k=1;k<=n;k++)
					for(int j=1;j<=n;j++)
						ans.m[i][j]+=m[i][k]*t.m[k][j];
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)
					ans.m[i][j]%=p;
			return ans;
		}
	}f[N][N],mi[10],dp[N];

	inline void pow10(Matrix &t)
	{
		t=t*t;
		Matrix tmp=t;
		t=t*t,t=t*t;
		t=t*tmp;
	}

	void work()
	{
		scanf("%s%d",str+1,&n);
		for(int i=1;i<=n;i++) mi[1].m[i][1]=1;
		for(int i=1;i<n;i++) mi[1].m[i][i+1]=1;
		for(int i=2;i<10;i++) mi[i]=mi[i-1]*mi[1];
		for(int i=1;i<=n;i++) dp[0].m[i][i]=1;
		int len=strlen(str+1);
		for(int i=1;i<=len;i++)
		{
			static Matrix tmp;
			memset(tmp.m,0,sizeof(tmp.m));
			for(int j=1;j<=n;j++) tmp.m[j][j]=1;
			for(int j=i;j<=len;j++,pow10(tmp))
			{
				if(str[j]!='0')
					tmp=tmp*mi[str[j]-'0'];
				f[i][j]=tmp;
			}
		}
		for(int i=1;i<=len;i++)
			for(int j=0;j<i;j++)
				dp[i]=dp[i]+dp[j]*f[j+1][i];
		printf("%lld\n",dp[len].m[1][1]);
	}
}

int main()
{
	TYC::work();
	return 0;
}
