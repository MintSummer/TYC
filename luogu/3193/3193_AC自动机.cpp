#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int m,p,cnt;
ll n;

int read()
{
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x;
}

struct Matrix
{
	ll x[25][25];
	Matrix operator * (const Matrix &a) const
	{
		Matrix res;
		memset(res.x,0,sizeof(res.x));
		for(int i=0;i<=cnt;i++)
			for(int j=0;j<=cnt;j++)
				for(int k=0;k<=cnt;k++)
					res.x[i][j]=(res.x[i][j]+x[i][k]*a.x[k][j])%p;
		return res;
	}
}ma;

struct AC
{
	int son[25][10],fail[25],end[25],q[25],now;
	
	void insert(char ch[])
	{
		now=0;
		for(int i=0;i<m;i++)
		{
			son[now][ch[i]-'0']=++cnt;
			now=son[now][ch[i]-'0'];
		}
		end[now]=1;
	}
	
	void get_fail()
	{
		int h=0,t=0;
		for(int i=0;i<10;i++)
			if(son[0][i]) q[++t]=son[0][i];
		while(h<t)
		{
			now=q[++h];
			int f=fail[now];
			if(end[f]) end[now]=1;
			for(int i=0;i<10;i++)
				if(son[now][i])
				{
					fail[son[now][i]]=son[f][i];
					q[++t]=son[now][i];
				}
				else son[now][i]=son[f][i];
		}
	}
	
	void build()
	{
		for(int i=0;i<=cnt;i++) if(!end[i])
			for(int j=0;j<10;j++) if(!end[son[i][j]])
				ma.x[i][son[i][j]]=(ma.x[i][son[i][j]]+1)%p;
	}
}ac;

Matrix qpow(Matrix mat,ll tim)
{
	Matrix ans;
	memset(ans.x,0,sizeof(ans.x));
	for(int i=0;i<=cnt;i++) ans.x[i][i]=1;
	for(;tim;tim>>=1,mat=mat*mat) 
		if(tim&1) ans=ans*mat;
	return ans;
}

int main()
{
	scanf("%lld",&n);
	m=read(),p=read();
	char ch[25];
	scanf("%s",ch);
	ac.insert(ch);
	ac.get_fail();
	ac.build();
	ma=qpow(ma,n);
	int ans=0;
	for(int i=0;i<=cnt;i++)
		ans=(ans+ma.x[0][i])%p;
	printf("%d",ans);
	return 0;
} 
