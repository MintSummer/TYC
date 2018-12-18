//我觉得这一定是我目前做过的最难的一道暴力枚举题，根本想不到好不好啊……笑
//感谢来自CSDN的题解（没这个我就完了） 
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;
/*
因为如果所有便全都连上，那么任意两条边都可达，而题目中说不会有这种情况 
所以这个环中一定存在断开的边，那么只用枚举每条断开的边就行了 
此时图变成一条或多条链 
*/
int n,p,ans=0x3f3f3f3f;
int f[10010];
//f[i]表示从i开始一直到f[i]都已经连接上了，全部记录的为顺序时可达 ，f[i]所指的为一个点，而不是一个距离 
struct qujian
{
	int x,y;
}cow[10010];

bool cmp(qujian a,qujian b)
{
	if(a.x==b.x) return a.y<b.y;
	else return a.x<b.x;
}

int main()
{
	scanf("%d%d",&n,&p);
	int x,y;
	for(int i=1;i<=p;i++)
	  {
	  	scanf("%d%d",&x,&y);
	  	if(x>y) swap(x,y);//保证x<=y 
	  	cow[i].x=x,cow[i].y=y;
	  }
	  
	sort(cow+1,cow+1+p,cmp);//提前排个序处理一下很重要 
	
	for(int d=1;d<=n;d++)//断点为d,例：当d=1时1、2之间不可链接 
	  {
	  	memset(f,0,sizeof(f));//断点不同，所能达到的f[i]值也不同 
	  	for(int i=1;i<=p;i++)
	  	  {
	  	  	if(d<cow[i].x||d>=cow[i].y)//断点不在x,y之间 
	  	  	  f[cow[i].x]=max(f[cow[i].x],cow[i].y); 
				  //从x开始的链要么原本就足以到达y，要么就还要变长 
	  	  	else//中间断开，只能逆序方向走 
	  	  	  {
	  	  	  	//将这段分为两个部分，一个为1到x,另一个为y到1 
	  	  	  	f[1]=max(f[1],cow[i].x);//更新从1开始的最远的点 
	  	  	  	f[cow[i].y]=n+1; //n+1其实就为实际上的点1，但因为后方为了表示一段距离（没有负数），故将1用n+1表示 
	  	  	  }
	  	  }
	  	int to=0,sum=0;//to表示此时能够到达的最远的点 
	  	for(int i=1;i<=n;i++)
	  	  {
	  	  	if(f[i]==0) continue;//从i开始无法到达任何 
	  	  	if(f[i]>to)//已经可达的不必再考虑 
	  	  	  {
	  	  	  	sum+=f[i]-max(i,to);//选取i与to中较大的，使其与f[i]连通
				//因为如果to>i，则i到t的这部分一定已经被加上了；而当i>to时，则说明i到t这段没必要连接
				to=f[i];//此时能到达的最远的点更新为f[i] 
	  	  	  }
	  	  }
	  	ans=min(ans,sum);
	  }
	printf("%d",ans);
	return 0;
}
