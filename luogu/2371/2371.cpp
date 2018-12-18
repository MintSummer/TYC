#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,int> pa;
const int MAXN=5*1e5+10;
int n,p,cnt,a[15],Head[MAXN],vis[MAXN];
ll Bmin,Bmax,ans,f[MAXN];
priority_queue<pa,vector<pa>,greater<pa> > q;

struct edge
{
    int to,next,w;
}E[5000010];

void add(int u,int v,int w)
{
    cnt++;
    E[cnt].to=v;
    E[cnt].next=Head[u];
    E[cnt].w=w;
    Head[u]=cnt;
}

void Dijkstra()
{
    //f[i]：i至少要加上f[i]才能进入一个余数环（均可以达到）
    //例如：当p==4，i==2时,f[i]==4能使i+f[i]后加上多少个p余数均为i
    for(int i=0;i<p;i++) f[i]=(ll)1e30;
    f[0]=0;
    q.push(make_pair(f[0],0));
    while(!q.empty())
    {
        int u=q.top().second;
        q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(f[v]>f[u]+E[i].w)
                f[v]=f[u]+E[i].w,q.push(make_pair(f[v],v));
        }
    }
}

int main()
{
    scanf("%d%lld%lld",&n,&Bmin,&Bmax);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    sort(a+1,a+1+n);
    p=a[1];//用最小的a作为模数，减少余数的情况
    for(int i=0;i<p;i++)
        for(int j=2;j<=n;j++)
            add(i,(i+a[j])%p,a[j]);
    Dijkstra();
    for(int i=0;i<p;i++)//求余数为i的情况对ans的贡献
        if(f[i]<=Bmax)//f[i]>Bmax就没有讨论的意义了
        {
            ll lt=max(0LL,(Bmin-f[i])/p);
            if(lt*p+f[i]<Bmin) lt++;//至少要有lt个p使得lt*p+f[i]在范围内
            ll rt=(Bmax-f[i])/p;
            if(rt*p+f[i]>Bmax) rt--;//至多能有rt个p使得rt*p+f[i]在范围内
            ans+=rt-lt+1;//求余数i能够产生的解
        }
    printf("%lld",ans);
    return 0;
}
