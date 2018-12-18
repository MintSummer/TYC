#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=110;
const int P=100000;
int M,cnt,q[MAXN*4];
ll N;
map<char,int> id;

struct Matrix
{
	ll x[MAXN][MAXN];
	
	Matrix operator * (const Matrix &a)
	{
		Matrix res;
		for(int i=0;i<=cnt;i++)
			for(int j=0;j<=cnt;j++)
			{
				res.x[i][j]=0;
				for(int k=0;k<=cnt;k++)
					res.x[i][j]=(res.x[i][j]+x[i][k]*a.x[k][j])%P;
			}
		return res;
	}
}m;

Matrix qpow(Matrix m,int tim)
{
	Matrix ans;
	for(int i=0;i<=cnt;i++)
		ans.x[i][i]=1;	
	for(;tim;tim>=1,m=m*m)
		if(tim&1) ans=ans*m;
	return ans;
}

struct AC
{
	int son[MAXN][4],fail[MAXN],end[MAXN];
	
	void insert(char ch[])
	{
		int len=strlen(ch),now=0;
		for(int i=0;i<len;i++)
		{
			int tmp=id[ch[i]];
			if(!son[now][tmp]) son[now][tmp]=++cnt;
			now=son[now][tmp];
		}
		end[now]=1;
	}
	
	void get_fail()
	{
		int h=0,t=0;
		for(int i=0;i<4;i++)
			if(son[0][i]) q[++t]=son[0][i];
		while(h<t)
		{
			int now=q[++h],f=fail[now];
			if(end[fail[now]]) end[now]=1;
			for(int i=0;i<4;i++)
			{
				int x=son[now][i];
				if(x)
				{
					fail[x]=son[f][i];
					q[++t]=x;
				}
				else son[now][i]=son[f][i];
			}
		}
	}
	
	void build()
	{
		for(int i=0;i<=cnt;i++) if(!end[i])
			for(int j=0;j<4;j++)
				if(!end[son[i][j]])
					m.x[i][son[i][j]]++,m.x[i][son[i][j]]%=P;
	}
}ac;

int main()
{
	scanf("%d%lld",&M,&N);
	id['A']=0,id['T']=1,id['C']=2,id['G']=3;
	char ch[15];
	for(int i=1;i<=M;i++)
		scanf("%s",ch),ac.insert(ch);
	ac.get_fail();
	ac.build();
	m=qpow(m,N);
	ll ans=0;
	for(int i=0;i<=cnt;i++)
		ans=(ans+m.x[0][i])%P;
	printf("%lld",ans);
	return 0;
} 
