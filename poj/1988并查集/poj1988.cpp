#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;
const int MAXN=1e5;
int p;
int fa[MAXN+10],st[MAXN+10],d[MAXN+10];
//以一堆的最下面一个作为ancestor 

int find(int a)
{
	if(fa[a]==a) return a;
	int F=find(fa[a]);
	//先要更新a的fa[a]为原a所在堆的最下面一个
	//再去更新d[a]的值才对 
	d[a]+=d[fa[a]];
	//在此时加上下方的积木数 
	return fa[a]=F;
}

int main()
{
	scanf("%d",&p);
	for(int i=1;i<=MAXN;i++) 
	  fa[i]=i,st[i]=1,d[i]=0;
	char ch;
	int x,y,z;
	while(p)
	  {
	  	p--;
	  	cin>>ch;
	  	if(ch=='M')
	  	  {
	  	  	scanf("%d%d",&x,&y);
	  	  	x=find(x),y=find(y);
	  	  	fa[x]=y;
	  	  	d[x]=st[y];
	  	  	st[y]+=st[x];
	  	  }
	  	else
	  	  {
	  	  	scanf("%d",&z);
	  	  	find(z);
	  	  	printf("%d\n",d[z]);
	  	  }
	  }
	return 0;
} 