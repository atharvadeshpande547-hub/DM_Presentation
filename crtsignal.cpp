#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

// Greatest common divisor (Euclid's algorithm)
ll gcdll(ll a, ll b) {
    while (b != 0) { ll r = a % b; a = b; b = r; }
    return a;
}

// Least common multiple
ll lcmll(ll a, ll b) { return a / gcdll(a, b) * b; }

// Method 1: LCM of all cycle lengths (all remainders zero)
ll methodLCM(const vector<ll>& c) {
    ll result = 1;
    for (ll x : c) result = lcmll(result, x);
    return result;
}

// Extended Euclid: returns g = gcd(a,b) and x, y with a*x + b*y = g
ll extGcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    ll x1, y1;
    ll g = extGcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// Multiplicative inverse of a modulo m (gcd(a,m) must be 1)
ll modInverse(ll a, ll m) {
    ll x, y;
    extGcd(((a % m) + m) % m, m, x, y);
    return ((x % m) + m) % m;
}

// Method 2: Chinese Remainder Theorem (moduli pairwise coprime)
// returns t in [0, M) with t = a[i] (mod m[i]); returns -1 if moduli are not coprime
ll methodCRT(const vector<ll>& a, const vector<ll>& m) {
    int n = m.size();
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (gcdll(m[i], m[j]) != 1) return -1;
    ll M = 1;
    for (ll x : m) M *= x;
    ll t = 0;
    for (int i = 0; i < n; i++) {
        ll Mi = M / m[i];
        ll yi = modInverse(Mi, m[i]);
        t = (t + (a[i] % m[i]) * Mi % M * yi) % M;
    }
    return t;
}

// Method 3: brute-force simulation, checks t = 1, 2, 3, ... minute by minute
ll methodSimulation(const vector<ll>& c) {
    for (ll t = 1; ; t++) {
        bool all = true;
        for (ll x : c) if (t % x != 0) { all = false; break; }
        if (all) return t;
    }
}

int main() {
    vector<ll> cycles = {3, 5, 7};
    ll l1 = methodLCM(cycles);
    ll l2 = methodCRT({0, 0, 0}, cycles);   // t = 0 (mod 105)
    ll l3 = methodSimulation(cycles);
    cout << "Cycles: 3 5 7" << endl;
    cout << "LCM method        : " << l1 << " minutes" << endl;
    cout << "CRT method (t mod M): " << l2 << "  (M = 105, so first positive t = M = " << l1 << ")" << endl;
    cout << "Simulation method : " << l3 << " minutes" << endl;
    cout << "Converted         : " << l1 / 60 << " h " << l1 % 60 << " min" << endl;
    cout << ((l1 == l3 && l2 == 0) ? "All methods agree." : "Mismatch detected!") << endl;
    return 0;
}
