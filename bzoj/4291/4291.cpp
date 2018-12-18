#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	int n,a,ans,num,mn=0x3f3f3f3f;
	void work()
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a);
			ans+=a;
			if(a&1) num++,mn=min(mn,a);
		}
		ans-=(num&1)*mn;
		if(ans) printf("%d\n",ans);
		else printf("NIESTETY\n");
	}
}

int main()
{
	TYC::work();
	return 0;
}
