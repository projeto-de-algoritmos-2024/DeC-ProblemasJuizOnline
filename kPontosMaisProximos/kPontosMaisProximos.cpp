#include <vector>
#include <cmath>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        //Calcula a distância ao quadrado de um ponto à origem
        auto distancia = [](const vector<int>& ponto) {
            return ponto[0]*ponto[0]+ponto[1]*ponto[1];
        };

        //Ordena os pontos pela coordenada x
        sort(points.begin(), points.end(), [](const vector<int>& n1, const vector<int>& n2){
            return n1[0] < n2[0];
        });

        //Vetor para armazenar os k pontos mais próximos
        vector<vector<int>> guardaMaisProximos;

        //Chama a função maisProximos para encontrar os k pontos mais próximos
        maisProximos(points, 0, points.size()-1, k, guardaMaisProximos, distancia);

        return guardaMaisProximos;
    }

private:
    //Combina os resultados dos dois vetores
    void merge(const vector<vector<int>>& esquerda, const vector<vector<int>>& direita, vector<vector<int>>& guardaMaisProximos, int k, auto& distancia) {
        //Vetor para guardar a cobinação dos vetores esquerdo e direito
        vector<vector<int>> guarda;
        auto salva1 = esquerda.begin(), salva2 = direita.begin();

        //Mescla os vetores ordenados
        while (salva1 != esquerda.end() && salva2 != direita.end()) {
            if (distancia(*salva1) < distancia(*salva2)) {
                guarda.push_back(*salva1++);
            } else {
                guarda.push_back(*salva2++);
            }
        }

        //Adiciona os elementos restantes do vetor esquerdo
        while (salva1 != esquerda.end()){
            guarda.push_back(*salva1++);
        }

        //Adiciona os elementos restantes do vetor direito
        while (salva2 != direita.end()){
            guarda.push_back(*salva2++);
        }

        //Mantém apenas os k pontos mais próximos
        guardaMaisProximos = move(guarda);
        if (guardaMaisProximos.size() > k){
            guardaMaisProximos.resize(k);
        }
    }

    void maisProximos(vector<vector<int>>& points, int esquerda, int direita, int k, vector<vector<int>>& guardaMaisProximos, auto& distancia) {
        //Se o número de pontos no intervalo for menor ou igual a k
        if (direita-esquerda+1 <= k) {
            //Adiciona todos os pontos do intervalo ao vetor resultado
            for (int i = esquerda; i <= direita; ++i) {
                guardaMaisProximos.push_back(points[i]);
            }

            //Ordena o resultado pelos pontos mais próximos à origem
            sort(guardaMaisProximos.begin(), guardaMaisProximos.end(), [&distancia](const vector<int>& n1, const vector<int>& n2) {
                return distancia(n1) < distancia(n2);
            });

            //Mantém apenas os k pontos mais próximos
            if (guardaMaisProximos.size() > k) {
                guardaMaisProximos.resize(k);
            }

            return;
        }

        //Calcula o meio (divisão)
        int meio = esquerda + (direita-esquerda) / 2;

        //Cria vetores para guardar os resultados dos subconjuntos esquerdo e direito
        vector<vector<int>> esquerdaFinal, direitaFinal;

        //Resolve recursivamente os k pontos mais próximos em cada lado
        maisProximos(points, esquerda, meio, k, esquerdaFinal, distancia);
        maisProximos(points, meio + 1, direita, k, direitaFinal, distancia);

        //Combina os resultados dos dois lados
        merge(esquerdaFinal, direitaFinal, guardaMaisProximos, k, distancia);
    }

};