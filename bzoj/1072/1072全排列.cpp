//全排列
#include<bits/stdc++.h>
#include<set>
using namespace std;
typedef long long ll;
set<ll>ss;
int t,n,p,num[15];


void solve()
{
	ll ans=0;
	char ch[15];
	ss.clear();
	scanf("%s%d",ch,&p);
	n=strlen(ch);
	for(int i=0;i<n;i++) num[i]=ch[i]-'0';
	sort(num,num+n);
	while(1)
	{
		ll tmp=0;
		for(int i=0;i<n;i++) tmp=tmp*10+num[i];
		if(!ss.count(tmp)&&tmp%p==0)
			ss.insert(tmp),ans++;
		if(!next_permutation(num,num+n)) break;
	}
	printf("%lld\n",ans);
}

int main()
{
	scanf("%d",&t);
	while(t--) solve();
	return 0;
}
