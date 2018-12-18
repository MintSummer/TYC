#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N=100010;

    int n,arr[2][200010];
    ll T,bin[100];

    inline int id(int x,int i,int type)
    {
        return (((x+bin[i-1]%n*type)%n+n)%n)<<1;
    }

    void work()
    {
        scanf("%d%lld",&n,&T);
        for(int i=0;i<n;i++)
            scanf("%d",&arr[0][i<<1]),arr[0][i<<1]--;
        bin[0]=1;
        for(int i=1;i<=60;i++) bin[i]=bin[i-1]<<1;
        int now=0;
        for(int i=1;bin[i]<=T;i++)
            if(T&bin[i])
            {
                now^=1;
                for(int j=0;j<n;j++)
                    arr[now][j<<1]=arr[now^1][id(j,i,-1)]^arr[now^1][id(j,i,1)];
            }
        if(T&1)
        {
            now^=1;
            for(int i=0;i<n;i++)
                arr[now][(i<<1)+1]=arr[now^1][i<<1]^arr[now^1][((i<<1)+2)%(n<<1)];
            for(int i=1;i<(n<<1);i+=2)
                printf("0 %d ",arr[now][i]+1);
        }
        else for(int i=0;i<(n<<1);i+=2)
            printf("%d 0 ",arr[now][i]+1);
	}
}

int main()
{
    TYC::work();
    return 0;
}
