#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long double ld;
    const int N=100010;
	const ld eps=1e-6;

    int n;
    ld start,a[N],b[N],rate[N],f[N],g[N];

    inline double read()
    {
        double x=0;int f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        if(ch=='.')
        {
            double t=0.1;ch=getchar();
            while(isdigit(ch)) x+=(ch-'0')*t,t*=0.1,ch=getchar();
        }
        return f?-x:x;        
    }

    void work()
    {
        n=read(),start=read();
        for(int i=1;i<=n;i++) 
            a[i]=read(),b[i]=read(),rate[i]=read();
		f[1]=start;
        g[1]=start/(b[1]+a[1]*rate[1]);
		for(int i=2;i<=n;i++)
        {
            for(int j=1;j<i;j++) 
			{
				ld x=g[j]*b[i]+g[j]*rate[j]*a[i];
				f[i]=max(f[i],max(f[j],x));
			}
			g[i]=f[i]/(b[i]+rate[i]*a[i]);
        }
		printf("%.3f",(double)f[n]);
    }    
}

int main()
{
    TYC::work();
    return 0;
}
