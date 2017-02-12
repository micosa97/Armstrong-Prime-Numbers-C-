#include <iostream>
#include <cmath>
#include <algorithm>
#include <ctime>
using namespace std;
clock_t start = clock();
int tab[30]; //elementy od 1-22 to cyfry liczby
int n; //dlugosc liczby jak¹ obecnie rozwa¿amy
int b[30];
int flag=0;
bool isstlilllookingfor=true;

class longerint
{
    public:
    unsigned long long int a;
    unsigned long long int b;
    void mult(long long int x)
    {
        b*=x;
        a*=x;

        a+=b/100000000000000;
        b%=100000000000000;
    };
    void add(longerint x)
    {
        a+=x.a;
        b+=x.b;
        a+=b/100000000000000;
        b%=100000000000000;
    };
    void dadd(longerint x)
    {
        a-=x.a;
        while (x.b>b)
        {
            a--;
            b+=100000000000000;
        }
    b-=x.b;
    a+=b/100000000000000;
    b%=100000000000000;
    };
    int moddiv10()
    {
        int g=b%10;
        b+=(a%10)*100000000000000;
        a/=10;
        b/=10;
        return g;
    };
};

longerint sum3;
longerint pot[11][31];

void ifPrime ()
{
    int u=1000;
    if ((sum3.a==0) and (sum3.b<1000))
    u=sum3.b;
    /*
    longerint u=pot[10][(n+1)/2];

    if ((sum3.a==0) and (sum3.b<u.b))
    u.b=sum3.b;
    */
    if (sum3.b%2==0 and ((sum3.a>0) or (sum3.b>2))) return;
    for (int i=3; (i<u); i+=2)
    {
        if ((((sum3.a)%i)*100000000000000+sum3.b)%i==0) return;
    }
    flag++;
    if (flag==7) isstlilllookingfor=false;
    cout<<" i jest pierwsza ("<<flag<<")";
}

void show(longerint s)
{
    int z[40];
    //cout<<endl<<" ["<<(clock() - start)/60000000<<":"<<((clock() - start)/1000000)%60<<":"<<(clock() - start)%1000000<<"] ";
    for (int i=0; i<40; i++)
    {
        z[i]=s.moddiv10();
    }
    bool did=false;
    for (int i=39; i>=0; i--)
    {
        if (z[i]!=0) did=true;
        if (did) cout<<z[i];
    }
    cout<<" jest liczba Armstronga";
    ifPrime();
    cout<<endl;

};

inline bool comp(longerint &x, longerint &y)
    {
        if (x.a==y.a)
        {
            if (x.b>y.b) return true;
            if (x.b<y.b) return false;
        }
        if (x.a>y.a) return true;
        return false;

    };

void sorting () //procedura sortuje cyfry sumy. Jeœ³i te pokrywaj¹ siê z multopodbiorem wygererowanym, to nieposortowana liczba sumy to nasza cyf arm
{
    longerint a=sum3;
    for (int i=n; i>=1; i--)
    {
        b[i]=a.moddiv10();
    }

    sort(&b[1], &b[n+1]);
    bool czy=false;
    for (int i=1; i<=n; i++)
    {
        if (b[i]!=tab[i]) {czy=true; break;}
    }
    if ((!czy)  and (comp(sum3,pot[10][n-1]))) show(sum3);//cout<<sum3.a<<" "<<sum3.b<<endl; //lse N
};
void filling (int pos) //pos to element, na ktorym zaczynamy wypelnianie. Wypisuje to wszytskie multipodzbiory
{
    if (pos == n+1)
    {
        if (isstlilllookingfor)
        sorting();

    } else
    for (int i=tab[pos-1]; i<=9; i++)
    {
        tab[pos]=i;
        sum3.add(pot[i][n]);
        if (comp(pot[10][n], sum3))
        {
            filling(pos+1);
        }
        //h:
        sum3.dadd(pot[i][n]);
    }



}

int main()
{

//h:
    for(int i=0; i<=10; i++)
        for(int i2=0; i2<=30; i2++)
        {
                if (i2==0)
                 {
                     pot[i][i2].a=0;
                     pot[i][i2].b=1;
                 }
                else
                {
                    pot[i][i2]=pot[i][i2-1];
                    pot[i][i2].mult(i);
                }


        }
    for (int p=0; p<30; p++)
    tab[p]=0;
    for (n=1; flag<7; n++)
        filling(1);
   // cout<<" ["<<(clock() - start);


}
