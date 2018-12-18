#include<bits/stdc++.h>
using namespace std;
const int inf=0x3f3f3f3f;
int T,n,a[20][20],now[20][20];

int read()
{
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return x;
}

int check(int x)
{
    memset(now,0,sizeof(now));
    for(int i=n;i;i--,x>>=1)
    {
	now[1][i]=(x&1);
	if(now[1][i]==0&&a[1][i]==1) return inf;
    }
    for(int x=2;x<=n;x++)
	for(int y=1;y<=n;y++)
	{
	    int sum=now[x-2][y]+now[x-1][y-1]+now[x-1][y+1];
	    now[x][y]=sum%2;
	    if(now[x][y]==0&&a[x][y]==1) return inf;
	}
    int ans=0;
    for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	    if(now[i][j]!=a[i][j]) ans++;
    return ans;
}

int main()
{
    T=read();
    for(int cas=1;cas<=T;cas++)
    {
	n=read();
	for(int i=1;i<=n;i++)
	    for(int j=1;j<=n;j++) 
		a[i][j]=read();
	int ans=inf;
	for(int i=0;i<(1<<n);i++)
	    ans=min(ans,check(i));
	if(ans==inf) ans=-1;
	printf("Case %d: %d\n",cas,ans);
    }
    return 0;
}
