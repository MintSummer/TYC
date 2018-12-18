#include<cstdio>
#include<cstring>
#include<cctype>
using namespace std;
int N,cnt[110];

inline int read()
{
	int x=0;
	char ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return x;
}

int buf[15];
inline void write(int x)
{
	int tot=0;
	if(x==0) tot++;
	else while(x) buf[tot++]=x%10,x/=10;
	for(int i=tot-1;i>=0;i--) putchar('0'+buf[i]);
}

int main()
{
	while(N=read())
	{
		memset(cnt,0,sizeof(cnt));
		for(int i=1;i<=N;i++) cnt[read()]++;
		int first=1;
		for(int i=1;i<=100;i++)
			for(int j=1;j<=cnt[i];j++)
			{
				if(!first) putchar(' ');
				first=0;
				write(i);
			}
		putchar('\n');
	}
	return 0;
}


