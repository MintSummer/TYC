#include<bits/stdc++.h>
using namespace std;
const int MAXN=1000010;
char a[MAXN],b[MAXN];
int n,pos[MAXN],c[MAXN];
queue<int> q[30];

inline int lowbit(int x) {return x&(-x);}

void insert(int x,int tim)
{
	for(int i=x;i<=n;i+=lowbit(i)) c[i]+=tim;
}

long long getans(int x)
{	
	long long sum=0;
	for(int i=x;i>=1;i-=lowbit(i)) sum+=c[i];
	return sum;
}

int main()
{
	scanf("%d",&n);
	scanf("%s%s",a+1,b+1);
	for(int i=1;i<=n;i++) q[a[i]-'A'].push(i);
	for(int i=1;i<=n;i++)
	{
		pos[i]=q[b[i]-'A'].front();
		q[b[i]-'A'].pop();
	}
	long long ans=0;
	for(int i=1;i<=n;i++)
	{
		insert(pos[i],1);
		ans+=i-getans(pos[i]);
	}
	printf("%lld",ans);
	return 0;
}
