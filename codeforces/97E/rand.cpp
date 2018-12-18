#include<bits/stdc++.h>
using namespace std;

const int N=100000;

int main()
{
	srand(time(NULL));
	cout<<N<<" "<<N<<"\n";
	for(int i=1;i<=N;i++) cout<<rand()%N+1<<" "<<rand()%N+1<<"\n";
	cout<<N<<"\n";
	for(int i=1;i<=N;i++) cout<<rand()%N+1<<" "<<rand()%N+1<<"\n";
	return 0;
}
