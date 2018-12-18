#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    typedef pair<ll,ll> pll;
    const int N=1010,inf=0x3f3f3f3f;
    int n,to[N][2];
    ll height[N],dis[N][N];

    inline ll read()
    {
        ll x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }
    
    inline ll Abs(ll x) {return x<0?-x:x;}

    inline void init()
    {
        for(int i=1;i<=n;i++)
        {
            int mn=0,smn=0;
            for(int j=i+1;j<=n;j++)
            {
                dis[i][j]=Abs(height[i]-height[j]);
                if(!mn||dis[i][j]<dis[i][mn]||
                    (dis[i][j]==dis[i][mn]&&height[mn]>height[j])) smn=mn,mn=j;
                else if(!smn||dis[i][j]<dis[i][smn]||
                    (dis[i][j]==dis[i][smn]&&height[smn]>height[j])) smn=j;
            }
            to[i][0]=smn,to[i][1]=mn;
        }
    }

    inline pll travel(int s,int tot)
    {
        int now=0;
        ll D[2]={0,0};
        while(tot)
        {
            int t=to[s][now];
            if(!t||dis[s][t]>tot) break;
            D[now]+=dis[s][t];
            tot-=dis[s][t];
            s=t;
            now^=1;
        }
        return make_pair(D[0],D[1]);
    }

    void work()
    {
        n=read();
        for(int i=1;i<=n;i++) height[i]=read();
        init();
        int x=read(),s,ans=0;
        ll a=0,b=0;
        for(int i=1;i<=n;i++)
        { 
            pll p=travel(i,x);
            if(!a&&!b) 
            {
                a=p.first,b=p.second;
                ans=i;
                continue;
            }
            ll ta=p.first*b,tb=p.second*a;//不要用除法,精度会挂
            if(!p.first) continue;
            if(ta<tb) ans=i,a=p.first,b=p.second;
            else if(ta==tb&&height[ans]<height[i]) ans=i;
        }   
        printf("%d\n",ans);
        int m=read();
        while(m--)
        {
            s=read(),x=read();
            pll p=travel(s,x);
            printf("%lld %lld\n",p.first,p.second);
        }
    }
}

int main()
{
    TYC::work();
    return 0;
}