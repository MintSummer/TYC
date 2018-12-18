#include<bits/stdc++.h>
using namespace std;
const int MAXN=200010;
int n,m;
int ans[MAXN],cnt[MAXN];
set<int> s[MAXN]; 
set<int>::iterator it;
/*
用cnt[x]记录此时x已经发了多少条微博，s[x]集合为x的当前好友集合 
x对y贡献的微博数量=x与y断绝关系时x发的微博数-x与y建立好友关系前x发的微博数 
*/ 

int main()
{
	scanf("%d%d",&n,&m);
	int x,y;
	char ch[5];
	while(m--)
	{
		scanf("%s",ch);
		if(ch[0]=='!') scanf("%d",&x),cnt[x]++;
		else if(ch[0]=='+')
		{
			scanf("%d%d",&x,&y);
			s[x].insert(y),s[y].insert(x);
			ans[x]-=cnt[y],ans[y]-=cnt[x];
		}
		else 
		{
			scanf("%d%d",&x,&y);
			s[x].erase(y),s[y].erase(x);//用set删除边真的很方便啊~
			ans[x]+=cnt[y],ans[y]+=cnt[x]; 
		}
	}
	for(int i=1;i<=n;i++)//若x与y直到最后也未断绝好友关系，直接加上x发的总微博数 
		for(it=s[i].begin();it!=s[i].end();it++)
			ans[*it]+=cnt[i];//x对y与y对x谁先谁后不影响结果 
	for(int i=1;i<n;i++) printf("%d ",ans[i]);
	printf("%d",ans[n]);
	return 0;
}
