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
	}w[N];
	
	int rev[N];
	
	inline void init(int n)
	{
		for(int i=0;i<n;i++)
			w[i]=cmplex(cos(2*PI*i/n),sin(2*PI*i/n));
		for(int i=0;i<n;i++)
			rev[i]=(rev[i>>1]>>1)|((n>>1)*(i&1));
	}
	
	void FFT(cmplex a[],const int n,const int type)
	{
		if(type) reverse(w+1,w+n);
		for(int i=0;i<n;i++)
			if(i<rev[i]) swap(a[i],a[rev[i]]);

		for(int i=1;i<n;i<<=1)
			for(int j=0,d=n/(i<<1);j<n;j+=(i<<1))
				for(int k=j,l=0;k<j+i;k++,l+=d)
				{
					cmplex x=a[k],y=w[l]*a[k+i];
					a[k]=x+y;
					a[k+i]=x-y;
				}
	}	

	void work()
	{
		int n,m;
		n=read(),m=read();
		static cmplex a[N],b[N];
		for(int i=0;i<=n;i++) a[i].re=read();
		for(int i=0;i<=m;i++) b[i].re=read();
		for(m+=n,n=1;n<=m;n<<=1);
		init(n);
		FFT(a,n,0),FFT(b,n,0);
		for(int i=0;i<n;i++) a[i]=a[i]*b[i];
		FFT(a,n,1);
		for(int i=0;i<=m;i++) 
			write((int)(a[i].re/n+0.5));
	}
}

int main()
{
	TYC::work();
	return 0;
}
