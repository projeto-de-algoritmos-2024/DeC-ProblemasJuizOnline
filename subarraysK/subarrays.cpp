#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Função para encontrar o k-ésimo menor elemento usando Mediana das Medianas
int findKthSmallest(vector<int>& nums, int k) {
    if (nums.size() == 1) {
        return nums[0];
    }

    // Dividindo o vetor em grupos de 5
    vector<int> medianas;
    for (int i = 0; i < nums.size(); i += 5) {
        int end = min((int)nums.size(), i + 5);
        vector<int> conj5(nums.begin() + i, nums.begin() + end);
        sort(conj5.begin(), conj5.end());
        medianas.push_back(conj5[conj5.size() / 2]); // Mediana do grupo
    }

    // Encontrar a mediana das medianas
    int pivo = findKthSmallest(medianas, medianas.size() / 2);

    // Particionar o vetor baseado no pivô
    vector<int> esq, dir;
    for (int num : nums) {
        if (num < pivo)
            esq.push_back(num);
        else if (num > pivo)
            dir.push_back(num);
    }

    int contagemPivo = nums.size() - esq.size() - dir.size();
    if (k < esq.size())
        return findKthSmallest(esq, k);
    else if (k < esq.size() + contagemPivo)
        return pivo;
    else
        return findKthSmallest(dir, k - esq.size() - contagemPivo);
}

// Função principal para contar subarrays
class Solution {
public:
    int countSubarrays(vector<int>& nums, int k) {
        int id = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == k) {
                id = i;
                break;
            }
        }

        // Vetores auxiliares
        vector<int> esq, dir;
        esq.push_back(0);
        dir.push_back(0);

        // Construção do vetor esq
        int contador = 0;
        for (int i = id - 1; i >= 0; i--) {
            if (nums[i] < k)
                contador++;
            else
                contador--;
            esq.push_back(contador);
        }

        // Construção do vetor dir
        contador = 0;
        for (int i = id + 1; i < nums.size(); i++) {
            if (nums[i] > k)
                contador++;
            else
                contador--;
            dir.push_back(contador);
        }

        // Encontra a mediana de esq e dir usando Mediana das Medianas
        findKthSmallest(esq, esq.size() / 2);
        findKthSmallest(dir, dir.size() / 2);

        // Ordena os vetores com std::sort
        sort(esq.begin(), esq.end());
        sort(dir.begin(), dir.end());

        // Contar subarrays válidos
        int ans = 0;
        for (auto i : dir) {
            auto lower = lower_bound(esq.begin(), esq.end(), i);
            auto upper = upper_bound(esq.begin(), esq.end(), i);
            ans += upper - lower;

            lower = lower_bound(esq.begin(), esq.end(), i - 1);
            upper = upper_bound(esq.begin(), esq.end(), i - 1);
            ans += upper - lower;
        }

        return ans;
    }
};
