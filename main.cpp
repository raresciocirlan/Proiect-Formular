#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <vector>
#include <fstream>

using namespace std;

void setConsoleTextColor(int color) 
{
    HANDLE stdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    if (stdOutput != INVALID_HANDLE_VALUE)
        SetConsoleTextAttribute(stdOutput, color);
}

class Formular 
{
private:
    string nume, prenume, liceu;
    int varsta;
    float medie_bac;

public:
   friend ostream& operator<<(ostream& str, Formular& form);
   friend istream& operator>>(istream& str, Formular& form);
   friend ofstream& operator<<(ofstream& str, Formular& form);
   friend ifstream& operator>>(ifstream& str, Formular& form);

};

ostream& operator<<(ostream& str, Formular& form)
{
   str << "\n\n\n";
   str << "Formularul curent:\n";
   str << "Nume: " << form.nume << endl;
   str << "Prenume: " << form.prenume << endl;
   str << "Varsta: " << form.varsta << endl;
   str << "Liceul absolvit: " << form.liceu << endl;
   str << "Media bac: " << form.medie_bac << endl;
   return str;
}

istream& operator>>(istream& str, Formular& form)
{
   cout << "Nume: ";
   str >> form.nume;
   cout << "Prenume: ";
   str >> form.prenume;
   cout << "Varsta: ";
   str >> form.varsta;
   cout <<"Liceul Absolvit: ";
   cin.ignore();
   getline(str,form.liceu,'\n');
   cout << "Media bac: ";
   str >> form.medie_bac;
   return str;
}

ofstream& operator<<(ofstream& str, Formular& form) 
{
        str << "----------------\n";
        str << "Nume: " << form.nume;
        str << "\n";
        str << "Prenume: " << form.prenume;
        str << "\n";
        str << "Varsta: " << form.varsta;
        str << "\n";
        str << "Liceul absolvit: " << form.liceu;
        str << "\n";
        str << "Media bac: " << form.medie_bac;
        str << "\n";
        str << "----------------\n\n";
       return str;
}

ifstream& operator>>(ifstream& str, Formular& form) 
{
        str >> form.nume >> form.prenume >> form.varsta >> form.liceu >> form.medie_bac;
        return str;
}

void meniu_principal() 
{
    setConsoleTextColor(3);
     cout <<"\n\n\t\t\t ██████  ██    ██ ███    ██     ██    ██ ███████ ███    ██ ██ ████████ ██ \n"
               "\t\t\t ██   ██ ██    ██ ████   ██     ██    ██ ██      ████   ██ ██    ██    ██ \n"
               "\t\t\t ██████  ██    ██ ██ ██  ██     ██    ██ █████   ██ ██  ██ ██    ██    ██ \n"
               "\t\t\t ██   ██ ██    ██ ██  ██ ██      ██  ██  ██      ██  ██ ██ ██    ██       \n"
               "\t\t\t ██████   ██████  ██   ████       ████   ███████ ██   ████ ██    ██    ██ \n"
           "\t\t\t                                                                         \n\n\n";

    setConsoleTextColor(7);

    cout <<"Selectati una dintre cele 4 optiuni: \n\n";
    cout <<"    1. Creare formular \n";
    cout <<"    2. Aplicare Universitate \n";
    cout <<"    3. Vizualizare formulare \n";
    cout <<"    4. Statistici \n";
    cout <<"\n";
    cout << "Optiunea aleasa este: ";
}

void citire_statistica(vector <int>& stat) 
{
    ifstream f("statistici.txt");

    int nr;
    while(f >> nr)
        stat.push_back(nr);

    f.close();
}

int main()
{
    int nr;
    double MeniuCurent = 0;
    system("chcp 65001 > nul");
    Formular form;
    vector <int> statistica;

    citire_statistica(statistica);
    meniu_principal();
    while(1) 
    {
        cin >> nr;
        system("CLS");
        switch(nr) 
        {
            case 1:
            if(MeniuCurent == 0)
            {
                MeniuCurent = 1.1;
                Formular form;
                cout << "Formular pentru inscriere\n\n";
                cin >> form;

                ofstream scriere("formular.txt");
                scriere << form;
                scriere.close();

                ofstream scriere2("formulare.txt", ios::app);
                scriere2 << form;
                scriere2.close();

                cout << "\nFormularul completat cu succes. \nVa rugam sa asteptati cateva secunde ca sa puteti fi introdus in baza de date...";
                Sleep(3000);
                system("CLS");
                MeniuCurent = 0;
                meniu_principal();
            } else {
                cout << "Caracter introdus gresit";
                Sleep(1500);
                system("CLS");
                MeniuCurent = 0;
                meniu_principal();
                }
                break;
            case 2:
            if (MeniuCurent == 0)
            {
                MeniuCurent = 2.1;
                cout << "Alegeti universitatea: \n\n";
                string u;
                ifstream citesteuniv("universitati/universitati.txt");
                
                while (getline(citesteuniv, u)) 
                {
                    cout << u << endl;
                }
                citesteuniv.close();

                cout << "\nOptiunea aleasa este: ";
                cin >> nr;

                if (nr == 1) 
                {
                    cout << "\nAlegeti facultatea: \n\n";
                    string f;
                    ifstream citestefac("universitati/facultati/facultati.txt");

                    getline (citestefac, f);
                    cout << f << endl;

                    citestefac.close();

                    cout << "\nOptiunea aleasa este: ";
                    cin >> nr;
                    
                    if (nr == 1) 
                    {
                        cout << "\nAlegeti specializarea: \n\n";
                        string s;
                        ifstream citestespec("universitati/facultati/specializari/s1.txt");

                        while (getline (citestespec, s)) 
                        {
                            cout << s << endl;
                        }
                        citestespec.close();
                        cout << "\nOptiunea aleasa este: ";
                        cin >> nr;

                        statistica[0]++;
                        statistica[1]++;
                        
                        if(nr == 1)
                            statistica[2]++;
                        else
                            statistica[3]++;

                        ofstream f("statistici.txt");
                        for(int i = 0; i < statistica.size(); i++)
                            f << statistica[i] << "\n";
                        f.close();

                        cout << "\nVeti fi redirectionat la meniul principal";
                        Sleep(3000);
                        system("CLS");
                        MeniuCurent = 0;
                        meniu_principal();
                    }
                    } else {

                        cout << "Alegeti facultatea: \n\n";
                        string f;
                        ifstream citestefac1("universitati/facultati/facultati.txt");
                        getline (citestefac1, f);
                        getline (citestefac1, f);
                        cout << f << endl;

                        citestefac1.close();

                        cout << "\nOptiunea aleasa este ";
                        cin >> nr;

                        if (nr == 1) 
                        {
                            cout << "\nAlegeti specializarea: \n\n";
                            string s;
                            ifstream citestespec("universitati/facultati/specializari/s2.txt");

                            while (getline (citestespec, s)) 
                            {
                                cout << s << endl;
                            }
                            citestespec.close();

                            cout << "\nOptiunea aleasa este ";
                            cin >> nr;

                            statistica[4]++;
                            statistica[5]++;
                            if(nr == 1)
                                statistica[6]++;
                            else
                                statistica[7]++;

                            ofstream f("statistici.txt");
                            for(int i = 0; i < statistica.size(); i++)
                                f << statistica[i] << "\n";
                            f.close();

                            cout << "\nVeti fi redirectionat la meniul principal";
                            Sleep(3000);
                            system("CLS");
                            MeniuCurent = 0;
                            meniu_principal();
                        }

                        }
            } else {
                cout << "Caracter introdus gresit";
                Sleep(1500);
                system("CLS");
                MeniuCurent = 0;
                meniu_principal();
            }
            break;

            case 3:
                if (MeniuCurent == 0)
                {
                    MeniuCurent = 3.1;
                    Formular form1;
                    cout << "Formulare inscrise \n\n";
                    string cf;
                    ifstream citesteform("formulare.txt");

                    while (getline (citesteform, cf)) 
                    {
                            cout << cf << endl;
                    }
                    citesteform.close();

                    cout << "5. Inapoi in meniul principal \n";
                    cout << "Optiunea aleasa este: ";
                } else {
                    cout << "Caracter introdus gresit";
                    Sleep(1500);
                    system("CLS");
                    MeniuCurent = 0;
                    meniu_principal();
                }
                break;

            case 4:
                if (MeniuCurent == 0)
                {
                    MeniuCurent = 4.1;

                    cout << "Statistici Facultati \n\n";

                    cout << "1. Statistici UVT Timisoara\n";
                    cout << "2. Statistici UBB Cluj\n\n";
                    cout << "Optiunea aleasa este ";
                    cin >> nr;

                    if (nr == 1) 
                    {

                        cout << "\nUniversitatea de Vest din Timisoara: " << statistica[0] << " studenti inscrisi\n";
                        cout << "\tFacultatea de Matematica si Informatica: " << statistica[1] << " studenti inscrisi\n";
                        cout << "\t\tSpecializarea Informatica Aplicata: " << statistica[2] << " studenti inscrisi\n";
                        cout << "\t\tSpecializarea Informatica Romana: " << statistica[3] << " studenti inscrisi\n";

                    } else if (nr == 2) {

                        cout << "\nUniversitatea Babes Bolyai: " << statistica[4] << " studenti inscrisi\n";
                        cout << "\tFacultatea de Fizica are: " << statistica[5] << " studenti inscrisi\n";
                        cout << "\t\tSpecializarea Fizica: " << statistica[6] << " studenti inscrisi\n";
                        cout << "\t\tSpecializarea Fizica informatica: " << statistica[7] << " studenti inscrisi\n";

                    } else {
                        cout << "Tasta gresita. Introduceti din nou\n";
                        cout << "Optiunea aleasa este ";
                    }

                    cout << "\n5. Inapoi in meniul principal \n";
                    cout << "Optiunea aleasa este ";
                } else {
                    cout << "Caracter introdus gresit";
                    Sleep(1500);
                    system("CLS");
                    MeniuCurent = 0;
                    meniu_principal();
                }
                break;

            case 5:

                MeniuCurent = 0;
                meniu_principal();
                break;

            default:
                cout << "Caracter introdus gresit, alegeti una dintre cele 4 variante";
                Sleep(1500);
                system("CLS");
                MeniuCurent = 0;
                meniu_principal();
            }
    }

    return 0;
}
