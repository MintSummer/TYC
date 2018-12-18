#include<bits/stdc++.h>
using namespace std;
int n,m,cnt=0,Head[4010],ans[4010];
char ch[3]={'?','N','Y'};
bool vis[4010];

struct edge
{
    int to,next;
}E[4010*10];

void add(int u,int v)
{
    cnt++;
    E[cnt].to=v;
    E[cnt].next=Head[u];
    Head[u]=cnt;
}

bool dfs(int u)
{
    if(vis[u]==true) return true;
    if(vis[u^1]==true) return false;
	vis[u]=true;
    int v;
    for(int i=Head[u];i;i=E[i].next)
    {
        v=E[i].to;
        if(!dfs(v)) return false;
    }
    return true;
}

inline bool check(int x)
{
    memset(vis,0,sizeof(vis));
    return dfs(x);
}

inline char read()
{
	char c;
    do{c=getchar();}while(c!='Y'&&c!='N');
    return c;
}

int main()
{
    scanf("%d%d",&n,&m);
    int a,b;
	char c,d;
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&a);
		c=read();
		scanf("%d",&b);
		d=read();
        a=a*2+(c=='N');
        b=b*2+(d=='N');
        add(a,b^1),add(b,a^1);
    }
    for(int i=1;i<=n;i++)
    {
        a=check(2*i),b=check(2*i+1);
        if(a&&b) ans[i]=0;
        else if(a) ans[i]=1;
        else if(b) ans[i]=2;
        else {printf("IMPOSSIBLE");return 0;} 
    }
    for(int i=1;i<=n;i++)
        cout<<ch[ans[i]];
    return 0;
}
