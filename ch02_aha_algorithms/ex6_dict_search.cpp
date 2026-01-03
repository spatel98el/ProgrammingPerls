// Exercise 6:
// given a dictionary of names in format {sirname name} format
//  - Dictionary is text file
//  - names are in all small case, no aphanum chars
//  - max names : 10k ?
// user enters names from telephone keybord to search in format {sirname*first letter of name*}
//  - mapping of phone key pad to char set
//  - for each key, search char set in dictinary (first char) and subset (from second char onward)
//  - on reading *, drop all the names having further chars from the subset
//  - repeate same process for name string
//  - if key with unmapped cahr pressed ignore it
// return all the matches from the dictionary
//  - return set, print of the screen as a list of names

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>

#include <Misc.hpp>
#include <SimpleProfiler.hpp>

using namespace std;

map<int, vector<char>> keyMap{
    {2, {'a','b','c'}},
    {3, {'d','e','f'}},
    {4, {'g','h','i'}},
    {5, {'j','k','l'}},
    {6, {'m','n','o'}},
    {7, {'p','r','s'}},
    {8, {'t','u','v'}},
    {9, {'w','x','y'}},
};


vector<pair<string, string>> getMatchingNames(int key, int pos, vector<pair<string, string>>& dict) {
    static int parseState = 0; //0 is lname complete, 1 is fname complete
    static int posOffset = 0;
    vector<char> charSet{};

    if(key >= '0' && key <= '9'){
        charSet = keyMap[key - '0'];
    } else {
        // presuming *
        parseState = 1;
        posOffset = pos + 1; // next char is at offset 0
        // return copy
        return vector<pair<string, string>>{dict};
    }

    vector<pair<string, string>> values{};
    for(char c : charSet) {
        for(int i = 0; i < dict.size(); i++) {
            char dc = parseState ? dict[i].second[pos - posOffset] : dict[i].first[pos - posOffset]; 
            // PRINT2PARAMS(dc, c);
            if(dc == c)
                values.push_back(dict[i]);
        }
    }

    return values;
}

int main() {
    // read dictionary of names
    ifstream dictFile{"./data/name_dict.txt"};
    SimpleProfiler prof(Resolution::USEC);
    // test - check dict names
    // string name;
    // while (getline(dictFile, name)) {
    //     PRINT1PARAM(name);
    // }

    // parse and read entire dictionary in memory
    PRINT1PARAM("Dictionary parsing");
    prof.startTimeProf();
    vector<pair<string, string>> dict{};
    string name;
    while (getline(dictFile, name)) {
        // search delimater " "
        string :: size_type idx = name.find(" ");
        string lname = name.substr(0, idx);
        string fname = name.substr(idx+1);
        // PRINT2PARAMS(lname, fname);
        dict.push_back(make_pair(lname, fname));
    }

    prof.endTimeProf();
    prof.printRunningTime();

    PRINT1PARAM("Enter keys");
    string inputKeys;
    getline(cin, inputKeys);

    prof.startTimeProf();
    // PRINT2PARAMS("Key", inputKeys[0]);
    vector<pair<string, string>> filteredDict = getMatchingNames(inputKeys[0], 0, dict); // matching name indices
    // for (auto e : filteredDict)
    // {
    //     PRINT2PARAMS(e.first, e.second);
    // }
    for(int i = 1; i < inputKeys.size(); i++) {
        //validateKey(); //later
        // PRINT2PARAMS("Key", inputKeys[i]);
        filteredDict = getMatchingNames(inputKeys[i], i, filteredDict);
        // filtered names
        // for(auto e : filteredDict) {
        //     PRINT2PARAMS(e.first, e.second);
        // }
    }
    prof.endTimeProf();
    prof.printRunningTime();

    for(auto e : filteredDict) {
        PRINT2PARAMS(e.first, e.second);
    }
   
}