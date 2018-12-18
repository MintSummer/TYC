#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int MAXN=1000010;
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
		if(val[x]>val[y]) swap(x,y);
		son[x][1]=merge(son[x][1],y);
		fa[son[x][1]]=x;
		if(dis[son[x][0]]<dis[son[x][1]])
			swap(son[x][0],son[x][1]);
		dis[x]=dis[son[x][1]]+1;
		return x;
	}
	
	void work()
	{
		n=read();
		for(int i=1;i<=n;i++)
			val[i]=read();
		m=read();
		char ch;
		int x,y;
		while(m--)
		{
			do{ch=getchar();}while(ch!='M'&&ch!='K');
			if(ch=='M')
			{
				x=read(),y=read();
				if(val[x]==-1||val[y]==-1) continue;
				int fx=find(x),fy=find(y);
				if(fx==fy) continue;
				merge(fx,fy);
			}
			else 
			{
				x=read();
				if(val[x]==-1) puts("0");
				else
				{
					int fx=find(x);
					printf("%d\n",val[fx]);
					val[fx]=-1;
					fa[son[fx][0]]=fa[son[fx][1]]=0;
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
