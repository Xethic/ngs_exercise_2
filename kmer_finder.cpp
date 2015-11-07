#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

//calculates the number of unique k-mers and different k-mers
//prints out these numbers and the percentage of the gene that is discovered
double checkHexamers(string sequence, int k){
	vector<string> hexamers;
	string hexamer; 
	
	//iterates over the entire sequence
	for (int outeri = 0; outeri < sequence.size(); outeri++){
		if(outeri > sequence.size() - k){
			break;
		}
		//iterates over 6 bases to build a hexamer
		hexamer = "";
		for (int inneri = 0; inneri < k; inneri++){
			hexamer += sequence[outeri];
			outeri++;
		}
		outeri -= k;
		
		hexamers.push_back(hexamer);
	}
	cout << "Number of total hexamers: " << hexamers.size() << endl;

	double size = hexamers.size();

	sort(hexamers.begin(), hexamers.end());
	
	double counterdiff = 0;
	double counteruni = 0;
	bool seen = false;

	for(vector<string>::iterator iter = hexamers.begin(); iter != hexamers.end()-1; ++iter){
		if(iter == hexamers.end()-2){
			if(*iter != *(iter+1)){
				counteruni += 2;
				counterdiff += 2;
			} else {
				if(!seen){
					counterdiff++;
				}
			}
		} else {
			if(*iter != *(iter+1)){
				if(!seen){
					counteruni++;
					counterdiff++;
					seen = false;
				}
				seen = false;
			} else {
				if(!seen){
					seen = true;
					counterdiff++;
				}
			}
		}
	}
	cout << "Number of unique hexamers: " << counteruni << endl;
	cout << "Number of different hexamers: " << counterdiff << endl;

	double perc = (counteruni / size)* 100;
	cout << perc << " percent of the gene are discovered uniquely with the hexamer library." << endl;
	return perc;
}


//reads in the gene file and stores the sequence in one stringstream
//checks the coverage of the gene with the hexamer library
//first parameter is the gene file
int main(int argc, char* argv[]){
	fstream file;
	file.open(argv[1], ios::in);
	string line;
	string header;
	stringstream sequence;

	if(file.is_open()) {
		getline(file, header);
		while(getline(file, line)){
			sequence << line;
			}			
	}	
	double perc;
	
	for(int i = 50; i < 100; i++) {
		perc = checkHexamers(sequence.str(), i);
		if (perc >= 100) {
			cout << "minimal k = " << i;
			break;
		}
	}
}
