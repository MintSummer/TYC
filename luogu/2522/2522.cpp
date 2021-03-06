#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=50010;
    int cnt,mu[N],vis[N],prime[N],sum[N];

    void init()
    {
		mu[1]=1;
		for(int i=2;i<=50000;i++)
		{
			if(!vis[i]) prime[++cnt]=i,mu[i]=-1;
			for(int j=1;j<=cnt&&i*prime[j]<=50000;j++)
			{
				vis[i*prime[j]]=1;
				if(i%prime[j]==0) break;
				mu[i*prime[j]]=-mu[i];
			}
		}
		for(int i=1;i<=50000;i++) sum[i]=sum[i-1]+mu[i];
    }	

    int query(int x,int y)
    {
		if(x>y) swap(x,y);
		int ans=0;
		for(int i=1,tmp;i<=x;i=tmp+1)
		{
			tmp=min(x,min(x/(x/i),y/(y/i)));
			ans+=(sum[tmp]-sum[i-1])*(x/i)*(y/i);
		}
		return ans;
    }

    void work()
    {
		int n;
		scanf("%d",&n);
		init();
		while(n--)
		{
			int a,b,c,d,k;
			scanf("%d%d%d%d%d",&a,&b,&c,&d,&k);
			a=ceil((double)a/k);
			b=floor((double)b/k);
			c=ceil((double)c/k);
			d=floor((double)d/k);
			printf("%d\n",query(b,d)-query(a-1,d)-query(b,c-1)+query(a-1,c-1));
		}
    }
}

int main()
{
    TYC::work();
    return 0;
}
