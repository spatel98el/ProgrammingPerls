// this are custom and practice sorting algos
#include <string>

#include <Misc.hpp>

namespace std {
    class SortAlgos
    {
    public:
        string alphabeticalSort(const string &s)
        {
            unsigned int freqCounter[26] = {};
            // presuming all lower case
            // o(n)
            for(auto c : s) {
                freqCounter[c-'a']++;
            }

            // now form string with it
            string ss{};
            // o(n)
            for(char i = 0; i < 26; i++) {
                // worst case - no limit
                // average case c = 10
                while(freqCounter[i]) {
                    ss += i + 'a';
                    freqCounter[i]--;
                }
            } // average case 10*o(n)
            return ss;
        } // C * o(n)
    };
}