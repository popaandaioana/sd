#include <iostream>
#include <fstream>
#include <ctime>
#include <stdlib.h>
#include <algorithm>
using namespace std;

void generare_vector(long long int &n, long long int &maxim, long long int *p)
{
    long long int i;
    srand(time(NULL));
    for(i=0; i<n; i++)
        *(p+i)=rand()%(maxim+1);
}

int test_sort(long long int *p, clock_t start, long long int n, clock_t curent)
{
    long long int i=0;
    if((double)(curent-start)/CLOCKS_PER_SEC>=30)
        return 0;
    else
        while(i<=n-2)
        {
            if(*(p+i)>*(p+i+1))
                return 0;
            i++;
        }
    return 1;
}

void bubblesort(long long int *p,long long int n, clock_t start, clock_t &curent)
{
    long long int m,aux,k,i;
    bool sortat;
    m=n-1;
    do
    {
        sortat=true;
        k=m;
        for(i=0; i<k; i++)
            if(*(p+i)>*(p+i+1))
            {
                aux=*(p+i);
                *(p+i)=*(p+i+1);
                *(p+i+1)=aux;
                sortat=false;
                m=i;
            }
        curent = clock();
    }
    while(!sortat && (double)(curent-start)/CLOCKS_PER_SEC<30);
}


void countsort(long long int *p,long long int n, clock_t start, clock_t &curent)
{
    long long int i,*k,*b,j;
    curent=clock();
    k=new long long int[n];
    b=new long long int[n];
    for(i=0;i<n;i++)
        *(k+i)=0;
    for(i=0;i<n-1 && (double)(curent-start)/CLOCKS_PER_SEC<30;i++)
    {
        for(j=i+1;j<n && (double)(curent-start)/CLOCKS_PER_SEC<30;j++)
        {
            if(*(p+i)>*(p+j))
                (*(k+i))++;
            else
                (*(k+j))++;
            curent=clock();
        }
    }
    if((double)(curent-start)/CLOCKS_PER_SEC<30)
    {
        for(i=0;i<n && (double)(curent-start)/CLOCKS_PER_SEC<30;i++)
        {
            curent=clock();
            *(b+*(k+i))=*(p+i);
        }
        for(i=0;i<n && (double)(curent-start)/CLOCKS_PER_SEC<30;i++)
        {
            curent=clock();
            p[i]=b[i];
        }
    }
    delete []k;
    delete []b;
}

void mergesort(long long int *p, long long int n, long long int st, long long int dr, clock_t start,clock_t &curent)
{
    long long int *tmp;
    curent=clock();
    tmp=new long long int[n];
    if(st < dr)
	{
		long long int m = (st + dr) / 2;
		mergesort(p,m-st+1, st , m,start,curent);
        mergesort(p,dr-m, m + 1 , dr,start,curent);
		//Interclasare
		long long int i = st, j = m + 1, k = -1;
		while( i <= m && j <= dr && (double)(curent-start)/CLOCKS_PER_SEC<30)
			{
            if(*(p+i) < *(p+j))
				{
				    k++;
				    *(tmp+k)=*(p+i);
				    i++;
				}
			else
				{
				    k++;
				    *(tmp+k)=*(p+j);
				    j++;
				}
            curent=clock();
			}
		while(i <= m)
                {
				    k++;
				    *(tmp+k)=*(p+i);
				    i++;
				}
		while(j <= dr)
                {
				    k++;
				    *(tmp+k)=*(p+j);
				    j++;
				}
		for(i = st , j = 0 ; i <= dr ; i ++ , j ++)
			*(p+i) = *(tmp+j);
	}
	delete []tmp;
}

void quicksort(long long int *p, long long int n, long long int st, long long int dr, clock_t start,clock_t &curent)
{
    long long int aux,pivot,x,y,z;
    if(st < dr)
    {
        //pivotul este mediana din 3

        srand(time(NULL));
        x=(rand()%(dr-st+1))+st;
        srand(time(NULL));
        y=(rand()%(dr-st+1))+st;
        srand(time(NULL));
        z=(rand()%(dr-st+1))+st;
        if(p[x]<=p[y]&&p[y]<=p[z]|| p[z]<=p[y] && p[z]<=p[x])
            pivot=p[y];
        if(p[x]<=p[z]&&p[z]<=p[y]|| p[y]<=p[z] && p[z]<=p[x])
            pivot=p[z];
        if(p[y]<=p[x]&&p[x]<=p[z]|| p[z]<=p[x] && p[x]<=p[y])
            pivot=p[x];


	    aux=pivot;
		long long int m = (st + dr) / 2;
		pivot = p[m];
		p[m] = aux;
		long long int i = st , j = dr, d = 0;
		curent=clock();
		while(i < j && (double)(curent-start)/CLOCKS_PER_SEC<30)
		{
			if(p[i] > p[j])
			{
				aux = p[i];
				p[i] = p[j];
				p[j] = aux;
				d = 1 - d;
			}
			i += d;
			j -= 1 - d;
		}
		curent=clock();
		quicksort(p,i-st, st , i - 1,start,curent);
		quicksort(p,dr-i, i + 1 , dr,start,curent);
	}
}

void count_sort_radix(long long int *p, long long int n, int exp, int radix)
{
    long long int *output, i, *cnt;
    int d;
    output=new long long int[n];
    cnt=new long long int[radix];
    for(i=0;i<radix;i++)
        cnt[i]=0;
    for(i=0;i<n;i++)
    {
        cnt[(p[i]/exp)%radix]++;
    }
    for(i=1;i<radix;i++)
        cnt[i]+=cnt[i-1];
    for(i=n-1;i>=0;i--)
    {
        d=(p[i]/exp)%radix;
        output[cnt[d]-1]=p[i];
        cnt[d]--;
    }
    for(i=0;i<n;i++)
        p[i]=output[i];
    delete []output;
    delete []cnt;
}

long long int get_max(long long int *p, long long int n)
{
    long long int x=-1;
    for(long long int i=0;i<n;i++)
        if(x<p[i])
            x=p[i];
    return x;
}

void radixsort(long long int *p,long long int n, int radix, clock_t start, clock_t &curent)
{
    long long int maxx=get_max(p, n);
    curent=clock();
    for(int exp=1;maxx/exp>0 && (double)(curent-start)/CLOCKS_PER_SEC<30;exp*=radix)
    {
        count_sort_radix(p,n,exp,radix);
        curent=clock();
    }
}

int main()
{
    long long int i,t,n,*p,*copie,maxim;
    clock_t start, stop, curent;
    ifstream f("teste.in");
    ofstream g("timpi.out");
    f>>t;
    for(i=1; i<=t; i++)
    {
        f>>n>>maxim;
        g<<n<<" numere <= "<<maxim<<endl;
        p=new long long int[n];
        if(p==NULL)
            g<<"nu pot aloca memorie pentru numere"<<endl;
        else
        {
            generare_vector(n,maxim,p);

            copie=p;
            //--------------------metoda bubblesort-------------------------------------
            start = clock();
            bubblesort(copie,n, start, curent);
            stop = clock();
            if(test_sort(copie, start, n, curent))
                g<<"bubblesort: "<<(double)(stop-start)/CLOCKS_PER_SEC << " secunde : vector sortat";
            else
                g<<"bubblesort: "<<"timp depasit : vector nesortat";
            g<<endl;
           //--------------------metoda countsort-------------------------------------
           copie=p;
           start = clock();
           countsort(copie,n, start, curent);
           stop = clock();
           if(test_sort(copie, start, n, curent))
               g<<"countsort: "<<(double)(stop-start)/CLOCKS_PER_SEC << " secunde : vector sortat";
           else
               g<<"countsort: "<<"timp depasit : vector nesortat";
           g<<endl;
           //--------------------metoda mergesort-------------------------------------
           copie=p;
           start = clock();
           mergesort(copie,n,0,n-1,start,curent);
           stop = clock();
           if(test_sort(copie, start, n, curent))
               g<<"mergesort: "<<(double)(stop-start)/CLOCKS_PER_SEC << " secunde : vector sortat";
           else
               g<<"mergesort: "<<"timp depasit : vector nesortat";
           g<<endl;
           //--------------------metoda quicksort-------------------------------------
           copie=p;
           start = clock();
           quicksort(copie,n,0,n-1,start,curent);
           stop = clock();
           if(test_sort(copie, start, n, curent))
               g<<"quicksort: "<<(double)(stop-start)/CLOCKS_PER_SEC << " secunde : vector sortat";
           else
               g<<"quicksort: "<<"timp depasit : vector nesortat";
           g<<endl;
           //--------------------metoda radix8-------------------------------------
           copie=p;
           start = clock();
           radixsort(copie,n,8, start, curent);
           stop = clock();
           if(test_sort(copie, start, n, curent))
               g<<"radixsort8: "<<(double)(stop-start)/CLOCKS_PER_SEC << " secunde : vector sortat";
           else
               g<<"radixsort8: "<<"timp depasit : vector nesortat";
           g<<endl;
           //--------------------metoda radix256-------------------------------------
           copie=p;
           start = clock();
           radixsort(copie,n,256, start, curent);
           stop = clock();
           if(test_sort(copie, start, n, curent))
               g<<"radixsort256: "<<(double)(stop-start)/CLOCKS_PER_SEC << " secunde : vector sortat";
           else
               g<<"radixsort256: "<<"timp depasit : vector nesortat";
           g<<endl;
           //--------------------metoda nativa-------------------------------------
           copie=p;
           start = clock();
           sort(copie,copie+n);
           stop = clock();
           if(test_sort(copie, start, n, curent))
               g<<"nativsort: "<<(double)(stop-start)/CLOCKS_PER_SEC << " secunde : vector sortat";
           else
               g<<"nativsort: "<<"timp depasit : vector nesortat";
           g<<endl;
        }
        delete []p;
    }

    f.close();
    g.close();
    return 0;
}

