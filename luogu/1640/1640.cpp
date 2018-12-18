#include<bits/stdc++.h>
using namespace std;
const int MAXN=1000010;
int n,cnt=0,fa[MAXN],Head[MAXN];
bool vis[MAXN];
struct wuqi
{
    int to,next;
}E[MAXN*2];

void add(int x,int y)
{
    cnt++;
    E[cnt].to=y;
    E[cnt].next=Head[x];
    Head[x]=cnt;
}

bool Path(int u)
{
	int v;
	for(int i=Head[u];i;i=E[i].next)
	  {
	  	v=E[i].to;
	  	if(vis[v]) continue;
	  	vis[v]=1;
		if(!fa[v]||Path(fa[v]))
		  {
		  	fa[v]=u;
		  	return true;
		  }
	  }
	return false;
}

int Hungary(int mx)
{
	int ans=0;
	for(int i=1;i<=mx;i++)
	  {
	  	memset(vis,0,sizeof(vis));
	  	if(Path(i)) ans++;
	    else break;
	  }
	return ans;
}

int main()
{
    scanf("%d",&n);)
    int a,b,mx=0,mn=0x3f3f3f3f;
    for(int i=1;i<=n;i++)
      {
        scanf("%d%d",&a,&b);
      	add(a,i);
      	add(b,i);
      	mx=max(mx,max(a,b));
      	mn=min(mn,min(a,b));
      }
    if(mn>1) 
	  {
    	printf("0");
    	return 0;
      }
    printf("%d",Hungary(mx));
    return 0;
} 
