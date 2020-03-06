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
    vector<int> toBeAdded;

    // Loop through top strand and find ORF
    while(i < top.size())
    {
        // Check For Start Codon
        if(top[i-2] == "A" && top[i-1] == "T" && top[i] == "G")
        {
            inFrame++;
            toBeAdded.push_back(i-2);
            toBeAdded.push_back(i-1);
            toBeAdded.push_back(i);

        } else if(top[i-2] == "T" && top[i-1] == "A" && top[i] == "G" && inFrame > 0) {
            inFrame--;

            toBeAdded.push_back(i-2);
            toBeAdded.push_back(i-1);
            toBeAdded.push_back(i);
            if (toBeAdded.size() > 150)
            {
                for(int k = 0; k < toBeAdded.size(); k++)
                {
                    ORFs[toBeAdded[k]] = 1;
                }
            }

            toBeAdded.clear();

        } else if(top[i-2] == "T" && top[i-1] == "A" && top[i] == "A" && inFrame > 0) {
            inFrame--;

            toBeAdded.push_back(i-2);
            toBeAdded.push_back(i-1);
            toBeAdded.push_back(i);
            if (toBeAdded.size() > 150)
            {
                for(int k = 0; k < toBeAdded.size(); k++)
                {
                    ORFs[toBeAdded[k]] = 1;
                }
            }

            toBeAdded.clear();

        } else if(top[i-2] == "T" && top[i-1] == "G" && top[i] == "A" && inFrame > 0) {
            inFrame--;

            toBeAdded.push_back(i-2);
            toBeAdded.push_back(i-1);
            toBeAdded.push_back(i);
            if (toBeAdded.size() > 150)
            {
                for(int k = 0; k < toBeAdded.size(); k++)
                {
                    ORFs[toBeAdded[k]] = 1;
                }
            }

            toBeAdded.clear();

        } else {
            if(inFrame > 0) {
                toBeAdded.push_back(i-2);
                toBeAdded.push_back(i-1);
                toBeAdded.push_back(i);
            }
        }

        // If In ORF, Set Frames in ORF Array To 1
        /*if(inFrame > 0)
        {
            ORFs[i-2] = 1;
            ORFs[i-1] = 1;
            ORFs[i] = 1;
        }*/

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
    toBeAdded.clear();

    // Loop through bot strand and find ORF
    while(j < bot.size())
    {
        // Check For Start Codon
        if(bot[j-2] == "A" && bot[j-1] == "T" && bot[j] == "G")
        {
            inFrame++;
            toBeAdded.push_back(j-2);
            toBeAdded.push_back(j-1);
            toBeAdded.push_back(j);

        } else if(bot[j-2] == "T" && bot[j-1] == "A" && bot[j] == "G" && inFrame > 0) {
            inFrame--;
            toBeAdded.push_back(j-2);
            toBeAdded.push_back(j-1);
            toBeAdded.push_back(j);

            if (toBeAdded.size() > 150)
            {
                for(int k = 0; k < toBeAdded.size(); k++)
                {
                    ORFs[toBeAdded[k] + i] = 1;
                }
            }

            toBeAdded.clear();

        } else if(bot[j-2] == "T" && bot[j-1] == "A" && bot[j] == "A" && inFrame > 0) {
            inFrame--;
            toBeAdded.push_back(j-2);
            toBeAdded.push_back(j-1);
            toBeAdded.push_back(j);

            if (toBeAdded.size() > 150)
            {
                for(int k = 0; k < toBeAdded.size(); k++)
                {
                    ORFs[toBeAdded[k] + i] = 1;
                }
            }

            toBeAdded.clear();

        } else if(bot[j-2] == "T" && bot[j-1] == "G" && bot[j] == "A" && inFrame > 0) {
            inFrame--;
            toBeAdded.push_back(j-2);
            toBeAdded.push_back(j-1);
            toBeAdded.push_back(j);

            if (toBeAdded.size() > 150)
            {
                for(int k = 0; k < toBeAdded.size(); k++)
                {
                    ORFs[toBeAdded[k] + i] = 1;
                }
            }

            toBeAdded.clear();

        } else {
            if(inFrame > 0) {
                toBeAdded.push_back(j-2);
                toBeAdded.push_back(j-1);
                toBeAdded.push_back(j);
            }
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
    cout << "\nORF +DNA: 5'  "; //orientation
    
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
    cout << "  3'\n\n"; //print newlines
}

void outputDNAORFs (vector<string> top, vector<string> bot) {
    cout << "DNA ORFs listed\n";
    int label = 1; //counts which ORF we are printing
    int i;
    
    for (i = 0; i < top.size(); i++) { //cycles through each element in first strand
        if (ORFs[i] == 1) { //upon finding an element that starts an ORF...
            cout << "ORF " << label << "+: "; //print labeling
            label++; //increment ORF count
            while (ORFs[i] == 1) { //keep printing elements until ORF is finished
                if (top[i] == "A") { //if statements to print correct nucleotide
                    cout << "A";
                }
                else if (top[i] == "T") {
                    cout << "T";
                }
                else if (top[i] == "G") {
                    cout << "G";
                }
                else if (top[i] == "C") {
                    cout << "C";
                }
                i++; //increment i to keep for loop on track
            }
            cout << "\n"; //print newline after finishing ORF
        }
    }
    
    label = 1; //reset ORF count to 1
    
    for (int j = 0; j < bot.size(); j++) { //cycle through every element in second strand
        if (ORFs[i + j] == 1) { //if element is the start of an ORF...
            cout << "ORF " << label << "-: "; //print out labeling
            label++; //icrement ORF count
            while (ORFs[i + j] == 1) { //keep printing elements until ORF is finished
                if (bot[j] == "A") { //if statements to print correct nucleotide
                    cout << "A";
                }
                else if (bot[j] == "T") {
                    cout << "T";
                }
                else if (bot[j] == "G") {
                    cout << "G";
                }
                else if (bot[j] == "C") {
                    cout << "C";
                }
                j++; //increment j to keep for loop on track
            }
            cout << "\n"; //print newline after finishing ORF
        }
    }
    
    cout << "\n"; //print newline before printing next portion
    
    cout << "DNA ORFs listed as codons\n"; //statement before beginning codon printing
    
    label = 1; //reset ORF count
    int counter = 0;

    for (i = 0; i < top.size(); i++) { //cycles through each element in first strand
        if (ORFs[i] == 1) { //upon finding an element that starts an ORF...
            cout << "ORF " << label << "+: "; //print labeling
            label++; //increment ORF count
            while (ORFs[i] == 1) { //keep printing elements until ORF is finished
                if (top[i] == "A") { //if statements to print correct nucleotide
                    cout << "A";
                }
                else if (top[i] == "T") {
                    cout << "T";
                }
                else if (top[i] == "G") {
                    cout << "G";
                }
                else if (top[i] == "C") {
                    cout << "C";
                }
                i++; //increment i to keep for loop on track
                counter++; //increment counter so that we know when to print a dash
                if (counter % 3 == 0 && ORFs[i+1] == 1) { //if a multiple of 3 has been printed and the next element is in the ORF...
                    cout<<"-"; //print dash
                }
            }
            counter = 0; //reset counter for next read
            cout << "\n"; //print newline after finishing ORF
        }
    }
    
    label = 1; //reset ORF count to 1
    
    for (int j = 0; j < bot.size(); j++) { //cycle through every element in second strand
        if (ORFs[i + j] == 1) { //if element is the start of an ORF...
            cout << "ORF " << label << "-: "; //print out labeling
            label++; //increment ORF count
            while (ORFs[i + j] == 1) { //keep printing elements until ORF is finished
                if (bot[j] == "A") { //if statements to print correct nucleotide
                    cout << "A";
                }
                else if (bot[j] == "T") {
                    cout << "T";
                }
                else if (bot[j] == "G") {
                    cout << "G";
                }
                else if (bot[j] == "C") {
                    cout << "C";
                }
                j++; //increment j to keep for loop on track
                counter++; //increment counter so that we know when to print a dash
                if (counter % 3 == 0 && ORFs[i+j+1] == 1) { //if a multiple of 3 has been printed and the next element is in the ORF...
                    cout<<"-"; //print dash
                }
            }
            counter = 0; //reset counter for next read
            cout << "\n"; //print newline after finishing ORF
        }
    }
    
    cout << "\n"; //print newline before exiting function


}

void outputRNASequence(vector<string> top, vector<string> bot) {
    cout << "mRNA listed\n";
    int label = 1; //counts which ORF we are printing
    int i;
    
    for (i = 0; i < top.size(); i++) { //cycles through each element in first strand
        if (ORFs[i] == 1) { //upon finding an element that starts an ORF...
            cout << "mRNA " << label << "+: "; //print labeling
            label++; //increment ORF count
            while (ORFs[i] == 1) { //keep printing elements until ORF is finished
                if (top[i] == "A") { //if statements to print correct nucleotide
                    cout << "A";
                }
                else if (top[i] == "T") {
                    cout << "U";
                }
                else if (top[i] == "G") {
                    cout << "G";
                }
                else if (top[i] == "C") {
                    cout << "C";
                }
                i++; //increment i to keep for loop on track
            }
            cout << "\n"; //print newline after finishing ORF
        }
    }
    
    label = 1; //reset ORF count to 1
    
    for (int j = 0; j < bot.size(); j++) { //cycle through every element in second strand
        if (ORFs[i + j] == 1) { //if element is the start of an ORF...
            cout << "mRNA " << label << "-: "; //print out labeling
            label++; //icrement ORF count
            while (ORFs[i + j] == 1) { //keep printing elements until ORF is finished
                if (bot[j] == "A") { //if statements to print correct nucleotide
                    cout << "A";
                }
                else if (bot[j] == "T") {
                    cout << "U";
                }
                else if (bot[j] == "G") {
                    cout << "G";
                }
                else if (bot[j] == "C") {
                    cout << "C";
                }
                j++; //increment j to keep for loop on track
            }
            cout << "\n"; //print newline after finishing ORF
        }
    }
    
    cout << "\n"; //print newline before printing next portion
    
    cout << "mRNA listed as codons\n"; //statement before beginning codon printing
    
    label = 1; //reset ORF count
    int counter = 0;

    for (i = 0; i < top.size(); i++) { //cycles through each element in first strand
        if (ORFs[i] == 1) { //upon finding an element that starts an ORF...
            cout << "mRNA " << label << "+: "; //print labeling
            label++; //increment ORF count
            while (ORFs[i] == 1) { //keep printing elements until ORF is finished
                if (top[i] == "A") { //if statements to print correct nucleotide
                    cout << "A";
                }
                else if (top[i] == "T") {
                    cout << "U";
                }
                else if (top[i] == "G") {
                    cout << "G";
                }
                else if (top[i] == "C") {
                    cout << "C";
                }
                i++; //increment i to keep for loop on track
                counter++; //increment counter so that we know when to print a dash
                if (counter % 3 == 0 && ORFs[i+1] == 1) { //if a multiple of 3 has been printed and the next element is in the ORF...
                    cout<<"-"; //print dash
                }
            }
            counter = 0; //reset counter for next read
            cout << "\n"; //print newline after finishing ORF
        }
    }
    
    label = 1; //reset ORF count to 1
    
    for (int j = 0; j < bot.size(); j++) { //cycle through every element in second strand
        if (ORFs[i + j] == 1) { //if element is the start of an ORF...
            cout << "mRNA " << label << "-: "; //print out labeling
            label++; //increment ORF count
            while (ORFs[i + j] == 1) { //keep printing elements until ORF is finished
                if (bot[j] == "A") { //if statements to print correct nucleotide
                    cout << "A";
                }
                else if (bot[j] == "T") {
                    cout << "U";
                }
                else if (bot[j] == "G") {
                    cout << "G";
                }
                else if (bot[j] == "C") {
                    cout << "C";
                }
                j++; //increment j to keep for loop on track
                counter++; //increment counter so that we know when to print a dash
                if (counter % 3 == 0 && ORFs[i+j+1] == 1) { //if a multiple of 3 has been printed and the next element is in the ORF...
                    cout<<"-"; //print dash
                }
            }
            counter = 0; //reset counter for next read
            cout << "\n"; //print newline after finishing ORF
        }
    }
    
    cout << "\n"; //print newline before exiting function


}
void outputAASequence(vector<string> top, vector<string> bot) {
    cout << "Amino Acid sequences: \n";
    string codon; //used to store 3 letter strings for conversions
    int nucCount = 0; //variable used to know how many nucleotides we have used
    int label = 1; //variable used as an ORF counter

    //read by 3 letters at a time from start codon index
    for (int i = 0; i < top.size(); i++) { //parse through top string
        if (ORFs[i] == 1) { //check if codon is marked as ORF
            cout << "AA " << label << "+: "; //print labeing
            label++;
            codon.clear(); //reset any leftover letters in codon string
            while (ORFs[i] == 1) {
                codon += top[i]; //add that element to our codon
                
                if(codon=="TTT" || codon=="TTC"){ //if and else if branches to print out appropriate amino acid
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
                
                else if (codon=="TAA" || codon=="TAG" || codon == "TGA"){
                    cout << "STOP" << endl; //in case of stop codon
                }
                
                nucCount++; //incrememnt amount of nucleotides
                if (ORFs[i+1] == 1 && ORFs[i-1] == 1 && nucCount % 3 == 0) { //if 3 nucleotides are present, clear and print a space
                    cout << " ";
                    codon.clear();
                }
                i++;
            }
        }
    }

}

void outputTRNASequence(vector<string> top, vector<string> bot){ //method to print tRNA anti-codons
    cout << "tRNA listed as anti-codons\n";
      
    int i; //to be used in loop
    int label = 1; //variable used as an ORF counter
    int counter = 0; //variable used to check if 3 nucleotides have been printed

      for (i = 0; i < top.size(); i++) { //cycles through each element in first strand
          if (ORFs[i] == 1) { //upon finding an element that starts an ORF...
              cout << "tRNA " << label << "+: "; //print labeling
              label++; //increment ORF count
              while (ORFs[i] == 1) { //keep printing elements until ORF is finished
                  if (top[i] == "A") { //if statements to print correct nucleotide
                      cout << "U";
                  }
                  else if (top[i] == "T") {
                      cout << "A";
                  }
                  else if (top[i] == "G") {
                      cout << "C";
                  }
                  else if (top[i] == "C") {
                      cout << "G";
                  }
                  i++; //increment i to keep for loop on track
                  counter++; //increment counter so that we know when to print a dash
                  if (counter % 3 == 0 && ORFs[i+1] == 1) { //if a multiple of 3 has been printed and the next element is in the ORF...
                      cout<<"-"; //print dash
                  }
              }
              counter = 0; //reset counter for next read
              cout << "\n"; //print newline after finishing ORF
          }
      }
      
      label = 1; //reset ORF count to 1
      
      for (int j = 0; j < bot.size(); j++) { //cycle through every element in second strand
          if (ORFs[i + j] == 1) { //if element is the start of an ORF...
              cout << "tRNA " << label << "-: "; //print out labeling
              label++; //increment ORF count
              while (ORFs[i + j] == 1) { //keep printing elements until ORF is finished
                  if (bot[j] == "A") { //if statements to print correct nucleotide
                      cout << "U";
                  }
                  else if (bot[j] == "T") {
                      cout << "A";
                  }
                  else if (bot[j] == "G") {
                      cout << "C";
                  }
                  else if (bot[j] == "C") {
                      cout << "G";
                  }
                  j++; //increment j to keep for loop on track
                  counter++; //increment counter so that we know when to print a dash
                  if (counter % 3 == 0 && ORFs[i+j+1] == 1) { //if a multiple of 3 has been printed and the next element is in the ORF...
                      cout<<"-"; //print dash
                  }
              }
              counter = 0; //reset counter for next read
              cout << "\n"; //print newline after finishing ORF
          }
      }
      
      cout << "\n"; //print newline before exiting function

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
        
    //print DNA sequence for top and bottom strands
    outputDNASequence(topStrand, botStrand);
    
    //print DNA ORFs for top and bottom strands
    outputDNAORFs(topStrand, botStrand);
    
    //print mRNA sequences for top and bottom strands
    outputRNASequence(topStrand, botStrand);
    
    //print tRNA anti-codons for top and bottom strands
    outputTRNASequence(topStrand, botStrand);
    
    //print amino acid translation for top and bottom strands
    outputAASequence(topStrand, botStrand);
    
    return 0;
}
