#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

// calculates the number of unique k-mers and different k-mers
// prints out these numbers, the percentage of the gene that is discovered,
// length of the k-mers of the designed library and the number of bases of this library
// when a k-mer is found on the gene, it is printed in an output file called "kmer_library.txt"
void checkKmers(string sequence, int k){
	vector<string> kmers;
	string kmer;
	fstream output;
	output.open("kmer_library.txt", ios::out);
	
	// iterates over the entire sequence
	for (int outeri = 0; outeri < sequence.size(); outeri++){
		if(outeri > sequence.size() - k){
			break;
		}
		// iterates over k bases to build a k-mer
		kmer = "";
		for (int inneri = 0; inneri < k; inneri++){
			kmer += sequence[outeri];
			outeri++;
		}
		outeri -= k;
        if(kmer != ""){
            kmers.push_back(kmer);
        }
	}
	cout << "Number of total "<<k<<"-mers: " << kmers.size() << endl;
    
	double size = kmers.size();
    if(size > 0){
        // sorts the k-mers alphabetically
        sort(kmers.begin(), kmers.end());
	
        double counterdiff = 0;
        double counteruni = 0;
        bool seen = false;
        
        // Searches for all unique and different kmers
        for(vector<string>::iterator iter = kmers.begin(); iter != kmers.end()-1; ++iter){
            if(iter == kmers.end()-2){
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
                        output << *iter << endl;
                    }
                    seen = false;
                } else {
                    if(!seen){
                        seen = true;
                        counterdiff++;
                        output << *iter << endl;
                    }
                }
            }
        }
        cout << "Number of unique "<<k<<"-mers: " << counteruni << endl;
        cout << "Number of different "<<k<<"-mers: " << counterdiff << endl;
        double perc = (counteruni / size) * 100;
        cout << perc << " % of the gene are discovered uniquely with the "<<k<<"-mer library" << endl;
        cout << "Number of bases in the "<<k<<"-mere library: " << counterdiff * k << endl;
    }
    output.close();
    cout << "Wrote Library to disk\n";
}




// reads in the gene file and stores the sequence in one stringstream
// checks the coverage of the gene with the k-mer library
// first parameter is the gene file
// second parameter is k of the k-mers
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
        checkKmers(sequence.str(), atoi(argv[2]));
        file.close();
        cout << "Done!\n";
	}
    else{
        cout << "File not found\n";
        return 1;
    }
}
