#include<bits/stdc++.h>
using namespace std;

int main()
{
	srand(time(NULL));
	int n=rand()%5000+1,m=rand()%5000+1;
	cout<<n<<" "<<m<<endl;
	for(int i=1;i<=n;i++)
		cout<<rand()<<" ";
	puts("");
	for(int i=1;i<=m;i++)
		cout<<rand()<<" "<<rand()<<endl;
	return 0;
}
