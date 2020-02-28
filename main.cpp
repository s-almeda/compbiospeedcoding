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

int ORFs[3];

// Ask User For Input File Name
string getFile() {
    string file;

    // Get input file
    cout << "Enter name of file (with extension): ";
    getline(cin, file);

    return file;
}

// Return Bottom Strand based on Top Strand
vector<string> getBottomStrand(vector<string> topStrand) {
    // Set Bottom Strand = Top Strand
    vector<string> bottomStrand = topStrand;

    // Reverse Bottom Strand (now 5' -> 3')
    reverse(bottomStrand.begin(), bottomStrand.end());

    // Complement Each DNA Character
    for(int i = 0; i < bottomStrand.size(); ++i)
    {
        if (bottomStrand[i] == "A")
            bottomStrand[i] = "T";
        else if (bottomStrand[i] == "T")
            bottomStrand[i] = "A";
        else if (bottomStrand[i] == "C")
            bottomStrand[i] = "G";
        else if (bottomStrand[i] == "G")
            bottomStrand[i] = "C";
    }

    return bottomStrand;
}

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

void outputDNASequence(vector<string> input) {
    for (int i = 0; i < input.size(); i++) { //iterate through each character
        if (ORFs[i] == 0) { //if the array indicates a non-ORF char
            if (input[i] == "A") { //if A, print a
                cout << "a ";
            }
            else if (input[i] == "T") { //if T, print t
                cout << "t ";
            }
            else if (input[i] == "G") { //if G, print g
                cout << "g ";
            }
            else if (input[i] == "C") { //if C, print c
                cout << "c ";
            }
        }
        else if (ORFs[i] == 1) { //if the array indicates an ORF char
            if (input[i] == "A") { //if A, print A
                cout << "A ";
            }
            else if (input[i] == "T") { //if T, print T
                cout << "T ";
            }
            else if (input[i] == "G") { //if G, print G
                cout << "G ";
            }
            else if (input[i] == "C") { //if C, print C
                cout << "C ";
            }
        }
    }
    cout << "\n"; //print newline
}

void outputRNASequence(vector<string> input) {
    cout << "mRNA listed\n";
    
    cout << "mRNA 1+: ";
    
    for (int i = 0; i < input.size(); i++) {
        if (ORFs[i] == 1) { //indicates the character is within an ORF
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
    }
    
    cout << "\n";

}
void outputAASequence(vector<string> input){
    cout << "Amino Acid sequence: ";
    string codon;
    int startCodonIndex;
    
    // Scan for start codon
    for (int i = 0; i< input.size(); i++) {
        codon = input[i] + input[i+1] + input[i+2];
        cout << codon << " | "; //print codon
        if (codon=="ATG"){
            startCodonIndex = i;
            //cout << "start codon found!";
            break;
        }
    }
    //read by 3 letters at a time from start codon index
    for (int i = startCodonIndex; i< input.size(); i+=3) {
        codon = input[i] + input[i+1] + input[i+2];
        cout << codon << ": "; //print codon
        
        if (codon=="TAA" || codon=="TAG" || codon == "TGA"){
            cout << "STOP" << endl;
            return; //if STOP codon, quit translating
        }
        else if(codon=="TTT" || codon=="TTC"){
            cout << "F";
        }
        else if(codon=="TTA" || codon=="TTG" || codon=="CTT" || codon=="CTC"){
            cout << "L";
        }
        else if(codon=="ATT" || codon=="ATC" || codon=="ATA"){
            cout << "I";
        }
        else if(codon=="ATG"){
            cout << "M";
        }
        else if(codon=="GTT" || codon=="GTC" || codon=="GTA" || codon=="GTG"){
            cout << "V";
        }
        else if(codon=="TCT" || codon=="TCC" || codon=="TCA" || codon=="TCG"|| codon=="AGT"|| codon=="AGC"){
            cout << "S";
        }
        else if(codon=="CCT" || codon=="CCC" || codon=="CCA" || codon=="CCG"){
            cout << "P";
        }
        else if(codon=="ACU" || codon=="ACC" || codon=="ACA" || codon=="ACG"){
            cout << "T";
        }
        
        else if(codon=="GCU" || codon=="GCC" || codon=="GCA" || codon=="GCG"){
            cout << "A";
        }
        else if(codon=="TAT" || codon=="TAC"){
            cout << "Y";
        }
        else if(codon=="CAT" || codon=="CAC"){
            cout << "H";
        }
        else if(codon=="CAA" || codon=="CAG"){
            cout << "Q";
        }
        else if(codon=="AAT" || codon=="AAC"){
            cout << "N";
        }
        else if(codon=="AAA" || codon=="AAG"){
            cout << "K";
        }
        else if(codon=="GAT" || codon=="GAC"){
            cout << "D";
        }
        else if(codon=="GAA" || codon=="GAG"){
            cout << "E";
        }
        else if(codon=="TGT" || codon=="TGC"){
            cout << "C";
        }
        else if(codon=="TGG"){
            cout << "W";
        }
        else if(codon=="CGT" || codon=="CGC"|| codon=="CGA"|| codon=="CGG"|| codon=="AGA"|| codon=="AGG"){
            cout << "R";
        }

        else if(codon=="GGT" || codon=="GGC"|| codon=="GGA"|| codon=="GGG"){
            cout << "G";
        }
        cout << " ";
    }

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
    // Get file name
    string file = getFile();

    // Get top strand (5'->3') sequence
    vector<string> topStrand = readFile(file);

    // Get bottom strand (3'->5') sequence and store as (5'->3')
    vector<string> botStrand = getBottomStrand(topStrand);
    
    cout << "ORF 1+: "; //indicates we are printing the 5' to 3' orientation
    outputDNASequence(topStrand);
    cout << "ORF 1-: "; //indicates we are printing in the 3' to 5' orientation
    outputDNASequence(botStrand);
    //outputTRNASequence(input);
    //outputAASequence(input);
    
    return 0;
}
