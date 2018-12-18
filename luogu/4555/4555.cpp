#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=1e5+10;
	char ch[N],s[N<<1];
	int len,n,p[N<<1],l[N<<1],r[N<<1];

	void work()
	{
		scanf("%s",ch);
		len=strlen(ch);
		for(int i=0;i<len;i++) s[n++]='#',s[n++]=ch[i];
		s[n++]='#';
		int mx=-1,pos=0,ans=0;
		for(int i=0;i<n;i++) 
		{
			if(i<mx) p[i]=min(p[2*pos-i],mx-i+1);
			else p[i]=1;
			while(0<=i-p[i]&&i+p[i]<n&&s[i-p[i]]==s[i+p[i]]) p[i]++;
			if(i+p[i]-1>mx) mx=i+p[i]-1,pos=i;
			l[i+p[i]-1]=max(l[i+p[i]-1],p[i]-1);
			r[i-p[i]+1]=max(r[i-p[i]+1],p[i]-1);
		}
		for(int i=0;i<n;i+=2) r[i]=max(r[i],r[i-2]-2);
		for(int i=n-1;i>=0;i-=2) l[i]=max(l[i],l[i+2]-2);
		for(int i=0;i<n;i+=2) 
			if(l[i]&&r[i]) ans=max(ans,l[i]+r[i]);
		printf("%d\n",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
