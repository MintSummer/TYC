#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=1<<20|5;
	const ll p=1e9+7;
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

	void init(int n)
	{
		for(int i=0;i<n;i++)
			w[i]=cmplex(cos(2*PI*i/n),sin(2*PI*i/n));
		for(int i=0;i<n;i++)
			rev[i]=(rev[i>>1]>>1)|((n>>1)*(i&1));
	}

	void FFT(cmplex a[],int n,const int type)
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

	ll Manacher(char *str,int len)
	{
		static int f[N<<1];
		static char ch[N<<1];
		int n=0;
		ch[0]='$',ch[++n]='#';
		for(int i=1;i<=len;i++)
			ch[++n]=str[i],ch[++n]='#';
		int mid=0,mx=0;
		ll tot=0;
		for(int i=1;i<=n;i++)
		{
			if(i<=mx) f[i]=min(f[mid*2-i],mx-i);
			else f[i]=1;
			while(i-f[i]>=1&&i+f[i]<=n&&ch[i-f[i]]==ch[i+f[i]]) f[i]++;
			if(i+f[i]>=mx) mid=i,mx=i+f[i];
			tot+=f[i]>>1;
		}
		return tot%p;
	}

	void work()
	{
		static char str[N];
		scanf("%s",str+1);
		int n=strlen(str+1),len,m=n<<1;
		for(len=1;len<=m;len<<=1);
		init(len);
		static cmplex a[N],b[N];
		for(int i=1;i<=n;i++) 
			if(str[i]=='a') a[i]=cmplex(1.0);
		FFT(a,len,0);
		for(int i=0;i<len;i++) b[i]=a[i]*a[i];
		memset(a,0,sizeof(a));
		for(int i=1;i<=n;i++) 
			if(str[i]=='b') a[i]=cmplex(1.0);
		FFT(a,len,0);
		for(int i=0;i<len;i++) b[i]=b[i]+a[i]*a[i];
		FFT(b,len,1);
		static int tmp[N];
		for(int i=1;i<len;i++) 
			tmp[i]=int((b[i].re+0.5)/len);
		ll ans=0;
		static ll Pow[N];Pow[0]=1;
		for(int i=1;i<len;i++) Pow[i]=(Pow[i-1]<<1)%p;
		for(int i=1;i<len;i++)
			ans+=Pow[(tmp[i]+1)>>1]-1,ans%=p;
		printf("%lld\n",(ans-Manacher(str,n)+p)%p);
	}
}
int main()
{
	TYC::work();
	return 0;
}
