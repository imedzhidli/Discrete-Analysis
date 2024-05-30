#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void addtoGraph(vector<vector<long long>> &graph, long long a, long long b, long long value){
    graph[a][b] = value;
}

long long bfs(vector<vector<long long>> &rgraph, vector<long long> &parent, long long s, long long t){
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    long long sizer = rgraph.size();
    queue<pair<long long, long long>> q;
    q.push({s, 1000000000});
    while(!q.empty()){
        long long u = q.front().first;
        long long imedy = q.front().second;
        q.pop();
        for (long long jj = 0; jj < sizer; ++jj){
            if(parent[jj] == -1 && rgraph[u][jj] > 0 && u != jj ){
                parent[jj] = u;
                long long min_edge = min(imedy, rgraph[u][jj]);
                if(jj == t) return min_edge;
                q.push({jj, min_edge});
            }
        }
    }
    return 0;
}

long long FFFunction(vector<vector<long long>> &graph, long long s, long long t){
    vector<vector<long long>> rgraph = graph;
    vector <long long> parent(graph.size(), -1);
    long long min_edge = 0, max_flow = 0;
    while(min_edge = bfs(rgraph, parent, s, t)){
        max_flow += min_edge;
        long long savet = t;
        while(savet != s){
            long long v = parent[savet];
            rgraph[v][savet] -= min_edge;
            rgraph[savet][v] += min_edge;
            savet = v;
        }
    }
    return max_flow;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    long long n, m, a, b, v;
    cin >> n >> m;
    vector<vector<long long>> graph(n, vector<long long>(n));
    for(long long i = 0; i < m; ++i){
        cin >> a >> b >> v;
        addtoGraph(graph, a-1, b-1, v);
    }
    long long res = FFFunction(graph, 0, n-1);
    cout << res;
    return 0;
}