#include <iostream>
#include <fstream>
#include <sstream>
#include "tezinski_graf.h"
using namespace std;

void readTSPFile(const string& filename, TezinskiGraf &graf) {

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        int id;
        double x, y;
        if (iss >> id >> x >> y) {
            graf.dodajGrad({x,y});
        }
    }
    //graf.ispis();
    //graf.ispis2();
}

int main() {

    TezinskiGraf g;
    string filename = "dj38.tsp";
    //string filename = "qa194.tsp";
    //string filename = "uy734.tsp";
    readTSPFile(filename, g);
    g.TSP1();
    g.TSP2();
    //g.TSP3();
}
