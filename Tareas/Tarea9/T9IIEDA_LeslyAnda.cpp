# include <bits/stdc++.h>

using namespace std;

unsigned long myhash(unsigned char *str) {
    unsigned long hash = 5381;
    int c;
    while (c = *str++)
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

vector<vector<int>> clusterIdenticalStrings(const vector<string> &arr) {
    vector<pair<long long, int>> hashValues(arr.size());
    for (int i = 0; i < arr.size(); i++)
        hashValues[i] = make_pair(static_cast<long long>(myhash(arr[i])), i);
    // Sort the hash values
    sort(hashValues.begin(), hashValues.end());
    vector<vector<int>> clusters;
    for (int i = 0; i < arr.size(); i++) {
        // We create a new group
        if (i == 0 || hashValues[i].first != hashValues[i-1].first)
        clusters.push_back(vector<int>());
        // We put the string index in the current group
        clusters.back().push_back(hashValues[i].second);
    }
    return clusters;
    }

int main(){
    vector<string> strarr = {"f", "fi", "fif", "fifi", "fifif", "fififi", "i", "if", "ifi", "ifif", "ififi", "f", "fi", "fif", "fifi", "i", "if", "ifi", "f", "fi", "i"};
    vector<vector<int>> clusters = clusterIdenticalStrings(strarr);

    return 0;
}