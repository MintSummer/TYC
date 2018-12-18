#include<bits/stdc++.h>
using namespace std;
const int MAXN=100010;
typedef long long ll;
int n,m,t,x[MAXN],y[MAXN];
ll cx[MAXN],cy[MAXN],sx,sy,ans;

void solve()
{
    if(t%n==0)
    {
	for(int i=1;i<=t;i++) cx[x[i]]++;
	int ba=t/n;
	for(int i=2;i<=n;i++)
	    cx[i]+=cx[i-1]-ba;
	sort(cx+1,cx+1+n);
	ll mid=cx[(n+1)>>1];
	for(int i=1;i<=n;i++)
	    ans+=abs(mid-cx[i]);
    }
    if(t%m==0)
    {
	for(int i=1;i<=t;i++) cy[y[i]]++;
	int ba=t/m;
	for(int i=2;i<=m;i++) 
	    cy[i]+=cy[i-1]-ba;
	sort(cy+1,cy+1+m);
	ll mid=cy[(m+1)>>1];
	for(int i=1;i<=m;i++)
	    ans+=abs(mid-cy[i]);
    }
}

int main()
{
    scanf("%d%d%d",&n,&m,&t);
    for(int i=1;i<=t;i++) 
	scanf("%d%d",&x[i],&y[i]),sx+=x[i],sy+=y[i];
    if(t%n!=0&&t%m!=0) {printf("impossible");return 0;}
    solve();
    if(t%m!=0) printf("row %lld",ans);
    else if(t%n!=0) printf("column %lld",ans);
    else printf("both %lld",ans);
    return 0;
}
