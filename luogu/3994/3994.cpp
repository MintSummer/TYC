#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	int T,n,m;

	void work()
	{
		scanf("%d",&T);
		while(T--)
		{
			scanf("%d%d",&n,&m);
			ll tot=n*m,ans=0;
			for(int i=1;i<=tot;i++)
				ans+=tot/i;
			printf("%lld\n",ans);
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
