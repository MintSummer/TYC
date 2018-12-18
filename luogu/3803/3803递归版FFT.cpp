#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=1<<21|5;
	const double PI=3.1415926535897932384626;
	
	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	inline void write(int x)
	{
		if(x<0) putchar('-'),x=-x;
		if(!x) putchar('0');
		else
		{
			int len=0;
			static int bask[50];
			while(x) bask[++len]=x%10,x/=10;
			for(;len;len--) putchar('0'+bask[len]);
		}
		putchar(' ');
	}

	struct cmplex
	{
		double re,im;
		cmplex(double _re=0.0,double _im=0.0): re(_re),im(_im){}
		cmplex operator +(const cmplex &x) const {return cmplex(re+x.re,im+x.im);}
		cmplex operator -(const cmplex &x) const {return cmplex(re-x.re,im-x.im);}
		cmplex operator *(const cmplex &x) const {return cmplex(re*x.re-im*x.im,re*x.im+im*x.re);}
	};
	
	void FFT(cmplex a[],const int n,const int type)
	{
		if(n==1) return;
		int mid=n>>1;
		static cmplex buf[N];
		for(int i=0;i<mid;i++)
		{
			buf[i]=a[i<<1];
			buf[i+mid]=a[i<<1|1];
		}
		memcpy(a,buf,sizeof(cmplex[n]));
		FFT(a,mid,type),FFT(a+mid,mid,type);	
		cmplex tmp(cos(type*2*PI/n),sin(type*2*PI/n));
		cmplex w(1.0,0.0);
		for(int i=0;i<mid;i++,w=w*tmp)
		{
			buf[i]=a[i]+w*a[i+mid];
			buf[i+mid]=a[i]-w*a[i+mid];
		}
		memcpy(a,buf,sizeof(cmplex[n]));
	}
	

	void work()
	{
		int n,m;
		n=read(),m=read();
		static cmplex a[N],b[N];
		for(int i=0;i<=n;i++) a[i].re=read();
		for(int i=0;i<=m;i++) b[i].re=read();
		for(m+=n,n=1;n<=m;n<<=1);
		FFT(a,n,1),FFT(b,n,1);
		for(int i=0;i<n;i++) a[i]=a[i]*b[i];
		FFT(a,n,-1);
		for(int i=0;i<=m;i++) 
			write((int)(a[i].re/n+0.5));
	}
}

int main()
{
	TYC::work();
	return 0;
}
