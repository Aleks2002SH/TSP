// TSP.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include<iostream>
#include<vector>
#include<cmath>
#include<limits>
#include <algorithm>
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
        cout << V[i]<<" ";
    }
    cout << endl;
}
// Получение веса ребра
double dist(pair<double, double> p1, pair<double, double> p2) {
    return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
}
// функция для нахождения минимума с использованием алгоритма ближайшего соседа
int find_min(vector<double>& e,int start_v, vector<bool>& used) {
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
double closest_neighbor(vector<vector<double>> edges, int N,vector<int> &tour) {
    int start_v = tour[0];
    double tour_weight = 0;
    int next_v;
    vector<bool> used(N, false);
    used[start_v] = true;
    next_v = find_min(edges[start_v],start_v, used);
    while (used[next_v] != true) {
        used[next_v] = true;
        tour.push_back(next_v);
        tour_weight += edges[start_v][next_v];
        start_v = next_v;
        next_v = find_min(edges[start_v],start_v,used);
    }
    tour_weight += edges[start_v][tour[0]];
    return tour_weight;
}

int main() {
    int N;
    double a, b;
    cin >> N;
    vector<pair<double, double>> V;
    for (int i = 0; i < N; i++) {
        cin >> a;
        cin >> b;
        V.push_back(make_pair(a, b));
    }
    vector<vector<double>> edges(N);
    for (int i = 0; i < N; i++) {
        pair<double, double> v1 = V[i];
        for (int j = 0; j < N; j++) {
            if (i != j) {
                pair<double, double> v2 = V[j];
                edges[i].push_back(dist(v1, v2));
            }
            else {
                edges[i].push_back(showMax<double>());
            }

        }
    }
    V.clear();
    vector<int> tour;
    tour.push_back(0);
    cout << closest_neighbor(edges, N, tour) << endl;
    show1d_matrix<int>(tour);
    show2d_matrix<double>(edges, N);
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
