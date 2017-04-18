#include <iostream>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <vector>
#include <limits.h>

using namespace std;

struct text{
    string cuvant;
    float x,y,w,h;
};

struct temp{
    int id;
    string ct; float pt;
    string cr; float pr;
    string cb; float pb;
    string cl; float pl;
};

ostream& operator<<(ostream& os, const text& a)
{
    os << a.cuvant << " " << a.x << " " << a.y << " " << a.w << " " << a.h <<endl;
    return os;
}

ostream& operator<<(ostream& os, const temp& a)
{
    os << a.id << " " << a.ct << " " << a.pt << " " << a.cr << " " << a.pr << " " << a.cb << " " <<a.pb << " " << a.cl << " " << a.pl<<endl;
    return os;
}

istream& operator>>(istream& is, text& a)
{
    is >> a.cuvant >> a.x >> a.y >> a.w >> a.h;
    return is;
}

istream& operator>>(istream& is, temp& a)
{
    is >> a.id;
    is >> a.ct;
    if(a.ct != "-")
        is >> a.pt;
    else
        a.pt = 0;

    is >> a.cr;
    if(a.cr != "-")
        is >> a.pr;
    else
        a.pr = 0;

    is >> a.cb;
    if(a.cb != "-")
        is >> a.pb;
    else
        a.pb = 0;

    is >> a.cl;
    if(a.cl != "-")
        is >> a.pl;
    else
        a.pl = 0;

    return is;
}

//true -> imi afla elementul de deasupra. false-> imi afla elementul de jos
text element_sus_jos(vector<text>& a, const text& b, bool ok)
{
    if(ok == true){
        int poz = 0;
        int minim = INT_MAX;

        for(int i=0;i<a.size();i++)
            if (minim > a[i].y && a[i].y > b.y && a[i].x == b.x){
                poz = i;
                minim = a[i].y;
        }
        return a[poz];
    }
    else{
        int poz = 0;
        int minim = INT_MAX;
        int dif = INT_MAX;

        for(int i=0;i<a.size();i++){
            if(a[i].y < b.y && a[i].x == b.x){
                minim = abs(b.y - a[i].y);
                if(dif > minim && dif != 0){
                    poz = i;
                    dif = minim;
                }
            }
        }
        return a[poz];
    }
}

//true -> imi afla elementul din dreapta. false-> imi afla elementul din stanga
text element_dreapta_stanga(vector<text>& a, const text& b, bool ok)
{
    if(ok == true){
        int poz = 0;
        int minim = INT_MAX;
        int dif = INT_MAX;

        for (int i=0;i<a.size();i++){
            if(a[i].x > b.x && a[i].y == b.y){
                minim = abs(b.x - a[i].x);
                if(dif > minim && dif != 0){
                    poz = i;
                    dif = minim;
                }
            }
        }
        return a[poz];
    }
    else{
        int poz = 0;
        int minim = INT_MAX;
        int dif = INT_MAX;

        for(int i=0;i<a.size();i++){
            if(a[i].x < b.x && a[i].y == b.y){
                minim = abs(b.x - a[i].x); //modulul trebuie sa fie minim
                if(dif > minim && dif != 0){
                    poz = i;
                    dif = minim;
                }
            }
        }
        return a[poz];
    }
}


void afisare_vector_text(const vector<text>& a)
{
    vector<text>::const_iterator it;
    for(it=a.begin();it!=a.end();++it)
        cout<<*it;
    cout<<endl;
}

void afisare_vector_temp(const vector<temp>& a)
{
    vector<temp>::const_iterator it;
    for(it=a.begin();it!=a.end();++it)
        cout<<*it;
    cout<<endl;
}

//ID-ul cu suma maxima
int aflare_ID(text* sus, text* dreapta, text* jos, text* stanga, vector<temp>& a)
{
    float poz;
    float maxim = 0, maxx = 0; //folosesc 2 maxim-uri pentru a putea compara

    for(int i=0;i<a.size();i++){
        if (sus != NULL) //daca am element deasupra
            if(a[i].ct == sus->cuvant)
                if(maxim < a[i].pt)
                    maxim = a[i].pt;
        if(dreapta != NULL) //daca am element in dreapta
            if(a[i].cr == dreapta->cuvant)
                if(maxim < a[i].pr)
                    maxim = a[i].pr;

        if(jos != NULL) //daca am element jos
            if(a[i].cb == jos->cuvant)
                if(maxim < a[i].pb)
                    maxim = a[i].pb;

        if(stanga != NULL) //daca am element in stanga
            if(a[i].cl == stanga->cuvant)
                if(maxim < a[i].pl)
                    maxim = a[i].pl;

        if(maxim > maxx){
            maxx = maxim;
            poz = i+1;//ID-ul este cu o unitate mai mare decat numarul template-ului
        }
    }
    return poz;
}

int main()
{
    int n; //numar cuvinte
    ifstream f("input2.txt");

    vector<text> vector_cuvinte;
    vector<temp> vector_template;

    f>>n;

    for(int i=2;i<=n+1;i++){
        text a;
        f>>a;

        vector_cuvinte.push_back(a);
    }

    int t; //numar template-uri
    f>>t;

    for(int i=n+3;i<n+t+3;i++){

        temp a;
        f>>a;

        vector_template.push_back(a);
    }

    afisare_vector_text(vector_cuvinte);
    afisare_vector_temp(vector_template);

    int indice;
    f>>indice;
    text prelucrare = vector_cuvinte[indice];

    text sus = element_sus_jos(vector_cuvinte,prelucrare,true);
    text dreapta = element_dreapta_stanga(vector_cuvinte,prelucrare,true);
    text jos = element_sus_jos(vector_cuvinte,prelucrare,false);
    text stanga = element_dreapta_stanga(vector_cuvinte,prelucrare,false);

    auto el = aflare_ID(&sus,&dreapta,&jos,&stanga,vector_template);
    cout<<el;

    return 0;
}
