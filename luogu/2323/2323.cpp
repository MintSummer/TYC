//这个题目好像排序了就不对...(反正我没弄出来)
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
    const int N=10010;
    int n,k,m,tot,fa[N];

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    struct edge
    {
        int u,v,w;
    }E1[N<<1],E2[N<<1];
    
    struct Road
    {
    	int id,x;
    }tmp[N<<1],choose[N<<1];

    int find(int a)
    {
        return a==fa[a]?a:fa[a]=find(fa[a]);
    }

    bool check(int limit)
    {
        for(int i=1;i<=n;i++) fa[i]=i;
        int cnt=0;
        for(int i=1;i<m;i++)
        {
            if(E1[i].w>limit) continue;
            int u=find(E1[i].u),v=find(E1[i].v);
            if(u!=v) 
            {
                fa[u]=v;
                tmp[++cnt]=(Road){i,1};
            }
        }
        if(cnt<k) return false;
        for(int i=1;i<m;i++)
        {
            if(E2[i].w>limit) continue;
            int u=find(E2[i].u),v=find(E2[i].v);
            if(u!=v) 
            {
                fa[u]=v;
                tmp[++cnt]=(Road){i,2};
            }	
        }
        if(cnt>=n-1) 
        {
        	for(int i=1;i<=cnt;i++) choose[i]=tmp[i];
        	tot=cnt;
        	return true;
        }
        return false;
    }

    void work()
    {
        n=read(),k=read(),m=read();
        int l=0,r=0,ans=1,mid;
        for(int i=1;i<m;i++)
        {
            int u=read(),v=read(),w1=read(),w2=read();
            E1[i]=(edge){u,v,w1};
            E2[i]=(edge){u,v,w2};
            r=max(r,w1);
        }
        while(l<=r)
        {
            mid=(l+r)>>1;
            if(check(mid)) ans=mid,r=mid-1;
            else l=mid+1;
        }
        printf("%d\n",ans);
        for(int i=1;i<=tot;i++) 
        	printf("%d %d\n",choose[i].id,choose[i].x);
    }
}

int main()
{
    TYC::work();
    return 0;
}
