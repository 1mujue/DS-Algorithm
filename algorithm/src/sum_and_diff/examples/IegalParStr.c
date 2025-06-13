// Problem: Given a string 's' composed of '(' and ')', and a string 'locked' composed 
// of '0' and '1', if 'locked[i] == 1', then 's[i]' is locked and can't be changed, 
// otherwise, 's[i]' can be changed to '(' or ')'.
// Return whether 's' can be a legal parentheses string.
// the length of s is in [1, 10^5]


// key conclusion: if a parentheses string is legal,let '(' be 1, ')' be -1, 
// then ANY prefix SUM of the string will be large or equals to 0 !!
// this is the key point to solve ALL the problems related to parentheses string.
int canBeValid(char* s, char* locked) {
    int slen = strlen(s);
    // if locked[i] is '0', we can change s[i] to '?' to represent that s[i]
    // can be '(' or ')'.
    for(int i = 0; i < slen; i++){
        if(locked[i] == '0'){
            s[i] = '?';
        }
    }

    // since '?' can be '(' or ')', the prefix sum would be bigger( '?' is '(' ) or smaller, 
    // ( '?' is ')' )  so the smaller result would be left, bigger result would be right.

    // attention: the POSSIBLE prefix sum would be CONTINUOUS with 2 as the diff. For example,
    // the prefix sum can be [1, 3, 5, 7], it can also be [0, 2, 4], BUT it can't be 
    // [1, 5, 7], [0, 3, 5] etc.
    // The reason is, each time we meet '(' or ')', the prefix sum would either plus 1 or minus 1
    // SIMUTANEOUSLY.  Only if we meet '?', the prefix sum can be DIVERGENT: you can plus 1 or minus 1,
    // so the diff is 2.

    int left = 0, right = 0;
    for(int i = 0; i < slen; i++){
        // if we meet '(', then the prefix sum would plus 1.
        if(s[i] == '('){
            left++;
            right++;
        }
        // if we meet ')', then the prefix sum would minus 1.
        else if(s[i] == ')'){
            left--;
            right--;
            if(right < 0) return 0;
            left = abs(left);
        }
        else if(s[i] == '?'){
            // if s[i] be '(', then the prefix sum would plus 1.
            right++;
            // if s[i] be ')', then the prefix sum would minus 1.
            left--;
            left = abs(left);
        }
    }
    return left == 0;
}