#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
    int n,cnt,prime[40010],phi[40010],vis[40010];

    void work()
    {
		scanf("%d",&n);
		n--;//不算自己那行那列
		if(!n) {puts("0");return;}//只有他一个人
		phi[1]=1;
		for(int i=2;i<=n;i++)
		{
			if(!vis[i]) prime[++cnt]=i,phi[i]=i-1;
			for(int j=1;j<=cnt&&i*prime[j]<=n;j++)
			{
				vis[i*prime[j]]=1;
				if(i%prime[j]==0)
				{
					phi[i*prime[j]]=phi[i]*prime[j];
					break;
				}
				else phi[i*prime[j]]=phi[i]*(prime[j]-1);
			}
		}
		for(int i=2;i<=n;i++) phi[i]+=phi[i-1];//只是一半的
		printf("%d",phi[n]*2+1);//多加的一个刚好是(1,1)这个对角线上的点
    }
}

int main()
{
    TYC::work();
    return 0;
}
