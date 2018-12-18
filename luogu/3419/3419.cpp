#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pa;
const int MAXN=500010;
int n,k,p,ans=0;
int vis[MAXN],Next[MAXN],a[MAXN],last[MAXN];
//记录下每个玩具下次出现的位置，每次要删的话选一个最远的删掉

priority_queue<pa,vector<pa> > q;

int main()
{
	scanf("%d%d%d",&n,&k,&p);
	for(int i=1;i<=n;i++) last[i]=p+1;
	for(int i=1;i<=p;i++) scanf("%d",&a[i]);
	for(int i=p;i>=1;i--)
	{
		Next[i]=last[a[i]];
		last[a[i]]=i;
	}
	int tim=0,ans=0;
	for(int i=1;i<=p;i++)
	{
		if(vis[a[i]]) {q.push(make_pair(Next[i],a[i]));continue;}
		if(tim<k)
		{
			ans++;
			q.push(make_pair(Next[i],a[i]));
			vis[a[i]]=1;
			tim++;
		}
		else
		{
			ans++;
			while(vis[q.top().second]==0) q.pop();
			vis[q.top().second]=0;
			q.pop();
			q.push(make_pair(Next[i],a[i]));
			vis[a[i]]=1;
		}
	}
	printf("%d",ans);
	return 0;
}
