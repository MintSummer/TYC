#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int MAXN=500010; 
int T,n,aa[MAXN],c[MAXN];
//树状数组c表示的是个数

struct point
{
	int num,id;
}a[MAXN];

bool cmp(point p,point q)
{
	return p.num<q.num;
}

inline int lowbit(int x) 
{
	return x&(-x);
}

inline void insert(int x,int tim)
{
	for(int i=x;i<=n;i+=lowbit(i)) c[i]+=tim;
}

inline long long getsum(int x)
{
	int sum=0;
	for(int i=x;i>=1;i-=lowbit(i)) sum+=c[i];
	return sum;  
}//求在x之前的>=x的数的个数

int main()
{	
	while(scanf("%d",&n)!=EOF)
	{
		if(n==0) continue;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i].num);
			a[i].id=i;
		}

		sort(a+1,a+1+n,cmp);
		for(int i=1;i<=n;i++)
			aa[a[i].id]=i;
		//离散化

		long long ans=0;
		memset(c,0,sizeof(c));
		for(int i=1;i<=n;i++)
		{
			insert(aa[i],1);//将排序后顺序为i的数加入树状数组
			ans+=i-getsum(aa[i]);
		}
		printf("%lld\n",ans);
	}
}
