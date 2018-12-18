#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=20,maxn=700,M=100005,mod=600;
struct edge{
    int link,next,w1,w2,opp;
}e[M];
int g[N][N],n,m,tot,S,T,head[maxn];
int xx[4]={0,0,-1,1},yy[4]={-1,1,0,0};
char s[N];
inline void add_edge(int u,int v,int w1,int w2){
    e[++tot]=(edge){v,head[u],w1,w2}; head[u]=tot;
}
inline void insert(int u,int v,int w1,int w2){
    add_edge(u,v,w1,w2); e[tot].opp=tot+1;
    add_edge(v,u,0,-w2); e[tot].opp=tot-1;
}
int id[200];
inline void init(){
    scanf("%d%d",&n,&m);
    id['L']=0; id['R']=1; id['U']=2; id['D']=3;
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            g[i][j]=(i-1)*m+j;
        }
    }
    for (int i=1;i<=n;i++){
        scanf("%s",s+1);
        for (int j=1;j<=m;j++){
            for (int k=0;k<4;k++){
                int X=(i+xx[k]-1+n)%n+1,Y=(j+yy[k]-1+m)%m+1;
                if (k==id[s[j]]){
                    insert(g[i][j],g[X][Y]+n*m,1,0);
                }else{
                    insert(g[i][j],g[X][Y]+n*m,1,1);
                }
            }
        }
    }
}
const int inf=1e9;
bool vis[maxn];
int ans,flow[maxn],pre[maxn],pred[maxn],dis[maxn],q[maxn],h,t;
inline void back(int i,int w){e[i].w1-=w; e[e[i].opp].w1+=w;}
inline int spfa(){
    memset(dis,127/3,sizeof(dis));
    dis[S]=0; q[++t]=S; flow[S]=inf; flow[T]=0;
    while (h!=t){
        int u=q[h=h%mod+1];
        for (int i=head[u];i;i=e[i].next){
            int v=e[i].link;
            if (e[i].w1&&dis[v]>dis[u]+e[i].w2){
                dis[v]=dis[u]+e[i].w2; pre[v]=u; pred[v]=i;
                flow[v]=min(flow[u],e[i].w1);
                if (!vis[v]){
                    q[t=t%mod+1]=v;
                    vis[v]=1;
                }
            }
        }
        vis[u]=0;
    }
    if (flow[T]==0) return 0;
    int u=T;
    while (u!=S){
        back(pred[u],flow[T]);
        u=pre[u];
    }
    ans+=flow[T]*dis[T];
    return 1;
}
inline void solve(){
    T=n*m*2+1;
    for (int i=1;i<=n*m;i++){
        insert(S,i,1,0);
        insert(i+n*m,T,1,0);
    }
    while (spfa());
    printf("%d\n",ans);
}
int main(){
    init();
    solve();
    return 0;
}
