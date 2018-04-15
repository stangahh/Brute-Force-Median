#include <iostream>
#include <algorithm>
#include <fstream>
#include <chrono>

//In Code::Blocks, you must enable 'Have g++ follow the C++11 ISO C++ language standard', in Settings > Compiler.
using namespace std;

vector<int> generateArray(int length, int max) {
    //init array
    std::vector<int> arr(length);

    //clear after each generation
    arr.clear();

    //generate array
    for (int i =0; i < length; i++) {
        int a = rand() % max + 1;
        arr.push_back(a);
    }

    return arr;
}

int main() {
    //CONFIG
    int PERMUTATIONS = 200; //Unique permutations of randomly filled arrays.
    int GROWTH = 25; //How many times the INCREMENT_AMOUNT will be added together to form new lengths of arrays
    int LENGTH = 1000; //Vector length, as well as degree that array length will grow with GROWTH
    long VALUE_MAX = 2147483647; //Array values will generate from 1 to VALUE_MAX

    //Prepare CSV
    ofstream myfile;
    myfile.open ("elapsedTime.csv");
    myfile << "Length (n)" << "," << "Time Taken (ms)" << endl;

    //set seed
    srand(time(NULL));

    //Length
    for (int i=1; i<=GROWTH; i++) {
        int length = i * LENGTH;
        int k = ceil(length/2.0);
        vector<int> a = generateArray(length, VALUE_MAX);
        cout << endl << length << endl;
        //Permutations
        for (int j=1; j<=PERMUTATIONS; j++) {
            //shuffle array
            std::random_shuffle(a.begin(), a.end());
            cout << "," << j;

            int median = 0;

            //start timer
            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

            //start BruteForceMedian
            for (int l=0; l<=(length-1); l++) {
                int numSmaller = 0;
                int numEqual = 0;

                for (int m=0; m<=(length-1); m++) {
                    if (a[m] < a[l]) {
                        numSmaller =  numSmaller + 1;
                    } else if (a[m] == a[l]) {
                        numEqual = numEqual + 1;
                    }
                }

                if ((numSmaller < k) && (k <= (numSmaller + numEqual))) {
                    median = a[l];
                    goto stop;w
                }
            }

            stop:
            //stop timer
            std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
            int elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

            //output line to CSV
            myfile << length << "," << elapsed << endl;

        }
    }
    cout << "Successfully exported to output.csv" << endl;
    myfile.close();
    return 0;
}
