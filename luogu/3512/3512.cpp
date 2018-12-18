#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N=3000010;
    ll k,a[N];
    int n,qmx[N],qmn[N];

    void work()
    {
		ios::sync_with_stdio(false);
		cin>>k>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		int lmx=1,lmn=1,rmx=1,rmn=1,ans=0,st=1;
		qmx[1]=qmn[1]=1;
		for(int i=2;i<=n;i++)
		{
			while(lmx<=rmx&&a[i]>a[qmx[rmx]]) rmx--;
			while(lmn<=rmn&&a[i]<a[qmn[rmn]]) rmn--;
			qmx[++rmx]=i,qmn[++rmn]=i;
			while(a[qmx[lmx]]-a[qmn[lmn]]>k)
			{
				if(qmx[lmx]<qmn[lmn]) st=qmx[lmx]+1,lmx++;
				else st=qmn[lmn]+1,lmn++;
			}
			ans=max(ans,i-st+1);
		}
		printf("%d",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
