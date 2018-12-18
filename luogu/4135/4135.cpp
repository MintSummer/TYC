//预处理块i内颜色j的和sum[i][j]，以及第i块到第j块的答案ans[i][j]
//每次询问整块直接查表，两边 n*sqrt(n)暴力算
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<string>
using namespace std;

namespace TYC
{
    const int MAXN=100010;
    int n,k,m,block,tot,a[MAXN],sum[350][MAXN],ans[350][350],cnt[MAXN],belong[MAXN];

    int query(int lt,int rt)
    {
		int num=0,bl=belong[lt],br=belong[rt];
		if(bl==br)
		{
			for(int i=lt;i<=rt;i++)
			{
				cnt[a[i]]++;
				if(!(cnt[a[i]]&1)) num++;
				else if(cnt[a[i]]>2) num--;
			}
			for(int i=lt;i<=rt;i++) cnt[a[i]]--;
		}
		else
		{
			num=ans[bl+1][br-1];
			for(int i=lt;i<=bl*block;i++)
			{
				cnt[a[i]]++;
				if(!((cnt[a[i]]+sum[br-1][a[i]]-sum[bl][a[i]])&1)) num++;
				else if((cnt[a[i]]+sum[br-1][a[i]]-sum[bl][a[i]])>2) num--;
			}
			for(int i=(belong[rt]-1)*block+1;i<=rt;i++)
			{
				cnt[a[i]]++;
				if(!((cnt[a[i]]+sum[br-1][a[i]]-sum[bl][a[i]])&1)) num++;
				else if(cnt[a[i]]+sum[br-1][a[i]]-sum[bl][a[i]]>2) num--;
			}
			for(int i=lt;i<=belong[lt]*block;i++) cnt[a[i]]--;
			for(int i=(belong[rt]-1)*block+1;i<=rt;i++) cnt[a[i]]--;
		}
		return num;
    }

    void work()
    {
		scanf("%d%d%d",&n,&k,&m);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);

		block=sqrt(n);
		tot=n/block+(n%block!=0);
		for(int i=1;i<=n;i++)
		{
			belong[i]=(i-1)/block+1;
			sum[belong[i]][a[i]]++;
		}
		for(int i=2;i<=tot;i++)
			for(int j=1;j<=k;j++)
				sum[i][j]+=sum[i-1][j];//前缀和
		int now=0;
		for(int i=1;i<=tot;i++)
		{
			now=0;
			for(int j=(i-1)*block+1;j<=n;j++)
			{
				cnt[a[j]]++;
				if(!(cnt[a[j]]&1)) now++;
				else if(cnt[a[j]]>2) now--;
				ans[i][belong[j]]=now;
			}
			for(int j=(i-1)*block+1;j<=n;j++) cnt[a[j]]--;
		}

		int lt,rt,before=0;
		while(m--)
		{
			scanf("%d%d",&lt,&rt);
			lt=(lt+before)%n+1;
			rt=(rt+before)%n+1;
			if(lt>rt) swap(lt,rt);
			printf("%d\n",before=query(lt,rt));
		}
    }
}

int main()
{
    TYC::work();
    return 0;
}
