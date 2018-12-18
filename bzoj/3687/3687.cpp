//dp[j+a[i]]^=dp[j] 加了偶数次异或为0 那么每位只有01,可以压位或者用bitset
#include<cstdio>
#include<bitset>
using namespace std;

namespace TYC
{
    bitset<2000010> f;

    void work()
    {
		int n,x,sum=0,ans=0;
		scanf("%d",&n);
		f[0]=1;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&x);
			sum+=x;
			f^=(f<<x);//f<<x相当于给f中每个值+x
		}
		for(int i=1;i<=sum;i++)
			if(f[i]) ans^=i;
		printf("%d",ans);
    }	
}

int main()
{
    TYC::work();
    return 0;
}
