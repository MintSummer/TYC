#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=1010;
	const int M=110;

	int n,arr[N][M],len[N],nxt[M][M],str[M][M],length[M];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	inline void KMP(int s,int *fail)
	{
		int l=0;
		for(int i=s;i<len[1];i++) str[s][l++]=arr[1][i];
		length[s]=l;
		fail[0]=fail[1]=0;
		for(int i=1;i<l;i++)
		{
			int tmp=fail[i];
			while(tmp&&str[s][tmp]!=str[s][i]) 
				tmp=fail[tmp];
			fail[i+1]=(str[s][tmp]==str[s][i]?tmp+1:0);
		}
	}

	inline int search(int *c,int l,int *fail,int *s)
	{
		int tmp=0,ans=0;
		for(int i=0;i<l;i++)
		{
			while(tmp&&c[i]!=s[tmp])
				tmp=fail[tmp];
			if(c[i]==s[tmp]) tmp++;
			ans=max(ans,tmp);
		}
		return ans;
	}

	void work()
	{
		n=read();
		for(int i=1;i<=n;i++)
		{
			len[i]=read();
			int x=read();
			for(int j=1;j<len[i];j++)
			{
				int y=read();
				arr[i][j-1]=y-x;
				x=y;
			}
			len[i]--;
		}
		for(int s=0;s<len[1];s++) KMP(s,nxt[s]);
		int ans=0;
		for(int s=0;s<len[1];s++)
		{
			int mn=M;
			for(int i=2;i<=n;i++)
				mn=min(mn,search(arr[i],len[i],nxt[s],str[s]));
			ans=max(ans,mn);
		}
		printf("%d\n",ans+1);
	}
}

int main()
{
	TYC::work();
	return 0;
}
