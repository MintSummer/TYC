#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int MAXN=100010;
    int n,m,fa[MAXN],val[MAXN],son[MAXN][2],dis[MAXN];

    inline int read()
    {
        int x=0,f=1;
        char ch=getchar();
        while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
        while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
        return x*f;
    }

    int merge(int x,int y)
    {
        if(x==0||y==0) return x+y;
        if(val[x]>val[y]||(val[x]==val[y]&&x>y))
            swap(x,y);
        son[x][1]=merge(son[x][1],y);
        fa[son[x][1]]=x;
        if(dis[son[x][0]]<dis[son[x][1]])
            swap(son[x][0],son[x][1]);
        dis[x]=dis[son[x][1]]+1;
        return x;
    }

    inline int find(int x)
    {
        while(fa[x]!=-1) 
			x=fa[x];
		return x;
    }

    void work()
    {
        n=read(),m=read();	
        for(int i=1;i<=n;i++) 
			val[i]=read(),fa[i]=-1;
        dis[0]=-1;
        int opt,x,y;
        while(m--)
        {
            opt=read(),x=read();
            if(opt==1)
            {
                y=read();
                if(x==y||val[x]==-1||val[y]==-1) continue;
                int fx=find(x),fy=find(y);
                merge(fx,fy);
            }
            else
            {
                if(val[x]==-1) printf("-1\n");
                else
                {
                    int fx=find(x);
                    printf("%d\n",val[fx]);
                    val[fx]=-1;
        			fa[son[fx][0]]=fa[son[fx][1]]=-1;
        			merge(son[fx][0],son[fx][1]);
                }
            }
        }
    }
}

int main()
{
    TYC::work();
    return 0;
}
