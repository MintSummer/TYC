#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=40010;
int n,cnt;
ll ans;
multiset<int> s;
//当一段区间先进行操作l,r,a，再进行操作l,r,b时，最后的结果一定是a,b中的最大值，那我们直接离线处理。
//对于每段区间，直接让它变成所有包含这段区间的操作中的最大值。

struct node
{
	ll x,val;
	bool last;
}a[MAXN*2];

bool cmp(node p,node q)
{
	return p.x<q.x;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) 
	{
		scanf("%lld%lld%lld",&a[cnt+1].x,&a[cnt+2].x,&a[cnt+1].val);
		if(a[cnt+1].x==a[cnt+2].x) continue;//因为区间为[a,b),即a<=x<b,当a,b相等时，该区间不存在
		a[cnt+2].val=a[cnt+1].val;
		a[cnt+2].last=true;
		cnt+=2;
	}
	sort(a+1,a+1+cnt,cmp);
	multiset<int>::iterator it;
	for(int i=1;i<=cnt;i++) 
	{
		if(!s.empty()&&a[i].x!=a[i-1].x)//s.empty()==true时表示此时i前方的所有区间都已结束，从a[i-1].x到a[i].x的这一段没有变更值，即为0
		{
			it=s.end(),it--;//插入从0开始,end()--才是最后一个数的迭代器
			ans+=(a[i].x-a[i-1].x)*(*it);//此时的*it一定为现有区间中的最大值
		}
		if(a[i].last) it=s.find(a[i].val),s.erase(it);//如果a[i]是一个区间的末尾，那么值为a[i].val的区间到i就完了
		else s.insert(a[i].val);//如果这是一个新区间的起始点，即可插入该区间的值，等待参与计算
		
		//注意：multiset会自动升序排序，当某一区间被其前一区间包含（可能完全，可能一部分），并且该区间值<其前一区间值时，该区间的值插入后并不会变为*(s.end()--)
		//要么找到其前一区间的末尾结束其前一区间（部分包含时），要么该区间值不参与计算（完全包含）
	}
	printf("%lld",ans);
	return 0;
}
