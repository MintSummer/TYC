//小根堆+贪心合并 小的*2<较小的 时直接排除小的
//但N 1e7,桶排+用单调队列维护加的和(必然有序)
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N=1e7+10;
    int n,m,seed,a[N],b[N];
    ll ans,q[N];

    void generate_array(int a[], int n, int m, int seed) 
    {
        unsigned x = seed;
        for (int i = 1; i <= n; ++i) 
        {
            x ^= x << 13;
            x ^= x >> 17;
            x ^= x << 5;
            a[i] = x % m + 1;
        }
    }

    void work()
    {
        scanf("%d%d%d",&n,&m,&seed);
        generate_array(a,n,m,seed);
        for(int i=1;i<=n;i++) 
	    b[a[i]]++,ans=max(ans,(ll)a[i]);
		int tot=0;
		for(int i=1;i<=m;i++)
			while(b[i]--) a[++tot]=i;
		int h=1,t=0;
		for(int i=1;i<=n;)
		{
			ll x,y;
			if(h<=t&&q[h]<a[i])
			{
			   	x=q[h++];
				if(h<=t&&q[h]<a[i]) 
				{
					y=q[h++];
					if(x*2<y) {h--;continue;}
					else 
					{
						ans=max(ans,x*2);
						q[++t]=x*2;
					}
				}
				else
				{ 
					y=a[i++];
					if(x*2<y) {i--;continue;}
					else
					{
						ans=max(ans,x*2);
						q[++t]=x*2;
					}
				}
			}
			else
			{
				x=a[i++];
				if((h<=t&&q[h]<a[i])||i>n) 
				{
					y=q[h++];
					if(x*2<y) {h--;continue;}
					else
					{
						ans=max(ans,x*2);
						q[++t]=x*2;
					}
				}
				else 
				{
					y=a[i++];
					if(x*2<y) {i--;continue;}
					else
					{
						ans=max(ans,x*2);
						q[++t]=x*2;
					}
				}
			}
		}
		if(h==t) ans=max(ans,q[h]);	
		while(h+1<=t)
		{
			ll x=q[h++],y=q[h++];
			if(x*2<y) {h--;continue;}
			ans=max(ans,x*2);
			q[++t]=x*2;
		}
		printf("%lld",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
