// print general container
// print vector
#define PRINTVEC(vec) {\
    for(auto i = vec.begin(); i != vec.end(); i++)\
        cout << *i << ",";\
    cout << endl;\
}

// TODO Fix with variadic macro
#define PRINT1PARAM(a) {cout << a << endl;}

#define PRINT2PARAMS(a, b) {cout << a << "," << b << endl;}

#define PRINT3PARAMS(a, b, c) {cout << a << "," << b << "," << c << endl;}
