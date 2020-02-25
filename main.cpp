#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;


// example input: TAATGACCCACGAATAAGCTTTTAAGTACTAGCGAACATTCTATGTTCTTGGCTAGTCACTAATTAATTAACTAATCAT

//TASKS:
// read input from a text file into a character array
// find ORF
// scan through codon by codon
// stop when stop codon is found
// 
// OUTPUT:
// RNA sequence
// amino acid sequence
// tRNA sequence

vector<string> readFile(string inputfile){
    ifstream readFile; //input stream
    char tmp; //stores chars from file
    string stmp; //stores chars from file
    vector<string> input; //stores vector

    // Open file
    readFile.open(inputfile);

    // Parse file and store into 'input'
    if (readFile.is_open()) 
    {
        while (!readFile.eof()) 
        {
            readFile.get(tmp);
            if(tmp == 'A' || tmp == 'C' || tmp == 'T' || tmp == 'G')
            {
                stmp += tmp;
                input.push_back(stmp);
                stmp.clear();
            }
        }

        //remove last char (last one is read twice)
        input.pop_back();
    }

    // Close file and return
    readFile.close();
    return input;
}

void outputRNASequence(vector<string> input) {
    cout << "mRNA sequence: ";
    
    for (int i = 0; i < input.size(); i++) {
        if (input[i] == "A") {
            cout << "U ";
        }
        else if (input[i] == "T") {
            cout << "A ";
        }
        else if (input[i] == "G") {
            cout << "C ";
        }
        else if (input[i] == "C") {
            cout << "G ";
        }
    }
    
    cout << "\n";

}
void outputAASequence(vector<string> input){
    cout << "output\n";

}
void outputTRNASequence(vector<string> input){
    cout << "tRNA sequence: ";
      
      for (int i = 0; i < input.size(); i++) {
          if (input[i] == "A") {
              cout << "A ";
          }
          else if (input[i] == "T") {
              cout << "U ";
          }
          else if (input[i] == "G") {
              cout << "G ";
          }
          else if (input[i] == "C") {
              cout << "C ";
          }
      }
      
      cout << "\n";
}

int main()
{
    string file;
    string isFiveToThree;
    
    // Get input file
    cout << "Enter name of file (with extension): ";
    getline(cin, file);

    // Get sequence direction
    cout << "Is sequence 5' to 3'? (enter 'y' or 'n') ";
    getline(cin, isFiveToThree);

    // Get sequence
    vector<string> input = readFile(file);

    // Reverse sequence if file is 3' to 5'
    if(isFiveToThree == "n")
        reverse(input.begin(), input.end());
        
    outputRNASequence(input);
    outputAASequence(input);
    outputTRNASequence(input);
    return 0;
}


