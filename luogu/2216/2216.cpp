#include<bits/stdc++.h>
using namespace std;
const int MAXN=1010;
int n,m,k,tot,G[MAXN][MAXN],q[MAXN];
int rmax[MAXN][MAXN],rmin[MAXN][MAXN],lmax[MAXN][MAXN],lmin[MAXN][MAXN];

int read()
{
    int x=0,f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return f?-x:x;
}

void row()
{
    for(int i=1;i<=n;i++)//行
    {
		int h=1,t=1;
		for(int j=1;j<=m;j++)//列
		{
			while(h<t&&G[i][q[t-1]]>G[i][j]) t--;
			q[t++]=j;
			while(h<t&&j-q[h]+1>k) h++;
			if(j>=k) rmin[i][j-k+1]=G[i][q[h]];
		}

		h=1,t=1;
		for(int j=1;j<=m;j++)
		{
			while(h<t&&G[i][q[t-1]]<G[i][j]) t--;
			q[t++]=j;
			while(h<t&&j-q[h]+1>k) h++;
			if(j>=k) rmax[i][j-k+1]=G[i][q[h]];
		}
    }
}

void line()
{
    for(int j=1;j<=m-k+1;j++)
    {
		int h=1,t=1;
		for(int i=1;i<=n;i++)
		{
			while(h<t&&rmin[q[t-1]][j]>rmin[i][j]) t--;
			q[t++]=i;
			while(h<t&&i-q[h]+1>k) h++;
			if(i>=k) lmin[i-k+1][j]=rmin[q[h]][j];
		}

		h=1,t=1;
		for(int i=1;i<=n;i++)
		{
			while(h<t&&rmax[q[t-1]][j]<rmax[i][j]) t--;
			q[t++]=i;
			while(h<t&&i-q[h]+1>k) h++;
			if(i>=k) lmax[i-k+1][j]=rmax[q[h]][j];
		}
    }
}

int get_ans()
{
    int ans=0x3f3f3f3f;
    for(int i=1;i<=n-k+1;i++)
		for(int j=1;j<=m-k+1;j++)
			ans=min(ans,lmax[i][j]-lmin[i][j]);
    return ans;	
}

int main()
{
    n=read(),m=read(),k=read();
    for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			G[i][j]=read();
    row();
    line();
    printf("%d",get_ans());
    return 0;
}
