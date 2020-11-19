#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <string>

using namespace std;

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

bool linearsearch(vector<int> &vec, int target){
    for(int i=0;i<vec.size();i++){
        if(vec[i]==target){
            return true;
        }
    }
    return false;
}

bool binarysearch(vector<int> &vec,int first, int last, int target){

    int middle=floor(float(first+last)/2);

    if(first==middle || last==middle){ //an meinoun mono 2 stoixeia
        if(target==vec[first] || target==vec[last]){ //an kapoio einai ayto poy psaxnoume
            return true;
        }
        else{
            return false;
        }
    }
    if(vec[middle]>target){ //an ayto pou psaxnoume einai mikrotero ths meshs
            binarysearch(vec,first,middle-1,target); //psaxnoume aristera ths meshs
    }
    else if(vec[middle]<target){ //an ayto pou psaxnoume einai megalytero ths meshs
            binarysearch(vec,middle+1,last,target); //psaxnoume dexia ths meshs
    }
    else // an h mesh isoytai me ayto poy psaxnoyme
        return true; //to stoixeio vrethike
}

bool interpsearch(vector<int> &vec, int first, int last, int target){

    int size=last-first+1;
    if(first==last){ //an meinei mono ena stoixeio
        if(target==vec[first]){ //an einai ayto poy psaxnoume
            return true;
        }
        else{
            return false;
        }
    }
    else{ //an exei meinei pano apo ena stoixeio
        int middle=ceil(first+(target-vec[first])*(float(last-first)/(vec[last]-vec[first])));
            if(vec[middle]>target){ //an ayto pou psaxnoume einai mikrotero ths meshs
                if(middle>=first && middle<=last){ //kai h mesh den ksepernaei ton pinaka
                    interpsearch(vec,first,middle-1,target); //psaxnoume aristera ths meshs
                }
                else //allios an den diaireitai allo
                    return false; // den uparxei to stoixeio
            }
            else if(vec[middle]<target){ //an ayto pou psaxnoume einai megalytero ths meshs
                if(middle>=first && middle<=last){ //kai h mesh den ksepernaei ton pinaka
                    interpsearch(vec,middle+1,last,target); //psaxnoume dexia ths meshs
                }
                else //allios an h mesh ksepernaei ton pinaka
                    return false; // den uparxei to stoixeio
            }
            else // an h mesh isoytai me ayto poy psaxnoyme
                return true; //to stoixeio vrethike
    }
}


int main(){
    cout<<"Hi I'm Ioanna and welcome to my program!"<<endl<<endl;
    cout<<"I will now load file \"integers.txt\"."<<endl;

    vector<int> vec = loadfile("integers.txt");

    cout<<"File loaded."<<endl<<endl;

    cout<<"I will now sort all the numbers from file \"integers.txt\"."<<endl;

    vector<int> finalvec;
    finalvec = mergesort(vec);

    cout<<"Numbers sorted."<<endl<<endl;

    // apeikonish taxinomisis
    /*cout<<"INITIAL: "<<'\t'<<"FINAL: "<<endl;
    for(int i=0;i<vec.size();i++){
        cout<<vec[i]<<'\t'<<'\t'<<finalvec[i]<<endl;
    }*/

    int target=0; //aritmos poy psaxnoyme
    int searchtype=0; //eidos anazitisis
    string tryagain="yes"; // xrhsimopoihtai se periptosi pou theloyme na ksanakanoyme anazitisi
    while(tryagain=="yes"){
        cout<<"What number to search ?"<<endl;
        cin>>target;
        cout<<endl;
        cout<<"How? Pick number:"<<endl<<"1.Linear Search"<<endl<<"2.Binary Search"<<endl<<"3.Interpolation Search"<<endl;
        cin>>searchtype;
        cout<<endl;
        while(searchtype!=1 && searchtype!=2 && searchtype!=3){
            cout<<"Please enter 1,2 or 3."<<endl;
            cin>>searchtype;
            cout<<endl;
        }

        bool found=0;
        switch(searchtype){
            case 1:
                found=linearsearch(finalvec,target);
                break;
            case 2:
                found=binarysearch(finalvec,0,finalvec.size()-1,target); // first->0 last->index teleytaioy stoixeioy toy pinaka
                break;
            case 3:
                found=interpsearch(finalvec,0,finalvec.size()-1,target);
                break;
        }
        if(found){
            cout<<"Found."<<endl<<endl;
        }
        else{
            cout<<"Not found."<<endl<<endl;
        }
        cout<<"Try again? (yes/no)"<<endl;
        cin>>tryagain;
        cout<<endl;
    }

}
