#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    int n,m,ans=0x3f3f3f3f,R[20],H[20];

    void dfs(int now,int V,int S)
    {
		if(now>m) 
		{
			if(V==0) ans=min(ans,S+R[1]*R[1]);
			return;
		}
		if(V<=0||S+R[1]*R[1]>ans) return;
		for(int r=R[now-1]-1;r>=m-now+1;r--)
			for(int h=H[now-1]-1;h>=m-now+1;h--)
			{
				if(V-r*r*h<0) continue;
				if(V-r*r*h*(m-now+1)>0) break;
				R[now]=r,H[now]=h;
				dfs(now+1,V-r*r*h,S+2*r*h);
			}
    }

    void work()
    {
		scanf("%d%d",&n,&m);
		R[0]=(int)sqrt(n);
		H[0]=(int)sqrt(n);
		dfs(1,n,0);
		printf("%d",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
