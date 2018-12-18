#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=1<<21|5;
	const double PI=3.1415926535897932384626;

	struct cmplex
	{
		double re,im;
		cmplex(double _re=0.0,double _im=0.0): re(_re),im(_im){}
		cmplex operator +(const cmplex &t) const {return cmplex(re+t.re,im+t.im);}
		cmplex operator -(const cmplex &t) const {return cmplex(re-t.re,im-t.im);}
		cmplex operator *(const cmplex &t) const {return cmplex(re*t.re-im*t.im,re*t.im+im*t.re);}
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
				for(int k=j,l=0;k<i+j;k++,l+=d)
				{
					cmplex x=a[k],y=a[k+i]*w[l];
					a[k]=x+y;
					a[k+i]=x-y;
				}
	}

	void work()
	{
		ios::sync_with_stdio(false);
		cin.tie(0);
		int n,m;
		static cmplex a[N],b[N];
		static string A,B;
		cin>>n>>A>>B;
		for(int i=0;i<n;i++) a[n-i-1].re=A[i]-'0';
		for(int i=0;i<n;i++) b[n-i-1].re=B[i]-'0';
		for(m=n+n,n=1;n<=m;n<<=1);
		init(n);
		FFT(a,n,0),FFT(b,n,0);
		for(int i=0;i<n;i++) a[i]=a[i]*b[i];
		FFT(a,n,1);
		static int ans[N];
		for(int i=0;i<m;i++)
		{
			int x=(int)(a[i].re/n+0.5);
			for(int num=i;x;x/=10,num++) ans[num]+=x%10;
		}
		for(int i=0;i<m;i++)
			if(ans[i]>=10) ans[i+1]+=ans[i]/10,ans[i]%=10;
		while(!ans[m]) m--;
		for(int i=m;i>=0;i--) putchar('0'+ans[i]);
	}
}

int main()
{
	TYC::work();
	return 0;
}
