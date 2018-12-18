#include<bits/stdc++.h>
using namespace std;
const double eps=1e-8;
const int MAXN=510;
int n,m,s,t,Head[MAXN],fa[MAXN];

int read()
{
    int x=0,f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return f?-x:x;
}

struct edge
{
    int u,v,w;
    bool operator < (const edge &a) const
    {
		return w<a.w;
    }
}E[5010];

int find(int x)
{
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

int gcd(int a,int b)
{
    return !b?a:gcd(b,a%b);
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++)
    {
		int u=read(),v=read(),w=read();
		E[i]=(edge){u,v,w};	
    }
    s=read(),t=read(); 

    sort(E+1,E+1+m);
    int flag=0,ansmn=1,ansmx=0x3f3f3f3f;
    for(int i=1;i<=m;i++)
    {
		int mn=0x3f3f3f3f,mx=0,ok=0;  
		for(int j=1;j<=n;j++) fa[j]=j;
		for(int j=i;j<=m;j++)
		{
			int fu=find(E[j].u),fv=find(E[j].v);
			if(fu!=fv)
			{
				fa[fu]=fv;
				mn=min(E[j].w,mn),mx=max(E[j].w,mx);
			}
			if(find(s)==find(t)) {ok=1;break;}
		}
		flag|=ok;
		if(ok&&(double)ansmx/ansmn-(double)mx/mn>eps) ansmn=mn,ansmx=mx;
    }

    if(!flag) printf("IMPOSSIBLE");
    else
    {
		int d=gcd(ansmx,ansmn);
		if(ansmn==d) printf("%d",ansmx/d);
		else printf("%d/%d",ansmx/d,ansmn/d);
    }
    return 0;
}
