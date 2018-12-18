#include<cstdio>
using namespace std;
int p,a[30010],s[30010],d[30010];
int find_and_update(int x)
{
	if(a[x]==x)return x;
	int tmp=a[x];
	a[x]=find_and_update(a[x]);
	d[x]+=d[tmp];
	return a[x];
}
int main(void)
{
	for(int i=0;i<30010;i++)a[i]=i,s[i]=1;
	scanf("%d",&p);
	getchar();
	while(p--)
	{
		char o;
		int m,n;
		do
			scanf("%c",&o);
		while(!(o=='M'||o=='C'));
		if(o=='M')
		{
			scanf("%d%d",&m,&n);
			int x=find_and_update(m),y=find_and_update(n);
			a[x]=y;
			d[x]+=s[y];
			s[y]+=s[x];
		}
		if(o=='C')
		{
			scanf("%d",&m);
			find_and_update(m);
			printf("%d\n",d[m]);
		}
	}
	return 0;
}
