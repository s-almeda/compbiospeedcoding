#include <iostream>
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
int main() 
{
    vector<char> input = readFile();

    // ask if it's from 3' to 5' or 5' to 3'
    // if it's 3' to 5', reverse input


    outputRNASequence(input);
    outputAASequence(input);
    outputTRNASequence(input); 
    return 0;
}

vector<char> readFile(){
	char input[] = { 'A', 'G', 'T', 'C', 'A' }; //get rid of this eventually

	//here pull in a text file, store it in input

	return input
}

void outputRNASequence(vector<char> input){ 
	cout << "output"

}
void outputAASequence(vector<char> input){ 
	cout << "output"

}
void outputTRNASequence(vector<char> input){ 
	cout << "output"

}