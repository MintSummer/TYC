#include<bits/stdc++.h>
using namespace std;
const int MAXN=3e5+10;
int n,m;

namespace LCT
{
    int son[MAXN][2],fa[MAXN],sum[MAXN],rev[MAXN],val[MAXN],q[MAXN];

    void update(int x)
    {
        sum[x]=sum[son[x][0]]^sum[son[x][1]]^val[x];
    }

    void rever(int x)
    {
        rev[x]^=1;
        swap(son[x][0],son[x][1]);
    }
    
    void pushdown(int x)
    {
        if(!rev[x]) return;
        if(son[x][0]) rever(son[x][0]);
        if(son[x][1]) rever(son[x][1]);
        rev[x]=0;
    }

    bool is_root(int x)
    {
        return son[fa[x]][0]!=x&&son[fa[x]][1]!=x;
    }

    int getdir(int x)
    {
        return x==son[fa[x]][1];
    }

    void rotate(int x)
    {
        int f=fa[x],ff=fa[f],d=getdir(x);
        if(!is_root(f)) son[ff][getdir(f)]=x;
        fa[x]=ff;

        son[f][d]=son[x][d^1];
        fa[son[f][d]]=f;

        son[x][d^1]=f;
        fa[f]=x;

        update(f);
        update(x);
    }
 
    void splay(int x)
    {
        int cnt=0;
        q[++cnt]=x;
        for(int i=x;!is_root(i);i=fa[i]) q[++cnt]=fa[i];
        for(int i=cnt;i;i--) pushdown(q[i]);
        while(!is_root(x))
        {
            int f=fa[x];
            if(!is_root(f))
            {
                if(getdir(x)==getdir(f)) rotate(f);
                else rotate(x);
            }
            rotate(x);
        }
    }

    void access(int x)
    {
        for(int tmp=0;x;tmp=x,x=fa[x])
        {
            splay(x);
            son[x][1]=tmp;
            update(x);
        }
    }

    void make_root(int x)
    {
        access(x);
        splay(x);
        rever(x);
    }
    
    void split(int x,int y)
    {
        make_root(x);
        access(y);
        splay(y);
    }

    int find(int x)
    {
        access(x);
        splay(x);
        while(son[x][0])
        	pushdown(x),x=son[x][0];
        return x;
    }

    void link(int x,int y)
    {
        make_root(x);
        fa[x]=y;
    }

    void cut(int x,int y)
    {
        split(x,y);
        if(son[y][0]!=x||son[x][1]) return;
        son[y][0]=fa[x]=0;
        update(y);
    }
}

int read()
{
    int x=0,f=0;
    char ch=getchar();
    while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
    while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
    return f?-x:x;
}

int main()
{
    //freopen("3690.in","r",stdin);
    using namespace LCT;
    n=read(),m=read();
    for(int i=1;i<=n;i++) val[i]=read();
    int opt,x,y;
    while(m--)
    {
        opt=read(),x=read(),y=read();
        if(opt==0) split(x,y),printf("%d\n",sum[y]);
        else if(opt==1) {if(find(x)!=find(y)) link(x,y);}
        else if(opt==2) {if(find(x)==find(y)) cut(x,y);}
        else val[x]=y,splay(x);
    }
    return 0;
}
