#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

namespace TYC
{
    typedef unsigned long long ull;
    typedef pair<ull, ull> pll;
    const ull p1 = 1e9 + 7, p2 = 1e9 + 9, seed = 233;
    const int LEN = 100010;
    int n;
	char Str[LEN];
    ull Pow[LEN];

    inline int read()
    {
        int x = 0, f = 0; char ch = getchar();
        while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
        while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
        return f ? -x : x;
    }

    inline void init(int n)
    {
        Pow[0] = 1;
        for (int i = 1; i <= LEN - 5; i++)
            Pow[i] = Pow[i - 1] * seed;
    }

    namespace Splay
    {
        struct node
        {
            int size;
            ull val, sum;
            node *fa, *son[2];
            node(ull v) : val(v)
            {
                sum = 0;
                size = 1;
                fa = son[0] = son[1] = NULL;
            }
        }*head;

        inline int dir(node *root)
        {
            return root->fa->son[1] == root;
        }

        void update(node *root)
        {
            int R = 0;
            ull ls = 0, rs = 0, v = root->val;
            root->size = 1;
            if (root->son[0]) 
            {
                ls = root->son[0]->sum;
                root->size += root->son[0]->size;
            }
            if (root->son[1]) 
            {
                R = root->son[1]->size;
                rs = root->son[1]->sum;
                root->size += root->son[1]->size;
            }
            root->sum = ls * Pow[R + 1] + v * Pow[R] + rs; 
        }

        inline void rotate(node *root)
        {
            int d = dir(root);
            node *f = root->fa;
            if (f->fa) 
                f->fa->son[dir(f)] = root;
            else 
                head = root;
            root->fa = f->fa;
            f->son[d] = root->son[d^1];
            if (root->son[d^1]) 
                root->son[d^1]->fa = f;
            root->son[d^1] = f;
            f->fa = root;
            update(f);
            update(root);
        }

        inline void splay(node *root, node *goal)
        {
            for (; root->fa != goal; rotate(root))
                if (root->fa->fa != goal)
                    rotate(dir(root->fa) == dir(root) ? root->fa : root); 
        }

        inline node *get_nxt(node *root)
        {
            splay(root, NULL);
            if (root->son[1] == NULL) return NULL;
            node *nxt = root->son[1];
            while (nxt->son[0])
                nxt = nxt->son[0];
            return nxt;
        }

        inline node *findkth(int k)
        {
            node *root = head;
            while (1)
            {
                if (root->son[0] && root->son[0]->size >= k)
                    root = root->son[0];
                else
                {
                    if (root->son[0]) k -= root->son[0]->size;
                    k--;
                    if (!k) return root;
                    else root = root->son[1];
                }
            }
        }
        
        inline void insert(int num, char c)
        {
            node *now = new node(c - 'a');
            if (head == NULL) 
                head = now;
            else if (num == 1)
            {
                node *root = head;
                root->fa = now;
                now->son[1] = root;
                head = now;
            }
            else
            {
                node *root = findkth(num - 1);
                splay(root, NULL);
                if (root->son[1])
                {
                    node *nxt = get_nxt(root);
                    splay(nxt, root);
                    nxt->son[0] = now;
                    now->fa = nxt;
                }
                else
                { 
                    root->son[1] = now;
                    now->fa = root;
                }
                splay(now, NULL);
            }
        }

        inline void del(int x)
        {
            node *root = findkth(x);
            splay(root, NULL);
            if (root->son[0] == NULL)
            {
                head = root->son[1];
                if (root->son[1]) root->son[1]->fa = NULL;
            }
            else if (root->son[1] == NULL)
            {
                head = root->son[0];
                if (root->son[0]) root->son[0]->fa = NULL;
            }
            else
            {
                node *nxt = get_nxt(root);
                splay(nxt,root);
                nxt->son[0] = root->son[0];
                root->son[0]->fa = nxt;
                nxt->fa = NULL;
                head = nxt;
                update(head);
            }
            delete(root);
        }

        inline ull hash(int l, int r)
        {
            l--;
			if (!l) 
			{
				if (r == n) return head->sum;
				node *root = findkth(r + 1);
				splay(root, NULL);
				return root->son[0]->sum;
			} 
			node *L = findkth(l);
			if (r == n) 
			{
				splay(L, NULL);
				return L->son[1]->sum;
			}
			else
			{
				node *R = findkth(r + 1);
				splay(L, NULL);
				splay(R, L);
				return R->son[0]->sum;
			}
        }
    }

    bool check(int x, int y, int len)
    {
        return Splay::hash(x, x + len - 1) == Splay::hash(y, y + len - 1); 
   }

    void work()
    {
        scanf("%s",Str + 1);
        n = strlen(Str + 1);
        init(n);
        for (int i = 1; i <= n; i++) 
            Splay::insert(i, Str[i]); 
        int ques = read(), x, y, l, r, mid, ans;
        char ch;
        while (ques--)
        {
            do ch = getchar(); while (!isalpha(ch));
            switch (ch)
            {
                case 'Q': 
                    x = read(), y = read();
                    if (x > y) swap(x, y);
                    l = 1, r = n - y + 1, ans = 0;
                    while (l <= r)
                    {
                        mid = (l + r) >> 1;
                        if (check(x, y, mid)) ans = mid, l = mid + 1;
                        else r = mid - 1;
                    }
                    printf("%d\n", ans);
                    break;
                case 'I':
                    x = read();
                    do ch = getchar(); while (!isalpha(ch));
                    Splay::insert(x + 1, ch);
                    n++;
                    break;
                case 'R':
                    x = read();
                    do ch = getchar(); while (!isalpha(ch));
                    Splay::del(x);
                    Splay::insert(x, ch);
                    break;
            }
        }
    }
}
int main()
{
    TYC::work();
    return 0;
}
