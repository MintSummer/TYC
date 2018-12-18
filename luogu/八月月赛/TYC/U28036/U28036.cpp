#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll p=998244353;
int n,m;
ll a[1000010],num[2010][2010],ans[10010];

struct ques
{
    int x,y,id;
    bool operator < (const ques &d) const
    {
        return x<d.x;
    }
}q[10010];

int main()
{
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>q[i].x>>q[i].y;q[i].id=i;}
    sort(q+1,q+1+m);
    int mx=q[m].x;
    for(int i=0;i<=mx+1;i++)
    {
        num[i][0]=1;
        for(int j=1;j<=i;j++)
            num[i][j]=(num[i-1][j-1]+num[i-1][j])%p;
    }
    for(int i=1;i<=m;i++)
    {
        int x=q[i].x,id=q[i].y,now=q[i].id;;
        for(int j=0;j<=x;j++)
            ans[now]=(ans[now]+num[x][j]*a[(id+j-1)%n+1]%p)%p;
    }
    for(int i=1;i<=m;i++) cout<<ans[i]<<endl;
    return 0;
}
