#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
       
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        } // coloca o menor array na primeira posição

        int m = nums1.size();
        int n = nums2.size();
        int totalEsq = (m + n + 1) / 2; //qtd elementos primeira parte

        int esq = 0, dir = m; 

        while (esq <= dir) {
            int part1 = (esq + dir) / 2; 
            int part2 = totalEsq - part1;

            int maxEsq1 = (part1 == 0) ? INT_MIN : nums1[part1 - 1];
            int minDir1 = (part1 == m) ? INT_MAX : nums1[part1];

            int maxEsq2 = (part2 == 0) ? INT_MIN : nums2[part2 - 1];
            int minDir2 = (part2 == n) ? INT_MAX : nums2[part2];

            if (maxEsq1 <= minDir2 && maxEsq2 <= minDir1) {
               
                if ((m + n) % 2 == 1) {
                    return max(maxEsq1, maxEsq2); //achou a mediana
                } else {
                    return (max(maxEsq1, maxEsq2) + min(minDir1, minDir2)) / 2.0;
                }

            } else if (maxEsq1 > minDir2) {
                dir = part1 - 1; //percorre para a esquerda
            } else {
                esq = part1 + 1; //percorre para a direita
            }
        }
        return 0;
    }
};

