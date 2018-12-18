#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=100010;
	int n;

	struct node
	{
		int pos,tag;
		bool operator < (const node &t) const
		{
			return (pos<t.pos)||(pos==t.pos&&tag>t.tag);
		}
	}a[N<<1];

	void work()
	{
		scanf("%d",&n);
		int l,r;
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d",&l,&r);
			a[(i<<1)-1]=(node){l,1};
			a[(i<<1)]=(node){r,0};
		}
		n<<=1;
		sort(a+1,a+1+n);
		int num=0;
		ll ans=0;
		for(int i=1;i<=n;i++)
		{
			if(!a[i].tag)
			{
				ans=max(ans,(ll)num*a[i].pos);
				num--;
			}
			else num++;
		}
		printf("%lld\n",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
