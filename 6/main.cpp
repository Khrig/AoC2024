#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include "../lib/inputParse.hpp"
#include <utility>

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

class guard{
    public:
    struct loc_t loc;
    struct loc_t locM;
    struct loc_t locDir;
    std::set<struct loc_t> placesBeen;
    std::set<std::pair<struct loc_t, struct loc_t>> statesBeen;
    std::vector<struct loc_t> directionsBeen;
    int numPlaces;
    bool hasBox;

    guard(std::vector<std::string> &grid, bool box)
    {
        hasBox = box;
        for(int i = 0; i < grid.size(); i++){
            size_t found = grid[i].find('^');
            if(found != std::string::npos){
                loc.r = i;
                loc.c = found;
                locDir.r = -1; //this is up
                locDir.c = 0;
                locM.r = grid.size();
                locM.c = grid[0].length();
                numPlaces = 0;
                return;
            }
        }
    }

bool check_box(std::vector<std::set<int>> &boxes, int row, int col)
{
    if(loc.r < 0 || loc.r == locM.r || loc.c < 0 || loc.c == locM.c){
        return false;
    } else {
        return boxes[row].count(col);
    }  
}

void rotate(struct loc_t &locDir){
    if(locDir.r == 1 )
    {
        locDir.c = -1;
        locDir.r = 0;
    } else if (locDir.r == -1) {
        locDir.c = 1;
        locDir.r = 0;
    } else if (locDir.c == 1) {
        locDir.c = 0;
        locDir.r = 1;
    } else {
        locDir.c = 0;
        locDir.r = -1;
    }
}

bool bounds_check(const struct loc_t &loc, const struct loc_t &locM){
    if(loc.r < 0 || loc.r == locM.r || loc.c < 0 || loc.c == locM.c){
        return false;
    } else{
        return true;
    }
}


bool move_guard(std::vector<std::set<int>> &boxes, bool &canLoop){
    //std::cout<<loc.r<<", "<<loc.c<<std::endl;
    if(!bounds_check(loc, locM)) return false;

    placesBeen.insert(loc);
    int size = statesBeen.size();
    statesBeen.insert(std::pair(loc, locDir));
    if(statesBeen.size() == size) canLoop = true;

    struct loc_t locTry = loc;
    locTry.r += locDir.r;
    locTry.c += locDir.c;
    if(bounds_check(locTry, locM)){
        if(!check_box(boxes, locTry.r, locTry.c)){            
            loc = locTry;
        } else{
            rotate(locDir);
        }
    } else {
        loc = locTry;
    }
    return true;
}

};
std::vector<std::set<int>> get_boxes(std::vector<std::string> &splitLines, char boxChar){
    std::vector<std::set<int>> boxes;
    for(auto line : splitLines){
        boxes.push_back({});
        int i = 0;
        while( true){
            size_t found = line.find(boxChar, i);
            if(found == std::string::npos){
                break;
            } else {
                boxes.back().insert(found);
                i = found + 1;
            }
        }
    }

    return boxes;
}

int main()
{
    std::string str = read_file("./input.txt");
    std::vector<std::string> splitLines = split(str, '\n');
    std::vector<std::set<int>> boxes = get_boxes(splitLines, '#');
    guard theGuard(splitLines, false);
    bool canLoop = false;
    int numPlacesCanLoop =0;
    while(theGuard.move_guard(boxes, canLoop)){
        if(canLoop){
            canLoop = false;
            numPlacesCanLoop++;
        }
    }
    std::cout<<theGuard.placesBeen.size();
    numPlacesCanLoop =0;

    for(auto place : theGuard.placesBeen){
        std::vector<std::set<int>> newBoxes = boxes;
        struct loc_t boxLoc = place;
        while(newBoxes.size() <= boxLoc.r) newBoxes.push_back({});
        newBoxes[boxLoc.r].insert(boxLoc.c);
        guard newGuard(splitLines, false);
        bool canLoop = false;
        while(newGuard.move_guard(newBoxes, canLoop)){
            if(canLoop){
                numPlacesCanLoop++;
                break;
            }
        }
    }

    std::cout<<numPlacesCanLoop;
    
    return theGuard.numPlaces;

}
