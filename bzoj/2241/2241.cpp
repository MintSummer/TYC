#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cctype>
using namespace std;

namespace TYC
{
	const int N=110,inf=0x3f3f3f3f;
	int m,n,tim,a[N][N],tmp[N][N];

	inline bool check(int x,int y)
	{
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++) 
				tmp[i][j]=a[i][j];
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				if(tmp[i][j])
				{
					if(i+x-1<=n&&j+y-1<=m)
					{
						int num=tmp[i][j];
						for(int g=0;g<x;g++)
							for(int h=0;h<y;h++)
							{
								tmp[i+g][j+h]-=num;
								if(tmp[i+g][j+h]<0) return false;
							}
					}
					else return false;
				}
		return true;
	}

	void work()
	{
		scanf("%d%d",&n,&m);
		int sum=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				scanf("%d",&a[i][j]),sum+=a[i][j];
		int ans=inf;
		for(int x=n;x>0;x--)
			for(int y=m;y>0;y--)
				if(sum%(x*y)==0&&sum/(x*y)<ans)//剪枝
					if(check(x,y)) ans=sum/(x*y);
		printf("%d\n",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
