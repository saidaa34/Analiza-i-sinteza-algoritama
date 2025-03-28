#include "tezinski_graf.h"
#include <climits>
#include <iostream>
#include <set>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;

TezinskiGraf::TezinskiGraf():n(0) {}
TezinskiGraf::TezinskiGraf(int broj_gradova):n(broj_gradova) {
    matrica_susjedstva.resize(n);
    for(int i=0;i<n;i++)
        matrica_susjedstva[i].resize(n);
}

//funkcija za računanje udaljenosti između dvije tačke
int udaljenost(pair<double,double> prvaKoord, pair<double,double> drugaKoord){
    double d = sqrt((drugaKoord.first - prvaKoord.first)*(drugaKoord.first - prvaKoord.first) + (drugaKoord.second - prvaKoord.second)*(drugaKoord.second - prvaKoord.second));
    return round(d);
}

//funkcija koju cu koristiti kada budem dodavala gradove iz file-a
void TezinskiGraf::dodajGrad(pair<double,double> koordinata){
    //prvo dodam koordinatu u vektor gradova
    gradovi.push_back(koordinata);
    //posto cu u matricu susjedstva trebati dodati udaljenost od drugih gradova do novog, matricu trebam prosiriti da ima jedan više red za novi grad
    matrica_susjedstva.resize(n+1);

    for(int i = 0; i < n +1; i++)
        matrica_susjedstva[i].resize(n + 1);

    for(int i=0;i < gradovi.size();i++){
        //u svaki red matrice dodajem udaljenost od i-tog grada do novog dodanog grada
        matrica_susjedstva[i][n] = (udaljenost(koordinata,gradovi[i]));
        //pošto je matrica simetrična, istu vrijednost trebam dodati i u zadnjem redu na i-toj poziciji
        matrica_susjedstva[n][i] = (udaljenost(koordinata,gradovi[i]));

    }
    //ako je ovo prvi grad kojeg unosimo, onda je njegova udaljenost od samog sebe jednaka nuli, pa samo to dodamo
    //kada dodam grad, povecavam broj gradova
    n++;
}

void TezinskiGraf::dodajGranu(int i, int j) {
    matrica_susjedstva[i][j] = 1;
    matrica_susjedstva[j][i] = 1;
}

void TezinskiGraf::obrisiGranu(int i, int j){
    matrica_susjedstva[i][j] = 0;
    matrica_susjedstva[j][i] = 0;
}

void TezinskiGraf::ispis(){
    for(int i=0;i<gradovi.size();i++)
        cout<<gradovi[i].first<<", "<<gradovi[i].second<<endl;
}

void TezinskiGraf::ispis2(){
    for(int i=0;i<matrica_susjedstva.size();i++){
        for(int j=0;j<matrica_susjedstva[i].size();j++){
            cout<<matrica_susjedstva[i][j]<<"  ";
        }
        cout<<endl;
    }
}

bool TezinskiGraf::postojiLiCiklus(int pocetni){
    vector<bool> posjecen(matrica_susjedstva.size(),false);
    vector<int> roditelj(matrica_susjedstva.size(),-1); //ovdje cu stavljati indekse roditelja odredjenog cvora
    queue<int> red;
    red.push(pocetni);
    roditelj[pocetni] = -2;
    posjecen[pocetni] = true;
    bool ciklus = false;
    vector<list<int>> lista_susjedstva(matrica_susjedstva.size());
    for(int i=0;i<matrica_susjedstva.size();i++){
        for(int j=0;j<matrica_susjedstva[i].size();j++){
            if(matrica_susjedstva[i][j]==1){
                lista_susjedstva[i].push_back(j);
            }
        }
    }
    while(!red.empty()){
        int trenutni = red.front();
        red.pop();
        for(auto it=lista_susjedstva[trenutni].begin();it!=lista_susjedstva[trenutni].end();it++){
            if(!posjecen[*it]){
                posjecen[*it]=true;
                red.push(*it);
                roditelj[*it] = trenutni;
            }
            else {
                if(roditelj[trenutni]!=*it){
                    ciklus=true;
                    break;
                }
            }
        }
    }
    return ciklus;
}

int TezinskiGraf::TSP1(){
    //pravim novi tezinski graf koji ce imati onolko cvorova koliko ima gradova
    TezinskiGraf rezultat(matrica_susjedstva.size());
    //na pocetku svi cvorovi imaju stepen 0, jer jos uvijek nemaju dodanih grana, kad im dodamo neku granu onda ce se stepen odgovarajuceg cvora povecavati
    vector<int> stepen(matrica_susjedstva.size(),0);
    //u stablu udaljenosti ce biti sve udaljenosti iz matrice susjedstva naseg baznog grafa u kojem su svi gradovi i sve grane
    set<pair<int,pair<int,int>>> stabloUdaljenosti; //stavljam tezinu grane i pamtim na kojem indeksu se nalazi ta grana
    for(int i=0;i<matrica_susjedstva.size();i++){
        for(int j = 0;j<matrica_susjedstva[i].size();j++){
            //posto je matrica simetricna, dovoljno je da se gleda samo jedan dio matrice gdje je indeks j veci od i
            if(j>i)
                //u stablo dodajem {tezina grane,{indeks na kojem je ta tezina}}
                stabloUdaljenosti.insert({matrica_susjedstva[i][j],{i,j}});
        }
    }
    int brojac = 0;
    int put = 0;
    while(brojac < n) {
        //u stablu ce na pocetku biti najmanja udaljenost, pa u "prvi" stavljam indekse tih cvororva izmedju kojih je najmanja udaljenost
        pair<int,int> prvi = stabloUdaljenosti.begin()->second;
        //da bi u sljedecem koraku uzela sljedecu najmanju udaljenost iz stabla brisem prvi element
        stabloUdaljenosti.erase(stabloUdaljenosti.begin());
        //ako cvor nema grana ili ima jednu granu, onda...
        if(stepen[prvi.first]<2 && stepen[prvi.second]<2){
            //... u nas novi tezinski graf koji se zove "rezultat" dodajem granu
            rezultat.dodajGranu(prvi.first,prvi.second);
            //rezultat.ispis2();
            //cout<<endl<<endl;
            put += matrica_susjedstva[prvi.first][prvi.second];
            //ako postoji ciklus onda tu granu moram obrisati, pa ovdje to provjeravam
            if(rezultat.postojiLiCiklus(prvi.first) && brojac != n -1){
                put -= matrica_susjedstva[prvi.first][prvi.second];
                 rezultat.obrisiGranu(prvi.first,prvi.second);
            }

            //ako nema ciklusa onda grana ostaje dodana, pocevavam broj dodanih grana i povecavam stepene za odgovarajuce gradove
            else{
                brojac++;
                stepen[prvi.first] = stepen[prvi.first] + 1;
                stepen[prvi.second] = stepen[prvi.second] + 1;
            }
        }
    }
    cout<<put<<endl;
    return put;
}

int TezinskiGraf::TSP2(){
    vector<int> stepen(matrica_susjedstva.size(),0);
    set<pair<int,pair<int,int>>> stabloUdaljenosti; //stavljam tezinu grane i pamtim na kojem indeksu se nalazi ta grana
    for(int i=0;i<matrica_susjedstva.size();i++){
        for(int j = 0;j<matrica_susjedstva[i].size();j++){
            if(j>i && matrica_susjedstva[i][j] != 0)
                stabloUdaljenosti.insert({matrica_susjedstva[i][j],{i,j}});
        }
    }
    int brojac=0;
    int put=0;
    DisjunktniSkupovi ds(matrica_susjedstva.size());
    while(brojac < n ){
        pair<int,int> prvi = stabloUdaljenosti.begin()->second;
        stabloUdaljenosti.erase(stabloUdaljenosti.begin());
        if(stepen[prvi.first]<2 && stepen[prvi.second]<2){
            put += matrica_susjedstva[prvi.first][prvi.second];
            if(ds.Nadji(prvi.first) == ds.Nadji(prvi.second) && brojac != n-1){
                put -= matrica_susjedstva[prvi.first][prvi.second];
            }
            else{
                brojac++;
                stepen[prvi.first] = stepen[prvi.first] + 1;
                stepen[prvi.second] = stepen[prvi.second] + 1;
                ds.Spoji(prvi.first,prvi.second);
            }
        }
    }
    cout<<put<<endl;
    return put;
}

int TezinskiGraf::TSP3(){
    vector<int> stepen(matrica_susjedstva.size(),0);
    set<pair<int,pair<int,int>>> stabloUdaljenosti; //stavljam tezinu grane i pamtim na kojem indeksu se nalazi ta grana
    for(int i=0;i<matrica_susjedstva.size();i++){
        for(int j = 0;j<matrica_susjedstva[i].size();j++){
            if(j>i && matrica_susjedstva[i][j] != 0)
                stabloUdaljenosti.insert({matrica_susjedstva[i][j],{i,j}});
        }
    }

    int brojac=0;
    int put=0;
    DisjunktniSkupoviLista ds(matrica_susjedstva.size());
    while(brojac < n ){
        pair<int,int> prvi = stabloUdaljenosti.begin()->second;
        stabloUdaljenosti.erase(stabloUdaljenosti.begin());
        if(stepen[prvi.first]<2 && stepen[prvi.second]<2){
            put += matrica_susjedstva[prvi.first][prvi.second];
            if(ds.Nadji(prvi.first) == ds.Nadji(prvi.second) && brojac != n-1){
                put -= matrica_susjedstva[prvi.first][prvi.second];
            }
            else{
                brojac++;
                stepen[prvi.first] = stepen[prvi.first] + 1;
                stepen[prvi.second] = stepen[prvi.second] + 1;
                ds.Spoji(prvi.first,prvi.second);
            }
        }
    }
    cout<<put<<endl;
    return put;
}





