class Solution {
public:
    bool isPalindrome(string s) {

        int left = 0;
        int right = s.size() - 1;

        while(left < right) {

            if(!isalnum((unsigned char)s[left])) {
                left++;
                continue;
            }

            if(!isalnum((unsigned char)s[right])) {
                right--;
                continue;
            }

            if(tolower((unsigned char)s[left]) !=
               tolower((unsigned char)s[right])) {
                return false;
            }

            left++;
            right--;
        }

        return true;
    }
};