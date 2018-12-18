#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    int n,m,ans;

    void dfs(int res,int k,int last)
    {
        if(!res) {ans+=(!k);return;}
		if(!k) return;
        for(int i=last,tmp=(k-1)*last;i+tmp<=res;i++)
            dfs(res-i,k-1,i);
    }

    void work()
    {
        scanf("%d%d",&n,&m);
        dfs(n,m,1);
        printf("%d\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
