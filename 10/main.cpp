#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include "../lib/inputParse.hpp"
#include <list>


int solve(std::vector<std::vector<int>> &grid, std::vector<std::pair<int, int>> &found9s, int r, int c, int currentTarget){
    int ans = 0;
    std::cout<<r<<", "<<c<< ", "<<currentTarget<<'\n';
    if(currentTarget != grid[r][c]) return 0;

    if(currentTarget == 9){
        for(auto nine: found9s){
            if(nine.first == r && nine.second == c){
                return 0;
            }
        }
        std::cout<<"gotone\n";

        found9s.push_back({r, c});
        return 1;
    }

    //left
    if(c > 0){
        ans += solve(grid, found9s, r, c - 1, currentTarget + 1);
    }
    //right
    if(c < grid[0].size() - 1){
        ans += solve(grid, found9s, r, c + 1, currentTarget + 1);
    }
    if(r > 0){
        ans += solve(grid, found9s, r - 1, c, currentTarget + 1);
    }

    if(r < grid.size() - 1){
        ans += solve(grid, found9s, r + 1, c, currentTarget + 1);
    }

    return ans;
}   

int solvetwo(std::vector<std::vector<int>> &grid, int r, int c, int currentTarget){
    int ans = 0;
    std::cout<<r<<", "<<c<< ", "<<currentTarget<<'\n';
    if(currentTarget != grid[r][c]) return 0;

    if(currentTarget == 9){
        std::cout<<"gotone\n";

        return 1;
    }

    //left
    if(c > 0){
        ans += solvetwo(grid, r, c - 1, currentTarget + 1);
    }
    //right
    if(c < grid[0].size() - 1){
        ans += solvetwo(grid, r, c + 1, currentTarget + 1);
    }
    if(r > 0){
        ans += solvetwo(grid, r - 1, c, currentTarget + 1);
    }

    if(r < grid.size() - 1){
        ans += solvetwo(grid, r + 1, c, currentTarget + 1);
    }

    return ans;
}   


int main(){

    std::string str = read_file("./input.txt");
    std::vector<std::string> vecs = split(str, '\n');
    std::vector<std::vector<char>>  charVecs;
    for(auto s : vecs){
        charVecs.push_back(split(s));
    }
    std::vector<std::vector<int>>  grid;
    for(auto s: charVecs){
        grid.push_back({});
        for(char c: s){
            grid.back().push_back(c - '0');
        }
    }

    int ans = 0;
    for(int r = 0; r <grid.size(); r ++){
        for(int c = 0; c<grid.size(); c++){
            std::vector<std::pair<int, int>> found9s;
            ans += solve(grid, found9s, r, c, 0);
        }
    }


    std::cout<<ans;


    ans = 0;
    for(int r = 0; r <grid.size(); r ++){
        for(int c = 0; c<grid.size(); c++){
            std::vector<std::pair<int, int>> found9s;
            ans += solvetwo(grid, r, c, 0);
        }
    }

    std::cout<<ans;


    return ans;
}