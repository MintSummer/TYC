#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int MAXN=1e6+10;
    int n,now,cnt,l[MAXN],r[MAXN],root[MAXN],son[MAXN][2],size[MAXN],dis[MAXN],a[MAXN],v[MAXN],num[MAXN];

    inline int read()
    {
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
    }

    inline int newnode(ll x)
    {
		v[++cnt]=x;
		size[cnt]=1;
		son[cnt][0]=son[cnt][1]=0;
		dis[cnt]=0;
		return cnt;
    }

    int merge(int x,int y)
    {
		if(!x||!y) return x+y;
		if(v[x]<v[y]) swap(x,y);
		son[x][1]=merge(son[x][1],y);
		size[x]=size[son[x][0]]+size[son[x][1]]+1;
		if(dis[son[x][1]]>dis[son[x][0]]) 
			swap(son[x][0],son[x][1]);
		dis[x]=dis[son[x][1]]+1;
		return x;
    }

    inline void del(int &x)
    {
		x=merge(son[x][0],son[x][1]);
    }

    void work()
    {
		n=read();
		for(int i=1;i<=n;i++) a[i]=read()-i;
		for(int i=1;i<=n;i++)
		{
			now++;
			l[now]=r[now]=i;
			root[now]=newnode(a[i]);
			num[now]=1;
			while(now>1&&v[root[now-1]]>v[root[now]])
			{
				now--;
				root[now]=merge(root[now],root[now+1]);
				r[now]=r[now+1];
				num[now]+=num[now+1];
				while(size[root[now]]*2>num[now]+1) del(root[now]);
			}
		}
		ll ans=0;
		for(int i=1;i<=now;i++)
		{
			int tmp=v[root[i]];
			for(int j=l[i];j<=r[i];j++)
			ans+=abs(a[j]-tmp);
		} 
		printf("%lld",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
