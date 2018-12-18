#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
    typedef long long ll;
    typedef pair<ll,ll> pa;
    const ll seed=233,p1=1e9+7,p2=1e9+9;
    const int N=110;
    char str[N];
    int dp[N][N];
    ll Pow1[N],Pow2[N],Hash1[N],Hash2[N];

    inline void get_hash(int n)
    {
        Pow1[0]=Pow2[0]=1;
        for(int i=1;i<=n;i++) 
        {
            Pow1[i]=Pow1[i-1]*seed%p1;
            Pow2[i]=Pow2[i-1]*seed%p2;
            Hash1[i]=(Hash1[i-1]*seed+str[i])%p1;
            Hash2[i]=(Hash2[i-1]*seed+str[i])%p2;
        }
    }

    inline pa hash(int l,int r)
    {
        return make_pair((Hash1[r]-Hash1[l-1]*Pow1[r-l+1]%p1+p1)%p1,
                         (Hash2[r]-Hash2[l-1]*Pow2[r-l+1]%p2+p2)%p2);
    }

    inline bool check(int l,int r,int len)
    {
        int tot=r-l+1;
        if(tot%len) return false;
        pa now=hash(l,l+len-1);
        for(int i=l+len;i<=r;i+=len)
            if(hash(i,i+len-1)!=now) return false;
        return true;
    }

    int dfs(int l,int r)
    {
        int &ans=dp[l][r];
        if(~ans) return ans;
        if(l==r) return ans=1;
        if(l>r) return ans=0;
        int len=r-l+1;
        ans=len;
        for(int i=l;i<r;i++)
            ans=min(ans,dfs(l,i)+dfs(i+1,r));
        for(int s=1;s<=(len>>1);s++)
            if(check(l,r,s))
            {
                int num=len/s,tmp=dfs(l,l+s-1)+2;
                if(num<10) tmp++;
                else if(num<99) tmp+=2;
                else tmp+=3;
                ans=min(ans,tmp);
            }
        return ans;
    }

    void work()
    {
        ios::sync_with_stdio(false);
        cin.tie(0);
        scanf("%s",str+1);
        int len=strlen(str+1);
        get_hash(len);
        memset(dp,-1,sizeof(dp));
        printf("%d",dfs(1,len));
    }
}

int main()
{
    TYC::work();
    return 0;
}