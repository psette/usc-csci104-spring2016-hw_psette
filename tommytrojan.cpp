#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char* argv[]){
  if(argc < 3){
    cerr << "Please provide an input and output file." << endl;
    return -1;
  }
  ifstream input(argv[1]);
  ofstream output(argv[2]);
  int **posessions, floors = 0, *floorsizes;
  string ***trojans , curr;
  bool first = true;

  input >> floors;
  trojans = new string**[floors];

  //you will need to keep track of how many people are on each floor.
  floorsizes = new int[floors];
  posessions = new int*[floors];

  for (int i = 0; i < floors; i++) {
	  floorsizes[i] = 0;
	  trojans[i] = NULL;
	  posessions[i] = NULL;
  }
	while(getline(input, curr)) {
		stringstream ss;
		ss << curr;
		ss >> curr;
		if (curr == "MOVEIN") {
			int i,k;
			ss >> i >> k;
			if (ss.fail()) output << "Error - incorrect command" << endl;
			else if (floorsizes[i] != 0) output << "Error - floor "<<i<<" is not empty"<<endl;
			else if (i > floors - 1) output << "Error - floor "<<i<<" does not exist"<<endl;
			else{
				floorsizes[i] = k;
				trojans[i] = new string*[k];
				posessions[i] = new int[k];
				for(int j = 0; j < k; j++){
					trojans[i][j] = NULL;
					posessions[i][j] = 0;
				}
			}
		}
		else if (curr == "MOVEOUT") {
			int i;
			ss >> i;
			if (ss.fail()) output << "Error - incorrect command" << endl;
			else if( floorsizes[i] == 0) output << "No students living on floor "<< i <<endl;
			else if (i > floors - 1) output << "Error - floor "<<i<<" does not exist"<<endl;
			else{
				for(int j = 0; j < floorsizes[i]; j++)	delete  trojans[i][j];
				delete [] posessions[i];
				delete [] trojans[i];
			 	posessions[i] = NULL;
				trojans[i] = NULL;
				floorsizes[i] = 0;
			}
		}
		else if (curr == "OBTAIN") {
			int i, j, k;
			ss >> i >> j >> k;
			string check_empty;
			if (ss.fail()) output << "Error - incorrect command" << endl;
			else if( floorsizes[i] == 0) output << "No students living on floor "<< i <<endl;
			else if (i > floors - 1) output << "Error - floor "<<i<<" does not exist"<<endl;
			else if ( posessions[i][j] != 0) output << "Error - student has posessions"<<endl;
			else if( j > floorsizes[i]) output << "Error - student does not exist" << endl;
			else{
				posessions[i][j] = k;
				trojans[i][j] = new string[k];
				for(int x = 0; x < k; x++)	ss >> trojans[i][j][x];
				if(ss >> check_empty) output << "More objects than specified!" <<endl;
			}
		}
		else if (curr == "OUTPUT") {

			int i, j;
			ss >> i;
			ss >> j;
			if (ss.fail()) output << "Error - incorrect command" << endl;
			else if( floorsizes[i] == 0) output << "No students living on floor "<< i <<endl;
			else if (i > floors - 1) output << "Error - floor "<<i<<" does not exist"<<endl;
			else if ( posessions[i][j] == 0) output << "Error - student has no posessions"<<endl;
			else if( j > floorsizes[i]) output << "Error - student does not exist" << endl;
			else
				for(int x = 0; x < posessions[i][j]; x++)	output << trojans[i][j][x] << endl;
		}
		else {
			if(!first) output << "Error - incorrect command" << endl;
			first = false;
		}
	}
  	for(int i = 0; i < floors; i++){
  		for(int j = 0; j < floorsizes[i]; j++)	delete [] trojans[i][j];
  		delete [] trojans[i];
  		delete [] posessions[i];
  	}
  delete [] trojans;
  delete [] floorsizes;
  delete [] posessions;
  return 0;
}
