#include<iostream>
#include<fstream>
using namespace std;
struct nodo{int info; nodo* next; nodo(int a=0, nodo* b=0){info=a; next=b;}}; // nodo di lista 
struct FIFOX{nodo* primo, *ultimo; int valp, valu,nele; FIFOX(nodo*a=0, int b=0, int c=0, int d=0){primo=a; ultimo=a;valp=b;valu=c;nele=d;}};

ostream & operator<<(ostream & OUT, FIFOX& a)
{
  OUT<< '['<<"nele="<<a.nele<<" valp="<<a.valp<<" valu="<<a.valu<<']'<<endl; 
  int x=0;
  nodo*z=a.primo;
  while(x<a.nele)
  {OUT<<z->info<<' ';z=z->next; x++;}
  OUT<<endl;
  return OUT;
}

FIFOX push_iter(FIFOX a, nodo* w) {
    if(!a.primo) {
        a.primo = a.ultimo = w;
        a.nele = 1;
        a.valp = a.valu = w->info;
        return a;
    }
    if(a.primo->info > w->info) {
        w->next = a.primo;
        a.primo = w;
        a.nele++;
        a.valp = w->info;
        return a;
    }
    if(a.ultimo->info < w->info) {
        a.ultimo->next = w;
        a.ultimo = w;
        a.valu = w->info;
        a.nele++;
        return a;
    }
    nodo* l = a.primo;
    while(l->next) {
        if(w->info > l->info && w->info < l->next->info) {
            nodo* TEMP = l->next;
            w->next = TEMP;
            l->next = w;
            a.nele++;
            return a;
        }
        else {
            l = l->next;
        }
    }
}

nodo* cancella(nodo* A, int x, nodo* &ultimo, bool& presente) {
    if(!A) {
        return 0;
    }
    if(A->info == x) {
        if(!A->next) {
            nodo* w = A;
            A = 0;
            delete(w);
            presente = true;
            return A;
        }
        else {
            nodo* w = A;
            A = A->next;
            delete(w);
            presente = true;
        }
    }
    A->next = cancella(A->next, x, ultimo, presente);
    if(A && !ultimo) {
        ultimo = A;
    }
    return A;    
}

FIFOX deleteX(FIFOX a, int x) {
    if(!a.primo) {
        return a;
    }
    if(a.primo->info > x || a.ultimo->info < x) {
        return a;
    }
    bool presente = false;
    nodo* ultimo = 0;
    a.primo = cancella(a.primo, x, ultimo, presente);
    if(presente) {
        if(ultimo) {
        a.ultimo = ultimo;
        a.nele--;
        a.valu = ultimo->info;
        a.valp = a.primo->info;
        }
        else {
            a.primo = a.ultimo = 0;
            a.nele = 0;
            a.valp = a.valu = 0;
        }
    }
    return a;
}
main()
{
   int dim1,dim2, x;
   
   cin>>dim1>>dim2;
   FIFOX a;
   while(dim1)
   {
   
   cin>>x;
   a=push_iter(a,new nodo(x));
   dim1--;
  }
   cout<< a;

   while(dim2)
   {
     cin>>x;
     a=deleteX(a,x);
     dim2--;
   }
   cout<<a;

   cout<<"end"<<endl;  
}
