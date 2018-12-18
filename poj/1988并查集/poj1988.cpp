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
//��һ�ѵ�������һ����Ϊancestor 

int find(int a)
{
	if(fa[a]==a) return a;
	int F=find(fa[a]);
	//��Ҫ����a��fa[a]Ϊԭa���ڶѵ�������һ��
	//��ȥ����d[a]��ֵ�Ŷ� 
	d[a]+=d[fa[a]];
	//�ڴ�ʱ�����·��Ļ�ľ�� 
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