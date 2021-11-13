#include <iostream>
#include <string>
#include <utility>
#define KAP 1000


using namespace std;


template<typename Tip1, typename Tip2>

class Mapa
{
public:
    Mapa() {};
    virtual ~Mapa() {};
    virtual Tip2& operator[](const Tip1& kljuc)=0;
    virtual const Tip2& operator[](const Tip1& kljuc)const=0;
    virtual int brojElemenata()const=0;
    virtual void obrisi()=0;
    virtual void obrisi(const Tip1& kljuc)=0;
};



template<typename Tip1, typename Tip2>
class NizMapa: public Mapa<Tip1, Tip2>
{
    int br_elemenata, kapacitet;
    Tip2 p;
    std::pair<Tip1, Tip2>*niz=nullptr;



    void povecaj()
    {
        kapacitet*=2;
        std::pair<Tip1,Tip2>*pomocni=new std::pair<Tip1,Tip2>[kapacitet];
        for(int i=0; i<br_elemenata; i++) {
            pomocni[i].first=niz[i].first;
            pomocni[i].second=niz[i].second;
        }
        delete[]niz;
        niz=pomocni;
        pomocni=nullptr;
    }
public:

    NizMapa():kapacitet(KAP),br_elemenata(0), niz(new std::pair<Tip1,Tip2>[kapacitet]),p(Tip2()) {}
    ~NizMapa()
    {
        delete []niz;
    }

    NizMapa(const NizMapa<Tip1, Tip2>&nm): kapacitet(nm.kapacitet),br_elemenata(nm.br_elemenata), niz(new std::pair<Tip1,Tip2>[kapacitet])
    {
        for(int i=0; i<br_elemenata; i++) {
            niz[i].first=nm.niz[i].first;
            niz[i].second=nm.niz[i].second;
        }
    }

    NizMapa<Tip1, Tip2>&operator=(const NizMapa<Tip1,Tip2>&nm)
    {
        if(this==&nm) return *this;
        delete[] niz;
        kapacitet=nm.kapacitet;
        br_elemenata=nm.br_elemenata;
        niz=new std::pair<Tip1,Tip2>[kapacitet];

        for(int i=0; i<br_elemenata; i++) {
            niz[i].first=nm.niz[i].first;
            niz[i].second=nm.niz[i].second;
        }
        return *this;
    }

    Tip2& operator[](const Tip1 &kljuc)
    {
        for(int i=0; i<br_elemenata; i++) {
            if(niz[i].first==kljuc) return niz[i].second;
        }

        if(br_elemenata==kapacitet) povecaj();
        niz[br_elemenata]=std::pair<Tip1,Tip2>(kljuc,Tip2());
        return niz[br_elemenata++].second;
    }

    const Tip2& operator[](const Tip1& kljuc)const
    {
        for(int i=0; i<br_elemenata; i++) {
            if(niz[i].first==kljuc) return niz[i].second;
        }
        return p;
    }

    int brojElemenata()const
    {
        return br_elemenata;
    }


   
    void obrisi(const Tip1 &kljuc)
    {
        for(int i=0; i<br_elemenata; i++) {
            if(niz[i].first==kljuc) {
                niz[i].first=niz[br_elemenata-1].first;
                niz[i].second=niz[br_elemenata-1].second;
                br_elemenata--;
                return;
            }
        }
        throw("Nije pronadjen element\n");
    }




    void obrisi()
    {
        br_elemenata=0;
    }
};




//testiranje NizMape
bool test1()
{
    NizMapa<string,string> nm;
    nm["skahvedzic1"]="Selma Kahvedžić";
    return (nm.brojElemenata()==1);
}

bool test2()
{
    NizMapa<int,int> nm;
    for(int i=0; i<4; i++) {
        nm[i]=i;
    }
    nm.obrisi(3);
    return nm.brojElemenata()==3;
}

bool test3()
{
    NizMapa<string,double> nm;
    nm["dm_z1"]=3.03;
    nm["dm_z2"]=5.00;
    nm["dm_z3"]=5.00;
    return (nm["dm_z3"]-5.00)<0.0001;
}

bool test4()
{
    NizMapa<int,char> nm;
    for(int i=0; i<5; i++) {
        nm[i]=(char)i;
    }
    nm.obrisi();
    return nm.brojElemenata()==0;
}

bool test5()
{
    NizMapa<string, string> nm;
    nm["skahvedzic1"]="Selma Kahvedžić";
    nm["skahvedzic1"]="Selma Kahvedžić";
    NizMapa<string,string> nm1(nm);
    return nm1.brojElemenata()==2;
}


int main()
{

    NizMapa<std::string, std::string>glavni_gradovi;
    glavni_gradovi["Bosna i Hercegovina"]="Sarajevo";
    glavni_gradovi["Hrvatska"]="Zagreb";
    glavni_gradovi["Srbija"]="Beograd";

    std::cout << "Pripremna Zadaca Za Vjezbu 7, Zadatak 1";
    return 0;
}
