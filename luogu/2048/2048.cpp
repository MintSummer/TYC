#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10;
int sum[N];

namespace RMQ
{
	int st[N][19];
    inline void init(int n)
    {
        for(int i=1;i<=19;i++)
            for(int j=1;j+(1<<i)-1<=n;j++)
            {
                int x=st[j][i-1],y=st[j+(1<<(i-1))][i-1];
                st[j][i]=(sum[x]>sum[y]?x:y);
            }
    }

    inline int query(int l,int r)
    {
        int k=log2(r-l+1);
        int x=st[l][k],y=st[r-(1<<k)+1][k];
        return sum[x]>sum[y]?x:y;
    }
}

namespace TYC
{
    typedef long long ll;
    struct node
    {
        int start,end,l,r;
        node(int _s,int _l,int _r) : start(_s),end(RMQ::query(_l,_r)),l(_l),r(_r) {}
        bool operator < (const node &t) const
        {
            return sum[end]-sum[start-1]<sum[t.end]-sum[t.start-1];
        }
    };
    priority_queue<node> q;

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    void work()
    {
        int n=read(),k=read(),L=read(),R=read();
        for(int i=1;i<=n;i++)
        {
            sum[i]=sum[i-1]+read();
			RMQ::st[i][0]=i;
        }
        RMQ::init(n);
        for(int i=1;i+L-1<=n;i++)
            q.push(node(i,i+L-1,min(i+R-1,n)));
        ll ans=0;
        while(k--)
        {
            node now=q.top();q.pop();
            ans+=sum[now.end]-sum[now.start-1];
            if(now.end!=now.l) q.push(node(now.start,now.l,now.end-1));
            if(now.end!=now.r) q.push(node(now.start,now.end+1,now.r));
        }
        printf("%lld\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
