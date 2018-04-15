#include <iostream>
#include <algorithm>
#include <fstream>
#include <chrono>

//In Code::Blocks, you must enable 'Have g++ follow the C++11 ISO C++ language standard', in Settings > Compiler.
using namespace std;

long long int basicOperationCounter = 0;

int bruteForceMedian(vector<int> a, int length, int k) {
    for (int i=0; i<=(length-1); i++) {
        int numSmaller = 0;
        int numEqual = 0;

        for (int j=0; j<=(length-1); j++) {
            //comment the line below to test execution time
            basicOperationCounter = basicOperationCounter + 1;

            if (a[j] < a[i]) {
                numSmaller =  numSmaller + 1;
            } else if (a[j] == a[i]) {
                numEqual = numEqual + 1;
            }
        }

        if ((numSmaller < k) && (k <= (numSmaller + numEqual))) {
            return a[i];
        }
    }
}

void printArray(std::vector<int> arr, int length, int median) {
    for (int i=0; i < length; i++) {
        cout << arr[i] << ", ";
    }
    cout << endl << "This array's Median is: " << median << endl << endl;
}

void testImplementationValidity() {
    cout << "Running Tests" << endl << endl;
    int length = 10;
    int medianLoc = ceil(length/2.0);

    vector<int> a = { 2, 4, 6, 8, 10, 12, 14, 16, 18, 20 };
    vector<int> b = { 4, 2, 6, 10, 8, 12, 16, 14, 20, 18 };
    vector<int> c = { 20, 18, 16, 14, 12, 10, 8, 6, 4, 2 };
    vector<int> d = { 12, 19, 13, 10, 12, 5, 19, 6, 4, 8 };
    vector<int> e = { 6, 6, 6, 6, 8, 10, 10, 10, 13, 20 };
    vector<int> f = { 6, 6, 6, 6, 8, 10, 10, 10, 13 };

    cout << "Sorted" << endl;
    printArray(a, length, bruteForceMedian(a, length, medianLoc));
    cout << "Nearly Sorted" << endl;
    printArray(b, length, bruteForceMedian(b, length, medianLoc));
    cout << "Reversed" << endl;
    printArray(c, length, bruteForceMedian(c, length, medianLoc));
    cout << "Random" << endl;
    printArray(d, length, bruteForceMedian(d, length, medianLoc));
    cout << "Few Unique" << endl;
    printArray(e, length, bruteForceMedian(e, length, medianLoc));
    cout << "Odd Length" << endl;
    printArray(f, 9, bruteForceMedian(f, 9, medianLoc));
}

vector<int> generateArray(std::mt19937 mt, int length, int maxVal) {
    //init array
    std::vector<int> arr(length);
    std:uniform_int_distribution<int> dist(0, maxVal);

    //clear after each generation
    arr.clear();

    //generate array
    for (int i = 0; i < length; i++) {
        arr.push_back(dist(mt));
    }

    return arr;
}

int main() {
    //CONFIG
    int PERMUTATIONS = 1; //Unique permutations of randomly filled arrays.
    int GROWTH_RATE = 1; //How many times the INCREMENT_AMOUNT will be added together to form new lengths of arrays
    int LENGTH = 20; //Vector length, as well as degree that array length will grow with GROWTH_RATE
    int VALUE_MAX = 1000000; //Array values will generate from 1 to VALUE_MAX
    int MT_SEED = 100; //Mersenne Twister engine seed

    //Prepare CSV
    ofstream myfile;
    myfile.open ("outputMain.csv");
    myfile << "Length (n)" << "," << "Array Median" << "," << "Basic Operations" << "," << "Best Case" << "," << "Worst Case" << "," << "Time Taken (ms)" << "," << "Theoretical Average Efficiency" << endl;

    //set seed
    std::mt19937 mt(MT_SEED);

    //Comment this to skip tests
    testImplementationValidity();
    cout << endl << "****************************************" << endl;

    //Length
    for (int i=1; i<=GROWTH_RATE; i++) {
        int length = i * LENGTH;
        int k = ceil(length/2.0);

        vector<int> a = generateArray(mt, length, VALUE_MAX);

        //Print array length to see what export is up to
        cout << endl << length << endl;

        //Permutations
        for (int j=1; j<=PERMUTATIONS; j++) {
            //shuffle array using Mersenne Twister Engine
            std::shuffle(a.begin(), a.end(), mt);

            //Print permutation number to see what export is up to
            cout << j << ",";

            basicOperationCounter = 0;
            int median = 0;

            //start timer
            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

            //start BruteForceMedian
            median = bruteForceMedian(a, length, k);

            //stop timer
            std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
            int elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

            //comment this when testing very large array lengths
//            cout << endl << "Printing Random Array" << endl;
//            printArray(a, length, median);

            //output line to CSV
            int bestCase = length;
            long long int averageCase = (pow(length,2)+ length)/2;
            long long int worstCase = ceil(pow(length, 2));
            myfile << length << "," << median  << "," << basicOperationCounter << "," << bestCase << "," << worstCase << "," << elapsed << "," << averageCase << endl;
        }
    }

    cout << endl << "Successfully exported to output.csv" << endl;
    myfile.close();
    return 0;
}
