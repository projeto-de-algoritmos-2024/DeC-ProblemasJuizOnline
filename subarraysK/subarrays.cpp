#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int countSubarrays(vector<int>& nums, int k) {
        
        int id = 0;
        for(int i=0; i<nums.size(); i++){
            if(nums[i] == k ) {
                id = i;
                break;
            }
        }  //busca o indice do k no vetor original
        
        vector<int>esq , dir; //vetores auxiliares para menor e maior que k
        esq.push_back(0);
        dir.push_back(0);
        
        int contador= 0;
        for(int i = id-1; i>=0; i--){
            if(nums[i] < k) contador++; //coloca os numeros menores que k à esquerda
            else contador--;
            
            esq.push_back(contador);
        }
        
        contador= 0;
        for(int i = id+1; i<nums.size(); i++){
            if(nums[i] > k) contador++; //maiores que k à direita
            else contador--;
            
            dir.push_back(contador);
        }
        
        sort(esq.begin(), esq.end());
        sort(dir.begin(), dir.end());

        int ans  = 0;
        for(auto i : dir){
            vector<int>::iterator lower, upper;
            lower = lower_bound(esq.begin(), esq.end(), i); //busca binária
            upper = upper_bound(esq.begin(), esq.end(), i);            
            ans += upper - lower;
            
            
            lower = lower_bound(esq.begin(), esq.end(), i-1);
            upper = upper_bound(esq.begin(), esq.end(), i-1);            
            ans += upper - lower;
        }
        return ans;        
    }
    
};