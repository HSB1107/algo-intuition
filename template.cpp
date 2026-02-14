#include <bits/stdc++.h>
typedef long long ll;
#define ld long double
#define pb push_back
#define ppb pop_back
#define ppf pop_front
#define fi first
#define se second
#define pii pair<ll, ll>
#define piII pair<ll, pair<ll, ll>>

using namespace std;

bool is_prime(ll& n) {
    if (n == 1) {
        return false;
    }
    if (n <= 3) {
        return true;
    }
    if (n % 2 == 0 or n % 3 == 0) return false;
    for (ll i{5}; i * i <= n; i += 6) {
        if (n % i == 0 or n % (i + 2) == 0) return false;
    }
    return true;
}

map<ll, ll> func(ll n) {
    map<ll, ll> mp;
    while (n % 2 == 0) {
        n /= 2;
        mp[2]++;
    }
    for (ll i{3}; i * i <= n; i += 2) {
        if (is_prime(i)) {
            while (n % i == 0) {
                n /= i;
                mp[i]++;
            }
        }
    }
    if (n > 2) {
        mp[n]++;
    }
    return mp;
}

ll inf = (long long)2e15;

template <typename T>
T inverse(T a, T m) {
    T u = 0, v = 1;
    while (a != 0) {
        T t = m / a;
        m -= t * a;
        swap(a, m);
        u -= t * v;
        swap(u, v);
    }
    assert(m == 1);
    return u;
}

template <typename T>
class Modular {
   public:
    using Type = typename decay<decltype(T::value)>::type;

    constexpr Modular() : value() {}
    template <typename U>
    Modular(const U& x) {
        value = normalize(x);
    }

    template <typename U>
    static Type normalize(const U& x) {
        Type v;
        if (-mod() <= x && x < mod())
            v = static_cast<Type>(x);
        else
            v = static_cast<Type>(x % mod());
        if (v < 0) v += mod();
        return v;
    }

    const Type& operator()() const { return value; }
    template <typename U>
    explicit operator U() const {
        return static_cast<U>(value);
    }
    static constexpr Type mod() { return T::value; }

    Modular& operator+=(const Modular& other) {
        value += other.value;
        if (value >= mod()) value -= mod();
        return *this;
    }
    Modular& operator-=(const Modular& other) {
        value -= other.value;
        if (value < 0) value += mod();
        return *this;
    }
    template <typename U>
    Modular& operator+=(const U& other) {
        return *this += Modular(other);
    }
    template <typename U>
    Modular& operator-=(const U& other) {
        return *this -= Modular(other);
    }

    Modular& operator++() { return *this += 1; }
    Modular& operator--() { return *this -= 1; }
    Modular operator++(int) {
        Modular res(*this);
        *this += 1;
        return res;
    }
    Modular operator--(int) {
        Modular res(*this);
        *this -= 1;
        return res;
    }
    Modular operator-() const { return Modular(-value); }

    template <typename U = T>
    typename enable_if<is_same<typename Modular<U>::Type, int>::value,
                       Modular>::type&
    operator*=(const Modular& rhs) {
        value = normalize(static_cast<int64_t>(value) *
                          static_cast<int64_t>(rhs.value));
        return *this;
    }

    template <typename U = T>
    typename enable_if<is_same<typename Modular<U>::Type, int64_t>::value,
                       Modular>::type&
    operator*=(const Modular& rhs) {
        int64_t q =
            int64_t(static_cast<long double>(value) * rhs.value / mod());
        value = normalize(value * rhs.value - q * mod());
        return *this;
    }

    Modular& operator/=(const Modular& other) {
        return *this *= Modular(inverse(other.value, mod()));
    }

    friend bool operator==(const Modular& lhs, const Modular& rhs) {
        return lhs.value == rhs.value;
    }
    friend bool operator!=(const Modular& lhs, const Modular& rhs) {
        return !(lhs == rhs);
    }
    friend bool operator<(const Modular& lhs, const Modular& rhs) {
        return lhs.value < rhs.value;
    }

    friend ostream& operator<<(ostream& os, const Modular& num) {
        return os << num();
    }
    friend istream& operator>>(istream& is, Modular& num) {
        typename common_type<typename Modular<T>::Type, int64_t>::type x;
        is >> x;
        num.value = Modular<T>::normalize(x);
        return is;
    }

   private:
    Type value;
};

// Operator overloads
template <typename T>
Modular<T> operator+(Modular<T> a, const Modular<T>& b) {
    return a += b;
}
template <typename T>
Modular<T> operator-(Modular<T> a, const Modular<T>& b) {
    return a -= b;
}
template <typename T>
Modular<T> operator*(Modular<T> a, const Modular<T>& b) {
    return a *= b;
}
template <typename T>
Modular<T> operator/(Modular<T> a, const Modular<T>& b) {
    return a /= b;
}

template <typename T, typename U>
Modular<T> power(Modular<T> a, U b) {
    assert(b >= 0);
    Modular<T> res = 1;
    while (b > 0) {
        if (b & 1) res *= a;
        a *= a;
        b >>= 1;
    }
    return res;
}

constexpr int MOD = 998244353;  // 1000000007
using Mint = Modular<std::integral_constant<int, MOD>>;

void solve() {
    
}

int main() {
    // your code goes here
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout); // Optional: writes output to a file
    #endif

    ll t{1};
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}
