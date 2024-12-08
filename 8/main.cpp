#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include "../lib/inputParse.hpp"

struct loc_t{int r;int c;};

bool operator==(const loc_t &a, const loc_t &b)
{
    return ((a.r == b.r) && (a.c == b.c));
}

bool operator<(const loc_t &a, const loc_t &b)
{
    if(a.r == b.r) {
        return a.c < b.c;
    } else {
        return a.r < b.r;
    }
}

loc_t operator-(const loc_t &a, const loc_t &b)
{
    return {.r = a.r - b.r, .c = a.c - b.c };
}

loc_t operator+(const loc_t &a, const loc_t &b)
{
    return {.r = a.r + b.r, .c = a.c + b.c };
}

bool bounds_check(const struct loc_t &loc, const struct loc_t &locM){
    if(loc.r < 0 || loc.r > locM.r || loc.c < 0 || loc.c > locM.c){
        return false;
    } else{
        return true;
    }
}

std::vector<loc_t> get_node_locs(const struct loc_t &loc1, const struct loc_t &loc2, const loc_t locM){
    struct loc_t newloc;
    struct loc_t dif;
    std::vector<loc_t> newLocs;
    dif = loc2 - loc1;
    newloc = loc2;
    while(bounds_check(newloc, locM)){
        newLocs.push_back(newloc);
        newloc = newloc + dif;
        }
    newloc = loc1;
    while(bounds_check(newloc, locM)){
        newLocs.push_back(newloc);
        newloc = newloc - dif;
        }
        
    return newLocs;
}

void get_ants_locs(const std::vector<loc_t> ants, std::set<loc_t> &nodes, loc_t &locM){
    for(int i = 0; i < ants.size() - 1; i++){
        for(int j = i + 1; j < ants.size(); j++){
            for(auto node: get_node_locs(ants[i], ants[j], locM))
            {
                nodes.insert(node);
            }
        }
    }
}

int main()
{
    std::string str = read_file("./input.txt");
    std::vector<std::string> vecs = split(str, '\n');

    std::map<char, std::vector<struct loc_t>> ants;
    for(int i = 0; i < vecs.size(); i++){
        for(int j = 0; j < vecs[0].length(); j++){
            ants[vecs[i][j]].push_back({.r  = i, .c = j});
        }
    }

    std::set<loc_t> nodes;
    loc_t locM = {.r = vecs.size() - 1, .c = vecs[0].length()-1};
    for(auto antT : ants){
        if(antT.first == '.') continue;
        get_ants_locs(antT.second, nodes, locM);
    }

    std::cout<<nodes.size()<<std::endl;
    return nodes.size();

}
