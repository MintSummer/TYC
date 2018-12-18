#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

namespace TYC
{
	const int MAXN=100010; 
	
	struct Meteor
	{
		double time;
		int isright;
		bool operator < (const Meteor &a) const
		{
			return (time<a.time)||(time==a.time&&isright>a.isright);
			//一定要先处理右端点，将出界了的先减掉 
		}
	}event[MAXN*2];
	
	void update(int now,int v,int side,double &L,double &R)
	{
		if(v==0) 
		{
			if(now<=0||now>=side) R=L-1;//无解 
		}
		else 
		{
			if(v>0)
			{
				L=max(L,-(double)now/v);
				R=min(R,(double)(side-now)/v);
			}
			else
			{
				L=max(L,(double)(side-now)/v);
				R=min(R,-(double)now/v);
			}
		}
	}
	
	void work()
	{
		ios::sync_with_stdio(false);
		int T,W,H,N;
		cin>>T;
		while(T--)
		{
			cin>>W>>H>>N;
			int x,y,a,b,cnt=0;;
			for(int i=1;i<=N;i++)
			{
				cin>>x>>y>>a>>b;
				double L=0,R=1e9;
				update(x,a,W,L,R);
				update(y,b,H,L,R);//记录流星穿过的时间区间做右端点 
				if(R>L) 
					event[++cnt]=(Meteor){L,0},event[++cnt]=(Meteor){R,1};
			}
			sort(event+1,event+1+cnt);//按照时间排序 
			int ans=0,now=0;
			for(int i=1;i<=cnt;i++)//扫描线 
			{
				if(event[i].isright==0) ans=max(ans,++now);
				else now--;
			}
			cout<<ans<<endl;
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
