#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
 
namespace TYC
{
    const int N=10010;
    int n,k,m,fa[N],choose[N<<1];
 
    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }
 
    struct edge
    {
        int id,u,v,w;
        bool operator < (const edge &a) const
        {
            return w<a.w;
        }
    }E1[N<<1],E2[N<<1];
 
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
            if(E1[i].w>limit) break;
            int u=find(E1[i].u),v=find(E1[i].v);
            if(u!=v) 
            {
                fa[u]=v;
                choose[E1[i].id]=1;
                ++cnt;
            }
        }
        if(cnt<k) return false;
        for(int i=1;i<m;i++)
        {
            if(E2[i].w>limit) break;
            int u=find(E2[i].u),v=find(E2[i].v);
            if(u!=v) 
            {
                fa[u]=v;
                choose[E2[i].id]=2;
                ++cnt;
            }   
        }
        if(cnt>=n-1) return true;
        return false;
    }
 
    void work()
    {
        n=read(),k=read(),m=read();
        int l=0,r=0,ans=1,mid;
        for(int i=1;i<m;i++)
        {
            int u=read(),v=read(),w1=read(),w2=read();
            E1[i]=(edge){i,u,v,w1};
            E2[i]=(edge){i,u,v,w2};
            r=max(r,w1);
        }
        sort(E1+1,E1+m);
        sort(E2+1,E2+m);
        while(l<=r)
        {
            mid=(l+r)>>1;
            if(check(mid)) ans=mid,r=mid-1;
            else l=mid+1;
        }
        printf("%d\n",ans);/
    }
}
 
int main()
{
    TYC::work();
    return 0;
}
