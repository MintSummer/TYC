#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;

struct Trie
{
	struct node
	{
		int count;
		node *son[26];
		node(){memset(son,0,sizeof(son));count=0;}
	}*head;
	
	void insert(char ch[])
	{
		if(head==NULL) head=new node;
		node *root=head;
		for(int i=0;i<strlen(ch);i++)
		{
			int tmp=ch[i]-'a';
			if(root->son[tmp]==NULL)
			{
				root->son[tmp]=new node;
				root=root->son[tmp];
				root->count++;
			}
			else 
				root=root->son[tmp],root->count++;
		}
	}
	
	int search(char ch[])
	{
		int len=strlen(ch);
		node *root=head;
		for(int i=0;i<len;i++)
		{
			int tmp=ch[i]-'a';
			if(root->son[tmp]==NULL) return 0;
			root=root->son[tmp];
		}
		return root->count;
	}
}trie;

int main()
{
	char ch[15];
	while(gets(ch)&&ch[0]!='\0') trie.insert(ch);
	while(gets(ch)) printf("%d\n",trie.search(ch));
	return 0;
}
