class Solution {
public:
    bool wordPattern(string pattern, string s) {
        unordered_map<char, string> map1;
        unordered_map<string, char> map2;

        stringstream ss(s);
        string word;

        int i = 0;

        while(ss >> word) {

            if(i >= pattern.size())
                return false;

            char ch = pattern[i];

            if(map1.count(ch) && map1[ch] != word)
                return false;

            if(map2.count(word) && map2[word] != ch)
                return false;

            map1[ch] = word;
            map2[word] = ch;

            i++;
        }

        return i == pattern.size();
    }
};