#include<bits/stdc++.h>
#define For(i,n) for(int i=1;i<=n;i++)
using namespace std;
int n,cnt,x,y,z;
char now[15][15][15],s[8][15][15];

int read()
{
    char ch=getchar();
    while((ch<'A'||ch>'Z')&&(ch!='.')) ch=getchar();
    return ch;
}

void Get(int k,int i,int j,int d,int &x,int &y,int &z)
{
    if(k==1) x=i,y=j,z=d;
    else if(k==2) x=i,y=d,z=n-j+1;
    else if(k==3) x=i,y=n-j+1,z=n-d+1;
    else if(k==4) x=i,y=n-d+1,z=j;
    else if(k==5) x=d,y=j,z=n-i+1;
    else x=n-d+1,y=j,z=i;
}

int main()
{
    while(scanf("%d",&n)&&n)
    {
	For(i,n) For(k,6) For(j,n)
	    s[k][i][j]=read();
	For(i,n) For(j,n) For(k,n) 
	    now[i][j][k]='#';
	For(k,6) For(i,n) For(j,n) 
	    if(s[k][i][j]=='.') 
		For(d,n)
		{
		    int x,y,z;
		    Get(k,i,j,d,x,y,z);
		    now[x][y][z]='.';
		}

	while(1)
	{
	    bool ok=true;
	    For(k,6) For(i,n) For(j,n)
		if(s[k][i][j]!='.') 
		{
		    int x,y,z;
		    For(d,n)
		    {
			Get(k,i,j,d,x,y,z);
			if(now[x][y][z]=='.') continue;
			if(now[x][y][z]=='#') 
			    {now[x][y][z]=s[k][i][j];break;}
			if(now[x][y][z]==s[k][i][j]) break;
			now[x][y][z]='.';
			ok=false;
		    }
		}
	    if(ok) break;
	}

	int ans=0;
	For(k,n) For(i,n) For(j,n)
	    if(now[k][i][j]!='.') ans++;
	
	printf("Maximum weight: %d gram(s)\n",ans);
    }
    return 0;
}
