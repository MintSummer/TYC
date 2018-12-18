#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<string>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int MAXN=300010;
    char s[MAXN];
    int tot,Head[MAXN];

    struct edge
    {
		int to,next;
    }E[MAXN*2];

    void add(int u,int v)
    {
		tot++;
		E[tot].to=v;
		E[tot].next=Head[u];
		Head[u]=tot;
    }

    struct PAM
    {
		int even,odd,cnt,now,son[MAXN][26],size[MAXN],len[MAXN],fail[MAXN];
		//size[i]表示节点i的串出现次数(要加上所有fail树中i的所有儿子的size的和才是真正的)
		PAM()
		{
			odd=++cnt,even=++cnt;
			fail[odd]=fail[even]=odd;
			len[odd]=-1,len[even]=0;
			now=even;
		}
		void insert(int pos,char c)
		{
			while(s[pos-1-len[now]]!=c) now=fail[now];
			if(!son[now][c-'a'])
			{
				son[now][c-'a']=++cnt;
				len[cnt]=len[now]+2;
				if(now==odd) fail[cnt]=even;
				else 
				{
					int tmp=fail[now];
					while(s[pos-1-len[tmp]]!=c) tmp=fail[tmp];
					fail[cnt]=son[tmp][c-'a'];
				}
			}
			now=son[now][c-'a'];
			size[now]++;
		}
		void build_fail()
		{
			for(int i=2;i<=cnt;i++) add(fail[i],i);
		}
		void dfs(int u)
		{
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				dfs(v);
				size[u]+=size[v];
			}
		}//深搜fail树得到每个串的出现次数
    }pam;

    void work()
    {
		scanf("%s",s);
		int len=strlen(s);
		for(int i=0;i<len;i++) 
			pam.insert(i,s[i]);
		ll ans=0;
		pam.build_fail();
		pam.dfs(pam.odd);
		for(int i=1;i<=pam.cnt;i++)
			ans=max(ans,(ll)pam.size[i]*pam.len[i]);
		printf("%lld",ans);
	}
}

int main()
{
    TYC::work();
    return 0;
}
