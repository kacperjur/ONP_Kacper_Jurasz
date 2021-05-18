#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "Nagłówek_ONP.h"

int main(int argc, char* argv[])
{
	string plik_dzialania, plik_dzialania_ONP, plik_wyniki;
	
		if (argc < 3) {
		cout << "musisz podać 3 argumenty: " << endl << "-i plik wejsciowy z dzialaniami w normalnej notacji " << endl << "-o plik wyjsciowy z dzialaniami ONP" << endl << "-w plik wyjsciowy gdzie beda zapisywane wyniki dzialan" << endl;
		return 1;
	}
	else 
		for (int i = 1; i < argc;  i++)
		{
			string parametr;
			parametr = argv[i];
			if (parametr == "-i" && i < argc - 1)
			{
				plik_dzialania = argv[++i];
			}

			else if (parametr == "-o" && i < argc - 1)
			{
				plik_dzialania_ONP = argv[++i];
			}

			else if (parametr == "-w" && i < argc - 1)
			{
				plik_wyniki = argv[++i];
			}
}
		

	stack<double> stos;
	stack<string> stos_NOR;
	string dzialanie, dzialanie_ONP;
	istringstream nor, onp;
	ifstream NOR_IN, ONP_IN;
	ofstream NOR_OUT, ONP_OUT;
	vector<string> wyniki;
	vector<string> znaki, skladniki, zwracany;
	bool blad = false;
	

	// WYCZYSZCZENIE PLIKU
	    NOR_OUT.open(plik_dzialania_ONP, ios::trunc);
		NOR_OUT.close();
	

	// PRZEKSZTALCENIE WYRAZENIA 
	NOR_IN.open(plik_dzialania);
	if (!NOR_IN.good()) 	return false;
	
	while (!NOR_IN.eof())
	{
		rozklad_na_elementy(NOR_IN, znaki, nor);


		for (int i = 0; i < znaki.size(); i++)
		{
			dzialanie = znaki[i];

			if (czy_liczba(dzialanie)) zwracany.push_back(dzialanie);
			else if (dzialanie == "(") stos_NOR.push(dzialanie);
			else if (dzialanie == ")")
			{
				while (!stos_NOR.empty() && stos_NOR.top() != "(")
				{
					zwracany.push_back(stos_NOR.top());
					stos_NOR.pop();
				}
				stos_NOR.pop();
			}
			else if (sprawdzanie_znakow(dzialanie) == true)
			{
				while (!stos_NOR.empty() && priorytet(stos_NOR.top()) >= priorytet(dzialanie))
				{
					zwracany.push_back(stos_NOR.top());
					stos_NOR.pop();
				}
				stos_NOR.push(znaki[i]);
			}
			else if (dzialanie == " ") continue;
			else if (dzialanie == "\0") continue;
			
			else {

				cout << "blad_p";
				blad = true;
				break;
			}
		
		}
		if (blad)
		{
			NOR_OUT.open(plik_dzialania_ONP, ios::app);
			NOR_OUT << "blad" << endl;
			NOR_OUT.close();

		}
		else
		{
			while (!stos_NOR.empty())
			{
				zwracany.push_back(stos_NOR.top());
				stos_NOR.pop();

			}
			NOR_OUT.open(plik_dzialania_ONP, ios::app);
			zapisanie_dzialania(NOR_OUT, zwracany);
			NOR_OUT.close();
		}
		while (!stos_NOR.empty())
		{
			stos_NOR.pop();
		}
		nor.clear();
		zwracany.clear();
		znaki.clear();
		blad = false;
		
	}
	
	NOR_IN.close();
	
	
	
	// WYKONANIE OBLICZEN NA ZAPISIE ONP 
	ONP_IN.open(plik_dzialania_ONP);
	if (!ONP_IN.good()) return false;
	
		
	while (!ONP_IN.eof())
	{
		
		rozklad_na_skladniki(ONP_IN, skladniki,onp); // wyciaganie 
		
		
			for (int i = 0; i < skladniki.size(); i++)
			{
				dzialanie_ONP = skladniki[i];
				
				//sprawdzanie liczb
				double znak;
				if (istringstream(dzialanie_ONP) >> znak) stos.push(znak);
				
				// sprawdzanie znakow
				else if (sprawdzanie_znakow(dzialanie_ONP))  wykonywanie_dzialania(dzialanie_ONP, stos);
				
				// usuwanie spacji
				else if (dzialanie_ONP == " ") continue;
				else if (dzialanie_ONP == "\0") continue;

				else 
				{
					cout << "blad_w" << " ";
					blad = true;
					break;
				}
			}
			if (blad)
			{
				wyniki.push_back("blad");
			}
			
			else
			{
				while (!stos.empty())
				{
					ostringstream s;
					s << fixed << setprecision(3) << stos.top();
					wyniki.push_back(s.str()); // wyniki kazdego zadania zapisujemy w kontenerze 
					stos.pop();
				}
			}
			// resetowanie flag
		
			blad = false;
			onp.clear();
			skladniki.clear();
	}
	ONP_IN.close();
	ONP_OUT.open(plik_wyniki);
	zapisanie_wyniku(ONP_OUT, wyniki); //zapis wyniku w pliku docelowym
	ONP_OUT.close();

}

