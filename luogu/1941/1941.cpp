#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=10010,inf=0x3f3f3f3f;
    int n,m,num,up[N],down[N],dp[1010],tmp[1010];

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    struct Obstacle
    {
        int pos,l,r;
        bool operator < (const Obstacle &t) const
        {
            return pos<t.pos;
        }
    }node[N];

    void work()
    {
        n=read(),m=read(),num=read();
        for(int i=1;i<=n;i++) 
            up[i]=read(),down[i]=read();
        for(int i=1;i<=num;i++)
            node[i]=(Obstacle){read(),read(),read()};
        sort(node+1,node+1+num);
        memset(dp,inf,sizeof(int[m+1]));
        int point=1;
        for(int i=1;i<=n;i++)
        {
            if(i==1) 
            {
                for(int j=1;j<=m;j++) dp[min(j+up[i],m)]=1;
                for(int j=m;j>=down[i]+1;j--) dp[j-down[i]]=0;
            }
            else
            {
                memcpy(tmp,dp,sizeof(int[m+1]));
                memset(dp,inf,sizeof(int[m+1]));
                for(int j=1;j<=m;j++)
                    {
                        int h=min(j+up[i],m);
                        dp[h]=min(dp[h],min(dp[j]+1,tmp[j]+1));
                    }
                for(int j=down[i]+1;j<=m;j++)
                    dp[j-down[i]]=min(dp[j-down[i]],tmp[j]);
            }
            if(node[point].pos==i)
            {
                for(int j=1;j<=node[point].l;j++) dp[j]=inf;
                for(int j=node[point].r;j<=m;j++) dp[j]=inf;
                int flag=0;
                for(int j=node[point].l+1;j<node[point].r;j++)
                    if(dp[j]!=inf) {flag=1;break;}
                if(!flag) {printf("0\n%d\n",point-1);return;}
                point++;
            }
        }
        puts("1");
        int ans=inf;
        for(int i=1;i<=m;i++) ans=min(ans,dp[i]);
        printf("%d\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}