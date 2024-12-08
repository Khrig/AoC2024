#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include "../lib/inputParse.hpp"

long int solve(long int &targ, std::vector<long int> &ops, int curOp, long int curSum)
{
    long int ans = 0;
    if(curOp == ops.size()){   
        if(curSum == targ){
            return targ;
        } else {
            return 0;
        }
    } else if(curSum > targ) return 0;
    //std::cout<<targ<<", "<<curOp<<", "<<ops[curOp]<<", "<<curSum<<'\n';

    ans = solve(targ, ops, curOp + 1, curSum + ops[curOp]);

    if(ans == 0){
        ans = solve(targ, ops, curOp + 1, curSum * ops[curOp]);
    }

    if(ans == 0){
        std::string val = std::to_string(curSum);
        val.append(std::to_string(ops[curOp]));
        ans = solve(targ, ops, curOp + 1, stol(val));
    }

    return ans;
    }

int main()
{
    std::string str = read_file("./input.txt");
    std::vector<std::string> vecs = split(str, '\n');
    long long int ans = 0;
    for(auto vec : vecs){
        std::vector<std::string> vecspl = split(vec ,':');
        std::string targ = vecspl[0];
        long int intTarg = stol(targ);
        std::string ops = vecspl[1];
        std::vector<std::string> opsspl = split(ops, ' ');
        std::vector<long int> intOps;
        for(auto op : opsspl) intOps.push_back(stoi(op));
        ans += solve(intTarg, intOps, 1, intOps[0]);
    }
    std::cout<<ans;

    return ans;

}
