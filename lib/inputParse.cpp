
#include "inputParse.hpp"
#include <iostream>
#include <fstream>

std::string read_file(std::string path)
{
    std::ifstream f(path);

    if(!f.is_open()) {
        std::cerr<<"couldnt open file";
    }

    std::string fContent;
    std::string line;
    while (std::getline(f, line)) {
        fContent.append(line);
        fContent.append("\n");
        std::cout << line << std::endl;
    }
    // Close the file
    f.close();
    return fContent;
}

std::vector<std::string> split(std::string s, std::string sf){
    int i = 0;
    std::vector<std::string> out;
    while(i < s.length()){
        size_t found = s.find(sf, i);
        if(found == std::string::npos) break;
        if(found - i > 0) out.push_back(s.substr(i, found - i));
        i = found + sf.length();
    }

    if(i < s.length())
    {
        out.push_back(s.substr(i, s.length() - i));
    }    
    
    return out;
}
std::vector<std::string> split(std::string s, char sf){
    int i = 0;
    std::vector<std::string> out;
    while(i < s.length()){
        size_t found = s.find(sf, i);
        if(found == std::string::npos) break;
        if(found - i > 0) out.push_back(s.substr(i, found - i));
        i = found + 1;
    }

    if(i < s.length())
    {
        out.push_back(s.substr(i, s.length() - i));
    }    
    
    return out;
}