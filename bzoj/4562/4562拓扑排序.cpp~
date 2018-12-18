#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue> 
#define M 100004
using namespace std;
int n,m,ans,tot;
int first[M],IN[M],OUT[M],f[M];
queue <int> q;
struct edge{int u,v,next;}e[M<<1];
void add(int x,int y){e[++tot]=(edge){x,y,first[x]};first[x]=tot;IN[y]++;OUT[x]++;}
int in()
{
    char ch=getchar();int t=0;
    while (!isdigit(ch)) ch=getchar();
    while (isdigit(ch)) t=(t<<3)+(t<<1)+ch-48,ch=getchar(); 
    return t;
}
main()
{
    n=in();m=in();
    for (int i=1;i<=m;i++) add(in(),in());
    for (int i=1;i<=n;i++)
        if (!IN[i]&&OUT[i]) f[i]=1,q.push(i);
    for (;!q.empty();q.pop())
    {
        int k=q.front();
        for (int i=first[k];i;i=e[i].next)
        {
            IN[e[i].v]--;
            f[e[i].v]+=f[k];
            if (!IN[e[i].v])
                if (OUT[e[i].v]) q.push(e[i].v);
                else ans+=f[e[i].v];
        }
    }
    printf("%d",ans);
}
