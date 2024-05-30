#include <iostream>
#include <vector>

using namespace std;

int main()
{   ios::sync_with_stdio(false); cin.tie(0);
    int n, m, c, M;
    unsigned long long value = 0;
    int maxf, maxs, maxth;
    cin >> n >> M;
    vector <pair <int, int>> arr(n+1);
    for(int i = 1; i <= n; ++i){
        cin >> m >> c;
        arr[i] = make_pair(m, c);
    }
    vector<vector<vector<unsigned long long>>> dp(n+1, vector<vector<unsigned long long>>(M+1, vector<unsigned long long>(n+1)));
    vector<vector<vector<pair<int, int>>>> path(n+1, vector<vector<pair<int, int>>>(M+1, vector<pair<int, int>>(n+1)));
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= M; ++j){
            for(int k = 1; k <= i; ++k){
            if(j < arr[i].first){
                dp[i][j][k] = dp[i-1][j][k];
                path[i][j][k] = {i-1, j};
            }
            else{
                if((k == 1 ) || (dp[i-1][j-arr[i].first][k-1] == 0)){
                if(dp[i-1][j][k] > arr[i].second){
                    dp[i][j][k] = dp[i-1][j][k];
                    path[i][j][k] = {i-1, j};
                }
                else{
                    if(dp[i][j][1] < arr[i].second){
                    dp[i][j][1] = arr[i].second;
                    path[i][j][1] = {i-1, j-arr[i].first};
                    }
                }
                }
                else if(dp[i-1][j][k] > (dp[i-1][j-arr[i].first][k-1] / (k-1)  + arr[i].second) * k){
                    dp[i][j][k] = dp[i-1][j][k];
                    path[i][j][k] = {i-1, j};
                    }
                else{
                    dp[i][j][k] = (dp[i-1][j-arr[i].first][k-1] / (k-1)  + arr[i].second) * k;
                    path[i][j][k] = {i-1, j-arr[i].first};
                    }
                }
            }
            }
    }
    

    for(int i = n; i <= n; ++i){
        for(int j = 1; j <= M; ++j){
            for (int k = 1; k <= n; ++k){
                if(value < dp[i][j][k]){
                    value = dp[i][j][k];

                    maxf = i; maxs = j; maxth = k;
                }
            }
        }
    }


    int i = maxf, j = maxs, k = maxth;
    vector<int> res;
    while((i > 0 && j > 0 && k > 0) && (dp[i][j][k] != 0)){
        if(path[i][j][k].second == j){
            --i;
        }
        else{
        res.push_back(i);
        int ii = i;
        i = path[i][j][k].first;
        j = path[ii][j][k].second;
        k-=1;
        }
    }
    
    cout << value << "\n";
    
    for(int i = res.size() - 1; i >= 0; --i){
        if(i == 0) {cout << res[i]; break;}
        cout << res[i] << " ";
    }
    
    return 0;
}