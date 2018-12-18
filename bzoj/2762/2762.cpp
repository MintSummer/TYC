#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	#define lowbit(x) x&(-x)
	const int N=1e6,MAXN=2e6+1;
	int n,L[N+10],R[N+10],tree[N*2+50],del[N+10];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}
	
	inline void add(int x,int val)
	{
		for(;x<=MAXN;x+=lowbit(x)) tree[x]+=val;
	}

	inline int query(int x)
	{
		int ans=0;
		for(;x;x-=lowbit(x)) ans+=tree[x];
		return ans;
	}

	inline void change(int l,int r,int val)
	{
		if(l>r) return;
		l=max(l,1);
		r=min(r,MAXN);
		add(l,val);
		add(r+1,-val);
	}

	void work()
	{
		n=read();
		char opt[10];
		int a,b,c,k,tot=0;
		while(n--)
		{
			scanf("%s",opt);
			switch(opt[0])
			{
				case 'A':
					tot++;
					a=read(),b=read(),c=read();
					if(a>0)
						L[tot]=floor((double)(c-b)/a)+N+2,R[tot]=MAXN;
					else if(a<0)
						L[tot]=1,R[tot]=ceil((double)(c-b)/a)+N;
					else if(b>c) 
						L[tot]=1,R[tot]=MAXN;
					else 
						L[tot]=2,R[tot]=1;//无解
					change(L[tot],R[tot],1);
					break;
				case 'D': 
					k=read();
					if(del[k]||k>tot) continue;
					del[k]=1;
					change(L[k],R[k],-1);
					break;
				case 'Q': 
					k=read();
					printf("%d\n",query(k+N+1));
					break;
			}
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
