#include "TSPheader.h"
#include<filesystem>
#include<fstream>
namespace  fs = std::filesystem;
using namespace std;

vector<string> filesindir(const fs::path &dir) {
	vector<string> files;
	for (auto& p : fs::recursive_directory_iterator(dir)) {
		if (fs::is_regular_file(p)) {
			files.push_back(p.path().string());
		}
	}
	return files;
}
void fill_result(double &wt,ofstream &out,vector<vector<double>> &edges,string &file_name) {
	out << file_name << '\n';
	out << wt <<'\n';
	/*for (int i = 0; i < tour.size(); i++) {
		out << tour[i] << " ";
	}
	out << '\n';*/
}