#include<bits/stdc++.h>
using namespace std;

namespace TYC
{	
	const int N=310;

	int n,m,now[N][N];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	struct Matrix
	{
		int arr[N][N];
	
		inline int lowbit(int x) {return x&(-x);}

		void insert(int x,int y,int val)
		{
			for(int i=x;i<=n;i+=lowbit(i))
				for(int j=y;j<=m;j+=lowbit(j))
					arr[i][j]+=val;
		}

		int num(int x,int y)
		{
			int sum=0;
			for(int i=x;i;i-=lowbit(i))
				for(int j=y;j;j-=lowbit(j))
					sum+=arr[i][j];
			return sum;
		}

		int query(int x1,int y1,int x2,int y2)
		{
			return num(x2,y2)-num(x1-1,y2)-num(x2,y1-1)+num(x1-1,y1-1);
		}
	}col[102];

	void work()
	{
		n=read(),m=read();
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				col[now[i][j]=read()].insert(i,j,1);
		int q=read();
		while(q--)
		{
			int opt=read();
			if(opt==1)
			{
				int x=read(),y=read();
				col[now[x][y]].insert(x,y,-1);
				col[now[x][y]=read()].insert(x,y,1);
			}
			else
			{
				int x1=read(),x2=read(),y1=read(),y2=read();
				printf("%d\n",col[read()].query(x1,y1,x2,y2));
			}
		}	
	}
}

int main()
{
	TYC::work();
	return 0;
}
