#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,g[5][35];
ll f[5][35];
//f[x][i]表示将编号为x的柱子有i个块，移走i个需要的步数
//g[x][i]表示将编号为x的柱子有i个块，将那i个移到了哪一个柱子

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=3;i++) f[i][1]=1;
    char ch[4];
    for(int i=1;i<=6;i++)
    {
	scanf("%s",ch);
	if(!g[ch[0]-'A'+1][1])
	    g[ch[0]-'A'+1][1]=ch[1]-'A'+1;
    }
    
    for(int i=1;i<n;i++)
	for(int x=1;x<=3;x++)
	{
	    int y=g[x][i],z=6-x-y;
	    f[x][i+1]=f[x][i]+1;
	    if(g[y][i]==z) f[x][i+1]+=f[y][i],g[x][i+1]=z;
	    else f[x][i+1]+=f[y][i]+1+f[x][i],g[x][i+1]=y;
	}
    printf("%lld",f[1][n]);
    return 0;
}
