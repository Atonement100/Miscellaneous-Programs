#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;


int main() {
   
    string s;
    cin>>s;
    
    std::vector<int> chars(26);
    for (unsigned int Index = 0; Index < chars.size(); Index++){chars[Index] = 0;}
    
    int flag = 1;
    for (unsigned int Index = 0; Index < s.length(); Index++){
        chars[s[Index] - 'a']++;
    }
    bool OddFound = false;
    for (unsigned int Index = 0; Index < chars.size(); Index++){
        if(chars[Index] % 2 != 0) { 
            if (!OddFound) {
                OddFound = true; 
            }  
            else { 
                flag = 0;
                break;
            } 
        } 
    }
    
    if(flag==0)
        cout<<"NO";
    else
        cout<<"YES";
    return 0;
}
