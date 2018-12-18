#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=100010;
	const int inf=0x3f3f3f3f;

	int n,m,belong[N];
	ll ans,arr[N],Ans[N],front[N],back[N];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	inline void write(ll x)
	{
		if(x<0) putchar('-'),x=-x;
		if(!x) putchar('0');
		else
		{
			int len=0;
			static int bask[50];
			while(x) bask[++len]=x%10,x/=10;
			for(;len;len--) putchar('0'+bask[len]);
		}
		putchar('\n');
	}

	struct ques
	{
		int l,r,id;
		bool operator < (const ques &t) const
		{
			return belong[l]==belong[t.l]?r<t.r:belong[l]<belong[t.l];
		}
	}q[N];

	namespace RMQ
	{
		int st[18][N],Log[N];

		inline int Min(int x,int y)
		{
			return arr[x]<arr[y]?x:y;
		}

		void init()
		{
			for(int i=0;i<=17;i++)
				for(int j=(1<<i);j<min(n+1,(1<<(i+1)));j++) Log[j]=i;
			for(int i=1;i<=n;i++) st[0][i]=i;
			for(int i=1;i<=17;i++)
				for(int j=1;j+(1<<i)-1<=n;j++)
					st[i][j]=Min(st[i-1][j],st[i-1][j+(1<<(i-1))]);
		}

		inline int Minn(int l,int r)
		{
			if(l>r) return inf;
			int k=Log[r-l+1];
			return Min(st[k][l],st[k][r-(1<<k)+1]);
		}
	}
	using RMQ::Minn;

	void init()
	{
		RMQ::init();
		static int top,pre,nxt,sta[N];
		for(int i=1;i<=n;i++) 
		{
			while(top&&arr[i]<arr[sta[top]]) top--;
			sta[++top]=i;
			if(top==1) pre=0;
			else pre=sta[top-1];
			back[i]=back[pre]+(ll)arr[i]*(i-pre);
		}
		top=0;
		for(int i=n;i;i--)
		{
			while(top&&arr[i]<arr[sta[top]]) top--;
			sta[++top]=i;
			if(top==1) nxt=n+1;
			else nxt=sta[top-1];
			front[i]=front[nxt]+(ll)arr[i]*(nxt-i);
		}
		int block=sqrt(n);
		for(int i=1;i<=n;i++) belong[i]=(i-1)/block+1;
	}

	inline void Left(int &l,int &r,int type)
	{
		int now=(type==1?l:l-1);
		int p=Minn(now,r);
		ll tmp=0;
		if(p==inf) tmp=front[now];
		else tmp=(ll)arr[p]*(r-p+1)+front[now]-front[p];
		ans+=tmp*(type==1?-1:1);
		l+=type;
	}	

	inline void Right(int &l,int &r,int type)
	{
		int now=(type==1?r+1:r);
		int p=Minn(l,now);
		ll tmp;
		if(p==inf) tmp=back[now];
		else tmp=(ll)arr[p]*(p-l+1)+back[now]-back[p];
		ans+=tmp*type;
		r+=type;
	}

	void work()
	{
		n=read(),m=read();
		for(int i=1;i<=n;i++) arr[i]=read();
		for(int i=1;i<=m;i++)
			q[i]=(ques){read(),read(),i};
		init();
		sort(q+1,q+1+m);
		int l=1,r=0;
		for(int i=1;i<=m;i++)
		{
			while(r<q[i].r) Right(l,r,1);
			while(r>q[i].r) Right(l,r,-1);
			while(l<q[i].l) Left(l,r,1);
			while(l>q[i].l) Left(l,r,-1);
			Ans[q[i].id]=ans;
		}
		for(int i=1;i<=m;i++) write(Ans[i]);
	}
}

int main()
{
	TYC::work();
	return 0;
}
