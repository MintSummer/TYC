#include<bits/stdc++.h>
#include<unordered_map>
using namespace std;

namespace TYC
{
	typedef long long ll;
	
	inline ll read()
	{
		ll x=0;int f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}
	
	inline void write(ll x)
	{
		int len=0;
		static int bask[18];
		if(!x) putchar('0');
		else
		{
			while(x) bask[++len]=x%10,x/=10;
			for(int i=len;i;i--) putchar('0'+bask[i]);
		}
	}
	
	ll gcd(ll a,ll b)
	{
		return !b?a:gcd(b,a%b);
	}
	
	void exgcd(ll a,ll b,ll &x,ll &y)
	{
		if(!b) {x=1,y=0;return;}
		exgcd(b,a%b,x,y);
		ll tmp=x;
		x=y;
		y=tmp-a/b*y;
	}
	
	ll inv(ll a,ll p)
	{
		ll x,y;
		exgcd(a,p,x,y);
		return (x%p+p)%p;
	}
	
	ll qpow(ll a,ll tim,ll p)
	{
		ll ans=1;
		for(;tim;tim>>=1,a=a*a%p)
			if(tim&1) ans=ans*a%p;
		return ans;
	}

	ll BSGS(ll A,ll B,ll P)
	{
		unordered_map<ll,int> num;//我用普通的map没有卡过去
		//unordered_map查询快得多
		ll m=sqrt(P+0.5),tmp=B;
		for(int i=1;i<=m;i++)
		{
			tmp=tmp*A%P;
			num[tmp]=i;
		}
		ll Pow=qpow(A,m,P);
		tmp=1;
		for(int i=1;i<=m;i++)
		{
			tmp=tmp*Pow%P;
			if(num.count(tmp)) return i*m-num[tmp];
		}
		return -1;
	}
	
	ll exBSGS(ll A,ll B,ll P)
	{
		A%=P,B%=P;
		if(B==1||P==1) return 0;
		if(!A)
		{
			if(!B) return 1;
			else return -1;
		}
		int res=0;
		ll D=1;
		for(ll G=gcd(A,P);G!=1;G=gcd(A,P))
		{
			if(B!=1&&B%G) return -1;
			B/=G;
			P/=G;
			D=D*(A/G)%P;
			res++;
		}
		B=B*inv(D,P)%P;
		ll ans=BSGS(A%P,B,P);
		return ~ans?ans+res:-1;
	}
	
	void work()
	{
		ll A,B,P;
		while(1)
		{
			A=read(),P=read(),B=read();
			if(!A&&!B&&!P) return;
			ll ans=exBSGS(A,B,P);
			if(ans==-1) puts("No Solution");
			else write(ans),puts("");
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
