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
        fContent.append(" ");
        std::cout << line << std::endl;
    }
    // Close the file
    f.close();
    return fContent;
}


void parse_input_str(std::string &input, std::vector<std::vector<int>> &out)
{
    out.push_back({}); out.push_back({});

    int j = 0;
    int x = 0;
    int i = 0;
    while(i < input.length()) {
        j=i;
        while(j < input.length()) {
            if(std::isspace(input[j])){
                std::string num = input.substr(i,j - i);
                long int val = std::stoul(num);
                out[x].push_back(val);
                x = x ^ 1;
                break;
            } else {
                j++;
            }
        }
        i = j;
        while(i<input.length() && std::isspace(input[i]))
        {
            i++;
        }
    }
}


int main()
{
    std::vector<std::vector< int>> out;
    std::string str = read_file("./input.txt");
    parse_input_str(str, out);
    std::sort(out[0].begin(), out[0].end());
    std::sort(out[1].begin(), out[1].end());

    int ans = 0;
    for(int i = 0; i < out[0].size(); i++) {
        ans += abs(out[1][i] - out[0][i]);
    }


    ans = 0;
    int sim = 0;
    for(int i = 0; i < out[0].size(); i++) {
        for(int j = 0; j < out[1].size(); j++) {
            if(out[0][i] == out[1][j])
            {
                sim++;
            }
        }

        ans += out[0][i] * sim;
        sim = 0;

    } 
}
