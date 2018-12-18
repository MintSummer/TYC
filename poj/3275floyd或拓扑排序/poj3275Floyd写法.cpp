#include<bits/stdc++.h>
using namespace std;
const int N=1005;
bitset<N> mat[N];
//floydд��������Ӧ��bitset�����Ż�������O(n3)����ȥ 
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        mat[i][i]=true;
    while(m--)
    {
        int u,v;
        cin>>u>>v;
        mat[u][v]=true;
    }
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            if(mat[i][k])
                mat[i]|=mat[k];
    int ans=0;
    for(int i=1;i<=n;i++)
        ans+=mat[i].count();
    cout<<n*(n-1)/2-ans+n<<endl;
    return 0;
}
