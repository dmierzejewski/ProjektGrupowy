#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <set>
#include <math.h>

using namespace std;

int main()
{
	string linia;
	fstream plik;
	string line;
	plik.open("epj_train_s.txt", ios::in);

	ofstream out("out.txt");

	vector <  vector <double>  > data;
	vector <  vector <double>  > reduced;
	vector <double> distances;
	double number = 0.0;
	
	if (plik.good())
	{
		//////////////////////////////////////////////////////////////////////////////
		//wczytanie danych
		int choroby, cechy, przypadki;
		plik >> choroby >> cechy >> przypadki;
		std::cout << choroby << " " << cechy << " " << przypadki;

		vector<double> row;
		for (int i = 0; i < przypadki; i++) {
			row.clear();
			for (int j = 0; j <= cechy; j++) {
				plik >> number;
				row.push_back(number);
			}
			data.push_back(row);
		}
		
		plik.close();
		//////////////////////////////////////////////////////////////////////////////

		int old = -1;

		while (reduced.size() != old) 
		{ 
			old = reduced.size();
			for (auto x : data) {
				
				/////////////////////////////////////////////////////////
				//pierwszy z danej klasy
				bool isFirst = true;
				for (auto z : reduced) if (x[0] == z[0]) isFirst = false;
				if (isFirst) reduced.push_back(x);
				/////////////////////////////////////////////////////////
				else {
					//liczenie odleg³oœci
					distances.clear();
					for (auto z : reduced) {
						double distance = 0.0;
						for (int i = 1; i < 11; i++) {
							distance += (x[i] - z[i]) * (x[i] - z[i]);
						}
						distances.push_back(distance);
					}

					double min = distances[0];

					int i = 1;
					int index = 0;

					for (i; i < distances.size(); i++) {
						if (distances[i] < min) {
							min = distances[i];
							index = i;
						}
					}

					//sprawdzenie klas porównywanych wierszy
					if (x[0] != reduced[index][0]) {
						reduced.push_back(x);
					}
				}

			}
			
			cout << endl << "Size: " << reduced.size();
			
			
		}



	}

	system("pause");
	return 0;
}
