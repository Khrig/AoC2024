#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include "../lib/inputParse.hpp"
#include <list>

class Blob{
    public:
    int size;
    bool isSpace;
    int id;
    bool hasMoved;
    Blob(int size, bool isSpace, int id){
        this->size = size;
        this->isSpace = isSpace;
        this->id = id;
        hasMoved =false;

    }
};

std::list<Blob>::reverse_iterator move_blob(std::list<Blob> &blobs, std::list<Blob>::reverse_iterator rIter){
    for(auto iter = blobs.begin(); iter != next(rIter).base(); ++iter){
        Blob blob = *iter;
        if(blob.isSpace == false)  continue;
        if(blob.size < (*rIter).size) continue;
        auto nIter = blobs.insert(iter, Blob(*rIter));
        (*nIter).hasMoved = true;
        (*iter).size -= (*rIter).size;
        if((*iter).size == 0) blobs.erase(iter);
        (*rIter).isSpace = true;
        //demonic Iterator bullshit
        return ++rIter;
    }
    return ++rIter;

}


long int get_sha(const std::vector<int> &vec){
    long int ans=0;
    for(int i = 0; i < vec.size(); i++){
        ans +=  vec[i]*i;
    }
    return ans;
}

long int get_sha(const std::list<Blob> &blobs){
        long int ans=0;
    int idx = 0;
    std::vector<int> ansvec;
    for(auto iter = blobs.begin(); iter != blobs.end(); ++iter){
        int val;
        if((*iter).isSpace){
            val = 0;
        } else{
            val = (*iter).id;
        }
        for(int i = 0; i < (*iter).size; i++){
            ansvec.push_back(val);
        }

    }
    return get_sha(ansvec);
}


int main()
{
    std::string str = read_file("./input.txt");
    str = str.substr(0, str.length() - 1);
    bool isFile = true;
    std::vector<std::pair<int, int>> files;
    std::vector<std::pair<int, int>> spaces;
    int finalIdx = 0;
    int fileID = 0;
    std::list<Blob> blobs;

    for(int i = 0; i< str.length(); i++){
        int size = str[i] - '0';
        Blob blob(size, !isFile, fileID);
        blobs.push_back(blob);
        if(isFile){
            files.push_back({finalIdx, size});
            fileID++;
        } else {
            spaces.push_back({finalIdx, size});
        }
        finalIdx += size;
        isFile = !isFile;
    }
    // Iterate in reverse order
    std::vector<int> final;
    finalIdx = 0;
    int filesRevIdx = files.size()-1;
    int fileRevIdx = files[filesRevIdx].second - 1;
    int filesIdx = 0;
    int fileIdx = 0;

    int spacesIdx = 0;
    int spaceIdx = 0;


    while(true){

        if(finalIdx >= files[filesIdx].first)
        {
            final.push_back(filesIdx);
            fileIdx++;
            finalIdx++;

            if(fileIdx < files[filesIdx].second)
            {
            } else {
                filesIdx++;
                fileIdx = 0;
            }
        } else if(finalIdx >= spaces[spacesIdx].first){
            final.push_back(filesRevIdx);
            spaceIdx++;
            finalIdx++;
            fileRevIdx--;

            if(spaceIdx < spaces[spacesIdx].second){
            } else {
                spacesIdx++;
                spaceIdx = 0;
            }

            if(fileRevIdx >= 0){
            } else {
                filesRevIdx --;
                fileRevIdx = files[filesRevIdx].second - 1;
            }
        }

        if(filesRevIdx < filesIdx || (filesRevIdx == filesIdx && fileIdx > fileRevIdx))
        {
            break;
        }
    }


    std::cout<<get_sha(final);
    finalIdx = 0;
    auto rIter = blobs.rbegin();
    while(rIter != blobs.rend()){
        if((*rIter).isSpace == false && !((*rIter).hasMoved)){
           rIter = move_blob(blobs, rIter);
        } else {
            rIter++;
        }
    }

    long int ansFinalFinal = get_sha(blobs);

    return 0;

}
