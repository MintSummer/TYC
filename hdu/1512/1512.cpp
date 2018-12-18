#include<bits/stdc++.h>
using namespace std;


namespace TYC
{
	const int MAXN=100010;
	int n,m,val[MAXN],fa[MAXN],son[MAXN][2],dis[MAXN];
	
	inline int read()
    {
        int x=0,f=1;
        char ch=getchar();
        while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
        while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
        return x*f;
    }
    
    int find(int x)
    {
    	while(fa[x]) x=fa[x];
    	return x;
	}
	
	int merge(int x,int y)
	{
		if(!x||!y) return x+y;
		if(val[x]<val[y]) swap(x,y);
		son[x][1]=merge(son[x][1],y);
		fa[son[x][1]]=x;
		if(dis[son[x][0]]<dis[son[x][1]])
			swap(son[x][0],son[x][1]);
		dis[x]=dis[son[x][1]]+1;
		return x;
	}

	int fight(int x)
	{
		val[x]>>=1;
		fa[son[x][0]]=fa[son[x][1]]=0;
		int root=merge(son[x][0],son[x][1]);
		son[x][0]=son[x][1]=dis[x]=fa[x]=0;
		return merge(x,root);
	}
	
	void work()
	{
		while(~scanf("%d",&n))
		{
			memset(dis,0,sizeof(dis));
			memset(son,0,sizeof(son));
			memset(fa,0,sizeof(fa));
			dis[0]=-1;
			for(int i=1;i<=n;i++) val[i]=read();
			m=read();
			int x,y;
			while(m--)
			{
				x=read(),y=read();
				int fx=find(x),fy=find(y);
				if(fx==fy) {puts("-1");continue;}
				merge(fight(fx),fight(fy));
				int f=find(fx);
				printf("%d\n",val[f]);
			}
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
