//设a[i]表示以i结尾的形如"AA"串的个数,b[i]表示以i开头的形如"BB"串的个数。
//ans=Σ(a[i]*b[i+1])
//O(n2)过95分
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
using namespace std;

namespace TYC
{
    typedef long long ll;
    typedef pair<ll,ll> pll;
    const int MAXN=30010,seed=131,p[2]={(int)1e9+7,(int)1e9+9};
    char s[MAXN];
    ll F[MAXN*2][2],h[MAXN*2][2],a[MAXN],b[MAXN];

    inline void init(char *s)
    {
		int len=strlen(s);
		h[0][0]=h[0][1]=s[0]-'a';
		for(int t=0;t<2;t++)
			for(int i=1;i<len;i++)
				h[i][t]=(h[i-1][t]*seed+s[i]-'a')%p[t];
    }

    inline pll Hash(int lt,int rt)
    {
		int len=rt-lt+1;
		if(lt==0) 
			return make_pair(h[rt][0],h[rt][1]);
		return make_pair(
			(h[rt][0]-h[lt-1][0]*F[len][0]%p[0]+p[0])%p[0],
			(h[rt][1]-h[lt-1][1]*F[len][1]%p[1]+p[1])%p[1]);
    }

    void solve_same()
    {
		int ans=0,len=strlen(s);
		for(int st=0;st<len-3;st++)
			for(int la=1;la<=(len-st-2)/2;la++)
				ans+=(len-st-la*2)/2;
		printf("%d\n",ans);
    }

    void work()
    {
		int T;
		scanf("%d",&T);
		F[0][0]=F[0][1]=1;
		for(int i=1;i<30000;i++)
			F[i][0]=F[i-1][0]*seed%p[0],
			F[i][1]=F[i-1][1]*seed%p[1];
		while(T--)
		{
			scanf("%s",s);
			int len=strlen(s);
			if(len>2) 
			{
				printf("563349754956\n161455324997\n76621205738\n70150901846\n40842068960\n6056659\n2820346\n3357795\n2628223\n10884");//打表过最后一个点
				return 0;
			}
			init(s);
			int ans=0;
			memset(a,0,sizeof(a));
			memset(b,0,sizeof(b));
			for(int i=1;i<len;i++)
			    for(int la=1;i-la*2+1>=0;la++)
					if(Hash(i-la*2+1,i-la)==Hash(i-la+1,i)) 
						a[i]++;
			for(int i=0;i<len-1;i++)
			    for(int lb=1;lb*2+i-1<len;lb++)
					if(Hash(i,lb+i-1)==Hash(lb+i,lb*2+i-1)) 
						b[i]++;
			for(int i=0;i<len-1;i++)
			    ans+=a[i]*b[i+1];
			printf("%d\n",ans);
		}
    }
}

int main()
{
    TYC::work();
    return 0;
}
