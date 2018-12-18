#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=100010;
	const int inf=0x3f3f3f3f;
	const ll inf_ll=(1LL<<61);

	int n;
	ll arr[N],d[N],list[N],cost[N],dp[N];
	vector<int> pos[N];

	inline ll read()
	{
		ll x=0;int f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	inline void get_len()
	{
		memset(list,inf,sizeof(list));
		for(int i=1;i<=n;i++) d[i]=arr[i]-i;
		int len=0;
		for(int i=1;i<=n;i++) 
		{
			if(d[i]<0) continue;
			int p=upper_bound(list+1,list+1+n,d[i])-list;
			pos[p].push_back(i);
			list[p]=min(list[p],d[i]);
		}	
	}

	struct Node
	{
		int pos,tag;
		ll x,y;
		Node(){}
		Node(int p,int t): pos(p),tag(t)
		{
			x=d[pos];
			y=dp[pos]+(ll)pos*(pos+1)/2-(ll)arr[pos]*(pos+1);
		}
	}node[N];

	bool CmpId(const Node &x,const Node &y)
	{
		return x.pos<y.pos;
	}

	bool CmpD(const Node &x,const Node &y)
	{
		return d[x.pos]==d[y.pos]?(!x.tag):d[x.pos]<d[y.pos];
	}

	bool check(const Node &now,const Node &A,const Node &B)
	{
		return (double)(now.y-A.y)*(A.x-B.x)<(double)(A.y-B.y)*(now.x-A.x);
	}

	void solve(int l,int r)
	{
		if(l==r)
		{
			if(node[l].tag)
			{
				int x=node[l].pos;
				dp[x]+=arr[x]+cost[x]+(ll)x*(x-1)/2;
			}
			return;
		}

		int mid=(l+r)>>1;
		solve(l,mid);
		static Node now[N],sta[N];
		int num=0,top=0;
		for(int i=l;i<=mid;i++)
			if(!node[i].tag) now[++num]=node[i];
		for(int i=mid+1;i<=r;i++)
			if(node[i].tag) now[++num]=node[i];
		sort(now+1,now+1+num,CmpD);

		for(int i=1;i<=num;i++)
			if(!now[i].tag)
			{
				while(top>=2&&check(now[i],sta[top],sta[top-1])) top--;
				sta[++top]=now[i];
			}
			else
			{
				int L=1,R=top,t=now[i].pos;
				while(R-L+1>3)
				{
					int len=(R-L+1)/3;
					int lmid=L+len,rmid=R-len;
					if((ll)sta[lmid].x*t+sta[lmid].y<=(ll)sta[rmid].x*t+sta[rmid].y) R=rmid;
					else L=lmid;
				}
				for(int j=L;j<=R;j++)
					dp[t]=min(dp[t],(ll)t*sta[j].x+sta[j].y);
			}
		solve(mid+1,r);
	}

	void work()
	{
		n=read();
		for(int i=1;i<=n;i++) arr[i]=read();
		for(int i=1;i<=n;i++) cost[i]=read();
		get_len();
		for(int i=1;i<=n;i++) dp[i]=inf_ll;
		pos[0].push_back(0);
		for(int len=1;;len++)
		{
			if(!pos[len].size())
			{
				len--;
				ll ans=(1LL<<61);
				for(int i=0;i<pos[len].size();i++)
				{
					int x=pos[len][i];
					ans=min(ans,dp[x]+(ll)arr[x]*(n-x)+(ll)(n-x)*(n-x+1)/2);
				}
				printf("%d %lld\n",len,ans);
				break;
			}
			int num=0;
			for(int i=0;i<pos[len-1].size();i++) 
				node[++num]=Node(pos[len-1][i],0);
			for(int i=0;i<pos[len].size();i++)
				node[++num]=Node(pos[len][i],1);
			sort(node+1,node+1+num,CmpId);
			solve(1,num);
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
