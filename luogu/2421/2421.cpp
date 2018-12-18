#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int M=1e6;
    int n,c[20],p[20],l[20];

    int gcd(int a,int b)
    {
		return b==0?a:gcd(b,a%b);
    }

    void exgcd(int a,int b,int &x,int &y)
    {
		if(!b) {x=1,y=0;return;}
		exgcd(b,a%b,x,y);
		int tmp=x;
		x=y;
		y=tmp-a/b*y;
    }

    bool check(int ans)
    {
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
			{
				int a=p[i]-p[j],b=ans,m=c[j]-c[i],x,y;
				int g=gcd(a,b);
				if(m%g==0)
				{
				    a/=g,b/=g,m/=g;
				    exgcd(a,b,x,y);
				    b=abs(b);
				    x=(x*m%b+b)%b;
				    if(!x) x+=b;
				    if(x<=min(l[i],l[j])) return false;
				}
			}
		return true;
    }

    void work()
    {
		scanf("%d",&n);
		int ans=0;
		for(int i=1;i<=n;i++) 
		{
			scanf("%d%d%d",&c[i],&p[i],&l[i]);
			ans=max(ans,c[i]);
		}
		for(ans=max(n,ans);;ans++)
			if(check(ans)) {printf("%d",ans);return;}
    }	
}

int main()
{
    TYC::work();
    return 0;
}
