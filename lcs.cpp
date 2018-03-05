#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <algorithm>
#include <numeric>
#include <string>

#include "Timer.h"
using namespace std;

class Solution {
public:
    // (m+1)*(n+1) space version
    int lcsDP(string &A, string &B) {
        // write your code here
        int sa = A.size();
        int sb = B.size();
        if(sa == 0 || sb == 0)
            return 0;
        int dp[sa+1][sb+1];
        for(int i=0;i<sa;i++)
            dp[i][0] = 0;
        for(int j=0;j<sa;j++)
            dp[0][j] = 0;        
        int max_n = 1;
        for(int i=1;i<=sa;i++) {
            for(int j=1;j<=sb;j++) {
                if(A[i]==B[j]) {
                    int max1 = max(dp[i-1][j], dp[i][j-1]);
                    dp[i][j] = max(dp[i-1][j-1], max1);
                }
                else
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                
                if(dp[i][j] > max_n)
                    max_n = dp[i][j];
            }
        }
        
        return max_n;
    }

    // 2*(n+1) space version
    int lcsDP2(string &A, string &B) {
        int m = A.size();
        int n = B.size();
        int dp[2][n+1];

        for(int j=0;j<=n;j++)
            dp[1][j] = 0;

        for(int i=1;i<=m;i++) {
            // copy to first row
            for(int j=0;j<=n;j++)
                dp[0][j] = dp[1][j];
            
            for(int k=1;k<=n;k++) {
                if(A[i-1] == B[k-1])
                    dp[1][k] = dp[0][k-1] + 1;
                else
                    dp[1][k] = max(dp[0][k], dp[1][k-1]);
            }
        }
        
        return dp[1][n];
    }
};

void generateStr(string &s, const int size) {
    static const char alphabet[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(int i=0;i<size;i++) {
       s += alphabet[rand()%sizeof(alphabet)]; 
    }
}

int main() {
    int size_arr[] = {10, 50, 100, 1000, 10000};
    sol = Solution();

    for(int i=0;i<5;i++) {
        string a;
        string b;
        
        int iterations = 100;
        float totalTime1 = 0;
        float totalTime2 = 0;
        int commonSequenceSize;
        for(int iter=0; iter<iterations;iter++) {
            generateStr(a, size_arr[i]);
            generateStr(b, size_arr[i]);
            Timer t;
            double eTime;
            t.start();
            commonSequenceSize = sol.lcsDP(a, b);
            t.elapsedUserTime(eTime);
            totalTime1 += eTime;

            t.start();
            commonSequenceSize = sol.lcsDP2(a, b);
            t.elapsedUserTime(eTime);
            totalTime2 += eTime;
        }
        float avgTime1 = totalTime1/iterations;
        float avgTime2 = totalTime2/iterations;
        cout<<"String size: "<<size_arr[i]<<" DP1: "<<avgTime1<<" DP2: "<<avgTime2<<endl;
    }
}