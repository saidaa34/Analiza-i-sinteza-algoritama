#ifndef TEZINSKI_GRAF_H
#define TEZINSKI_GRAF_H
#include <vector>
#include <list>
#include <map>
#include <utility>
using namespace std;

class TezinskiGraf {
    int n;
    vector<vector<int>> matrica_susjedstva;
    vector<pair<double,double>> gradovi;

public:
    TezinskiGraf();
    TezinskiGraf(int broj_gradova);
    void dodajGranu(int i, int j);
    void dodajGrad(pair<double,double> koordinata);
    bool postojiLiCiklus(int pocetni);
    void obrisiGranu(int i, int j);
    int TSP1();
    int TSP2();
    int TSP3();
    void ispis();
    void ispis2();
};

class DisjunktniSkupovi {

    int n;
    vector<int> roditelj;

    public:
    DisjunktniSkupovi(int broj_cvorova):n(broj_cvorova) {
        for(int i = 0; i < n; i++)
            roditelj.push_back(i);
    }

    int Nadji(int cvor) {
        if(roditelj[cvor] == cvor)
            return cvor;
        roditelj[cvor] = Nadji(roditelj[cvor]);
        return roditelj[cvor];
    }

    void Spoji(int i, int j) {
        roditelj[roditelj[i]] = roditelj[j];
    }
};

class DisjunktniSkupoviLista {
    int n;
    vector<list<int>> skupovi;
    public:
    DisjunktniSkupoviLista(int broj_cvorova):n(broj_cvorova) {
        for(int i = 0; i < n; i++){
            list<int> lista;
            lista.push_back(i);
            skupovi.push_back(lista);
        }
    }
    int Nadji(int cvor) {
        for(int i = 0; i < n; i++)
            for(auto it = skupovi[i].begin(); it != skupovi[i].end(); it++)
                if(*it == cvor)
                    return i;
    }
    void Spoji(int i, int j) {
        for(auto it = skupovi[j].begin(); it != skupovi[j].end(); it++)
            skupovi[i].push_back(*it);
        for(auto it = skupovi[j].begin(); it != skupovi[j].end(); it++)
            skupovi[j].erase(it);
    }
};

#endif // TEZINSKI_GRAF_H

