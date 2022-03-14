#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace std::chrono;
ifstream fin("input.txt");

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

    auto start = high_resolution_clock::now();

    srand(time(0));
    for (int i = 0; i < n; i++){
        int rand_nr = (rand() * rand()) % (maxx + 1);
        v.push_back(rand_nr);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout<<"Numerele au fost randomizate in "<<duration.count()/1000000.00000000000 <<" secunde"<< endl;

}

//Fiind o functie recursiva, nu pot masura timpul in cadrul functiei pentru ca se va autoapela si voi avea returnati mai multi timpi
//asa ca voi masura timpul in main
void MergeSort(vector<int> &v, int st, int dr)
{

    ///maxim sir de 10^5 numere!!!!!
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

        //la fiecare pas verific daca timpul de rulare sare de 10 minute
        //daca timpul de rulare a sarit de 7 minute, opresc sortarea si afisez mesajul corespunzator
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        if (duration.count()/1000000.00000000000 > 420){
            cout<<"Timpul de rulare pentru SelectionSort este prea mare, s-a oprit sortarea."<<endl;
            return;

        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    if (test_sort(v, n))
        cout<<"SelectionSort a sortat corect numerele in "<<duration.count()/1000000.00000000000 <<" secunde"<< endl;
    else
        cout<<"SelectionSort nu a sortat numerele corect"<<endl;
}

void CountingSort(vector<int> v, int n, int maxx)
{
    auto start = high_resolution_clock::now();

    int size = v.size();
    vector<int> w;
    for (int i = 0 ; i <= maxx; i++) w.push_back(0); //imi creez vectorul de frecventa initializat cu 0
    for (auto it: v) w[it]++; //completez vectorul de frecventa in functie de vectorul dat
    v.clear(); //golesc vectorul ca apoi sa adaug numerele sortate conform vectorului de frecventa
    for (int i = 0; i <= maxx; i++){
        if (w[i]){
            for (int j = 1; j <= w[i]; j++) v.push_back(i);
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    if (test_sort(v, n))
        cout<<"CountingSort a sortat corect numerele in "<<duration.count()/1000000.00000000000 <<" secunde"<< endl;
    else
        cout<<"CountingSort nu a sortat numerele corect"<<endl;

    w.clear(); //sterg vectorul de frecventa
}

//RadixSort doar in baza 10
void RadixSort(vector<int> v, int n){
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

        //la fiecare pas verific daca timpul de rulare sare de 10 minute
        //daca timpul de rulare a sarit de 5 minute, opresc sortarea si afisez mesajul corespunzator
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        if (duration.count()/1000000.00000000000 > 300){
            cout<<"Timpul de rulare pentru SelectionSort este prea mare, s-a oprit sortarea."<<endl;
            return;

        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    if (test_sort(v, n))
        cout<<"RadixSort a sortat corect numerele in "<<duration.count()/1000000.00000000000<<" secunde"<< endl;
    else
        cout<<"RadixSort nu a sortat numerele corect"<<endl;

}

//functia de InsertionSort folosita pentru ShellSort cand ajung la gap = 1
void InsersionSort (vector<int> &v, int n)
{
    for (int i = 1; i < n; i++){
        int elem_curent = v[i];
        int j = i - 1;
        while (j >= 0 and v[j] > elem_curent){
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = elem_curent;
    }
}
void ShellSort (vector<int> v, int n)
{
    auto start = high_resolution_clock::now();
    int gap;
    for (gap = (n - 1) / 2; gap > 1; gap /= 2 ){
        for (int i = 0; i < gap; i ++){
            if (v[i] > v[i+gap]) swap(v[i], v[i+gap]);
        }
        for (int i = 2 * gap; i < n - gap ; i++){
            if ((i + gap < n) and (v[i] > v[i+gap])) swap(v[i], v[i+gap]);
        }

        //la fiecare pas verific daca timpul de rulare sare de 10 minute
        //daca timpul de rulare a sarit de 5 minute, opresc sortarea si afisez mesajul corespunzator
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        if (duration.count()/1000000.00000000000 > 300){
            cout<<"Timpul de rulare pentru ShellSort este prea mare, s-a oprit sortarea."<<endl;
            return;

        }

    }
    if (gap == 1 and !test_sort(v, n)) InsersionSort(v, n); // daca ajung la gap = 1 si vectorul inca nu e sortat, intru in InserstionSort

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    if (test_sort(v, n))
        cout<<"ShellSort a sortat corect numerele in "<<duration.count()/1000000.00000000000 <<" secunde"<< endl;
    else
        cout<<"ShellSort nu a sortat numerele corect"<<endl;
}


int main() {


    int n, maxx, numar_teste;
    vector <int> v;
    fin>>numar_teste;
    for (int i = 1; i <= numar_teste; i++){
        fin>>n>>maxx;
        cout<<"n = "<<n<<" "<<"maxx = "<<maxx<<":"<<endl;
        get_random_vector(v, n, maxx);

        //sortarea nativa
        vector<int> copie;
        for (auto it: v) copie.push_back(it);
        auto start = high_resolution_clock::now();
        sort(copie.begin(), copie.end());
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        if (test_sort(copie, n))
            cout<<"Sortarea nativa a compilatorului a sortat corect numerele in "<<duration.count()/1000000.00000000000 <<" secunde"<< endl;
        else
            cout<<"Sortarea nativa a compilatorului nu a sortat numerele corect"<<endl;
        copie.clear();

        //MergeSort
        for (auto it: v) copie.push_back(it);
        start = high_resolution_clock::now();
        MergeSort(copie, 0 , n-1);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        if (test_sort(copie, n))
            cout<<"MergeSort a sortat corect numerele in "<<duration.count()/1000000.00000000000 <<" secunde"<< endl;
        else
            cout<<"MergeSort nu a sortat numerele corect"<<endl;
        copie.clear();

        //SelectionSort
        if (n >= 1000000)
            cout<<"Sunt prea multe numere pentru a fi sortate folosind SelectionSort. Va dura prea mult."<<endl;
        else
            SelectionSort(v, n);

        //RadixSort si CountingSort
        RadixSort(v, n);
        CountingSort(v, n, maxx+1);

        //ShellSort
        if (n >= 10000000)
            cout<<"Sunt prea multe numere pentru a fi sortate folosind ShellSort. Va dura prea mult."<<endl;
        else
            ShellSort(v, n);

        cout<<endl<<endl;
        v.clear();

    }

    return 0;
}
