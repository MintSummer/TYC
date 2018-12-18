//简单dp，分段矩阵快速幂 
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,p;

struct Matrix
{
	int n,m;
	ll x[3][3];
	Matrix()
	{
		for(int i=0;i<3;i++) 
			for(int j=0;j<3;j++)
				x[i][j]=0LL;
	}
	Matrix operator * (const Matrix &a) const
	{
		Matrix res;
		res.n=n,res.m=m;
		for(int i=0;i<n;i++)
			for(int j=0;j<a.m;j++)
				for(int k=0;k<m;k++)
					res.x[i][j]=(res.x[i][j]+x[i][k]*a.x[k][j])%p;
		return res;
	}
}M,T;

void build(ll k)
{	
	T.n=T.m=3;
	T.x[0][0]=k%p;
	T.x[0][1]=T.x[0][2]=T.x[1][2]=0LL;
	T.x[1][0]=T.x[1][1]=T.x[2][0]=T.x[2][1]=T.x[2][2]=1LL;
	M.n=1,M.m=3;
	M.x[0][1]=(k/10-1)%p;M.x[0][2]=1LL;
}

Matrix qpow(ll tim)
{
	for(;tim;tim>>=1,T=T*T) 
		if(tim&1) M=M*T;
	return M;
}

int main()
{
	scanf("%lld%lld",&n,&p);
	M.x[0][0]=0LL;
	ll k=1LL;
	while(k<=n)
	{
		k*=10;
		build(k);
		ll tim=min(k/10*9,n-k/10+1);
		M=qpow(tim);
	}
	printf("%lld",M.x[0][0]);
	return 0;
} 
