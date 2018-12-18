#include<bits/stdc++.h>
using namespace std;
priority_queue<int,vector<int>,greater<int> > q;

int main()
{
	int n,opt,x;
	scanf("%d",&n);
	while(n--)
	{
		scanf("%d",&opt);
		if(opt==1) scanf("%d",&x),q.push(x);
		else if(opt==2) printf("%d\n",q.top());
		else q.pop();
	}
	return 0;
}
