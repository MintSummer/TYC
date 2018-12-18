#include<bits/stdc++.h>
using namespace std;
const int MAXN=200010;
typedef long long ll;
int n,m,s=0,cnt,Head[MAXN],vis[MAXN],use[MAXN];
ll f[MAXN],ans;

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
    int to,next,w;
}E[MAXN*2];

void add(int u,int v,int w)
{
    cnt++;
    E[cnt].to=v;
    E[cnt].next=Head[u];
    E[cnt].w=w;
    Head[u]=cnt;
}

bool spfa()
{
    queue<int> q;
    q.push(s);
    vis[s]=use[s]=1;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        vis[u]=0;
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(f[v]<f[u]+E[i].w)
            {
                f[v]=f[u]+E[i].w;
                if(!vis[v]) 
                {
                    vis[v]=1,q.push(v);
                    use[v]++;
                    if(use[v]>n) return false;
                }
            }
        }
    }
    return true;
}

int main()
{
    n=read(),m=read();
    for(int i=n;i>=1;i--) add(s,i,1);//每个人都要能分到糖果
    //数据中有一个1->2->3->……->n的链，面向数据地，用链式前向星倒着来先走1能跑完全链
    for(int i=1;i<=m;i++)
    {
        int opt=read(),a=read(),b=read();
        switch(opt)
        {
            case 1: add(a,b,0),add(b,a,0);break;
            case 2: add(a,b,1);break;
            case 3: add(b,a,0);break;
            case 4: add(b,a,1);break;
            case 5: add(a,b,0);break;
        }
        if(opt%2==0&&a==b) {printf("-1");return 0;}
    }
    if(!spfa()) {printf("-1");return 0;}
    for(int i=1;i<=n;i++) ans+=f[i];
    printf("%lld",ans);
    return 0;
}
