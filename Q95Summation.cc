// C++ program to demonstrate the use of std::nth_element 
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
 * This file uses 2 different approaches: std::nth_element vs std::priority_queue
 * and compares them in terms of performance
 */

using namespace std; 
int main() 
{ 
    int n = 150;
    int numDiscardables = n * 0.05f; // number of values to discard
    std::vector<int> v1 (n);
    auto vBeginIt = v1.begin();
    auto vEndIt   = v1.end();
    std::generate(vBeginIt, vEndIt, [](){return rand()%100;}); 
    
    std::vector<int> v2 { v1 };
    

    // METHOD 1: nth_element
    std::chrono::steady_clock::time_point t0 = std::chrono::steady_clock::now();
    auto vIt = vEndIt - numDiscardables;  // samples that count are [vBegin, vIt]
    if (numDiscardables > 0 )
    {
        std::nth_element(vBeginIt, vIt, vEndIt);
    }
    int sum1 = std::accumulate(vBeginIt, vIt, 0);

    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
    auto elapsed1 = std::chrono::duration_cast<std::chrono::microseconds>(t1-t0).count();


    // METHOD 2: priority queue
    std::priority_queue<int, vector<int>, std::greater <int> > q;
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
    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    auto elapsed2 = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
    cout << endl;
    
    std::cout << "sum1=" << sum1 << " calculated in " << elapsed1 <<std::endl;
    std::cout << "sum2=" << sum2 << " calculated in " << elapsed2 <<std::endl;
	return 0; 
} 