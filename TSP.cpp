// TSP.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "for_file_output.h"

int main() {
    vector<string> files;
    auto cur_p = fs::current_path();
    fs::path dir{ "data" };
    fs::path pathtodata = cur_p / dir;
    files = filesindir(pathtodata);
    ofstream out("result.txt");
    for (int file = 0; file < files.size(); file++) {
        int N;
        double a, b;
        ifstream in(files[file]);
        in >> N;
        vector<pair<double, double>> V;
        for (int i = 0; i < N; i++) {
            in >> a;
            in >> b;
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
        vector<int> initial_tour;
        initial_tour.push_back(0);
        closest_neighbor(edges, N, initial_tour);
        double wt = two_opt(initial_tour,N,edges);
        cout << wt << endl;
        fill_result(wt, out, edges, files[file]);
        in.close();
    }
    out.close();
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
