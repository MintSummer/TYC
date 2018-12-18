#include<bits/stdc++.h>
using namespace std;
const int MAXN=500010;
int n,m,a[MAXN],c[MAXN*2];

int lowbit(int x){return x&(-x);}

void insert(int i,int val)
{
	for(;i<=n;i+=lowbit(i)) c[i]+=val;
}

int ask(int i)
{
	int sum=0;
	for(;i;i-=lowbit(i)) sum+=c[i];
	return sum;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		insert(i,a[i]-a[i-1]);
	}
	int opt,x,y,k;
	while(m--)
	{
		scanf("%d",&opt);
		if(opt==1)
		{
			scanf("%d%d%d",&x,&y,&k);
			insert(y+1,-k),insert(x,k);
		}
		else 
		{
			scanf("%d",&x);
			printf("%d\n",ask(x));
		}
	}
	return 0;
} 
