#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=500010;
	int n,root,son[N][2],mx[N][2],mn[N][2];
	char ch[N];
	#define ls son[i][0]
	#define rs son[i][1]	

	void build(int &u)
	{
		u=++n;
		for(int i=0;i<ch[u]-'0';i++)
			build(son[u][i]);
	}

	void work()
	{
		scanf("%s",ch+1);
		build(root);
		for(int i=n;i;i--)
		{
			mx[i][1]=mx[ls][0]+mx[rs][0]+1;
			mx[i][0]=max(mx[ls][1]+mx[rs][0],mx[ls][0]+mx[rs][1]);
			mn[i][1]=mn[ls][0]+mn[rs][0]+1;
			mn[i][0]=min(mn[ls][1]+mn[rs][0],mn[ls][0]+mn[rs][1]);
		}
		printf("%d %d\n",max(mx[1][0],mx[1][1]),min(mn[1][0],mn[1][1]));
	}
}

int main()
{
	TYC::work();
	return 0;
}
