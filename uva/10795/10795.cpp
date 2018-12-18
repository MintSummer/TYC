#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,s[70],e[70];

ll change(int *now,int x,int to)
{
    if(!x) return 0;
    if(now[x]==to) return change(now,x-1,to);
    else return change(now,x-1,6-now[x]-to)+(1LL<<(x-1));
}

int main()
{
    int kase=0;
    while(scanf("%d",&n)&&n)
    {
		kase++;
		for(int i=1;i<=n;i++) scanf("%d",&s[i]);
		int k=n;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&e[i]);
			if(e[i]==s[i]) k--;
		}
		ll ans=0;
		if(k)
		{   
			int other=6-s[k]-e[k];
			ans+=change(s,k-1,other)+change(e,k-1,other)+1;
		}
		printf("Case %d: %lld\n",kase,ans);
    }
}
