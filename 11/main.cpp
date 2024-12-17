#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include "../lib/inputParse.hpp"
#include <list>

long int solve(long int stoneNum, std::unordered_map<long int, std::unordered_map<int, long int>> &dp, int depth, const int &maxDepth){
    
    long int ans = 0;

    if(dp.count(stoneNum)){
        if(dp[stoneNum].count(depth)){
            return dp[stoneNum][depth];
        }
    }

    if(depth == maxDepth){
        return 1;
    }

    if(stoneNum == 0){
        ans += solve(1, dp, depth + 1, maxDepth);
    } else{
        std::string sStone = std::to_string(stoneNum);
        if(sStone.length() % 2 == 0){
            int middle = sStone.length() / 2;
            long int ans1 = stol(sStone.substr(middle, middle));
            long int ans2 = stol(sStone.substr(0, middle));
            ans += solve(ans1, dp, depth + 1, maxDepth);
            ans += solve(ans2, dp, depth + 1, maxDepth);
        } else{
            ans += solve(2024 * stoneNum, dp, depth + 1, maxDepth);
        }
    }

    dp[stoneNum][depth] = ans;

    return ans;

}

int main(){

    std::string str = read_file("./input.txt");
    std::vector<std::string> vecs = split(str, ' ');
    std::vector<int>  ints;
    std::unordered_map<long int, std::unordered_map<int, long int>> dp; 

    for(auto s : vecs){
        ints.push_back(stoi(s));
    }

    long int ans = 0;
    const int depth = 75;
    for(auto e : ints){
        ans += solve(e, dp, 0, depth);
    }

    std::cout<<ans<<std::endl;

    return ans;
}