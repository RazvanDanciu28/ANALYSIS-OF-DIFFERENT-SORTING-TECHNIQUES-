#include <iostream>
#include <fstream>
#include <vector>
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


void MergeSort(vector<int> v, int st, int dr)
{

    //int size = v.size();
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
    return 0;
}
