#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=1e6+10;

	namespace SAM
	{
		int tot=1,last=1;

		struct node
		{
			int fa,mx,size,son[26];
		}tr[N<<2];

		inline void insert(const int c)
		{
			int now=++tot,p=last;
			tr[now].size=1;
			tr[now].mx=tr[p].mx+1;
			while(p&&!tr[p].son[c])
				tr[p].son[c]=now,p=tr[p].fa;
			if(p==0) tr[now].fa=1;
			else
			{
				int q=tr[p].son[c];
				if(tr[q].mx==tr[p].mx+1) tr[now].fa=q;
				else
				{
					int clone=++tot;
					tr[clone]=tr[q];
					tr[clone].size=0;
					tr[clone].mx=tr[p].mx+1;
					while(p&&tr[p].son[c]==q)
						tr[p].son[c]=clone,p=tr[p].fa;
					tr[q].fa=tr[now].fa=clone;
				}
			}
			last=now;
		}

		inline void radix_sort(const int &n)
		{
			static int bask[N],q[N<<2];
			for(int i=1;i<=tot;i++) bask[tr[i].mx]++;
			for(int i=2;i<=n;i++) bask[i]+=bask[i-1];
			for(int i=tot;i;i--) q[--bask[tr[i].mx]]=i;
			for(int i=tot;i;i--) 
			{
				node &now=tr[q[i]];
				tr[now.fa].size+=now.size;
			}
		}
	}

	void work()
	{
		static char s[N];
		scanf("%s",s);
		int len=strlen(s);
		for(int i=0;i<len;i++)
			SAM::insert(s[i]-'a');
		SAM::radix_sort(len);
		ll ans=0;
		for(int i=1;i<=SAM::tot;i++)
			if(SAM::tr[i].size!=1)
				ans=max(ans,(ll)SAM::tr[i].size*SAM::tr[i].mx);
		printf("%lld\n",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
