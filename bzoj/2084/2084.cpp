#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=1000010;
	typedef unsigned long long ull;
    char ch[N],s[N<<1];
    int n,tot,len[N<<1];

    inline char to(char x)
    {
		if(x=='0'||x=='1')
			return (!(x-'0'))+'0';
		else return x;
    }

    void work()
    {
        scanf("%d%s",&n,ch+1);
        s[0]='$',s[++tot]='#';
        for(int i=1;i<=n;i++)
            s[++tot]=ch[i],s[++tot]='#';
        int Right=1,mid=1;
		ull ans=0;
        for(int i=1;i<=tot;i+=2)
        {
            if(i<Right) 
				len[i]=min(len[(mid<<1)-i],Right-i);
			else len[i]=1;
            while(i+len[i]<=tot&&s[i-len[i]]==to(s[i+len[i]])) len[i]++;
            if(i+len[i]>Right) 
				Right=i+len[i]-1,mid=i;
			ans+=(len[i]-1)>>1;
        }
        printf("%llu\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
