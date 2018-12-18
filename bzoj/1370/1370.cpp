#include<bits/stdc++.h>
using namespace std;
const int MAXN=1000*2+10;
int n,m,fa[MAXN],vis[MAXN];

int read()
{
    char ch=getchar();
    while(ch<'A'||ch>'Z') ch=getchar();
    if(ch=='F') return 1;
    else return 2;
}

int find(int a)
{
    return a==fa[a]?a:fa[a]=find(fa[a]);
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=2*n;i++) fa[i]=i;
    while(m--)
    {
		int opt=read(),a,b;
		scanf("%d%d",&a,&b);
		if(opt==1)
		{
			int f1=find(a),f2=find(b);
			if(f1!=f2) fa[f1]=f2;
		}
		else 
		{
			int f1=find(a+n),f2=find(b);
			if(f1!=f2) fa[f1]=f2;
			f1=find(a),f2=find(b+n);
			if(f1!=f2) fa[f1]=f2;
		}
    }
    int ans=0;
    for(int i=1;i<=n;i++)
    {
		int f=find(i);
		if(!vis[f]) ans++,vis[f]=1;
    }
    printf("%d",ans);
    return 0;
}
