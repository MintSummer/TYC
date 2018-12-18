#include<bits/stdc++.h>
using namespace std;
const int MAXN=200010;
int n,m,tot,block,a[MAXN],belong[MAXN],st[MAXN],end[MAXN];
int step[MAXN],to[MAXN];
//step[i]表示从点i跳几步才能出它当前的块，to[i]表示跳出这个块后到了哪个点

int main()
{
    scanf("%d",&n);
    block=sqrt(n);
    tot=n/block;
    if(tot*block<n) tot++;
    for(int i=1;i<=n;i++) 
		scanf("%d",&a[i]),belong[i]=(i-1)/block+1;
    for(int i=1;i<=tot;i++)
		st[i]=end[i-1]+1,end[i]=st[i]+block-1;
    end[tot]=n;
    for(int i=n;i;i--)
		if(a[i]+i>end[belong[i]]) 
			step[i]=1,to[i]=a[i]+i;
		else 
			step[i]=step[a[i]+i]+1,to[i]=to[a[i]+i];

    scanf("%d",&m);
    int opt,x,k;
    while(m--)
    {
		scanf("%d%d",&opt,&x);
		x++;
		if(opt==1)
		{
			int ans=0;
			while(x<=n) ans+=step[x],x=to[x];
			printf("%d\n",ans);
		}
		else
		{
			scanf("%d",&k);
			a[x]=k;
			for(int i=end[belong[x]];i>=st[belong[x]];i--)//一定要倒着修改
			    if(a[i]+i>end[belong[i]]) 
					step[i]=1,to[i]=a[i]+i;
			    else 
					step[i]=step[a[i]+i]+1,to[i]=to[a[i]+i];
		}//不论什么操作，复杂度均为O(根号n)
    }
    return 0;
}
