//并查集

#include<iostream>
#include<cstdio>
using namespace std;
inline int read()
{
    char ch=getchar();
    int f=1,x=0;
    while(!(ch>='0'&&ch<='9')){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+(ch-'0');ch=getchar();}
    return x*f;
}
int n,fa[1000005];
bool vis[1000005];
int find(int x)
{return x==fa[x]?x:fa[x]=find(fa[x]);}
void un(int x,int y)
{
	if(x<y)swap(x,y);
	vis[y]=1;
	fa[y]=x;
}
int main()
{
	n=read();
	for(int i=1;i<=n+1;i++)fa[i]=i;
	for(int i=1;i<=n;i++)
	{
		int x=read(),y=read();
		int p=find(x),q=find(y);
		if(p==q)vis[p]=1;
		else un(p,q);
	}
	for(int i=1;i<=n+1;i++)
	    if(!vis[i]){printf("%d",i-1);break;}
	return 0;
}
