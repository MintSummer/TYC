#include<bits/stdc++.h>
using namespace std;
int T,n,dx[5]={0,1,0,-1,0},dy[5]={0,0,1,0,-1};
char a[15][15];

bool check(int x,int y,char k)
{
    for(int i=1;i<=4;i++)
    {
		int nx=x+dx[i],ny=y+dy[i];
		if(nx<0||nx>=n||ny<0||ny>=n) continue;
		if(k==a[nx][ny]) return false;
    }
    return true;
}

int main()
{
    scanf("%d",&T);
    for(int kase=1;kase<=T;kase++)
    {
		printf("Case %d:\n",kase);
		memset(a,0,sizeof(a));
		scanf("%d",&n);
		for(int i=0;i<n;i++) scanf("%s",a[i]);
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			if(a[i][j]!='.') printf("%c",a[i][j]);
			else 
			{
				for(char k='A';k<='Z';k++)
				if(check(i,j,k))
					{printf("%c",a[i][j]=k);break;}
			}
			printf("\n");
		}
    }
    return 0;
}
