#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,p,inv[3000010];

int main()
{
    scanf("%d%d",&n,&p);
    inv[1]=1;
    printf("%d\n",inv[1]);
    for(int i=2;i<=n;i++)
	printf("%d\n",inv[i]=(ll)(p-p/i)*inv[p%i]%p);
    return 0;
}
