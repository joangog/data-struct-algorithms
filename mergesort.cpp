#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <string>

using namespace std;

/*
DATA STRUCTS PROJECT
*/

vector<int> loadfile(char* filename){ // synartisi gia anoigma arxeiou
    ifstream file;
    file.open(filename);
    vector<int> vec;
    string line;
    int i=0;
    while (getline (file,line)){
            int lineint=atoi(line.c_str()); // metatropi tou string "line" pou peirame meso getline se int
            vec.push_back(lineint);
            i++;
    }
    file.close();
    return vec;
}

vector<int> merging(vector<int> &vec1,vector<int> &vec2){ //synartisi tis sigxonefis 2 pinakwn
    int i=0, j=0;
    int length1=vec1.size();
    int length2=vec2.size();
    vector<int> finalvec;
    while(i<length1 && j<length2){ //oso den eksantlitai kanenas apo tous pinakes
            if(vec1[i]<vec2[j]){ //an to stoixeio tou pinaka 1 einai mikrotero tou pinaka 2, valto ston teliko pinaka
                finalvec.push_back(vec1[i]);
                i++;
            }
            else{ //an to stoixeio tou pinaka 2 einai mikrotero h iso tou pinaka 1, valto ston teliko pinaka
                finalvec.push_back(vec2[j]);
                j++;
            }
    } // gia ton pinaka o opoios den exei eksantlithei vale ola ta ypoloipa stoixeia tou ston teliko pinaka
    if(i<length1){
        while(i<length1){
            finalvec.push_back(vec1[i]);
            i++;
        }
    }
    if(j<length2){
        while(j<length2){
            finalvec.push_back(vec2[j]);
            j++;
        }
    }
    return finalvec;
}

vector<int> mergesort(vector<int> &vec){
    int length=vec.size();
    int length1=floor(float(length)/2); // pinakas me megethos ton megalitero prohgoymeno akeraio
    int length2=ceil(float(length)/2); //pinakas me megethos ton mikrotero epomeno akeraio
    vector<int> vec1;
    vector<int> vec2;
    vector<int> finalvec;
    for(int i=0;i<length1;i++){ //vazoume ta katallhla stoixeia stous epimerous pinakes
        vec1.push_back(vec[i]);
    }
    for(int i=0;i<length2;i++){
        vec2.push_back(vec[length1+i]);
    }                                       //taxinomisi twn epimerous merwn
    if(vec1.size()>1){
        vec1=mergesort(vec1);
    }
    if(vec2.size()>1){
        vec2=mergesort(vec2);
    }
    finalvec=merging(vec1,vec2); // sygxonefsi
    return finalvec;
}

int main(){
    vector<int> vec = loadfile("integers.txt");
    vector<int> finalvec;
    finalvec = mergesort(vec);
    cout<<"INITIAL: "<<'\t'<<"FINAL: "<<endl;
    for(int i=0;i<vec.size();i++){
        cout<<vec[i]<<'\t'<<'\t'<<finalvec[i]<<endl;
    }

}
