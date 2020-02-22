//
// Created by Jian Wu on 22/02/2020.
//

#ifndef LEETCODE_DYNAMICPROGRAMMINGSOLUTION_H
#define LEETCODE_DYNAMICPROGRAMMINGSOLUTION_H

#include <vector>

using namespace std;

class DynamicProgrammingSolution {
public:
    int maxSubArray(vector<int>& nums);
    int maxProduct(vector<int>& nums);
    int minPathSum(vector<vector<int>>& grid); // LeetCode 64
    int minimumTotal(vector<vector<int>>& triangle); // LeetCode 120;
    int findLongestChain(vector<vector<int>>& pairs); // LeetCode 646;
};


#endif //LEETCODE_DYNAMICPROGRAMMINGSOLUTION_H
