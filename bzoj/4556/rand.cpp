#include<bits/stdc++.h>
using namespace std;
const int N=5;
int fa[N+10];

int find(int x)
{
	return x==fa[x]?x:fa[x]=find(fa[x]);
}

int main()
{
	srand(time(NULL));
	int n=rand()%N+1,m=rand()%N+1;
	cout<<n<<" "<<m<<"\n";
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<n;i++)
	{
		int u,v,fu,fv;
		do
		{
			u=rand()%n+1,v=rand()%n+1;
			fu=find(u),fv=find(v);
		}
		while(fu==fv);
		fa[fu]=fv;
		cout<<u<<" "<<v<<"\n";
	}
	for(int i=1;i<=m;i++)
		cout<<rand()%n+1<<" "<<rand()%n+1<<" "<<rand()%3+1<<"\n";
}
