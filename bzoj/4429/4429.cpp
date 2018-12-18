 
//from:TYC
//论long long毒害了TYC多久
//论少了一个else让TYC调了多久 
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL n,cnt=0,Head[2510*4],fa[2510*4],opt[2510*4];
LL pos[2510*4];
bool vis[2510*4];
 
struct number
{
    LL x;
    LL id;
}num[2510*4];
 
struct ques
{
    LL a,b;
}q[2510*4];
 
struct edge
{
    LL to,next;
}E[2510*4];
 
void add(int u,int v)
{
    cnt++;
    E[cnt].to=v;
    E[cnt].next=Head[u];
    Head[u]=cnt;
}
 
bool cmp(number a,number b)
{
    return a.x<b.x;
}
 
bool Path(int u)
{
    int v;
    for(int i=Head[u];i;i=E[i].next)
    {
        v=E[i].to;
        if(vis[v]) continue;
        vis[v]=1;
        if(!fa[v]||Path(fa[v]))
        {
            fa[v]=u;
            opt[u]=v;
            return true;
        }
    }
    return false;
}
 
void Hungary()
{
    bool flag=false;
    for(int i=1;i<=n;i++)
    {
        memset(vis,false,sizeof(vis));
        if(!Path(i)) {flag=true;break;}
    }
    if(flag) {printf("impossible");return;}
    LL ans;
    LL a,b;
    for(int i=1;i<=n;i++)
    {
        a=q[i].a,b=q[i].b;
        ans=pos[opt[i]];
        if(a+b==ans) printf("%lld + %lld = %lld\n",a,b,ans);
        else if(a-b==ans) printf("%lld - %lld = %lld\n",a,b,ans);
        else if(a*b==ans) printf("%lld * %lld = %lld\n",a,b,ans);
    }
}
 
int main()
{
    scanf("%lld",&n);
    LL a,b;
    LL c;
    for(int i=1;i<=n;i++)
    {
        scanf("%lld%lld",&a,&b);
        q[i].a=a,q[i].b=b;
        c=a+b;
        num[i*3-2].x=c,num[i*3-2].id=i;
        c=a-b;
        num[i*3-1].x=c,num[i*3-1].id=i;
        c=a*b;
        num[i*3].x=c,num[i*3].id=i;
    }
    sort(num+1,num+3*n+1,cmp);
    LL tmp=0;
    pos[++tmp]=num[1].x;
    add(num[1].id,tmp);
    for(int i=2;i<=n*3;i++)
    {
        if(num[i].x!=num[i-1].x) pos[++tmp]=num[i].x;
        add(num[i].id,tmp);
    }
    Hungary();
    return 0;
}

