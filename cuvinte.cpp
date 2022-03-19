#include <iostream>
#include <string>
#include <stdlib.h>
#include <chrono>
using namespace std;

//declaratie functii
char genereazaCaracter(int);
string genereazaPropozitie(int, int &, int *);
int numaraGreseli(string, string, int *);

int main() {
    // declaratie variabile
    using Clock = std::chrono::high_resolution_clock;
    using Seconds = std::chrono::seconds;
    srand(time(NULL));
    int nrCuvinte, greseli = 0, aparitiiGreseli[26];
    float medieAr;
    string cuvinteUser, propozitie, raspuns;
    //initializare vector
    for (int i = 0; i < 26; i++) {
        aparitiiGreseli[i] = 0;
    }

    do { 
        //definire variabile
        cuvinteUser = "";
        propozitie = "";
        raspuns = "";
        nrCuvinte = rand() % 5 + 1;
        
        cout << "Incercati sa va antrenati viteza si acuratetea folosind urmatorul sir de caractere generate:" << endl;

        //generare propozitie
        propozitie = genereazaPropozitie(nrCuvinte, greseli, aparitiiGreseli);

        //calcul medie aritmetica a caracterelor cuvintelor
        medieAr = propozitie.length() / nrCuvinte;

        cout << propozitie << endl;
        cout << "Randul dumneavoastra:" << endl;

        // pornesc cronometrul in momentul in care i-a fost afisata propozitia utilizatorului
        auto start = Clock::now();
        getline(cin, cuvinteUser);
        auto end = Clock::now();

        // la final se face diferenta dintre timpul de final si start si se ofera un raspuns in secunde
        Seconds duration_sec = std::chrono::duration_cast<Seconds>(end - start);

        // se contorizeaza numarul de greseli
        greseli = numaraGreseli(propozitie, cuvinteUser, aparitiiGreseli);

        cout << "Ati avut " << greseli << " greseli!" << endl;
        cout << "Timp: " << duration_sec.count() << " secunde. (" << cuvinteUser.length() / ((float)duration_sec.count() / 60) << " cpm sau "; 
        cout << ((float)cuvinteUser.length() / medieAr) / ((float)duration_sec.count() / 60) << " cuvinte/min)" << endl;
        cout << "Doriti sa mai incercati, apasati D/N?" << endl;
        getline(cin, raspuns);
    } while (raspuns == "D");
}

char genereazaCaracter(int pozitie){
    if (rand() % 2 == 0) {
        return 'A' + pozitie;
    } else {
        return 'a' + pozitie;
    }
}

string genereazaPropozitie(int nrCuvinte, int &greseli, int * aparitiiGreseli) {
    string propozitie = ""; 
    int nrCarac;
    while (nrCuvinte--) {
        nrCarac = rand() % 10 + 1;
        for (int i = 0; i < nrCarac; i++) {
            if (greseli != 0) {
                for (int j = 0; j < 26; j++) {
                    if (aparitiiGreseli[j] != 0)
                    {
                        propozitie += genereazaCaracter(j);
                        aparitiiGreseli[j]--;
                        greseli--;
                        break;
                    }
                }
            } else {
                propozitie += genereazaCaracter(rand() % 26);
            }
        }
        if (nrCuvinte != 0)
        {
            propozitie += " ";
        }
    }
    return propozitie;
}

int numaraGreseli(string propozitie, string cuvinteUser, int *aparitiiGreseli)
{
    int i = 0, greseli = 0;
    while (i < propozitie.length() && i < cuvinteUser.length())
    {
        if (propozitie[i] != cuvinteUser[i])
        {
            greseli++;
            if ('A' <= cuvinteUser[i] && cuvinteUser[i] <= 'Z')
            {
                aparitiiGreseli[cuvinteUser[i] - 'A']++;
            }
            if ('a' <= cuvinteUser[i] && cuvinteUser[i] <= 'z')
            {
                aparitiiGreseli[cuvinteUser[i] - 'a']++;
            }
        }
        i = i + 1;
    }
    return greseli + abs((int)(propozitie.length() - cuvinteUser.length()));
}