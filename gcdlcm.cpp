#include <iostream> // optional

// necessary for better formatting
using namespace std;
typedef long long ll;

ll findgcd(ll a, ll b) {
    if (b == 0) {
        return a;
    }
    return findgcd(b, a % b);
}

ll findlcm(ll a, ll b) {
    return (a / findgcd(a, b)) * b; // do division first to avoid overflow
}

int main() {
    cin.tie(0)->sync_with_stdio(0); // recommended for faster I/O
    ll a, b;
    cin >> a >> b;
    cout << findgcd(a, b) << " " << findlcm(a, b) << "\n";
    return 0;
}