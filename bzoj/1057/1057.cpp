//话说我好想嘴一下：这个题让先输出正方形，再输出矩形，然后我因为输反了WA了很多次……
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2010;
int n,m,G[MAXN][MAXN],f[MAXN][MAXN],st[MAXN],w[MAXN],mx1,mx2;
int dx[5]={0,1,0,-1,0},dy[5]={0,0,1,0,-1};

int read()
{
    int x=0,f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return f?-x:x;
}

void get_f()
{
    memset(f,0,sizeof(f));
    for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(G[i][j]) f[i][j]=f[i][j-1]+1;
			else f[i][j]=0;
}

int sqr(int x) {return x*x;}

void search()
{
    for(int j=1;j<=m;j++)//一行一行地做单调栈
    {
		int top=0;
		for(int i=1;i<=n+1;i++)
		{
			int minw=i;
			while(top&&f[i][j]<=st[top])
			{
				mx1=max(mx1,st[top]*(i-w[top]));
				mx2=max(mx2,sqr(min(st[top],i-w[top])));
				minw=w[top];
				top--;
			}
			st[++top]=f[i][j],w[top]=minw;
		}
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			int a=read();
			if((i&1)==(j&1)) 
			{
				if(a) G[i][j]=1;
				else G[i][j]=0;
			}
			else 
			{
				if(a) G[i][j]=0;
				else G[i][j]=1;
			}
		}
    get_f();
    search();
    for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			G[i][j]=!G[i][j];
    get_f();
    search();
    printf("%d\n%d",mx2,mx1);
    return 0; 
}
