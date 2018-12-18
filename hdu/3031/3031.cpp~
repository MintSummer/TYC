#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int MAXN=1000010;
    int son[MAXN][2],root[110],num[110],dis[MAXN],val[MAXN],card[2];

    int inline read()
    {
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
    }

    int merge(int x,int y)
    {
		if(!x||!y) return x+y;
		if(val[x]<val[y]) swap(x,y);
		son[x][1]=merge(son[x][1],y);
		if(dis[son[x][0]]<dis[son[x][1]])
			swap(son[x][0],son[x][1]);
		dis[x]=dis[son[x][1]]+1;
		return x;
    }

    void pop(int &x)
    {
		int tmp=x;
		x=merge(son[x][0],son[x][1]);
		son[tmp][0]=son[tmp][1]=dis[tmp]=0;
    }

    bool check(char c)
    {
		return c!='T'&&c!='C'&&c!='L'&&c!='A'&&c!='E';
    }

    void init()
    {
		card[0]=card[1]=0;
		memset(root,0,sizeof(root));
    }

    void work()
    {
		int T;
		while(~scanf("%d",&T))
		{
			while(T--)
			{
				init();
				int n=read(),m=read(),cnt=0,x,d;
				for(int i=2;i<=m+1;i++) num[i]=read();
				dis[0]=-1;
				for(int i=2;i<=m+1;i++)
					for(int j=1;j<=num[i];j++)	    
					{
						cnt++;
						son[cnt][0]=son[cnt][1]=dis[cnt]=0;
						val[cnt]=read();
						root[i]=merge(root[i],cnt);
					}
				char opt;
				for(int kase=0;kase<n;kase++)
				{	
					do{opt=getchar();}while(check(opt));
					switch(opt)
					{
						case 'T':
							x=read()+1;
							root[kase&1]=merge(root[kase&1],root[x]);
							card[kase&1]+=num[x];
							break;
						case 'C': 
							d=(val[root[0]]<val[root[1]]);
							root[d]=merge(root[0],root[1]);
							card[d]+=card[d^1];
							root[d^1]=card[d^1]=0;
							break;
						case 'L': 
							pop(root[kase&1]);
							card[kase&1]--; 
							break;
						case 'A': val[root[kase&1]]+=read();break;
						case 'E': val[root[kase&1]]=read();break;
					}
				}
				printf("%d:%d\n",card[0],card[1]);
			}
			if(card[0]>card[1]) puts("Hahaha...I win!!");
			else puts("I will be back!!");
		}
    }
}

int main()
{
    TYC::work();
    return 0;
}
