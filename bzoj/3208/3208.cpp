//from:TYC
//论一个long long到底折磨了TYC多久 
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m;
int dx[5]={0,-1,0,1,0},dy[5]={0,0,1,0,-1};
bool cannot[710][710];
ll h[710][710],dp[710][710];

inline ll MAXX(ll a,ll b)
{
	return a>b?a:b;
}

ll dis(int x,int y)
{
	if(cannot[x][y]) return -999999999;
	if(dp[x][y]!=-1) return dp[x][y];
	int xx,yy;
	dp[x][y]=1;
	for(int i=1;i<=4;i++)
	{
		xx=x+dx[i],yy=y+dy[i];
		if(xx<1||xx>n||yy<1||yy>n) continue;
		if(h[x][y]>h[xx][yy]) dp[x][y]=max(dp[x][y],dis(xx,yy)+1);
	}
	return dp[x][y];
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) 
			scanf("%lld",&h[i][j]);
	scanf("%d",&m);
	char opt[5];
	int a,b,c,d;
	ll val;
	while(m--)
	{
		scanf("%s",opt);
		if(opt[0]=='C')
			scanf("%d%d%lld",&a,&b,&val),h[a][b]=val;
		else if(opt[0]=='S')
		{
			scanf("%d%d%d%d",&a,&b,&c,&d);
			for(int i=a;i<=c;i++)
				for(int j=b;j<=d;j++) cannot[i][j]=true;
		}
		else if(opt[0]=='B')
		{
			scanf("%d%d%d%d",&a,&b,&c,&d);
			for(int i=a;i<=c;i++)
				for(int j=b;j<=d;j++) cannot[i][j]=false;
		}
		else
		{
			ll ans=0;
			for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) dp[i][j]=-1;
			for(int i=1;i<=n;i++) 
				for(int j=1;j<=n;j++)
					ans=MAXX(ans,dis(i,j));
			printf("%lld\n",ans);
		}
	}
	return 0;
}
