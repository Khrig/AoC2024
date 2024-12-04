#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

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

int get_num(std::string &in, int numStart) {
    while( std::isdigit(in[numStart]))
    {
        if(numStart == (in.size() - 1))
        {
            return numStart;
        }

        numStart++;
    }
    numStart--;
    return numStart;

}

int solve(std::string &in)
{

    std::string searchStr = "mul(";
    int pos = 0;
    int foundPos = 0;
    bool notDone = true;
    int mul = 0;
    bool isDo = true;
    int dontLoc = -1;
    while(notDone)
    {

        if(pos >= in.length()){
            notDone = false;
            break;
        }

        if(isDo){
            searchStr = "don't()";
        } else {
            searchStr = "do()";
        }
        int lenDoSearchStr = searchStr.length();

        std::size_t dontFound = in.find(searchStr, pos);
        if(dontFound != std::string::npos) {
            dontLoc = dontFound;
        } else {
            dontLoc = -1;
        }

        if(!isDo)
        {
            pos = dontLoc + lenDoSearchStr;
        }

        searchStr = "mul(";
        std::size_t found = in.find(searchStr, pos);
        if(found != std::string::npos) {
            foundPos = found;
        } else {
            return mul;
        }

        if(dontLoc < foundPos && dontLoc != -1) {
            isDo = !isDo;
            pos = dontLoc + lenDoSearchStr;
            continue;
        } else {
            pos = foundPos + searchStr.length();

            if(pos >= in.length()){
                notDone = false;
                break;
            }

            if(isDo){
                if(isdigit(in[pos])) {
                    int endDigit = get_num(in, pos);
                    int otherEndDigit = endDigit;
                    if(endDigit >= in.length() - 3 || in[endDigit+1] != ',')
                    {
                        continue;
                    } 
                    if(isdigit(in[endDigit + 2])) {
                        otherEndDigit = get_num(in, endDigit + 2);
                        if(otherEndDigit == in.length() - 1 || in[otherEndDigit + 1] != ')') {
                            continue;
                        }
                    }
                    std::string num1 = in.substr(pos, endDigit - pos + 1);
                    std::string num2 = in.substr(endDigit + 2, otherEndDigit - (endDigit + 2)+ 1);
                    mul += std::stoi(num1) * std::stoi(num2);
                }
            } else {

            }
        }
    } 
}


int main()
{
    std::string str = read_file("./input.txt");

    std::cout<<solve(str);


}
