#include<bits/stdc++.h>
using namespace std;
int T,len,tim,n,order[10010];
/*
蚂蚁相遇后的反向其实相当于没有掉头，继续向前走，
只是这时候已经不是同一只蚂蚁在朝这个方向走了而已，相当于互换了编号 
（其实也可以考虑直接穿过去了，只不过蚂蚁的编号一直在变而已） 
但无论怎么变，相对位置不会改变 
*/

int read()
{
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') 
	{
		if(ch=='L') return -1;
		else if(ch=='R') return 1; 
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x;
}

struct Ant
{
	int id,pos,dir;
	bool operator < (const Ant &a) const
	{
		return pos<a.pos;
	}
}before[10010],after[10010];

int main()
{
	T=read();
	for(int cas=1;cas<=T;cas++)
	{
		printf("Case #%d:\n",cas);
		len=read(),tim=read(),n=read();
		int a,b;
		for(int i=1;i<=n;i++)
		{
			a=read(),b=read();
			before[i]=(Ant){i,a,b};
			after[i]=(Ant){0,a+tim*b,b};
		}
		sort(before+1,before+1+n);
		for(int i=1;i<=n;i++)
			order[before[i].id]=i;
		sort(after+1,after+1+n);
		for(int i=1;i<n;i++)
			if(after[i].pos==after[i+1].pos) 
				after[i].dir=after[i+1].dir=0;
		for(int i=1;i<=n;i++)
		{
			int x=order[i];
			if(after[x].pos<0||after[x].pos>len)
				{printf("Fell off\n");continue;}
			printf("%d ",after[x].pos);
			if(after[x].dir==0) printf("Turning\n");
			else if(after[x].dir==1) printf("R\n");
			else printf("L\n");
		}
		puts("");
	}
	return 0;
} 
