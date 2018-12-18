#include<bits/stdc++.h>
using namespace std; 

namespace TYC
{
	const int N=2510;
	int n,m,bin[35]; 
	
	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}
	
	inline void write(int x,int dep)
	{
		if(dep>=30) return;
		putchar('1'+(x&1));
		write(x>>1,dep+1);
	}
	
	#define lowbit(x) x&(-x)
	namespace BitTree
	{
		int c1[N][N],c2[N][N],c3[N][N],c4[N][N];
		
		inline void change(int x,int y,int val)
		{
			for(int a=x;a<=n;a+=lowbit(a))
				for(int b=y;b<=n;b+=lowbit(b))
				{
					c1[a][b]^=val;
					if(x&1) c2[a][b]^=val;
					if(y&1) c3[a][b]^=val;
					if((x*y)&1) c4[a][b]^=val;
				} 
		}
		
		inline void add(int x1,int y1,int x2,int y2,int val)
		{
			change(x1,y1,val);
			change(x2+1,y1,val);
			change(x1,y2+1,val);
			change(x2+1,y2+1,val);
		}
		
		inline int ask(int x,int y)
		{
			int s1=0,s2=0,s3=0,s4=0;
			for(int a=x;a;a-=lowbit(a))
				for(int b=y;b;b-=lowbit(b))
				{
					s1^=c1[a][b];
					s2^=c2[a][b];
					s3^=c3[a][b];
					s4^=c4[a][b];
				}
			int ans=s4;
			if((y+1)&1) ans^=s2;
			if((x+1)&1) ans^=s3;
			if(((x+1)*(y+1))&1) ans^=s1;
			return ans; 
		}
		
		int query(int x1,int y1,int x2,int y2)
		{
			return ask(x2,y2)^ask(x1-1,y2)^ask(x2,y1-1)^ask(x1-1,y1-1);
		}
	}
	
	using BitTree::add;
	using BitTree::query;
	
	void work()
	{
		n=read(),m=read();
		bin[1]=1;
		for(int i=2;i<=32;i++) bin[i]=bin[i-1]<<1;
		char ch;
		for(int i=1;i<=m;i++)
		{
			do ch=getchar(); while(!isalpha(ch));
			int x1=read(),y1=read(),x2=read(),y2=read();
			if(ch=='P') 
			{
				int k=read(),val=0;
				while(k--)
				{
					int a=read(),b=read();
					if(b&1) val^=bin[a];
				}
				add(x1,y1,x2,y2,val);
			}
			else
			{
				write(query(x1,y1,x2,y2),0);
				putchar('\n');
			}
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
