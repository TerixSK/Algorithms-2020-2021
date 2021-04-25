#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define ll long long
static ll INF = 100000000000;

vector<ll> findLIS(vector<ll> a)
{
    vector<ll> d(a.size() + 1, INF);
    vector<ll> pos(a.size() + 1);
    vector<ll> prev(a.size());
    ll l = 0;
    pos[0] = prev[0] = -1;
    d[0] = -INF;

    for (auto i = 0; i < a.size(); ++i)
    {
        ll j = upper_bound (d.begin(), d.end(), a[i]) - d.begin();
        if (d[j - 1] < a[i] && a[i] < d[j])
        {
            d[j] = a[i];
            pos[j] = i;
            prev[i] = pos[j - 1];
            l = max(l, j);
        }
    }
    vector<ll> ans;
    ll p = pos[l];
    while (p != -1)
    {
        ans.emplace_back(a[p]);
        p = prev[p];
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int main()
{
    ll n;
    cin >> n;
    vector<ll> arr(n);
    for (auto i = 0; i < n; ++i)
        cin >> arr[i];
    vector<ll> ans = findLIS(arr);

    cout << ans.size() << endl;
    for (auto const &i : ans)
        cout << i << ' ';
    return 0;
}