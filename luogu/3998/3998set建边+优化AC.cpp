#include<bits/stdc++.h>
using namespace std;
const int MAXN=200010;
int n,m;
int ans[MAXN],cnt[MAXN];
set<int> s[MAXN]; 
set<int>::iterator it;
/*
��cnt[x]��¼��ʱx�Ѿ����˶�����΢����s[x]����Ϊx�ĵ�ǰ���Ѽ��� 
x��y���׵�΢������=x��y�Ͼ���ϵʱx����΢����-x��y�������ѹ�ϵǰx����΢���� 
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
			s[x].erase(y),s[y].erase(x);//��setɾ������ĺܷ��㰡~
			ans[x]+=cnt[y],ans[y]+=cnt[x]; 
		}
	}
	for(int i=1;i<=n;i++)//��x��yֱ�����Ҳδ�Ͼ����ѹ�ϵ��ֱ�Ӽ���x������΢���� 
		for(it=s[i].begin();it!=s[i].end();it++)
			ans[*it]+=cnt[i];//x��y��y��x˭��˭��Ӱ���� 
	for(int i=1;i<n;i++) printf("%d ",ans[i]);
	printf("%d",ans[n]);
	return 0;
}
