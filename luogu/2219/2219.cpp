#include<bits/stdc++.h>
using namespace std;
const int MAXN=1010;
typedef long long ll;
int n,m,a,b,c,d,q[MAXN];
int sum[MAXN][MAXN],ab[MAXN][MAXN],cd[MAXN][MAXN],mn[MAXN][MAXN],tmp[MAXN][MAXN];

void debug(int x[MAXN][MAXN])
{
    for(int i=1;i<=n;i++)
    {
		for(int j=1;j<=m;j++)
			cout<<x[i][j]<<' ';
		puts("");
    }
    puts("");
}

void get_sum(int s[MAXN][MAXN],int x,int y)//简单容斥
{
	for(int i=x;i<=n;i++)
		for(int j=y;j<=m;j++)
	  		s[i-x+1][j-y+1]=sum[i][j]-sum[i-x][j]-sum[i][j-y]+sum[i-x][j-y];
}

int read()
{
    int x=0,f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return f?-x:x;
}

void solve()
{
    for(int i=1;i<=n;i++)
    {
		int h=1,t=1;
		for(int j=1;j<=m;j++)
		{
			while(h<t&&cd[i][q[t-1]]>cd[i][j]) t--;
			q[t++]=j;
			while(h<t&&j-q[h]+1>b) h++;
			if(j>=b) tmp[i][j-b+1]=cd[i][q[h]];
		}
    }
    for(int j=1;j<=m-b+1;j++)
    {
		int h=1,t=1;
		for(int i=1;i<=n;i++)
		{
			while(h<t&&tmp[q[t-1]][j]>tmp[i][j]) t--;
			q[t++]=i;
			while(h<t&&i-q[h]+1>a) h++;
			if(i>=a) mn[i-a+1][j]=tmp[q[h]][j];
		}
    }
}

int main()
{
    n=read(),m=read(),a=read(),b=read(),c=read(),d=read();
    for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) 
			sum[i][j]=sum[i-1][j]+sum[i][j-1]+read()-sum[i-1][j-1];
    get_sum(ab,a,b);
    get_sum(cd,c,d);
    
    n-=c-1,m-=d-1;
    a-=c+2-1,b-=d+2-1;
    solve();
    n+=c-1,m+=d-1;
    a+=c+2-1,b+=d+2-1;
    int ans=0;
    for(int i=1;i<=n-a+1;i++)
		for(int j=1;j<=m-b+1;j++)
			ans=max(ans,ab[i][j]-mn[i+1][j+1]);
    printf("%d",ans);
}
