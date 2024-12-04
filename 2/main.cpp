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


void parse_input_str(std::string &input, std::vector<std::vector<int>> &out)
{
    out.push_back({});
    int j = 0;
    int x = 0;
    int i = 0;
    while(i < input.length()) {
        j=i;
        while(j < input.length()) {
            if(std::isspace(input[j]) || input[j] == '\n'){
                std::string num = input.substr(i,j - i);
                long int val = std::stoul(num);
                out.back().push_back(val);

                if(input[j] == '\n') {
                    out.push_back({});
                }
                break;
            }
            j++;
        }
        i = j;
        while(i<input.length() && std::isspace(input[i]))
        {
            i++;
        }
    }
}

bool is_safe(std::vector<int> &in)
{
    if(in.size() == 0) {
        return false;
    }

    int dir;

    if(in.back() == in.front()) {
        return false;
    } else if(in.front() > in.back()) {
        dir = -1;
    } else {
        dir = 1;
    }


    for(int i = 1; i<in.size(); i++) {
        bool isIncr = true;
        if(abs(in[i-1] - in[i]) > 3) {
            return false;
        }

        if(in[i-1] > in[i]) {
            isIncr = false;
        } else if(in[i-1] < in[i]) {
            isIncr = true;
        } else {
            return false;
        }

        if((dir == -1 &&  isIncr) || (dir == 1 && !isIncr)) {
            return false;
        } 

    }

    return true;
}

int solve(std::vector<std::vector< int>> &in)
{
    int count = 0;
    for(std::vector<int>rep : in) {

        if(is_safe(rep))
        {
            count++;
        } else {

            for(int i = 0; i<rep.size(); i++)
            {
                std::vector<int> repCpy;
                for(int j = 0; j<rep.size(); j++)
                {
                    if(j == i )
                    {
                        continue;
                    } else {
                        repCpy.push_back(rep[j]);
                    }

                }

                if(is_safe(repCpy))
                {
                    count++;
                    break;
                }


            }
        }
    }
    std::cout<<count;
    return count;
}


int main()
{
    std::vector<std::vector< int>> out;
    std::string str = read_file("./input.txt");
    parse_input_str(str, out);

    solve(out);


}
