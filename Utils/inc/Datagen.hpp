// Implement data generator
// Brief Requirements :
// Generate random data of type reqeusted
// support generation with no duplicates
// support to fill in provided container, start with vector
// support to write to file

#include <vector>
#include <string>
#include <random>

namespace std {
    class Datagen {
        public:
            Datagen(const int min,
                    const int max) :
                    m_min{min},
                    m_max{max}
            {
                // Generator
                Initialize();
            };        
            Datagen(vector<int> &out,
                    const int min,
                    const int max,
                    const bool nodup) :
                    m_min{min},
                    m_max{max},
                    m_nodup {nodup}
            {
                // with container
                Initialize();
            };

            Datagen(const string &path,
                    const int min,
                    const int max,
                    const bool nodup) :
                    m_min{min},
                    m_max{max},
                    m_nodup {nodup}                    
            {
                // with filepath
                Initialize();
            }

            ~Datagen(){}

            bool writeData() {
                // write to provided path
                cout << "writeData() method not implemented yet!!" << endl;
                return false;
            }

            // could be duplicate
            int getRandom() {
                return(did(dre));
            }

        private:

            void Initialize() {
                // generate random numbers from 0 to maxRange
                random_device rd;
                dre = default_random_engine(rd());
                did = uniform_int_distribution(m_min, m_max);
            };

            int m_min {-1};
            int m_max {-1};
            bool m_nodup {false};

            // random engine
            default_random_engine dre;
            uniform_int_distribution<int> did;
    };
}