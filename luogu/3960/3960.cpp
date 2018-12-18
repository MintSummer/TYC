#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N = 3e5 + 10;

    inline int read()
    {
        int x = 0, f = 0;
        char ch = getchar();
        while (!isdigit(ch))
            f |= (ch == '-'), ch = getchar();
        while (isdigit(ch))
            x = x * 10 + ch - '0', ch = getchar();
        return f ? -x : x;
    }

    struct Splay
    {
        struct node
        {
            ll size, l, r;
            node *fa, *son[2];
            node(ll _l, ll _r) : l(_l), r(_r), size(_r - _l + 1) {}
        } * head;

        void update(node *root)
        {
            root->size = root->r - root->l + 1;
            if (root->son[0])
                root->size += root->son[0]->size;
            if (root->son[1])
                root->size += root->son[1]->size;
        }

        int dir(node *root)
        {
            return root->fa->son[1] == root;
        }

        void rotate(node *root)
        {
            int d = dir(root);
            node *f = root->fa;
            if (f->fa)
                f->fa->son[dir(f)] = root;
            else
                head = root;
            root->fa = f->fa;
            f->son[d] = root->son[d ^ 1];
            if (root->son[d ^ 1])
                root->son[d ^ 1]->fa = f;
            root->son[d ^ 1] = f;
            f->fa = root;
            update(f);
            update(root);
        }

        void splay(node *root)
        {
            for (; root->fa; rotate(root))
                if (root->fa->fa)
                    rotate(dir(root) == dir(root->fa) ? root->fa : root);
        }

        void insert(node *now)
        {
            now->size = now->r - now->l + 1;
            if (head == NULL)
                head = now;
            else
            {
                node *root = head;
                while (root->son[1])
                    root = root->son[1];
                splay(root);
                root->son[1] = now;
                now->fa = root;
                update(root);
            }
        }

        node *split(node *root, ll k)
        {
            k += root->l - 1;
            node *now = new node(k + 1, root->r);
            root->r = k;
            if (root->son[1] == NULL)
            {
                root->son[1] = now;
                now->fa = root;
            }
            else
            {
                node *t = root->son[1];
                while (t->son[0])
                    t = t->son[0];
                t->son[0] = now;
                now->fa = t;
                while (t != root)
                    update(t), t = t->fa;
            }
            splay(now);
            return now;
        }

        void del(node *root)
        {
            splay(root);
            if (root->son[0] == NULL)
            {
                head = root->son[1];
                if (root->son[1])
                    root->son[1]->fa = NULL;
            }
            else if (root->son[1] == NULL)
                head = root->son[0], root->son[0]->fa = NULL;
            else
            {
                node *t = root->son[0];
                while (t->son[1])
                    t = t->son[1];
                splay(t);
                root->son[1]->fa = t;
                t->son[1] = root->son[1];
                update(root->son[1]);
            }
            root->son[0] = root->son[1] = root->fa = NULL;
        }

        node *findkth(ll k)
        {
            node *root = head, *ans;
            while (true)
            {
                if (root ->son[0] && root->son[0]->size >= k)
                    root = root->son[0];
                else
                {
                    if (root->son[0])
                        k -= root->son[0]->size;
                    int len = root->r - root->l + 1;
                    if (k <= len)
                    {
                        if (k != len)
                            split(root, k);
                        if (k != 1)
                            ans = split(root, k - 1);
                        else ans = root;
                        break;
                    }
                    else
                    {
                        root = root->son[1];
                        k -= len;
                    }
                }
            }
            del(ans);
            return ans;
        }
    } splay[N];

    void work()
    {
        int n = read(), m = read(), q = read();
        for (ll i = 1; i <= n; i++)
            splay[i].head = new Splay::node((i - 1) * m + 1, i * m - 1);
        splay[0].head = new Splay::node(m, m);
        for (ll i = 2; i <= n; i++)
        {
            Splay::node *now = new Splay::node(i * m, i * m);
            splay[0].insert(now);
        }
        while (q--)
        {
            int x = read(), k = read();
            splay[x].insert(splay[0].findkth(x));
            Splay::node *ans = splay[x].findkth(k);
            printf("%lld\n", ans->l);
            splay[0].insert(ans);
        }
    }
} // namespace TYC

int main()
{
    TYC::work();
    return 0;
}