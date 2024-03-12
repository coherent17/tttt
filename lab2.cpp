#include <bits/stdc++.h>
using namespace std;

// global variables
double R_lowerBound, R_upperBound;

void calSoftBlock(int area, vector<vector<pair<int,int>>> &results){
    // find all integer factor pairs of area
    vector<pair<int,int>> factorPairs; // {width,height}
    for(int i = 1; i <= area; i++){
        // if i is an integer factor of area,
        // also current width/height is inside the range of bounding ratio,
        // store such pair into the vector
        double curRatio = (double)i*i/area;
        if(area % i == 0 && curRatio >= R_lowerBound && curRatio <= R_upperBound){ 
            factorPairs.push_back({i,area/i});
        }
    }
    results.push_back(factorPairs);
}

void calHardBlock(int width, int height, vector<vector<pair<int,int>>> &results){
    if(width == height){
        results.push_back({{width,height}});
        return;
    }

    if(width > height){
        results.push_back({{height,width},{width,height}});
        return;
    }

    results.push_back({{width,height},{height,width}});
    return;
}

int main(int argc, char* argv[]){
    // *********************************
    // *        Read Input File        *
    // *********************************
    ifstream input(argv[1]);
    input >> R_lowerBound >> R_upperBound;
    input.ignore(2,'\n');

    string curLine;
    stringstream ss;
    vector<vector<string>> blockInfs; // blockInfs[i][0]: input width of ith block
                                      // blockInfs[i][1]: input height of ith block
                                      // blockInfs[i][2](may not exist): S
    while(getline(input,curLine)){
        // clean up ss
        ss.str("");
        ss.clear();

        // read blocks inf
        ss << curLine;
        string tmpString;
        ss >> tmpString;
        int blockID = stoi(tmpString.erase(0,1));
        if(blockID > (int)blockInfs.size()) blockInfs.resize(blockID);
        while(ss >> tmpString){
            blockInfs[blockID-1].push_back(tmpString);
        }
    }
    input.close();

    // *********************************
    // *          Calculation          *
    // *********************************
    vector<vector<pair<int,int>>> results;
    for(vector<string> blockInf:blockInfs){
        if(blockInf.size() == 3){ // current block is a soft block
            calSoftBlock(stoi(blockInf[0])*stoi(blockInf[1]), results);
            continue;
        }
        // current block is a hard block
        calHardBlock(stoi(blockInf[0]), stoi(blockInf[1]), results);
    }

    // *********************************
    // *       Write Output File       *
    // *********************************
    ofstream output(argv[2]);
    int len = results.size();
    for(int i = 0; i < len; i++){
        output << 'b' << i+1 << ' ';
        for(pair<int,int> whPair:results[i]){
            output << '{' << whPair.first << ',' << whPair.second << "} ";
        }
        output << '\n';
    }
    output.close();

    return 0;
}