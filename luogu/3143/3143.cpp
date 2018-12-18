#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
    const int N=50010;
    int n,k,ans,a[N],f[N];

    bool cmp(const int &x,const int &y)
    {
		return x<=y;
    }

    void work()
    {
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		sort(a+1,a+1+n);
		for(int i=1;i<=n;i++) 
			f[i]=lower_bound(a+1,a+1+n,a[i]+k,cmp)-a-i;
		for(int i=n;i;i--)
		{
			ans=max(ans,f[i]+f[i+f[i]]);
			f[i]=max(f[i],f[i+1]);//将最优解压在一个点上,保证27行计算的正确性
		}
		printf("%d",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
