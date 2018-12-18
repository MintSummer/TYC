#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
const int N=100010;

namespace Trie
{
    int cnt,val[N*15],son[N*15][26];
	
    void insert(int &root,int last,char *ch)
    {
		int len=strlen(ch);
		root=++cnt;
		int tmp=root;
		for(int i=0;i<len;i++)
		{
			val[root]=val[last]+1;
			for(int j=0;j<26;j++) son[root][j]=son[last][j];
			int c=ch[i]-'a';
			root=son[root][c]=++cnt;
			last=son[last][c];
		}
		val[root]=val[last]+1;
		root=tmp;
    }

    int query(int root,char *ch)
    {
		int len=strlen(ch);
		for(int i=0;i<len;i++)
			root=son[root][ch[i]-'a'];
		return val[root];
    }
}

namespace TYC 
{
    int n,m,cnt,Head[N],root[N],fa[N][20],dep[N];
    char ch[N*2][15];

    struct edge
    {
		int to,next;
    }E[N*2];

    void add(int u,int v,char *tmp)
    {
		E[++cnt]=(edge){v,Head[u]};
		Head[u]=cnt;
		memcpy(ch[cnt],tmp,sizeof(ch[cnt]));
    }

    void dfs(int u)
    {
		for(int i=1;i<=18;i++)
			fa[u][i]=fa[fa[u][i-1]][i-1];
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==fa[u][0]) continue;
			fa[v][0]=u;
			dep[v]=dep[u]+1;
			Trie::insert(root[v],root[u],ch[i]);
			dfs(v);
		}
    }

    int lca(int u,int v)
    {
		if(dep[u]<dep[v]) swap(u,v);
		for(int d=dep[u]-dep[v],i=0;d;d>>=1,i++)
			if(d&1) u=fa[u][i];
		if(u==v) return u;
		for(int i=18;i>=0;i--)
			if(fa[u][i]!=fa[v][i])
				u=fa[u][i],v=fa[v][i];
		return fa[u][0];
    }

    void work()
    {
		scanf("%d",&n);
		int u,v;
		char tmp[15];
		for(int i=1;i<n;i++)
		{
			scanf("%d%d%s",&u,&v,tmp);
			add(u,v,tmp),add(v,u,tmp);
		}
		dep[1]=1;
		dfs(1);
		scanf("%d",&m);
		char ques[15];
		while(m--)
		{
			scanf("%d%d%s",&u,&v,ques);
			int ans=Trie::query(root[u],ques)+Trie::query(root[v],ques);
			ans-=Trie::query(root[lca(u,v)],ques)*2;
			printf("%d\n",ans);
		}
    }
}

int main()
{
    TYC::work();
    return 0;
}
