#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <chrono>
using namespace std;
using namespace std::chrono;
ifstream fin ("input.txt");

//functie care testeaza daca vectorul este sortat corect
int test_sort (vector<int> v_sortat, int n)
{
    for (int i = 0; i < n-1; i++){
        if (v_sortat[i] > v_sortat[i+1]) return 0;
    }
    return 1;
}
//functie care atriubuie valori random vectorului in functie de numarul de numere si numarul maxim
void get_random_vector (vector<int> &v, int n, int maxx)
{
    srand(time(0));
    for (int i = 0; i < n; i++){
        int rand_nr = (rand() * rand()) % (maxx + 1);
        v.push_back(rand_nr);
    }
}

//Fiind o functie recursiva, nu pot masura timpul in cadrul functiei pentru ca se va autoapela si voi avea returnati mai multi timpi
//asa ca voi masura timpul in main
void MergeSort(vector<int> v, int st, int dr)
{

    //creez vector auxiliar pentru interclasare
    vector<int> w;
    if(st < dr)
    {
        int m = (st + dr) / 2;
        MergeSort(v, st , m);
        MergeSort(v, m + 1 , dr);
        //Interclasare
        int i = st, j = m + 1, k = 0;
        while( i <= m and j <= dr ){
            if( v[i] < v[j]) w.push_back(v[i++]);
            else w.push_back(v[j++]);
        }
        while(i <= m)
            w.push_back(v[i++]);
        while(j <= dr)
            w.push_back(v[j++]);
        for(i = st , j = 0 ; i <= dr ; i ++ , j ++)
            v[i] = w[j];
    }
    w.clear();
}

void SelectionSort (vector<int> v, int n)
{
    auto start = high_resolution_clock::now();
    for (int i = 0; i < n-1; i++){
        for (int j = i + 1; j < n; j++){
            if (v[i] > v[j]) swap(v[i], v[j]);
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    if (test_sort(v, n))
        cout<<"SelectionSort a sortat corect numerele in "<<duration.count()/10000.0000000000 <<" secunde"<< endl;
    else
        cout<<"SelectionSort nu a sortat numerele corect";
}

void CountingSort(vector<int> v, int n, int maxx)
{
    auto start = high_resolution_clock::now();
    int size = v.size();
    vector<int> w;
    for (int i = 0 ; i <= maxx; i++) w.push_back(0);
    for (auto it: v) w[it]++;
    v.clear();
    for (int i = 0; i <= maxx; i++){
        if (w[i]){
            for (int j = 1; j <= w[i]; j++) v.push_back(i);
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    if (test_sort(v, n))
        cout<<"CountingSort a sortat corect numerele in "<<duration.count()/10000.0000000000 <<" secunde"<< endl;
    else
        cout<<"CountingSort nu a sortat numerele corect";
    w.clear();
}

//RadixSort doar in baza 10
int RadixSort(vector<int> v, int n){
    auto start = high_resolution_clock::now();
    //caut maximul pentru a sti cate cifre are cel mai mare si pana la cat merg cu forul
    int max_el = v[0];
    for (auto it: v) if (it > max_el) max_el = it;

    //incep de la lsd spre msd
    for (int nr_cifra = 1; max_el / nr_cifra > 0; nr_cifra *= 10){
        //imi fac o structura de cozi, pentru fiecare cifra din baza 10, voi avea o coada aferenta
        struct cozi { queue<int> c;};
        //imi fac un pointer de cozi (tipul structurii) pentru a putea sterge la final si a salva memorie
        cozi *w = new cozi[11];
        for (auto it: v){
            w[(it / nr_cifra) % 10].c.push(it);
        }
        v.clear(); //sterg vectorul pentru a-l completa la loc cu numerele sortate dupa cifra curenta
        for (int i = 0; i <= 10; i++){
            while (!w[i].c.empty()){
                v.push_back(w[i].c.front());
                w[i].c.pop();
            }
        }
        delete[] w;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    if (test_sort(v, n))
        cout<<"RadixSort a sortat corect numerele in "<<duration.count()/10000.0000000000 <<" secunde"<< endl;
    else
        cout<<"CountingSort nu a sortat numerele corect";

}

void ShellSort (vector<int> &v, int n)
{
    for (int gap = n / 2; gap > 1; gap /= 2 ){
        for (int i = 0; i <= gap; i ++)
    }
}

int main() {

    /*citire fisier
     * int n, maxx, numar_teste;
     * vector <int> v;
     * fin>>numar_teste;
     * for (int i = 1; i <= numar_teste; i++){
     *      fin>>n>>maxx;
     *      get_random_vector(v, n, maxx);
     *
     *
     * }
     */


    int n, maxx, numar_teste;
    vector <int> v;
    cin>>n;
    for (int i = 1; i <= n; i++){
        int x; cin>>x;
        v.push_back(x);
    }
    CountingSort(v, n, 11001);
    for (auto it: v) cout<<it<<" ";
    return 0;
}
