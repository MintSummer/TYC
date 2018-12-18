#include<cstdio>
#include<algorithm>
#include<iostream>
#include<stack>
#include<queue>
using namespace std;
int n;

int main()
{
	while(~scanf("%d",&n))
	{
		stack<int> st;
		queue<int> q;
		priority_queue<int> pq;
		int fst=1,fq=1,fpq=1,opt,x;
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d",&opt,&x);
			if(opt==1)
				st.push(x),q.push(x),pq.push(x);
			else
			{
				if(fst) 
				{
					if(st.empty()||st.top()!=x) fst=0;
					if(!st.empty()) st.pop();
				}
				if(fq) 
				{
					if(q.empty()||q.front()!=x) fq=0;
					if(!q.empty()) q.pop();
				}
				if(fpq) 
				{
					if(pq.empty()||pq.top()!=x) fpq=0;
					if(!pq.empty()) pq.pop();
				}
			}
		}
		if(fst|fq|fpq) 
		{
			if((fst&fq)|(fst&fpq)|(fq&fpq)) printf("not sure");
			else if(fst) printf("stack");
			else if(fq) printf("queue");
			else printf("priority queue");
		}
		else printf("impossible");
		printf("\n");
	}
	return 0;	
}
