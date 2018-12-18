#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
using namespace std;
int N,T,ans=0,vis[25005];
struct edge
{
	int s,e;
}cow[25005];

bool cmp(edge a,edge b)
{
	if(a.s!=b.s) return a.s<b.s;
	else return a.e>b.s;
}

int search()
{
	if(cow[1].s>1) return -1;
	if(cow[1].e>=T) return 1;
	int i=1,j,next,count=1,d=1;
	bool t=0;
	while(d<T&&i<N)
	  {
	  	vis[i]=1;
	  	for(j=i+1;cow[j].s<=cow[i].e+1;j++)
	  	  	if(cow[j].e>d&&vis[j]==0) t=1,d=cow[j].e,next=j;
	  	if(t==0) return -1;
	  	i=next;
	  	count++;
	  	if(i==N&&d<T) return -1;
	  } 
	return count;
}

int main()
{
	scanf("%d%d",&N,&T);
	for(int i=1;i<=N;i++)
	  {
	  	scanf("%d%d",&cow[i].s,&cow[i].e);
	  }
	memset(vis,0,sizeof(vis));
	sort(cow+1,cow+N+1,cmp);
	ans=search();
	if(ans>N) printf("-1");
	else printf("%d",ans);
	return 0;
}