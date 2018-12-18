#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	namespace Trie
	{
		const int N=6000010;
		int cnt,son[N][10],num[N];
		vector<int> tim[N];

		void insert(char *s,int kase,int val,int n)
		{
			int len=strlen(s),now=0;
			for(int i=0;i<len;i++)
			{
				int c=s[i]-'a';
				if(!son[now][c]) son[now][c]=++cnt;
				now=son[now][c];
				num[now]+=val;
				if(val==1&&num[now]>tim[now].size()) 
					tim[now].push_back(kase);
			}
		}

		int query(char *s,int k)
		{
			int len=strlen(s),now=0;
			for(int i=0;i<len;i++)
			{
				int c=s[i]-'a';
				if(!son[now][c]) return -1;
				now=son[now][c];
			}
			return tim[now].size()>k?tim[now][k]:-1;
		}
	}

	void work()
	{
		int n,opt,ans=0,a,b,c;
		scanf("%d",&n);
		char name[70];
		for(int kase=1;kase<=n;kase++)
		{
			scanf("%d%s",&opt,name);
			if(opt<3) Trie::insert(name,kase,(opt==1?1:-1),n);
			else 
			{
				scanf("%d%d%d",&a,&b,&c);
				a=((long long)a*abs(ans)+b+c)%c;
				printf("%d\n",ans=Trie::query(name,a));
			}
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
