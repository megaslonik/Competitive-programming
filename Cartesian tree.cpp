/* A segment from l to r should be moved to the beginning of an array */


#include <iostream>

using namespace std;

struct node
{
    int x, pr, sz;
    node *l, *r;
};

node *t;

int get_size(node *t)
{
    return (t == 0) ? 0 : t->sz;
}

void Updsz(node *t)
{
    if (t != 0)
        t->sz = get_size(t->l) + get_size(t->r) + 1;
}

node* Merge(node *tl, node *tr)
{
    if (tl == 0)
        return tr;
    if (tr == 0)
        return tl;
    if (tl->pr < tr->pr)
    {
        tr->l = Merge(tl, tr->l);
        Updsz(tr);
        return tr;
    }
    else
    {
        tl->r = Merge(tl->r, tr);
        Updsz(tl);
        return tl;
    }
}

void Split(node *t, node *&tl, node *&tr, int k)
{
    if (t == 0)
    {
        tl = tr = 0;
        return;
    }
    if (get_size(t->l) + 1 < k)
    {
        int newk = k - get_size(t->l) - 1;
        Split(t->r, t->r, tr, newk);
        tl = t;
        Updsz(t);
    }
    else
    {
        Split (t->l, tl, t->l, k);
        tr = t;
        Updsz(t);
    }
}

void Insert(node *&t, int x)
{
    node *tm;
    tm = new node;
    tm->x = x;
    tm->pr = rand() * rand();
    tm->sz = 1;
    tm->l = tm->r = 0;

    t = Merge(t, tm);
}

void Build(int n)
{
    for (int i = 1; i <= n; i++)
        Insert(t, i);
}

void Out(node *t)
{
    if (t == 0)
        return;
    Out(t->l);
    cout << t->x << " ";
    Out(t->r);
}

void Shift(node *&t, int l, int r)
{
    node *tl, *tmr, *tm, *tr;
    Split (t, tmr, tr, r + 1);
    Split (tmr, tl, tm, l);

    t = Merge(tm, Merge(tl, tr));
}

int main()
{
    int n, m;
    cin >> n >> m;
    Build(n);
    for (int i = 1; i <= m; i++)
    {
        int l, r;
        cin >> l >> r;
        Shift(t, l, r);
    }
    Out(t);
    return 0;
}
