#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef unsigned long long ll;
    const ll p=2012182013;
    ll A,B,C,D,E,F;
    char N[1000010],M[1000010];
    
    struct Matrix
    {
		ll v[9];
    }m1,m2;

    inline Matrix operator * (const Matrix &a,const Matrix &b)
    {
		Matrix ans;
		ans.v[0]=(a.v[0]*b.v[0]+a.v[1]*b.v[3]+a.v[2]*b.v[6])%p;
		ans.v[1]=(a.v[0]*b.v[1]+a.v[1]*b.v[4]+a.v[2]*b.v[7])%p;
		ans.v[2]=(a.v[0]*b.v[2]+a.v[1]*b.v[5]+a.v[2]*b.v[8])%p;
		ans.v[3]=(a.v[3]*b.v[0]+a.v[4]*b.v[3]+a.v[5]*b.v[6])%p;
		ans.v[4]=(a.v[3]*b.v[1]+a.v[4]*b.v[4]+a.v[5]*b.v[7])%p;
		ans.v[5]=(a.v[3]*b.v[2]+a.v[4]*b.v[5]+a.v[5]*b.v[8])%p;
		ans.v[6]=(a.v[6]*b.v[0]+a.v[7]*b.v[3]+a.v[8]*b.v[6])%p;
		ans.v[7]=(a.v[6]*b.v[1]+a.v[7]*b.v[4]+a.v[8]*b.v[7])%p;
		ans.v[8]=(a.v[6]*b.v[2]+a.v[7]*b.v[5]+a.v[8]*b.v[8])%p;
		return ans;
    }
    
    inline void sub(char *ch)
    {
		int len=strlen(ch);
		for(int i=len-1;i>=0;i--)
			if(ch[i]=='0') ch[i]='9';
			else {ch[i]--;return;}
    }

    inline Matrix qpow(Matrix a,char *tim)
    {
		Matrix ans,mi[11];
		ans.v[0]=ans.v[4]=ans.v[8]=1;
		ans.v[1]=ans.v[2]=ans.v[3]=ans.v[5]=ans.v[6]=ans.v[7]=0;
		mi[0].v[0]=mi[0].v[4]=mi[0].v[8]=1;
		mi[0].v[1]=mi[0].v[2]=mi[0].v[3]=mi[0].v[5]=mi[0].v[6]=mi[0].v[7]=0;
		for(int i=1;i<=9;i++) mi[i]=mi[i-1]*a;
		int len=strlen(tim);
		for(int i=0;i<len;i++)
		{
			Matrix tmp=ans*ans;
			ans=tmp*tmp;
			ans=ans*ans;
			ans=ans*tmp;
			ans=ans*mi[tim[i]-'0'];
		}
		return ans;
    }

	ll read()
	{
		ll s=0;
		int ch;
		while(!isdigit(ch=getchar())){}
		do
			s=(s*10+ch-'0')%p;
		while(isdigit(ch=getchar()));
		return s;
	}

    void work()
    {
		scanf("%s%s",N,M);
		A=read(),B=read(),C=read(),D=read(),E=read(),F=read();
		sub(N),sub(M),sub(M);
		m1.v[0]=B,m1.v[1]=A,m1.v[2]=C,m1.v[3]=m1.v[8]=1;
		m2.v[0]=E,m2.v[1]=D,m2.v[2]=F,m2.v[3]=m2.v[8]=1;
		m1=qpow(m1,M);
		m2=m2*m2,m2=m2*m1;
		m2=m1*qpow(m2,N);
		printf("%llu\n",(m2.v[0]+m2.v[1]+m2.v[2])%p);
    }
}

int main()
{
    TYC::work();
    return 0;
}
