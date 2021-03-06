#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    int n;
    ll p;

    struct Matrix
    {
		ll m[80][80];
		bool operator < (const Matrix &x) const
		{
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)
					if(m[i][j]!=x.m[i][j]) return m[i][j]<x.m[i][j];
			return false;
		}
		
		bool operator > (const Matrix &x) const
		{
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)
					if(m[i][j]!=x.m[i][j]) return m[i][j]>x.m[i][j];
			return false;
		}
		
		bool operator == (const Matrix &x) const
		{
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)
					if(m[i][j]!=x.m[i][j]) return false;
			return true;
		}

		Matrix operator * (Matrix x)
		{
			Matrix ans;
			memset(ans.m,0,sizeof(ans.m));
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)
					for(int k=1;k<=n;k++)
						ans.m[i][j]=(ans.m[i][j]+m[i][k]*x.m[k][j]%p)%p;
			return ans;
		}
    }A,B;

    map<Matrix,int> id;

    Matrix qpow(Matrix a,int tim)
    {
		Matrix ans;
		memset(ans.m,0,sizeof(ans.m));
		for(int i=1;i<=n;i++) ans.m[i][i]=1;
		for(;tim;tim>>=1,a=a*a)
			if(tim&1) ans=ans*a;
		return ans;
    }

    int BSGS()
    {
		int m=(int)(sqrt(p)+0.5);
		Matrix now=B;
		id[now]=0;
		for(int i=1;i<=m;i++)
		{
			now=now*A;
			id[now]=i;
		}
		Matrix tmp=qpow(A,m);
		now=tmp;
		for(int i=1;i<=m;i++)
		{
			if(id.count(now)) return i*m-id[now];
			now=now*tmp;
		}
		return -1;
    }

    void work()
    {
		scanf("%d%lld",&n,&p);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++) 
				scanf("%lld",&A.m[i][j]);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				scanf("%lld",&B.m[i][j]);
		printf("%d",BSGS());
    }
}

int main()
{
    TYC::work();
    return 0;
}
