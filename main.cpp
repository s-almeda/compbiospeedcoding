#include <iostream>
#include <vector>
#include <string>
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

vector<string> readFile(){
    vector<string> input; //get rid of this eventually
    input.push_back("A");
    input.push_back("T");
	input.push_back("G");
    input.push_back("C");
    //here pull in a text file, store it in input

    return input;
}

void outputRNASequence(vector<string> input){
    cout << "output\n";

}
void outputAASequence(vector<string> input){
    cout << "output\n";

}
void outputTRNASequence(vector<string> input){
    cout << "output\n";

}

int main()
{
    vector<string> input = readFile();

    // ask if it's from 3' to 5' or 5' to 3'
    // if it's 3' to 5', reverse input


    outputRNASequence(input);
    outputAASequence(input);
    outputTRNASequence(input);
    return 0;
}


