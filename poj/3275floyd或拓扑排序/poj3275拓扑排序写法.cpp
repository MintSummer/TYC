#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
#include<queue>
//ø»ø»°≠°≠Ã‚Ω‚ 
using namespace std;
const int N=1e3+5;
struct cs{int to,nxt;}a[N*10];
int head[N],ll,g[N];
bool f[N][N],vi[N],in[N];
int n,m,x,y,z,ans;
void init(int x,int y){
    a[++ll].to=y;
    a[ll].nxt=head[x];
    head[x]=ll;
}
void bfs(){
    queue<int>Q;
    for(int i=1;i<=n;i++)if(!g[i])Q.push(i);
    while(!Q.empty()){
        int x=Q.front();Q.pop();vi[x]=1;
        for(int k=head[x];k;k=a[k].nxt){
            if(vi[a[k].to])exit(puts("-1")&0);
            for(int i=1;i<=n;i++)if(f[i][x])f[i][a[k].to]=1;
            g[a[k].to]--;
            if(g[a[k].to]==0)Q.push(a[k].to);
        }
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)scanf("%d%d",&x,&y),init(x,y),f[x][y]=1,g[y]++;
    bfs();
    for(int i=1;i<=n;i++){
        if(!vi[i])exit(printf("-1")&0);
        for(int j=1;j<=n;j++)if(!f[i][j]&&!f[j][i])ans++;
    }
    printf("%d",(ans-n)/2);
}
