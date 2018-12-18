#include<bits/stdc++.h>
using namespace std;
const int MAXN=(1<<20)+10;
int n,m,f[MAXN],q[MAXN*2];
bool vis[MAXN];

struct node
{
    int tim,b1,b2,f1,f2;
}a[110];

void spfa(int s)
{
    memset(f,0x3f3f3f3f,sizeof(f));
    int h=0,t=0;
    q[++t]=s;
    vis[s]=true;
    f[s]=0;
    while(h<t)
    {
	int u=q[++h];
	vis[u]=false;
	for(int i=1;i<=m;i++)
	    if( (a[i].b1^(a[i].b1&u))==0 && (a[i].b2&u)==0 )
	    {
		int v=(u^(u&a[i].f1))|a[i].f2;
		if(f[v]>f[u]+a[i].tim)
		{
		    f[v]=f[u]+a[i].tim;
		    if(!vis[v]) vis[v]=true,q[++t]=v;
		}
	    }
    }
}

int main()
{
    scanf("%d%d",&n,&m);

    char ch1[110],ch2[110];
    for(int i=1;i<=m;i++)
    {
	scanf("%d%s%s",&a[i].tim,ch1,ch2);
	for(int j=0;j<n;j++)
	{
	    if(ch1[j]=='+') a[i].b1+=(1<<j);
	    if(ch1[j]=='-') a[i].b2+=(1<<j);
	}
	for(int j=0;j<n;j++)
	{
	    if(ch2[j]=='-') a[i].f1+=(1<<j);
	    if(ch2[j]=='+') a[i].f2+=(1<<j);
	}
    }

    int e=(1<<n)-1;
    spfa(e);
    if(f[0]==f[e+1]) printf("0");
    else printf("%d",f[0]);
    return 0;
}
