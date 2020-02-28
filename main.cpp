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

int ORFs[20000];

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

// Set ORF Array 
void setORFArray(vector<string> top, vector<string> bot) {
    int i = 2; //index for top
    int j = 2; //index for bot
    int inFrame = 0; //increment when ATG is found

    // Loop through top strand and find ORF
    while(i < top.size())
    {
        // Check For Start Codon
        if(top[i-2] == "A" && top[i-1] == "T" && top[i] == "G")
        {
            inFrame++;
            //cout << "Increment Top Frame\n";
        }

        // If In ORF, Set Frames in ORF Array To 1
        if(inFrame > 0)
        {
            ORFs[i-2] = 1;
            ORFs[i-1] = 1;
            ORFs[i] = 1;
        }

        // Check For Stop Codon
        if(top[i-2] == "T" && top[i-1] == "A" && top[i] == "G" && inFrame > 0) {
            inFrame--;
            //cout << "Decrement Top Frame\n";

        } else if(top[i-2] == "T" && top[i-1] == "A" && top[i] == "A" && inFrame > 0) {
            inFrame--;
            //cout << "Decrement Top Frame\n";

        } else if(top[i-2] == "T" && top[i-1] == "G" && top[i] == "A" && inFrame > 0) {
            inFrame--;
            //cout << "Decrement Top Frame\n";
        }

        // Increment Index
        if(inFrame > 0)
        {
            i += 3;
        }
        else
        {
            i += 1;
        }
    }

    inFrame = 0; //reset inFrame for bot strand

    // Loop through bot strand and find ORF
    while(j < bot.size())
    {
        // Check For Start Codon
        if(bot[j-2] == "A" && bot[j-1] == "T" && bot[j] == "G")
        {
            //cout << "Increment Bot Frame\n";
            inFrame++;
        }

        // If In ORF, Set Frames in ORF Array To 1
        if(inFrame > 0)
        {
            ORFs[i+j-2] = 1;
            ORFs[i+j-1] = 1;
            ORFs[i+j] = 1;
        }

        // Check For Stop Codon
        if(bot[j-2] == "T" && bot[j-1] == "A" && bot[j] == "G" && inFrame > 0) {
            inFrame--;
            //cout << "Decrement Bot Frame\n";

        } else if(bot[j-2] == "T" && bot[j-1] == "A" && bot[j] == "A" && inFrame > 0) {
            inFrame--;
            //cout << "Decrement Bot Frame\n";

        } else if(bot[j-2] == "T" && bot[j-1] == "G" && bot[j] == "A" && inFrame > 0) {
            inFrame--;
            //cout << "Decrement Bot Frame\n";
        }

        // Increment Index
        if(inFrame > 0)
        {
            j += 3;
        }
        else
        {
            j += 1;
        } 
    }
}

// Parse Through File and Return String of Contents
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

// Print top and bottom DNA Strands
void outputDNASequence(vector<string> top, vector<string> bot) {
    // Print Top Strand
    cout << "ORF +DNA: 5'  "; //orientation
    
    int i;
    for (i = 0; i < top.size(); i++) { //iterate through each character
        if (ORFs[i] == 0) { //if the array indicates a non-ORF char
            if (top[i] == "A") { //if A, print a
                cout << "a";
            }
            else if (top[i] == "T") { //if T, print t
                cout << "t";
            }
            else if (top[i] == "G") { //if G, print g
                cout << "g";
            }
            else if (top[i] == "C") { //if C, print c
                cout << "c";
            }
        }
        else if (ORFs[i] == 1) { //if the array indicates an ORF char
            if (top[i] == "A") { //if A, print A
                cout << "A";
            }
            else if (top[i] == "T") { //if T, print T
                cout << "T";
            }
            else if (top[i] == "G") { //if G, print G
                cout << "G";
            }
            else if (top[i] == "C") { //if C, print C
                cout << "C";
            }
        }
    }
    cout << "  3'\n"; //print newline

    // Print Bottom Strand
    cout << "ORF -DNA: 5'  "; //orientation
    
    for (int j = 0; j < bot.size(); j++) { //iterate through each character
        if (ORFs[i + j] == 0) { //if the array indicates a non-ORF char
            if (bot[j] == "A") { //if A, print a
                cout << "a";
            }
            else if (bot[j] == "T") { //if T, print t
                cout << "t";
            }
            else if (bot[j] == "G") { //if G, print g
                cout << "g";
            }
            else if (bot[j] == "C") { //if C, print c
                cout << "c";
            }
        }
        else if (ORFs[i + j] == 1) { //if the array indicates an ORF char
            if (bot[j] == "A") { //if A, print A
                cout << "A";
            }
            else if (bot[j] == "T") { //if T, print T
                cout << "T";
            }
            else if (bot[j] == "G") { //if G, print G
                cout << "G";
            }
            else if (bot[j] == "C") { //if C, print C
                cout << "C";
            }
        }
    }
    cout << "  3'\n"; //print newline
}

void outputRNASequence(vector<string> input) {
    cout << "mRNA sequence: ";
    
    for (int i = 0; i < input.size(); i++) {
        if (input[i] == "A") {
            cout << "U";
        }
        else if (input[i] == "T") {
            cout << "A";
        }
        else if (input[i] == "G") {
            cout << "C";
        }
        else if (input[i] == "C") {
            cout << "G";
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
              cout << "A";
          }
          else if (input[i] == "T") {
              cout << "U";
          }
          else if (input[i] == "G") {
              cout << "G";
          }
          else if (input[i] == "C") {
              cout << "C";
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

    // Set ORF frames array
    setORFArray(topStrand, botStrand);
        
    outputDNASequence(topStrand, botStrand);
    //outputTRNASequence(input);
    //outputAASequence(input);
    
    return 0;
}


