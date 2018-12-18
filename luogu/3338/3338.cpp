#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=1<<18|5;
	const double PI=acos(-1);

	struct cmplex
	{
		double re,im;
		cmplex(double _re=0.0,double _im=0.0):re(_re),im(_im){}
		cmplex operator +(const cmplex &t) const {return cmplex(re+t.re,im+t.im);}
		cmplex operator -(const cmplex &t) const {return cmplex(re-t.re,im-t.im);}
		cmplex operator *(const cmplex &t) const {return cmplex(re*t.re-im*t.im,re*t.im+im*t.re);}
	}w[N];

	int rev[N];
	double arr[N];

	inline double sqr(double x) {return x*x;}

	void init(int n)
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
				for(int k=j,l=0;k<i+j;k++,l+=d)
				{
					cmplex x=a[k],y=a[k+i]*w[l];
					a[k]=x+y;
					a[k+i]=x-y;
				}
		if(type)
			for(int i=0;i<n;i++) a[i].re=a[i].re/n;
	}

	void query(int n,int len,cmplex a[],const int type=0)
	{
		static cmplex b[N];
		for(int i=0;i<n;i++) a[i].re=arr[i];
		b[0]=cmplex();
		for(int i=1;i<n;i++) b[i]=(double)1.0/sqr(i);
		for(int i=n;i<len;i++) b[i]=cmplex();
		init(len);
		FFT(a,len,0),FFT(b,len,0);
		for(int i=0;i<len;i++) a[i]=a[i]*b[i];
		FFT(a,len,1);
	}

	void work()
	{
		int n,len;
		scanf("%d",&n);
		for(len=1;len<=n+n;len<<=1);
		for(int i=0;i<n;i++) scanf("%lf",&arr[i]);
		static cmplex ans1[N],ans2[N];
		query(n,len,ans1);
		reverse(arr,arr+n);
		query(n,len,ans2,1);
		for(int i=0;i<n;i++)
			printf("%.5f\n",ans1[i].re-ans2[n-i-1].re);
	}
}

int main()
{
	TYC::work();
	return 0;
}
