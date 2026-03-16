#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n , q;
int a[N];
int lazy[4 * N][31] , st[4 * N][31];

void flip(int id , int pos , int l , int r)
{
    lazy[id][pos] ^= 1;
    st[id][pos] = (r - l + 1) - st[id][pos];
}

void push(int id , int p , int l , int r , int mid)
{
    if(lazy[id][p] != 0)
    {
        flip(id * 2 , p , l , mid);
        flip(id * 2 + 1 , p , mid + 1 , r);
        lazy[id][p] = 0;
    }

}

void build(int id , int l , int r)
{
    if(l == r)
    {
        for(int i = 0 ; i <= 30 ; i++)
            st[id][i] = ((a[l] >> i) & 1);
        return;
    }
    int mid = (l + r) / 2;
    build(id * 2 , l , mid);
    build(id * 2 + 1 , mid + 1 , r);
    for(int i = 0 ; i <= 30 ; i++)
        st[id][i] = (st[id * 2][i] + st[id * 2 + 1][i]);
}

void update(int id , int l , int r , int u , int v , int p)
{
    if(l > v || r < u)
        return;
    if(l >= u && r <= v)
    {
        flip(id , p , l , r);
        return;
    }
    int mid = (l + r) / 2;
    push(id , p , l , r , mid);
    update(id * 2 , l , mid , u , v , p);
    update(id * 2 + 1 , mid + 1 , r , u , v , p);
    st[id][p] = (st[id * 2][p] + st[id * 2 + 1][p]);
}

int get(int id , int l , int r , int u , int v , int p)
{
    if(l > v || r < u)
        return 0;
    if(l >= u && r <= v)
        return st[id][p];
    int mid = (l + r) / 2;
    push(id , p , l , r , mid);
    return get(id * 2 , l , mid , u , v , p)
        +  get(id * 2 + 1 , mid + 1 , r , u , v , p);
}

main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> q;
    for(int i = 1 ; i <= n ; i++)
        cin >> a[i];
    build(1 , 1 , n);
    while(q--)
    {
        int l , r , x , type;
        cin >> type >> l >> r >> x;

        if(type == 1)
        {
            for(int i = 0 ; i <= 30 ; i++)
                if((x >> i) & 1)
                   update(1 , 1 , n , l , r , i);
        }
        else if(type == 2)
        {
            int ans = 0;
            for(int i = 0 ; i <= 30 ; i++)
            {
                int cnt_1 = get(1 , 1 , n , l , r , i);
                if(cnt_1 % 2 == 1)
                    ans += (1 << i);
            }
            cout << (ans ^ x) << "\n";
        }
        else if(type == 3)
        {
            int ans = 0;
            for(int i = 0 ; i <= 30 ; i++)
            {
                int cnt_1 = get(1 , 1 , n , l , r , i);
                if(cnt_1 == (r - l + 1))
                    ans += (1 << i);
            }
            cout << (ans & x) << "\n";
        }
        else
        {
            int ans = 0;
            for(int i = 0 ; i <= 30 ; i++)
            {
                int cnt_1 = get(1 , 1 , n , l , r , i);
                if(cnt_1 > 0)
                    ans += (1 << i);
            }
            cout << (ans | x) << "\n";
        }
    }
}