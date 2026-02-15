#include<bits/stdc++.h>
using namespace std;

struct Fenwick{
    vector<int> tree;
    Fenwick(int n): tree(n+1, 0){}
    void update(int i, int val){
        for (; i < tree.size(); i += i & -i) tree[i] ^= val;
    }
    void rangeUpdate(int l, int r, int val){
        update(l, val);
        update(r+1, val);
    }
    int query(int i){
        int res = 0;
        for (; i > 0; i -= i & -i){
            res ^= tree[i];
        }
        return res;
    }
};

class Solution {
    vector<vector<int>> adj;
    vector<int> in, out, depth;
    vector<vector<int>> up;
    int timer, lim;
    void dfs(int u, int p, int d){
        in[u] = ++timer;
        depth[u] = d;
        up[u][0] = p;
        for (int i = 1; i < lim; i++){
            up[u][i] = up[up[u][i-1]][i-1];
        }
        for (auto& nbr: adj[u]){
            if (nbr == p) continue;
            dfs(nbr, u, d+1);
        }
        out[u] = timer;
    }
    int get_lca(int u, int v){
        if(depth[u] < depth[v]) swap(u, v);
        for (int i = lim; i >= 0; i--){
            if (depth[u] - (1 << i) >= depth[v]) u = up[u][i];
        }
        if (u == v) return u;
        for (int i = lim; i >= 0; i--){
            if (up[u][i] != up[v][i]){
                u = up[u][i];
                v = up[v][i];
            }
        }
        return up[u][0];
    }
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges, string s, vector<string>& queries) {
        adj.assign(n, {});
        for (auto& ed: edges){
            adj[ed[0]].push_back(ed[1]);
            adj[ed[1]].push_back(ed[0]);
        }
        timer = 0;
        lim = 18;
        in.resize(n);
        out.resize(n);
        depth.resize(n);
        up.assign(n, vector<int>(lim + 1));
        dfs(0, 0, 0);
        Fenwick ft(n);
        vector<int> curr(n);
        for (int i{}; i < n; i++){
            int msk = 1 << (s[i] - 'a');
            curr[i] = msk;
            ft.rangeUpdate(in[i], out[i], msk);
        }
        vector<bool> results;
        for (const string& q: queries){
            stringstream ss(q);
            string type; ss >> type;
            if (type == "update"){
                int u; 
                char c;
                ss >> u >> c;
                int new_msk = 1 << (c - 'a');
                int del = curr[u] ^ new_msk;
                ft.rangeUpdate(in[u], out[u], del);
                curr[u] = new_msk;
            }
            else{
                int u, v;
                ss >> u >> v;
                int lca = get_lca(u, v);
                int xr = (ft.query(in[u])) ^ (ft.query(in[v])) ^ curr[lca];
                results.push_back((xr & (xr - 1)) == 0);
            }
        }
        return results;
    }
};