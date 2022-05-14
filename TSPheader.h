#include <iostream>
#include<vector>
#include<cmath>
#include<limits>
#include <algorithm>
#include <string>

using namespace std;

template<typename T>
T showMax() {
    return numeric_limits<T>::max();
}
// функции для проверки промежуточных результатов
template<class T>
void show2d_matrix(vector<vector<T>>& M, int N) {
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++) {
            cout << M[i][j] << " ";
        }
        cout << endl;
    }
}
template<class T>
void show1d_matrix(vector<T>& V) {
    int N = V.size();
    for (int i = 0; i < N; i++) {
        cout << V[i] << " ";
    }
    cout << endl;
}
// Получение веса ребра
double dist(pair<double, double> p1, pair<double, double> p2) {
    return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
}
// функция для нахождения минимума с использованием алгоритма ближайшего соседа
int find_min(vector<double>& e, int start_v, vector<bool>& used) {
    int size = e.size();
    double min = e[start_v];
    int iter = start_v;
    for (int i = 0; i < size; i++) {
        if (min > e[i] && used[i] != true) {
            min = e[i];
            iter = i;
        }
    }
    return iter;
}
// Построение изначального тура с использованием алгоритма ближайшего соседа
void closest_neighbor(vector<vector<double>>& edges, int& N, vector<int>& tour) {
    int start_v = tour[0];
    int next_v;
    vector<bool> used(N, false);
    used[start_v] = true;
    next_v = find_min(edges[start_v], start_v, used);
    while (used[next_v] != true) {
        used[next_v] = true;
        tour.push_back(next_v);
        start_v = next_v;
        next_v = find_min(edges[start_v], start_v, used);
    }
}
double tour_weight(vector<vector<double>>& edges, vector<int>& tour) {
    int size = tour.size();
    double weight = 0;
    for (int i = 1; i < size; i++) {
        weight += edges[tour[i - 1]][tour[i]];
    }
    weight += edges[tour[size - 1]][tour[0]];
    return weight;
}
// 2-opt
vector<int> two_opt_swp(int i, int j, vector<int>& initial_tour, int& N) {
    vector<int> new_tour;
    copy(initial_tour.begin(), initial_tour.begin() + i, back_inserter(new_tour));
    vector<int> reversed_vec;
    copy(initial_tour.begin() + i, initial_tour.begin() + j + 1, back_inserter(reversed_vec));
    reverse(reversed_vec.begin(), reversed_vec.end());
    copy(reversed_vec.begin(), reversed_vec.end(), back_inserter(new_tour));
    copy(initial_tour.begin() + j + 1, initial_tour.end(), back_inserter(new_tour));
    return new_tour;
}
double two_opt(vector<int>& initial_tour, int& N, vector<vector<double>>& edges) {
    int improve = 0;
    int max_possible_improve = 10;
    vector<int> new_tour;
    int iter = 0;
    double min_dist = tour_weight(edges, initial_tour);
    while (improve < max_possible_improve) {
        for (int i = 0; i < N - 1; i++) {
            for (int j = i + 1; j < N; j++) {
                new_tour = two_opt_swp(i, j, initial_tour, N);
                double new_dist = tour_weight(edges, new_tour);
                if (new_dist < min_dist) {
                    improve = 0;
                    initial_tour = new_tour;
                    min_dist = new_dist;
                }
            }
        }
        iter++;
        improve++;
    }
    cout << iter << endl;
    return min_dist;
}