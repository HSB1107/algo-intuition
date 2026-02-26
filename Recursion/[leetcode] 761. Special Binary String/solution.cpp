#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int find_right_end(int i, string& s){
        int cnt = 1;
        for (int j = i + 1; j < s.length(); j++){
            if (s[j] == '1') cnt++;
            else cnt--;
            if (cnt < 0) return -1;
            if (cnt == 0) return j;
        }
        return -1;
    }
    string recur(int i, int j, string& s){
        if (i > j) return "";
        vector<string> parts;
        int left = i;
        while(left < j){
            int right = find_right_end(left, s);
            string child = recur(left + 1, right - 1, s);
            left = right + 1;
            parts.push_back("1" + child + "0");
        }
        sort(parts.rbegin(), parts.rend());
        string result;
        for (auto& mem: parts) result += mem;
        return result;
    }
    string makeLargestSpecial(string s) {
        int n = s.size();
        return recur(0, n-1, s);
    }
};