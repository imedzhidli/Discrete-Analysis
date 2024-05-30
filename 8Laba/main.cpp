#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    long long N, p, imedy;
    cin >> N >> p >> imedy;
    long long resf[N];
    long long ress[N] ={0};
    resf[0] = 1;
    for(long long i = 1; i < N; ++i){
        resf[i] = pow(p, i);
    }
    
    long long ch = N - 1;
    long long help = imedy;
    while(imedy > 0){
        if(imedy >= resf[ch]){
            imedy %= resf[ch];
            ress[ch] = (help - imedy) / resf[ch];
            help = imedy;
        }
        else --ch;
    }
    
    for(auto &k : ress){
        cout << k << "\n";
    }
    return 0;
}