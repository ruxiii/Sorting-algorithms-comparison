#include <iostream>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

ifstream fin("date.in");

int baza, t;

void CountingSort(int v[], int n)
{
    int*b;
    b=new int[n];
    int*c;
    c=new int[n];
    int i, j;
    for(i=0; i<n; i++)
        b[i]=0;
    for(i=0; i<n; i++)
        c[i]=v[i];
    for(i=1; i<n; i++)
        for(j=0; j<i; j++)
            if(c[j]<c[i])
                b[i]++;
            else
                b[j]++;
    for(i=0; i<n; i++)
        v[b[i]]=c[i];
}

void Mergesort(int v[], int stanga, int dreapta, int nou[])
{
    if(stanga<dreapta)
    {
        int m=stanga+(dreapta-stanga)/2;
        Mergesort(v, stanga, m, nou);
        Mergesort(v, m+1, dreapta, nou);
        int i=stanga, j=m+1, contor=0;
        while(i<=m && j<=dreapta)
        {
            if(v[i]<v[j])
                nou[++contor]=v[i++];
            else
                nou[++contor]=v[j++];
        }
        while(i<=m)
            nou[++contor]=v[i++];
        while(j<=dreapta)
            nou[++contor]=v[j++];
        j=1;
        for(i=stanga; i<=dreapta; i++)
        {
            v[i]=nou[j];
            j++;
        }
    }
}

void Quicksort(int v[], int stanga, int dreapta)
{
    if(stanga<dreapta)
    {
        int m=(stanga+dreapta)/2;
        swap(v[stanga], v[m]);
        int i=stanga, j=dreapta, k=0;
        while(i<j)
        {
            if(v[i]>v[j])
            {
                swap(v[i], v[j]);
                k=1-k;
            }
            i=i+k;
            j=j-1+k;
        }
        Quicksort(v, stanga, i-1);
        Quicksort(v, i+1, dreapta);
    }
}

int maxim(int v[], int n)
{
    int i, mx=v[0];
    for(i=1; i<n; i++)
        if(v[i]>mx)
            mx=v[i];
    return mx;
}

void Counting(int v[], int n, int exp, int baz)
{
    int i;
    int *b;
    b=new int[n];
    int c[10]={0};
    for(i=0; i<n; i++)
        c[(v[i]/exp)%baz]++;
    for(i=1; i<10; i++)
        c[i]=c[i]+c[i-1];
    for(i=n-1; i>=0; i--)
    {
        b[c[(v[i]/exp)%baz]-1]=v[i];
        c[(v[i]/exp)%baz]--;
    }
    for(i=0; i<n; i++)
        v[i]=b[i];
}

void RadixSort(int v[], int n, int b)
{
    int i, m=maxim(v, n);
    for(i=1; m/i>0; i=i*b)
        Counting(v, n, i, b);
}

void ShellSort(int v[], int n)
{
    int i=n/2, j, k, curent;
    while(i>0)
    {
        j=i;
        while(j<n)
        {
            curent=v[j];
            for(k=j; k>=i && v[k-i]>curent; k=k-i)
                v[k]=v[k-i];
            v[k]=curent;
            j++;
        }
        i=i/2;
    }
}

void Sorting(int v[], int n)
{
    sort(v,v+n);
}

void Sortari(int N, int NMAX, int v[])
{
    int i;
    int *copie;
    copie=new int[N];
    for(i=0;i<N;i++)
        copie[i]=v[i];

    auto start6 = std::chrono::steady_clock::now();
    CountingSort(v,N);
    auto end6 = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds6 = end6-start6;
    std::cout << "CountingSort: " << elapsed_seconds6.count() << "s\n";


    for(i=0;i<N;i++)
        v[i]=copie[i];
    int *nou;
    nou=new int[N+1];
    auto start1 = std::chrono::steady_clock::now();
    Mergesort(v, 0, N-1, nou);
    auto end1 = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds1 = end1-start1;
    std::cout << "MergeSort: " << elapsed_seconds1.count() << "s\n";

    for(i=0;i<N;i++)
        v[i]=copie[i];
    auto start2 = std::chrono::steady_clock::now();
    Quicksort(v, 0, N-1);
    auto end2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds2 = end2-start2;
    std::cout << "QuickSort: " << elapsed_seconds2.count() << "s\n";

    for(i=0;i<N;i++)
        v[i]=copie[i];
    auto start3 = std::chrono::steady_clock::now();
    RadixSort(v, N, baza);
    auto end3 = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds3 = end3-start3;
    std::cout << "RadixSort: " << elapsed_seconds3.count() << "s\n";

    for(i=0;i<N;i++)
        v[i]=copie[i];
    auto start4 = std::chrono::steady_clock::now();
    ShellSort(v,N);
    auto end4 = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds4 = end4-start4;
    std::cout << "ShellSort: " << elapsed_seconds4.count() << "s\n";

    for(i=0;i<N;i++)
        v[i]=copie[i];
    auto start5 = std::chrono::steady_clock::now();
    Sorting(v, N);
    auto end5 = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds5 = end5-start5;
    std::cout << "Sort: " << elapsed_seconds5.count() << "s\n";
    cout<<'\n';
}

void Generare(int lungime, int maxim)
{
    int i;
    int *v;
    v=new int[lungime];
    srand((unsigned)time(NULL));
    for (i = 0; i < lungime; i++)
        v[i] = rand() % maxim;
    Sortari(lungime,maxim,v);
}

void Teste(int nr_teste)
{
    int N, NMAX;
    for (int i = 1; i <= nr_teste; i++)
    {
        fin>>N>>NMAX;
        cout << "Pentru testul " << i << " avem:" << '\n';
        cout << "N = " << N << "  NMAX = " << NMAX << '\n';
        Generare(N,NMAX);
    }
}

int main()
{
    cin>>baza>>t;
    Teste(t);
    return 0;
}


