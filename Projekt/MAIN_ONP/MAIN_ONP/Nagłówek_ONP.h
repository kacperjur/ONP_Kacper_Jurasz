#pragma once
#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <fstream>


using namespace std;

int priorytet(const string& znak);
void rozklad_na_elementy(ifstream& plik, vector<string>& znaki, istringstream& iss);
bool czy_liczba(const string &znak);
bool sprawdzanie_znakow(const string& dzialanie);
void wykonywanie_dzialania(const string& dzialanie, stack<double>& stos);
double potegowanie(double a, double b);
void zapisanie_wyniku(ofstream& plik, vector<string>& wyniki);
void  rozklad_na_skladniki(ifstream& plik, vector<string>& skladniki, istringstream& iss);
void zapisanie_dzialania(ofstream& plik, vector<string>& wyniki);
int czy_int(const string& nl);



	