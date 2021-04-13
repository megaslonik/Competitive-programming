/* make a tree from a graph */

#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;
vector <int> dist(120, INF), g[120];
int par[120], vis[120], n;

void Prima()
{
    for (int i = 1; i <= n; i++)
    {
        int u, MIN = 1e9;
        for (int j = 1; j <= n; j++)
            if (dist[j] < MIN && vis[j] == 0)
            {
                MIN = dist[j];
                u = j;
            }
        vis[u] = 1;
        if (u != 1)
            cout << par[u] << " " << u << endl;
        for (int j = 0; j < g[u].size(); j++)
            if (vis[g[u][j]] == 0 && 1 < dist[g[u][j]])
            {
                dist[g[u][j]] = 1;
                par[g[u][j]] = u;
            }
    }
}

int main()
{
    int m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dist[1] = 0;
    Prima();
    return 0;
}
