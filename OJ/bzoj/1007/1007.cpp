#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N=50010,inf=0x3f3f3f3f;
    int n,top,cnt,st[N],ans[N];

    struct Line
    {
        int id;
        double k,b;
        bool operator < (const Line &t) const
        {
            return (k<t.k)||(k==t.k&&b>t.b);
        }
    }line[N];

    double GetNode(int i,int j)
    {
        return (double)(line[i].b-line[j].b)/(line[j].k-line[i].k);
    }

    void work()
    {
        ios::sync_with_stdio(false);
        cin>>n;
        for(int i=1;i<=n;i++)
            cin>>line[i].k>>line[i].b,line[i].id=i;
        sort(line+1,line+1+n);
        for(int i=1;i<=n;i++)
        {
            if(i!=1&&line[i].k==line[i-1].k) continue;
            while(top>1&&GetNode(st[top],i)<=GetNode(st[top-1],st[top])) top--;
            st[++top]=i;
        }
        for(int i=1;i<=top;i++)
            ans[++cnt]=line[st[i]].id;
        sort(ans+1,ans+1+cnt);
        for(int i=1;i<=cnt;i++)
            printf("%d ",ans[i]);
    }
}

int main()
{
    TYC::work();
    return 0;
}