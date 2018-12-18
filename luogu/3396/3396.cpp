#include<bits/stdc++.h>
using namespace std;
const int MAXN=150005;
int n,m,s,a[MAXN],ans[390][MAXN];
//ans[i][j]表示在模i意义下，余数为j的数的个数 

void init()
{
	for(int p=1;p<=s;p++)
		for(int i=1;i<=n;i++)
			ans[p][i%p]+=a[i];
}

int main()
{	
	scanf("%d%d",&n,&m);
	s=sqrt(n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	init();
	char ch[5];
	int x,y;
	while(m--)
	{
		scanf("%s%d%d",ch,&x,&y);
		if(ch[0]=='A')
		{
			if(x<=s) printf("%d\n",ans[x][y]);
			else
			{
				int sum=0;
				for(int i=y;i<=n;i+=x) sum+=a[i];
				printf("%d\n",sum);
			} 
		}
		else
		{
			for(int p=1;p<=s;p++)
				ans[p][x%p]=ans[p][x%p]-a[x]+y;
			a[x]=y;
		}
	}
	return 0;
} 
