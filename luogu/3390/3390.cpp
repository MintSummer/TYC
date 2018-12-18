#include<iostream>
#include<cstring>
#define mod 1000000007
#define ll long long
using namespace std;
struct Mat{
    ll m[101][101];
}a,e;
ll n,p;
Mat Mul(Mat x,Mat y)
{
    Mat c;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) c.m[i][j]=0;
    for(int i=1;i<=n;i++)
      for(int j=1;j<=n;j++)
        for(int k=1;k<=n;k++)
        	c.m[i][j]=c.m[i][j]%mod+x.m[i][k]*y.m[k][j]%mod;
    return c; 
}
Mat qpow(Mat x,ll y) 
{
    Mat ans=e;
    for(;y;y>>=1,x=Mul(x,x))
    	if(y&1) ans=Mul(ans,x);
    return ans;
}

int main()
{
    cin>>n>>p;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) cin>>a.m[i][j]; 
    for(int i=1;i<=n;i++) e.m[i][i]=1;    
    Mat ans=qpow(a,p);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++) cout<<ans.m[i][j]%mod<<" ";
        cout<<endl;
    }  
    return 0;
}
