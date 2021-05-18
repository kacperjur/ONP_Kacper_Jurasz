#include <iostream>
#include <iomanip>
#include <stack>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "Nag³ówek_ONP.h"
using namespace std;

void rozklad_na_elementy(ifstream& plik, vector<string>& znaki, istringstream& iss)
{
	string dzialanie;
	getline(plik, dzialanie);
	iss.str(dzialanie);
	
	while (iss)
	{
		string pomocniczy;
		iss >> pomocniczy;
		znaki.push_back(pomocniczy);
	
		
	}

}
bool czy_liczba(const string &znaki)
{
	double liczba;
	bool czy_liczba = false;
	
	
	if (istringstream(znaki) >> liczba) czy_liczba = true;
	
	
	return czy_liczba;
}
int priorytet(const string& znak)
{
	if (znak == "^") return 3;
	else if (znak == "*" || znak == "/") return 2;
	else if (znak == "-" || znak == "+") return 1;
	else return 0;
}

bool sprawdzanie_znakow(const string& dzialanie)
{
	string znaki[] = { "-","+","*","/", "^"};
	for (int i = 0; i < 5; i++)
	{
		if (dzialanie == znaki[i])
			return true;
	}
	return false;
}

void rozklad_na_skladniki(ifstream& plik, vector<string>& skladniki, istringstream& iss)
{

	string dzialanie;
	getline(plik, dzialanie);
	iss.str(dzialanie);
	while (iss)
	{
		string pomocniczy;
		iss >> pomocniczy;
		skladniki.push_back(pomocniczy);
	}

}
void wykonywanie_dzialania(const string& dzialanie, stack<double>& stos)
{
	double a, b, wynik;
	a = stos.top();
	stos.pop();

	b = stos.top();
	stos.pop();

	if (dzialanie == "-")
	{
		wynik = b - a;
	}
	else if (dzialanie == "+")
	{
		wynik = b + a;
	}
	else if (dzialanie == "*")
	{
		wynik = b * a;
	}
	else if (dzialanie == "/")
	{
		wynik = b / a;
	}
	else if (dzialanie == "^")
	{
		wynik = potegowanie(a, b);
	}
	stos.push(wynik);

	
	
}

double potegowanie(double a, double b)
{
	double wynik = b;
	for (int i = 0; i < a - 1; i++)
		wynik *= b;
	
	return wynik;

	
}

void zapisanie_wyniku(ofstream& plik, vector<string>& wyniki)
{

	for (int i = 0; i < wyniki.size(); i++)
	{
		plik << wyniki[i] << endl;

	}
	
}
void zapisanie_dzialania(ofstream& plik, vector<string>& wyniki)
{
	
		
		
		for (int i = 0; i < wyniki.size(); i++)
		{
			plik << wyniki[i] << " ";

		}
		plik << endl;
	

}




