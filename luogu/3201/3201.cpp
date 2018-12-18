#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int MAXN=1e6+10;
    int n,m,ans,a[MAXN],fa[MAXN];
    set<int> col[MAXN];
    set<int>::iterator it;

    inline int read()
    {
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
    }

    void change(int x,int to)
    {
		for(it=col[x].begin();it!=col[x].end();it++)
		{
		    int now=*it;
		    if(a[now-1]==to) ans--;
		    if(a[now+1]==to) ans--;
		    col[to].insert(now);
		}
		for(it=col[x].begin();it!=col[x].end();it++)
		    a[*it]=to;
		col[x].clear();
    }

    void work()
    {
		n=read(),m=read();
		for(int i=1;i<=n;i++)
		{
		    a[i]=read();
		    if(a[i]!=a[i-1]) ans++;
		    fa[a[i]]=a[i]; 
		    col[a[i]].insert(i);
		}
		while(m--)
		{
		    int opt=read();
		    if(opt==1)
		    {
				int x=read(),y=read();
				if(x==y) continue;
				if(col[fa[x]].size()>col[fa[y]].size()) swap(fa[x],fa[y]);
				change(fa[x],fa[y]);
		    }
		    else printf("%d\n",ans);
		}
    }
}

int main()
{
    TYC::work();
    return 0;
}
