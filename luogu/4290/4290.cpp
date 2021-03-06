#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
	int tot,cnt[6],from[80],to[80][2],a[210],dp[210][210][80];
	char name[210];

	int num(char ch)
	{
		switch(ch)
		{
			case 'W': return 1;
			case 'I': return 2;
			case 'N': return 3;
			case 'G': return 4;
		}
	}

	void work()
	{
		for(int i=1;i<=4;i++) scanf("%d",&cnt[i]);
		char ch[4];
		for(int i=1;i<=4;i++)
			for(int j=1;j<=cnt[i];j++)
			{
				scanf("%s",ch);
				from[++tot]=i;
				to[tot][0]=num(ch[0]);
				to[tot][1]=num(ch[1]);
			}
		scanf("%s",name+1);
		int len=strlen(name+1);
		for(int i=1;i<=len;i++) dp[i][i][num(name[i])]=1;
		for(int i=1;i<=len;i++)
			for(int j=i+1;j<=len;j++)
				for(int k=i;k<j;k++)
					for(int word=1;word<=tot;word++)
						if(dp[i][k][to[word][0]]&&dp[k+1][j][to[word][1]])
							dp[i][j][from[word]]=1;
		bool flag=false;
		for(int i=1;i<=4;i++)
			if(dp[1][len][i])
			{
				flag=true;
				switch(i)
				{
					case 1: printf("W");break;
					case 2: printf("I");break;
					case 3: printf("N");break;
					case 4: printf("G");break;
				}
			}
		if(!flag) printf("The name is wrong!");
	}
}

int main()
{
	TYC::work();
	return 0;
}
