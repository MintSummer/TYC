#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
    const int N=60;
    int n,root,son[N][2],fa[N],ans[N];
    #define ls son[x][0]
    #define rs son[x][1]

    void work()
    {
        scanf("%d",&n);n++;
        int x;
        for(int i=2;i<=n;i++)
        {
            scanf("%d",&x);x++;
            if(x<=100) fa[i]=x,ls=i;                
            else x-=100,fa[i]=x,rs=i;
        }
        root=1;
        for(int now=n;now;now--)
        {
            int x=root;
            while(rs) x=ls;
            if(ls&&!son[ls][0]&&!son[rs][0]) x=ls;
            ans[now]=x;
			int tmp=root;
            if(x==root) 
                fa[ls]=0,root=ls;
            else if(ls) 
                son[fa[x]][0]=ls,fa[ls]=fa[x];
            else 
                son[fa[x]][0]=0;
            while(x!=tmp)
                x=fa[x],swap(ls,rs);
        }
        for(int i=1;i<=n;i++) printf("%d ",ans[i]-1);
    }   
}

int main()
{
    TYC::work();
    return 0;
}
