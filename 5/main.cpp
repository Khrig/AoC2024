#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>

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


std::map<int, std::vector<int>> parse_input_rules(std::string &input) {
    std::vector<std::string> parsed;
    int j = 0;
    std::size_t found = input.find("zzzzzzzzzzzzzzzzzz");
    int end = found;

    for(int i = 0; i< end; i++){
        if(input[i] == '\n') {
            parsed.push_back(input.substr(j, i-j));
            j = i + 1;
        } 
    }

    std::map<int, std::vector<int>> rules;

    for(auto str : parsed){
        std::size_t middle = str.find('|');
        int middleInt = middle;
        int first = stoi(str.substr(0, middle));
        int second = stoi(str.substr(middle + 1, str.length() - middle));
        rules[first].push_back(second);
    }
    return rules;
}

std::vector<std::vector<int>> parse_input(std::string &input) {
    std::vector<std::vector<int>> parsed;
    int j = 0;
    std::string splitString = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz\n";
    std::size_t found = input.find(splitString);
    int start = found;
    start = start + splitString.length() + 1;
    parsed.push_back({});
    j=start;
    for(int i = start; i< input.length(); i++){
        if(input[i] == '\n') {
            parsed.back().push_back(stoi(input.substr(j, i-j)));
            if(i != input.length()-1)
            {
                parsed.push_back({});
            }
            j = i + 1;
        } 

        if(input[i] == ','){
            parsed.back().push_back(stoi(input.substr(j, i-j)));
            j = i + 1;
        }
    }

    return parsed;
}

bool check_array(std::map<int, std::vector<int>> &rules, std::vector<int> arr){
    for(int i=1; i<arr.size(); i++){
        if(rules.count(arr[i])){
            for(auto rule : rules[arr[i]]){
                for(int j = 0; j < i; j++){
                    if(arr[j] == rule)
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}



int main()
{
    std::string str = read_file("./input.txt");
    std::map<int, std::vector<int>> rules = parse_input_rules(str);
    std::vector<std::vector<int>> in = parse_input(str);
    int count = 0;
    for(auto arr : in){
        if(check_array(rules, arr)){
            count += arr[arr.size() / 2];
        }
    }


    std::cout<<count<<std::endl;
    count = 0;
    for(auto arr : in){
        bool wasFail = false;
        bool isFail = false;
        do{
            isFail = false;
            for(int i=1; i<arr.size(); i++){
                if(rules.count(arr[i])){
                    for(auto rule : rules[arr[i]]){
                        for(int j = 0; j < i; j++){
                            if(arr[j] == rule)
                            {
                                isFail = true;
                                wasFail = true;
                                int temp = arr[j];
                                arr[j] = arr[i];
                                arr[i] = temp;
                                break;
                            }
                            if(isFail) break;
                        }
                        if(isFail) break;
                    }
                }
                if(isFail) break;
            }
        } while(isFail);
        if(wasFail){
            for(auto x : arr){
                std::cout<<x<<", ";
            }
            std::cout<<std::endl;

            count += arr[arr.size() / 2];
        }
    }
    std::cout<<count;

    std::string searchStr = "XMAS";


}
