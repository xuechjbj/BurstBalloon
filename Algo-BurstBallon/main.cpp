//
//  main.cpp
//  Algo-BurstBallon
//
//  Created by Chaojun Xue on 1/11/16.
//  Copyright © 2016 Chaojun Xue. All rights reserved.
//
/*
 https://leetcode.com/problems/burst-balloons/
 
 Given n balloons, indexed from 0 to n-1. Each balloon is painted with a number on it represented by array nums. You are asked to burst all the balloons. If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins. Here left and right are adjacent indices of i. After the burst, the left and right then becomes adjacent.
 
 Find the maximum coins you can collect by bursting the balloons wisely.
 
 Note:
 (1) You may imagine nums[-1] = nums[n] = 1. They are not real therefore you can not burst them.
 (2) 0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100
 
 Example:
 
 Given [3, 1, 5, 8]
 
 Return 167
 
 nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
 coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167
 
 */

#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Solution {
    
public:
    int maxCoins1(vector<int>& nums) {
        int n = nums.size();
        vector<int> NUMS; // include the boundaries
        NUMS.push_back(1);
        int i;
        for(i=0; i<n; i++)
            NUMS.push_back(nums[i]);
        NUMS.push_back(1);
        int N = n+2;
        
        vector< vector<int> > DP;
        DP.resize(N);
        for(i=0; i<N; i++)
            DP[i].resize(N, 0); // dymanic programming
        // DP[start][end] denotes maxCoins in NUMS[start,.....,end]
        // return DP[1][n] as maxCoins in nums[0,......,n-1]
        
        int length, start, end;
        for(length=1; length<=n; length++)
        {
            for(start=1; start<=n-length+1; start++)
            {
                end = start+length-1;
                for(i=start; i<=end; i++)
                {
                    // i-the ballon is the last to burst
                    if(DP[start][end] < DP[start][i-1]+DP[i+1][end]+NUMS[start-1]*NUMS[i]*NUMS[end+1])
                        DP[start][end] = DP[start][i-1]+DP[i+1][end]+NUMS[start-1]*NUMS[i]*NUMS[end+1];
                    // divide and conquer
                }
            }
        } // O(N*N*N) complexity
        return DP[1][n];
    }
    
    long maxCoins(vector<int>& nums) {
        
        vector<vector<int> > vv;
        vector<vector<int> > newvv;
        
        for(int i=0; i<nums.size(); i++){
            vector<int> v;
            v.push_back(i);
            newvv.push_back(v);
        }
        
        int level = 0;
        long max = 0l;
        
        while(true){
            
            max = calcMax(nums, newvv);
            
            if(++level >= nums.size()) break;
            vv = newvv;
            newvv.clear();
            
            nextCombinations(nums.size()-1, vv, newvv);
        }
        
        return max;
    }
    
protected:
    long calcMax(vector<int>& nums, vector<vector<int> > &vv){
        long max = 0;
        for(vector<int> &v: vv){
            long max1 = 0;
            
            for(int i = 0; i<v.size(); i++){
                long value = getBurstValue(nums, i, v);
                if(value > max1){
                    max1 = value;
                }
            }
            
            saveBurstValue(max1, v);
            
            if(max1 > max){
                max = max1;
            }
        }
        return max;
    }
    
    void saveBurstValue(long max, vector<int> &v){
        string key = vector2string(v);
        printf("key=%s, value=%ld\n", key.c_str(), max);
        mapQ[key] = max;
    }
    
    long getMaxValue(vector<int> &prev){
        if(prev.size() == 0) return 0;
        
        string key = vector2string(prev);
        return mapQ[key];
    }
    
    long getBurstValue(vector<int>& nums, int burstIndexIndex, vector<int> &v){
        
        int left = 0;
        int middle = nums[v[burstIndexIndex]];
        int right = 0;
        vector<int> prev = v;
        
        if(burstIndexIndex == 0){
            left = 1;
        }
        else{
            left = nums[v[burstIndexIndex-1]];
        }
        
        //prev.push_back(v[burstIndexIndex]);
        
        if(burstIndexIndex == v.size() - 1){
            right = 1;
        }
        else{
            right = nums[v[burstIndexIndex+1]];
        }
        prev.erase(prev.begin()+burstIndexIndex);
        long value = getMaxValue(prev);
        return left * middle * right + value;
    }
    
    void nextCombinations(size_t maxIndex, vector<vector<int> > &vv, vector<vector<int> > &newvv){
        for(vector<int> v: vv){
            int lastIndex = v.back();
            
            for(int i=lastIndex + 1; i<=maxIndex; i++){
                vector<int> newComb;
                for(int e:v){
                    newComb.push_back(e);
                }
                newComb.push_back(i);
                newvv.push_back(newComb);
            }
        }
        
    }
    
    string vector2string(vector<int> &v){
        string str="";
        bool first = true;
        
        for(int i:v){
            if(!first){
                first = false;
                str += ',';
            }
            str += to_string(i);
        }
        
        return str;
    }
    
private:
    map<string, long> mapQ;
};

int main(int argc, const char * argv[]) {
    vector<int> nums = {2,4,8,4,0,7,8,9,1,2,4,7,1,7,3,6};
    
    Solution solution;
    
    long max = solution.maxCoins(nums);
    
    std::cout << "Hello, World! "<<max<<"\n";
    return 0;
}
