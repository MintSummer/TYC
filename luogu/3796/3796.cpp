#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e6+10;
int cnt,q[MAXN];
string st[160];

struct Str
{
	int tim,pos;
	bool operator < (const Str &p) const
	{
		return (tim>p.tim)||(tim==p.tim&&pos<p.pos);
	}
}a[160];

struct node
{
	int end,fail,son[26];
	void clean()
	{
		end=fail=0;
		memset(son,0,sizeof(son));
	}
}AC[MAXN];

inline void insert(string ch,int num)
{
	int len=ch.size();
	int now=0;
	for(int i=0;i<len;i++)
	{
		int tmp=ch[i]-'a';
		if(!AC[now].son[tmp]) 
			AC[now].son[tmp]=++cnt,AC[cnt].clean();
		now=AC[now].son[tmp];
	}
	AC[now].end=num;
}

inline void get_fail()
{
	int h=0,t=0;
	for(int i=0;i<26;i++)
		if(AC[0].son[i])
			AC[AC[0].son[i]].fail=0,q[++t]=AC[0].son[i];
	while(h<t)
	{
		int now=q[++h];
		for(int i=0;i<26;i++)
			if(AC[now].son[i])
			{
				AC[AC[now].son[i]].fail=AC[AC[now].fail].son[i];
				q[++t]=AC[now].son[i];
			}
			else AC[now].son[i]=AC[AC[now].fail].son[i];			
	}
}

void search(string ch)
{
	int len=ch.size();
	int now=0;
	for(int i=0;i<len;i++)
	{
		int tmp=ch[i]-'a';
		now=AC[now].son[tmp];
		for(int j=now;j;j=AC[j].fail) a[AC[j].end].tim++;
	}
}

int main()
{
	int n;
	string ques;
	while(scanf("%d",&n)&&n)
	{
		AC[0].clean();
		cnt=0;
		
		for(int i=1;i<=n;i++)
		{
			cin>>st[i];
			insert(st[i],i);
			a[i].tim=0,a[i].pos=i;
		}
		get_fail();
		cin>>ques;
		
		search(ques);
		sort(a+1,a+1+n);
		cout<<a[1].tim<<endl;
		cout<<st[a[1].pos]<<endl;
		for(int i=2;i<=n;i++)
			if(a[i].tim==a[i-1].tim) cout<<st[a[i].pos]<<endl;
			else break;
	}
	return 0;
} 
