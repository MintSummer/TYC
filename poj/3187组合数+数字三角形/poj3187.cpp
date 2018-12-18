#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int n,sum,ans[25]={0},c[25][25]={0};
bool vis[25]={0};
void solve(int step,int &maxx,int &minx)
{
    maxx=minx=0;
    int j1=1,j2=n;
    for(int i=0;n-i>=i+1;i++)
    {
        if (!ans[i+1])
        {
            while(vis[j1]) j1++;
            while(vis[j2]) j2--;
            maxx+=j1*c[n][i+1];j1++;
            minx+=j2*c[n][i+1];j2--;
        }
        if (!ans[n-i]&&n-i>i+1)
        {
            while(vis[j1]) j1++;
            while(vis[j2]) j2--;
            maxx+=j1*c[n][i+1];j1++;
            minx+=j2*c[n][i+1];j2--;
        }
    }
}
bool dfs(int step,int now)
{
    if (step==n+1)
    {
        if (now==sum) {for(int i=1;i<=n;i++) printf("%d ",ans[i]);return 1;}
        else return 0;
    }
    int maxx,minx;
    solve(step,maxx,minx);
    if (now+maxx<sum) return 0;
    if (now+minx>sum) return 0;
    int i=1;
    if (step>n-step+1) i=ans[n-step+1]+1;
    for(;i<=n;i++)
        if (!vis[i])
        {
            ans[step]=i;
            vis[i]=1;
            if (dfs(step+1,now+i*c[n][step])) return 1;
            ans[step]=0;
            vis[i]=0;
        }
    return 0;
}
int main()
{
    scanf("%d%d",&n,&sum);
    c[1][1]=1;
    for(int i=2;i<=n;i++)
        for(int j=1;j<=i;j++)
            c[i][j]=c[i-1][j-1]+c[i-1][j];
    dfs(1,0);
    return 0;
}