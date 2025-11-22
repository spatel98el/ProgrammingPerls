// Problem :
// find all the valid anagrams of given word

// Scheme:
// sort dictinary in order of signature of the word
//  create a set of signatures and associate word index
//  sort signatures
// generate signature of the word
// serach signature on the dictionary and return all respective words from index

// got text dictionary from https://github.com/dwyl/english-words/blob/master/words_alpha.txt

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

#include <Misc.hpp>
#include <SortAlgos.hpp>
#include <SimpleProfiler.hpp>

using namespace std;

// typedef map<string, vector<int>> signatureMap;
typedef map<string, vector<string>> signatureMap;

// go oveall all the words
// create signature, add to the set and add and index to pair
// if already existing signature then add index
signatureMap getDictSignatureIndexMap(ifstream& dictStream) {
    signatureMap smap{};
    if(!dictStream) {
        PRINT1PARAM("Error, File not opened!");
        return (smap);
    }

    string word{};
    SortAlgos sa;

    int index{};

    while(dictStream >> word) {
        index++;
        string sig = sa.alphabeticalSort(word);

        // check if this already exists then just add index
        if (smap.find(sig) != smap.end())
        {
            // existing key
            // smap[sig].push_back(index);
            smap[sig].push_back(word);
        }
        else
        {
            // first time
            // smap[sig] = vector<int>{index};
            smap[sig] = vector<string>{word};
        }
    }

    return smap;

}

int main() {

    ifstream dict("./data/words_alpha.txt");

    // Test
    // ifstream dict("./data/test.txt");
    // string word{};
    // dict >> word;
    // for(int i = 0; i < 10; i++, dict >> word)
    //     PRINT1PARAM(word);
    
    SimpleProfiler prof(Resolution::NSEC);
    prof.startTimeProf();
    
    signatureMap smap = getDictSignatureIndexMap(dict);
    
    prof.endTimeProf();
    PRINT1PARAM("Map construction time");
    prof.printRunningTime();

    // Test map
    // for(auto v : smap) {
    //     PRINT1PARAM(v.first);
    //     for(auto e : v.second){
    //         PRINT1PARAM(e);
    //     }
    //     cout << endl;
    // }

    // Read the input-> generate signature -> check sig in map -> pull the indexes
    while (1)
    {
        PRINT1PARAM("Enter search word, Ctrl+c to exit");
        string input;
        cin >> input;

        SortAlgos sa;
        
        // search
        prof.startTimeProf();
        auto sig = sa.alphabeticalSort(input);
        auto entry = smap.find(sig);
        prof.endTimeProf();
        PRINT1PARAM("Search time");
        prof.printRunningTime();


        if (entry != smap.end())
        {
            PRINT3PARAMS("Found entry : ", input, sig);
            for (auto idx : entry->second)
                PRINT1PARAM(idx);
        } else {
            PRINT1PARAM("Entry not found");
        }
    }
}