#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const ll p=1000000007;
    ll A,B,C,D;
    char N[1000010],M[1000010];

    struct Matrix
    {
		ll v[4];
    }m1,m2;

    inline Matrix operator * (const Matrix &a,const Matrix &b)
    {
		Matrix ans;
		ans.v[0]=(a.v[0]*b.v[0]+a.v[1]*b.v[2])%p;
		ans.v[1]=(a.v[0]*b.v[1]+a.v[1]*b.v[3])%p;
		ans.v[2]=(a.v[2]*b.v[0]+a.v[3]*b.v[2])%p;
		ans.v[3]=(a.v[2]*b.v[1]+a.v[3]*b.v[3])%p;
		return ans;
    }

    inline void sub(char *ch)
    {
		int len=strlen(ch);
		for(int i=len-1;i>=0;i--)
			if(ch[i]=='0') ch[i]='9';
			else {ch[i]=ch[i]-1;return;}
    }

    inline Matrix qpow(Matrix a,char *tim)
    {
		Matrix ans;
		ans.v[0]=ans.v[3]=1,ans.v[1]=ans.v[2]=0;
		Matrix mi[11];
		mi[0].v[0]=mi[0].v[3]=1,mi[0].v[1]=mi[0].v[2]=0;
		for(int i=1;i<=9;i++) mi[i]=mi[i-1]*a;
		int len=strlen(tim);
		for(int i=0;i<len;i++)
		{
			int x=tim[i]-'0';
			Matrix tmp=ans*ans;
			ans=tmp*tmp;
			ans=ans*ans;
			ans=ans*tmp;
			ans=ans*mi[x];
		}
		return ans;
    }

    void work()
    {
		scanf("%s%s",N,M);
		scanf("%lld%lld%lld%lld",&A,&B,&C,&D);
		sub(N),sub(M);
		m1.v[0]=A,m1.v[1]=B,m1.v[2]=0,m1.v[3]=1;
		m2.v[0]=C,m2.v[1]=D,m2.v[2]=0,m2.v[3]=1;
		m1=qpow(m1,M);
		m2=m2*m1;
		Matrix ans=m1*qpow(m2,N);
		printf("%lld",(ans.v[0]+ans.v[1])%p);
    }
}

int main()
{
    TYC::work();
    return 0;
}
