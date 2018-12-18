#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    typedef pair<ll,ll> pll;
    const int N=100010,inf=0x3f3f3f3f;
    int n,city[2][N][22];
    ll height[N],disA[2][N][22],disB[2][N][22];

    inline ll read()
    {
        ll x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }
    
    inline ll Abs(ll x) {return x<0?-x:x;}

    struct node
    {
        int id,h;
        bool operator < (const node &t) const
        {
            return h!=t.h?h<t.h:id<t.id;
        }
    };
    set<node> S;
    set<node>::iterator it;

    bool cmp(const node &x,const node &y)
    {
        return x.h!=y.h?x.h<y.h:height[x.id]<height[y.id];
    }

    void init()
    {
        for(int i=n;i;i--)
        {
            node now=(node){i,height[i]};
            S.insert(now);
            it=S.find((node){i,height[i]});
            node tmp[8];
            int num=0;
            if(it!=(--S.end())) ++it,tmp[++num]=(node){(*it).id,Abs(height[i]-(*it).h)};
            if(it!=(--S.end())) ++it,tmp[++num]=(node){(*it).id,Abs(height[i]-(*it).h)};
            it=S.find((node){i,height[i]});
            if(it!=S.begin()) --it,tmp[++num]=(node){(*it).id,Abs(height[i]-(*it).h)};
            if(it!=S.begin()) --it,tmp[++num]=(node){(*it).id,Abs(height[i]-(*it).h)};
            sort(tmp+1,tmp+num+1,cmp);
            
            if(num>1)
            {
                city[0][i][0]=tmp[2].id;
                disA[0][i][0]=tmp[2].h;
                disB[0][i][0]=0;
            }
            if(num>0)
            {
                city[1][i][0]=tmp[1].id;
                disA[1][i][0]=0;
                disB[1][i][0]=tmp[1].h;
            }
        }
        for(int i=1;i<=n;i++)
        {
            city[0][i][1]=city[1][city[0][i][0]][0];
            disA[0][i][1]=disA[0][i][0];
            disB[0][i][1]=Abs(height[city[0][i][1]]-height[city[0][i][0]]);
            city[1][i][1]=city[0][city[1][i][0]][0];
            disA[1][i][1]=Abs(height[city[1][i][1]]-height[city[1][i][0]]);
            disB[1][i][1]=disB[1][i][0];
        }
        for(int j=2;j<=20;j++)
            for(int i=1;i<=n;i++)
            {
                int f=city[0][i][j-1];
                city[0][i][j]=city[0][f][j-1];
                disA[0][i][j]=disA[0][i][j-1]+disA[0][f][j-1];
                disB[0][i][j]=disB[0][i][j-1]+disB[0][f][j-1];

                f=city[1][i][j-1];
                city[1][i][j]=city[1][f][j-1];
                disA[1][i][j]=disA[1][i][j-1]+disA[1][f][j-1];
                disB[1][i][j]=disB[1][i][j-1]+disB[1][f][j-1];
            }
    }

    inline pll travel(int s,ll tot)
    {
        ll A=0,B=0;
        int flag=0;
        for(int i=17;i>=0;i--)
            if(city[0][s][i] && A+B+disA[0][s][i]+disB[0][s][i]<=tot)
            {
                A+=disA[0][s][i];
                B+=disB[0][s][i];
                s=city[0][s][i];
                if(i==0) flag=1;
            }
        if(flag&&A+B+disB[1][s][0]<=tot) B+=disB[1][s][0];
        return make_pair(A,B);
    }

    void work()
    {
        n=read();
        for(int i=1;i<=n;i++) height[i]=read();
        init();
        #define INF (double)1e18
        int s,ans=0;
        ll x=read();
        double mn=(double)1e20;
        for(int i=1;i<=n;i++)
        { 
            pll p=travel(i,x);
            if(!p.second)
            {
                if(mn>INF) mn=INF,ans=i;
                else if(mn==INF&&height[ans]<height[i]) ans=i;
            }
            else
            {
                double now=(double)p.first/(double)p.second;
                if(mn>now) mn=now,ans=i;
                else if(mn==now&&height[ans]<height[i]) ans=i;
            }
        }   
        printf("%d\n",ans);
        #undef INF
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