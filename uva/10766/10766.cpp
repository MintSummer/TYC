//Matrix_tree 基尔霍夫矩阵
#include<bits/stdc++.h>
using namespace std;
const int MAXN=60;
typedef long double ld;
const ld eps=1e-10;
int n,m,k;
bool G[MAXN][MAXN];
ld a[MAXN][MAXN],d[MAXN][MAXN];

int Get(ld x)
{
    if(fabs(x)<=eps) return 0;
    return x<0?-1:1;
}

//高斯消元求行列式的值
//行列式的两个性质
//1、上三角行列式（下三角行列式）的值等于其主对角线上n个元素的乘积。
//2、互换行列式的两行（列），行列式变号（正、负）。
ld judge()
{
    ld ans=1;
    int tim=0;//记录乘-1的次数
    for(int i=0;i<n;i++)//删掉最后一行一列
	for(int j=0;j<n;j++)
	    d[i][j]=a[i][j];
    
    for(int i=0;i<n;i++)
    {
	if(Get(d[i][i])==0)//由性质一得，行列式里的第一行第一列不能为0
	{
	    int k=i+1;
	    while(Get(d[k][i])==0) k++; 
	    if(k==n) return 0;//这一列（第一列）全为0
	    else 
	    {
		for(int j=i;j<n;j++)//将第一个不是0的那一个换上来
		    swap(d[i][j],d[k][j]);
		tim++;//性质二
	    }
    	}
	ans*=d[i][i];
	for(int j=i+1;j<n;j++)//性质一
	{
	    ld res=d[j][i]/d[i][i];
	    for(int k=i+1;k<n;k++)
		d[j][k]-=d[i][k]*res;
	}
    }
    return tim&1?-ans:ans;
}


int main()
{
    while(~scanf("%d%d%d",&n,&m,&k))
    {
	memset(a,0,sizeof(a));
	memset(G,true,sizeof(G));

	n--;
	int u,v;
	for(int i=1;i<=m;i++)
	{
	    scanf("%d%d",&u,&v);
	    u--,v--;
	    G[u][v]=G[v][u]=false;//u、v不能建边
	}
	for(int i=0;i<=n;i++)
	    for(int j=i+1;j<=n;j++)
		if(G[i][j])
		{
		    a[i][i]++,a[j][j]++;
		    a[i][j]=-1,a[j][i]=-1;
		}
	printf("%.0Lf\n",judge());
    }
    return 0;
}
