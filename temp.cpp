
#include <bits/stdc++.h>

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define ll long long int

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pbds; // find_by_order, order_of_key

bool prime[10000001];
vector<ll> fact;
// ll mod = (ll)(1e9+7);
//To find prime numbers using sieve
vector<ll> sieve(){
    vector<ll> primes;
    for(ll i=0;i<1000001;i++) prime[i]=true;
    for(ll i=2;i<1000001;i++){
        if(!prime[i]) continue;
        primes.push_back(i);
        for(ll j=2;i*j<1000001;j++){
            prime[i*j]=false;
        }
    }
    return primes;
}

//To calculate (a^b)%p
ll bin_expo(ll a,ll b,ll p){
    a=a%p;
    if(a==0) return 0;
    ll res=1;
    while(b>0){
        if(b&1) res=(res*a)%p;
        a=(a*a)%p;
        b=b>>1;
    }
    return res;
}

//Using fermats little theorm here p should be prime
ll mod_inv(ll n,ll p){
    return bin_expo(n,p-2,p);
}

// To calculate gcd
ll gcd(ll a ,ll b){
    if(a==0){
        return b;
    }
    return gcd(b%a,a);
}

//To compute factorial mod p of 1 to n
void computeFact(ll n,ll p){
    fact.resize(n+1);
    fact[0]=1;
    for(ll i=1;i<=n;i++) fact[i]=(fact[i-1]*i)%p;
}

//to calculate (nCr)%p
ll ncr(ll n,ll r,ll p){
    if(n<r) return 0;
    if(r==0) return 1;
    return fact[n]*mod_inv(fact[r],p)%p*mod_inv(fact[n-r],p)%p;
}

class DisjSet {
    int *rank, *parent, n;
 
    public:
    DisjSet(int n)
    {
        rank = new int[n];
        parent = new int[n];
        this->n = n;
        makeSet();
    }
    void makeSet()
    {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    int find(int x)
    {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
 
        return parent[x];
    }
    void Union(int x, int y)
    {
        int xset = find(x);
        int yset = find(y);
        if (xset == yset)
            return;
        if (rank[xset] < rank[yset]) {
            parent[xset] = yset;
        }
        else if (rank[xset] > rank[yset]) {
            parent[yset] = xset;
        }
        else {
            parent[yset] = xset;
            rank[xset] = rank[xset] + 1;
        }
    }
};

//state
//dp[i][j] taking ith persons jth item as last item
//transition
//dp[i][j]=min(dp[i-1][j-1]+1,dp[i-1][j]+1,dp[i][j-1]+1); //replace remove insert
//base case
//dp[i][0]=i dp[0][j]=j;
//final subproblem
//dp[n][m]
int dx[4]={1,-1,0,0};
int dy[4]={0,0,-1,1};
ll mod = (ll)1e9+7;

void getZarr(vector<int> &str, vector<int> &Z)
{
    int n = str.size();
    int L, R, k;
    L = R = 0;
    for (int i = 1; i < n; ++i)
    {
        if (i > R)
        {
            L = R = i;
            while (R<n && str[R-L] == str[R])
                R++;
            Z[i] = R-L;
            R--;
        }
        else
        {
            k = i-L;
            if (Z[k] < R-i+1)
                Z[i] = Z[k];
            else
            {
                L = i;
                while (R<n && str[R-L] == str[R])
                    R++;
                Z[i] = R-L;
                R--;
            }
        }
    }
}

vector<int> search(vector<int> &text, vector<int> &pattern)
{
    vector<int> concat;
    for(auto it:pattern) concat.push_back(it);
    concat.push_back(-1);
    for(auto it:text) concat.push_back(it);
    for(auto it:text) concat.push_back(it);
    int l = concat.size();
    vector<int> Z(l,0);
    getZarr(concat, Z);
    vector<int> ans;
    for (int i = 0; i < l; ++i)
    {
        if (Z[i] == pattern.size())
            ans.push_back(i - pattern.size() -1);
    }
    return ans;
}

int main() {
    // #ifndef ONLINE_JUDGE
    //   freopen("input.txt", "r", stdin);
    //   freopen("output.txt", "w", stdout);
    // #endif // ONLINE_JUDGE
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll t=1,tc=1;
    cin>>t;
    while(t--!=0){
        // cout<<"Case #"<<tc++<<": ";
        
    }
}
