// n=25 的点本机1.7s , CF上2s TLE了
#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=30;	
	const int M=1594350;
	const int inf=0x3f3f3f3f;

	int n,L,R,a[N],b[N],c[N];

	struct node
	{
		ll A,B,C;
		string str;
	}x[M],y[M];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	void dfs(int now,int limit,ll A,ll B,ll C,node t[],int &tot,string str)
	{
		if(now>limit)
		{
			t[++tot]=(node){A,B,C,str};
			return;
		}
		dfs(now+1,limit,A+a[now],B+b[now],C,t,tot,str+"LM");
		dfs(now+1,limit,A+a[now],B,C+c[now],t,tot,str+"LW");
		dfs(now+1,limit,A,B+b[now],C+c[now],t,tot,str+"MW");
	}

	bool cmpl(const node &p,const node &q)
	{
		if(p.A-p.B!=q.A-q.B) return p.A-p.B<q.A-q.B; 
		else return p.B-p.C<q.B-q.C;
	}

	bool cmpr(const node &p,const node &q)
	{
		if(p.A-p.B!=q.A-q.B) return p.A-p.B>q.A-q.B; 
		else return p.B-p.C>q.B-q.C;
	}

	inline int find(int l,int r,ll p)
	{
		int mid,ans=-1;
		while(l<=r)
		{
			mid=(l+r)>>1;
			if(y[mid].C-y[mid].B>=p) ans=mid,r=mid-1;
			else l=mid+1;
		}
		return ans;
	}

	void work()
	{
		n=read();
		for(int i=1;i<=n;i++)
			a[i]=read(),b[i]=read(),c[i]=read();
		int Mid=n>>1;
		dfs(1,Mid,0,0,0,x,L,"");
		dfs(Mid+1,n,0,0,0,y,R,"");	
		sort(x+1,x+1+L,cmpl);
		sort(y+1,y+1+R,cmpr);
		y[0]=(node){-inf,0,inf,""};
		int l=1,r=0,idx=-1,idy=-1;
		ll equ=-inf;
		for(int i=1;i<=L;i++)
		{
			int t=x[i].A-x[i].B;
			while(l<=R&&y[l].B-y[l].A<t) l++;
			while(r<R&&y[r+1].B-y[r+1].A<=t) r++;
			int p=find(l,r,x[i].B-x[i].C);
			if(p==-1||y[p].C-y[p].B!=x[i].B-x[i].C) continue;
			ll tmp=x[i].A+y[p].A;
			if(tmp>equ)
				idx=i,idy=p,equ=tmp;
		}
		if(idx==-1||idy==-1) puts("Impossible");
		else
		{	
			int len=x[idx].str.size();
			for(int i=0;i<len;i+=2)
				cout<<x[idx].str[i]<<x[idx].str[i+1]<<"\n";
			len=y[idy].str.size();
			for(int i=0;i<len;i+=2)
				cout<<y[idy].str[i]<<y[idy].str[i+1]<<"\n";
		}
	}
}

int main()
{
	freopen("a.in","r",stdin);
	TYC::work();
	return 0;
}
