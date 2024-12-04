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

bool search(std::vector<std::string> &grid, int startIndex[2], std::string &string, std::vector<int> &direction)
{
    int strIndex = 0;
    int row = startIndex[0];
    int col = startIndex[1];
    while(grid[row][col] == string[strIndex]){

        if(strIndex == string.length() - 1)
        {
            return true;
        }

        row += direction[0];
        col += direction[1];

        if(row >= grid.size()  || row < 0)
        {
            return false;
        }

        if(col >= grid[row].length() || col < 0)
        {
            return false;
        }

        strIndex++;
    }

    return false;
}

int solve(std::vector<std::string> &grid, std::string &searchStr)
{
    int count = 0;
    std::vector<std::vector<int>> directions;
    std::vector<int> direction;
    direction.push_back(0); direction.push_back(0);
    for(int i = -1; i < 2; i+=1)
    {
        for(int j = -1; j < 2; j+=1){
            if(i == 0 && j ==0){
                continue;
            }
            direction[0] = i;
            direction[1] = j;
            directions.push_back(direction);
        }
    }

    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j< grid[i].length(); j++){
            int strIndex = 0;
            if(grid[i][j] == searchStr[strIndex])
            {
                strIndex++;
            }

            for(auto dir : directions){
                int startIndex[2] = {i, j};
                if(search(grid, startIndex, searchStr, dir))
                {
                    count++;
                }
            }
        }
    }
    return count;
}

int solve2(std::vector<std::string> &grid, std::string &searchStr)
{
    int count = 0;
    std::vector<std::vector<int>> directions;
    std::vector<int> direction;
    direction.push_back(0); direction.push_back(0);
    for(int i = -1; i < 2; i+=1)
    {
        for(int j = -1; j < 2; j+=1){
            if(i == 0 || j ==0){
                continue;
            }
            direction[0] = i;
            direction[1] = j;
            directions.push_back(direction);
        }
    }
    std::vector<std::vector<int>> centres;
    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j< grid[i].length(); j++){
            int strIndex = 0;
            if(grid[i][j] == searchStr[strIndex])
            {
                strIndex++;
            }

            for(auto dir : directions){
                int startIndex[2] = {i, j};
                if(search(grid, startIndex, searchStr, dir)){
                    std::vector<int> foundCentre; 
                    foundCentre.push_back(startIndex[0] + dir[0]);
                    foundCentre.push_back(startIndex[1] + dir[1]);
                    bool notFound = true;
                    for(auto centre : centres){
                        if(centre == foundCentre){
                            count++;
                            notFound = false;
                        } 
                    }
                    if(notFound){
                        centres.push_back(foundCentre);
                    }
                }
            }
        }
    }
    return count;
}



std::vector<std::string> parse_input(std::string &input) {
    std::vector<std::string> parsed;
    int j = 0;
    for(int i = 0; i< input.length(); i++){
        if(input[i] == '\n') {
            parsed.push_back(input.substr(j, i-j + 1));
            j = i + 1;
        } 
    }
    return parsed;
}

int main()
{
    std::string str = read_file("./input.txt");
    std::vector<std::string> grid = parse_input(str);
    std::string searchStr = "XMAS";
    std::cout<<solve(grid, searchStr)<<std::endl;
     searchStr = "MAS";
    std::cout<<solve2(grid, searchStr);


}
