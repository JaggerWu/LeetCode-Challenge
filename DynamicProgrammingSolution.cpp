//
// Created by Jian Wu on 22/02/2020.
//
#include <algorithm>
#include <numeric>
#include <math.h>

#include "DynamicProgrammingSolution.h"


int DynamicProgrammingSolution::maxSubArray(vector<int>& nums)
{
    vector<int> dp;
    dp.push_back(nums.front());

    for (int i = 1; i < nums.size(); ++i) {
        if (dp[i-1] < 0)
            dp.push_back(nums[i]);
        else
            dp.push_back(dp[i-1]+nums[i]);
    }

    return *max_element(dp.begin(), dp.end());
}

int DynamicProgrammingSolution::maxProduct(vector<int>& nums) {
    if (nums.size() == 1) return nums.front();

    int size = nums.size();
    vector<int> pos(size, 0), neg(size, 0);
    pos[0] = nums[0] > 0 ? nums[0] : 0;
    neg[0] = nums[0] < 0 ? nums[0] : 0;

    for (int i = 1; i < nums.size(); ++i) {
        if (nums[i] > 0) {
            pos[i] = pos[i-1] == 0 ? nums[i] : pos[i-1] * nums[i];
            neg[i] = neg[i-1] * nums[i];
        } else if (nums[i] < 0) {
            pos[i] = neg[i-1] * nums[i];
            neg[i] = pos[i-1] == 0 ? nums[i] : pos[i-1] * nums[i];
        }
    }

    return *max_element(pos.begin(), pos.end());
}

int DynamicProgrammingSolution::minPathSum(vector<vector<int>> &grid) {
    if (grid.empty()) return 0;

    for (int i = 1; i < grid[0].size(); ++i) {
        grid[0][i] += grid[0][i-1];
    }

    for (int i = 1; i < grid.size(); ++i) {
        grid[i][0] += grid[i-1][0];
    }

    for (int i = 1; i < grid[0].size(); ++i) {
        for (int j = 1; j < grid.size(); ++j) {
            grid[j][i] += min(grid[j-1][i], grid[j][i-1]);
        }
    }

    return grid.back().back();
}

int DynamicProgrammingSolution::minimumTotal(vector<vector<int>>& triangle)
{
//    if (triangle.empty()) return 0;
//
//    for (int row = 1; row < triangle.size(); ++row) {
//        triangle[row].front() += triangle[row-1].front();
//        triangle[row].back() += triangle[row-1].back();
//
//        for (int col = 1; col < triangle[row].size() - 1; ++col) {
//            triangle[row][col] += min(triangle[row-1][col-1], triangle[row-1][col]);
//        }
//    }
//    return *min_element(triangle.back().begin(), triangle.back().end());
    if (triangle.empty()) return 0;
    int numOfRows = triangle.size();

    for (int row = numOfRows - 2; row >= 0 ; --row) {
        for (int col = 0; col < triangle[row].size(); ++col) {
            triangle[row][col] += min(triangle[row+1][col], triangle[row+1][col+1]);
        }
    }

    return triangle.front().front();
}

int DynamicProgrammingSolution::findLongestChain(vector<vector<int>> &pairs) {
    // Greedy implement

    sort(
            pairs.begin(),
            pairs.end(),
            [](const vector<int>& v1, const vector<int>& v2) -> bool {return v1[1] < v2[1];});

    int ans = 0, cur = INT_MIN;

    for (const auto& pair : pairs) {
        if (cur < pair[0]) {
            cur = pair[1];
            ans++;
        }
    }

    return ans;
}

vector<vector<int>> DynamicProgrammingSolution::findSubsequences(vector<int> &nums) {
    return vector<vector<int>>(9, vector<int>(9, 0));
}

bool DynamicProgrammingSolution::canPartition(vector<int>& nums) {
    int sum = accumulate(nums.begin(), nums.end(), 0);

    if (sum % 2 == 1 || nums.size() == 1) return false;
    vector<vector<int>> dp(nums.size(), vector<int>(sum/2 + 1, 0));

    dp[0][nums[0]] = 1;
    dp[0][0] = 1;

    for (int i = 0; i < nums.size(); ++i) {
        dp[i][0] = 1;
    }

    for (int i = 1; i < nums.size(); ++i) {
        for (int j = 0; j < sum/2+1; ++j) {
            dp[i][j] = dp[i - 1][j] || ((j >= nums[i]) ? dp[i - 1][j - nums[i]] : 0);
        }

        if (dp[i].back() == 1) return true;
    }

    return false;
}

int DynamicProgrammingSolution::numDecodings(string s) {
    if (s.empty()) return 0;
    vector<int> ans(s.size() + 1, 0);
    ans[0] = 1;
    ans[1] = s[0] == '0' ? 0 : 1;

    for (int i = 2; i < s.size() + 1; ++i) {
        int index = s[i-1] - '0';
        ans[i] = ans[i-1] * (index > 0 ? 1 : 0);
        int doubleChar = index + 10 * (s[i - 2] - '0');
        if (doubleChar <= 26 && doubleChar >= 10)
            ans[i] += ans[i-2];
    }

    return ans.back();
}

vector<TreeNode *> DynamicProgrammingSolution::generateTrees(int n) {
    if (n == 1) return vector<TreeNode*> {new TreeNode(n)};
    vector<vector<TreeNode*>> ans(n);
    ans[0] = {new TreeNode(n)};

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < ans[i-1].size(); ++j) {
            while (i)
            {
                TreeNode* cur = new TreeNode(0);
                cur->right = ans[i-1][j];
                TreeNode* newTreeNode = new TreeNode(i+1);

                ans[i].push_back(cur->right);
            }
        }
    }

    return ans.back();
}

int DynamicProgrammingSolution::numSquares(int n) {
    vector<int> ans(n+1, INT_MAX);
    ans[0] = 0;

    for (int i = 1; i < n+1; ++i) {
        int maxSqrt = sqrt(i);

        for (int j = 1; j <= maxSqrt; ++j) {
            ans[i] = min(ans[i], ans[i-j * j] + 1);
        }
    }

    return ans.back();
}

inline bool isPrime(const int n) {
    if (n == 1) return false;
    if (n == 2) return true;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }

    return true;
}

int DynamicProgrammingSolution::countPrimes(int n) {
    if (n <= 1) return 0;

    int dp[n]; //array is faster than vector
    memset(dp, -1, sizeof(dp));
    dp[0] = 0;
    dp[1] = 0;

    for (int i = 2; i < n; ++i) {
        if(dp[i] == -1){
            for(int j=2;i*j < n;j++){
                dp[i*j]=0;
            }
        }
    }

    return -accumulate(dp, dp + n, 0);
}

int DynamicProgrammingSolution::lenLongestFibSubseq(vector<int> &A) {
    return 0;
}

int DynamicProgrammingSolution::integerBreak(int n) {
    vector<int> ans(n + 1, 0);
    ans[1] = 1;

    for (int i = 2; i < n+1; ++i) {
        for (int j = 1; j < i; ++j) {
            ans[i] = max(ans[i], j * ans[i-j]);
            ans[i] = max(ans[i], j * (i-j));
        }
    }

    return ans.back();
}

vector<int> DynamicProgrammingSolution::countBits(int num) {
    if (!num) return {0};

    vector<int> res(num+1, 0);
    res[0] = 0, res[1] = 1;
    int start = 2;
    while(start * 2 <= num) {
        for (int i = start; i < 2 * start; ++i) {
            res[i] = 1 + res[i - start];
        }

        start <<= 1;
    }

    for (int i = start; i < num + 1; ++i) {
        res[i] = 1 + res[i - start];
    }

    return res;
}

int DynamicProgrammingSolution::rob(vector<int> &nums) {
    int len = nums.size();

    if (!len) return 0;
    if (len == 1) return nums[0];

    vector<int> ans(nums.size(), 0);
    ans[0] = nums[0], ans[1] = max(nums[0], nums[1]);
    for (int i = 2; i < len; ++i) {
        ans[i] = max(ans[i-1], nums[i] + ans[i-2]);
    }

    return ans.back();
}

int DynamicProgrammingSolution::robInCircle(vector<int> &nums) {
    int len = nums.size();
    if (!len) return 0;
    if (len <= 3) return *max_element(nums.begin(), nums.end());

    vector<int> fromFirst(len-1, 0);
    fromFirst[0] = nums[0], fromFirst[1] = max(nums[0], nums[1]);

    vector<int> fromSecond(len-1, 0);
    fromSecond[0] = nums[1], fromSecond[1] = max(nums[1], nums[2]);

    for (int i = 2; i < len-1; ++i) {
        fromFirst[i] = max(fromFirst[i-1], nums[i] + fromFirst[i-2]);
        fromSecond[i] = max(fromSecond[i-1], nums[i+1] + fromSecond[i-2]);
    }

    return max(fromFirst.back(), fromSecond.back());
}

bool DynamicProgrammingSolution::wordBreak(string s, vector<string> &wordDict) {
    vector<bool> dp(s.size()+1, false);
    dp[0] = true;

    for (int i = 1; i <= s.size(); ++i) {
        for (const auto& word : wordDict)
        {
            int startIndex = i - word.size();
            if (startIndex < 0 || !dp[startIndex]) continue;
            if (s.substr(startIndex, i - startIndex) == word && dp[startIndex])
            {
                dp[i] = true;
                break;
            }
        }
    }

    return dp.back();
}

int DynamicProgrammingSolution::lengthOfLIS(vector<int> &nums) {
    if (!nums.size()) return 0;
    vector<int> dp(nums.size()+1, 0);
    dp[1] = 1;
    int length = 1;

    for (int i = 2; i < nums.size()+1; ++i) {
        dp[i] = 1;

        for (int j = 1; j < i; ++j) {
            if (nums[i] >= nums[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }

        length = max(length, dp[i]);
    }

    return length;
}