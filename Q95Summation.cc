// C++ program to demonstrate the use of nth_element 
#include <iostream> 
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <chrono>

/**
 * How to SUM the Quartile95 of a list of elements, that is, sum all elements in 
 * the list except the 5% highest values in the list. 
 * 
 * This file uses 2 different approaches: nth_element vs priority_queue
 * and compares them in terms of performance
 */

using namespace std; 
int main() 
{ 
    int n = 150;
    int numDiscardables = n * 0.05f; // number of values to discard
    vector<int> v1 (n);
    auto vBeginIt = v1.begin();
    auto vEndIt   = v1.end();
    generate(vBeginIt, vEndIt, [](){return rand()%100;}); 
    
    vector<int> v2 { v1 };
    

    // METHOD 1: nth_element
    chrono::steady_clock::time_point t0 = chrono::steady_clock::now();
    auto vIt = vEndIt - numDiscardables;  // samples that count are [vBegin, vIt]
    if (numDiscardables > 0 )
    {
        nth_element(vBeginIt, vIt, vEndIt);
    }
    int sum1 = accumulate(vBeginIt, vIt, 0);

    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
    auto elapsed1 = chrono::duration_cast<chrono::microseconds>(t1-t0).count();


    // METHOD 2: priority queue
    priority_queue<int, vector<int>, greater <int> > q;
    int sum2 = 0;
    for (auto sample: v2) {
        sum2 += sample;
        if (q.size() < numDiscardables) {
            q.push(sample);
            sum2 -= sample;
        }
        else
        {
            auto m = q.top();
            if ( m < sample) {
                sum2 = sum2 - sample + m;
                q.pop();
                q.push(sample);
            }
        }
    }
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    auto elapsed2 = chrono::duration_cast<chrono::microseconds>(t2-t1).count();
    cout << endl;
    
    cout << "sum1=" << sum1 << " calculated in " << elapsed1 <<endl;
    cout << "sum2=" << sum2 << " calculated in " << elapsed2 <<endl;
	return 0; 
} 