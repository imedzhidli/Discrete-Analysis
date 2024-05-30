#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    string T, P;
    cin >> T;
    int k = 0, ssize = T.length();
    vector <int> suff(ssize);
    iota(suff.begin(), suff.end(), 0);
    sort(suff.begin(), suff.end(),
              [&T, &ssize](int i, int j) {
                  return T.compare(i, ssize - i, T, j, ssize - j) < 0;
              });
    while(cin >> P){
        ++k;
        int size = P.length();int l = 0, r = ssize-1, mid = (r + l) / 2, up = 0, down = 0;
        vector <int> res;
        while((r - l +1) > 0){
            string subik = T.substr(suff[mid]);
            if(P[0] == subik[0]){
                if(P == T.substr(suff[mid], size)) res.push_back(suff[mid]+1); 
                
                up = mid - 1, down = mid + 1;
                if(up!=-1){
                    string subikup = T.substr(suff[up]);
                while(P[0] == subikup[0]){
                    if(P == T.substr(suff[up], size)) res.push_back(suff[up]+1);
                    --up;
                    if(up == -1) break;
                    }
                }
                if (down != ssize){
                    string subikdown = T.substr(suff[down]);
                while(P[0] == subikdown[0]){
                    if(P == T.substr(suff[down], size)) res.push_back(suff[down]+1);
                    ++down;
                    if(down == ssize) break;
                    }
                }
                int ressize = res.size();
                if(ressize == 0) break;
                sort(res.begin(), res.end());
                cout << k << ": ";
                for(int lk = 0; lk < ressize; ++lk){
                    if(lk == ressize - 1){
                        cout << res[lk] << "\n";
                        break;
                    }
                    cout << res[lk] << ", ";
                }
                break;
            }

            else if(P[0] < subik[0]) r = mid - 1;
            
            else if(P[0] > subik[0]) l = mid + 1;
                
            mid = (r + l) / 2;
        }
    }
    
    return 0;
}