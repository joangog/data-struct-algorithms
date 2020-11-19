#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

vector<string> loadfile(string filename){ // synartisi gia anoigma arxeiou (string h char*)

    ifstream file;
    file.open(filename);
    vector<string> vec;
    string line;
    int i=0;
    while (getline (file,line)){
            vec.push_back(line);
            i++;
    }
    file.close();
    return vec;
}

string uncapitalise(string word){ //voithitiki synartisi gia na mhn exei shmasia an h eisagomenh lexh exei kefalaia h oxi
    for(int i=0;i<word.length();i++){ // gia kathe gramma tou str
        if(word[i]>='A' && word[i]<='Z'){ //an einai kefalaio
            word[i]+=32; //metatropi se pezo
        }
    }
    return word;
}

vector<char> strtovec(string word){ //voithitiki synartisi metatropis string se dianysma xaraktiron
    vector<char> vec;
    for(int i=0;i<word.length();i++){
        vec.push_back(word[i]);
    }
    return vec;
}

class Node{

    private:

        Node* children[26]={NULL}; //pinakas paidion (sthn ousia pinakas alphavitou me komvo se kathe thesi)
        Node* parent; //diefkolinei sthn delete dioti proxorame apo kato pros ta kato sto tree
        string suffix;
        bool isword; //xrhsimevei oste na kseroume an ontos ena monopati antistoixei se lexi pou exoume eisagei

    public:

        Node(){
            parent=NULL;
            suffix="";
            isword=false;

        }

        Node* getchild(int i){ // "i" einai to index toy paidiou apo ton pinaka paidion
            return children[i];
        }
        Node* getparent(){
            return parent;
        }
        string getsuffix(){
            return suffix;
        }
        bool getisword(){
            return isword;
        }
        void setchild(int i,Node* child){
            children[i]=child;
        }
        Node* setparent(Node* parent){
            this->parent=parent;
        }
        void setsuffix(string suffix){
            this->suffix=suffix;
        }
        void setisword(bool isword){
            this->isword=isword;
        }




};

class Trie{

    private:

        Node* root; //riza

    public:

        Trie(){
            root=new Node(); //arxikopoihsh rizas
        }

        Node* getroot(){
            return root;
        }

        bool hasnochild(Node* node){ //voithitiki synartisi gia elegxo an o komvos den exei KATHOLOU paidia
            for(int j=0;j<26;j++){
                    if(node->getchild(j)!=NULL){
                        return false;
                    }
            }
            return true;
        }

        void insert(string word){
            word=uncapitalise(word); //metatropi kefalaion se peza grammata
            vector<char> lettervec=strtovec(word); // metatrepoume to word se vector
            int index=0; //metavliti gia to index tou pinaka paidion

            Node* startnode=root; // h diadikasia ksekinaei apo thn riza

            for(int i=0;i<lettervec.size();i++){ //gia kathe gramma tou word

                index=lettervec[i]-97; // -97 dioti 'a'=97 kai dioti theloume na xrhsimopoihsoume char os index

                if(startnode->getchild(index)==NULL){ //an sthn thesi tou sygekrimenou grammatos ston pinaka paidion tou komvou, den yparxei komvos hdh
                    startnode->setchild(index,new Node()); //topothetisi tou pio neou komvou stin thesi tou katallilou grammatos ston pinaka paidion
                    startnode->getchild(index)->setparent(startnode); //orise ton patera tou komvou
                    startnode->getchild(index)->setsuffix(startnode->getsuffix()+=lettervec[i]); //orise os suffix to string pou apoteleitai apo tous xaraktires tou monopatiou komvon pou akolouthisame (sthn ousia prosthetoume ton xarakthra tou torinou komvou sto suffix apo ton proigoumeno komvo
                }

                startnode=startnode->getchild(index); //proxora sto epomeno komvo kai sto epomeno gramma tis lexis

            }

            startnode->setisword(true); //kane to flag isword true
        }

        bool search(string word){
            word=uncapitalise(word); //metatropi kefalaion se peza grammata
            vector<char> lettervec=strtovec(word); //metatrepoume to word se vector
            Node* startnode=root;

            for(int i=0;i<lettervec.size();i++){ //gia kathe gramma tou word

                    if(startnode==NULL) //an ftasei se komvo NULL prin diaperasei ola ta grammata shmainei oti den yparxei h lexi
                        return false;

                    startnode=startnode->getchild(lettervec[i]-97); //proxora thn diadikasia sto paidi tou node
            }

            // meta tin oloklirosi ths "for" xoris apotyxia h diadikasia exei sarosei gia kathe gramma tou word olo to monopati komvon (oson yparxoun) kai exei ftasei se enan teliko komvo

            if(startnode!=NULL && startnode->getsuffix()==word && startnode->getisword()){ //an o telikos komvos pou eftase den einai NULL kai exei ontos thn lexi poy psaxname, kai einai lexi pou exoume eisagei ( px an psaxnoume cat kai exoume eisagei catlover den tha prepei na theorei oti to cat yparxei)
                return true; //tote i lexi yparxei
            }
            else{
                return false;
            }

        }

        bool delet(string word){
            word=uncapitalise(word); //metatropi kefalaion se peza grammata
            vector<char> lettervec=strtovec(word); // metatrepoume to word se vector
            vector<Node*> nodestack;

            Node* startnode=root;
            nodestack.push_back(startnode);

            for(int i=0;i<lettervec.size();i++){ //gia kathe gramma tou word

                    int index=lettervec[i]-97; //metavliti gia to index tou pinaka paidion (-97 dioti 'a'=97 opote gia na xrhsimopoihsoume char os index kanoume ayto)

                    if(startnode->getchild(index)==NULL){ //an den yparxei paidi stamata thn diadikasia
                        break;
                    }

                    nodestack.push_back(startnode->getchild(index));
                    startnode=startnode->getchild(index); //proxora thn diadikasia sto paidi tou node
            }

            // meta tin "for" h diadikasia exei sarosei gia kathe gramma tou word olo to monopati komvon (oson yparxoun) kai exei ftasei se enan teliko komvo

            if(nodestack.back()->getsuffix()==word && nodestack.back()->getisword()){ //an o telikos komvos pou eftase exei ontos thn lexi poy psaxname, kai einai lexi pou exoume eisagei ( px an psaxnoume cat kai exoume eisagei catlover den tha prepei na theorei oti to cat yparxei)

                while(hasnochild(nodestack.back())){ //oso o pio prosfatos komvos pou prostethike den exei paidia (an eixe paidia den prepei na ton svisoume giati shmainei oti yparxoun kai alles lexis pou ksekinane apo to prothema auto)

                    for(int i=0;i<lettervec.size();i++){ //gia na vreis to index(i) psaxe poio apo ta grammata tis lexis einai to gramma tou torinou mas komvos
                        int index=lettervec[i]-97; //metavliti gia to index tou pinaka paidion (-97 dioti 'a'=97 opote gia na xrhsimopoihsoume char os index kanoume ayto)

                        if(nodestack.back()->getparent()->getchild(index)==nodestack.back()){ //otan telika vreis to index

                            //svise ton komvo (efoson o pateras tou den einai null, pou ayto tha shmaine oti o komvos einai riza, kai thn riza den thn svinoume pote)
                            if(nodestack.back()->getparent()!=NULL){
                                nodestack.back()->getparent()->setchild(index,NULL);
                                nodestack.back()->setparent(NULL);
                                nodestack.pop_back();
                                break; // vges apo thn for afou vrikes to index, den xreiazete na psaksei allo
                            }
                        }
                    }
                }

                startnode->setisword(false);

                /*
                an aferesoume mia lexi h opoia apotelei oloklhrh prothema gia kapoia allh lexi tote prepei na papsoume na theoroume thn lexi ayth os
                lexi sto tree (px an sto tree yparxei cat kai catlover, afairontas to cat prepei na allaksoume kai to flag isword, dioti an meta
                psaksoume cat, tha vrei monopati cat eksetias tou catlover kai an diavasei kai oti to flag isword einai true tha theorisei oti h lexi yparxei sto tree
                parolo pou emeis thn svisame
                */

                return true; //svistike
            }
            return false; //den svistike
        }
};

int main(){
    Trie tree;

    cout<<"Hi I'm Ioanna and welcome to my program!"<<endl<<endl;

    cout<<"I will now load file \"words.txt\"."<<endl;

    vector<string> wordvec=loadfile("words.txt");

    cout<<"File loaded."<<endl<<endl;

    cout<<"I will now insert every word from file \"words.txt\" to the trie."<<endl;

    for(int i=0;i<wordvec.size();i++){
        tree.insert(wordvec[i]);
    }

    cout<<"Words inserted."<<endl<<endl;

    int choice=0;
    string target;
    string tryagain="yes";
    while(tryagain=="yes"){
        cout<<"What to do now? Pick number:"<<endl<<"1.Search word"<<endl<<"2.Delete word"<<endl<<"3.Exit"<<endl;
        cin>>choice;
        cout<<endl;
        while(choice!=1 && choice!=2 && choice!=3){
            cout<<"Please enter 1,2 or 3."<<endl;
            cin>>choice;
            cout<<endl;
        }
        switch(choice){
            case 1:{
                cout<<"What word to search?"<<endl;
                cin>>target;
                cout<<endl;
                if(tree.search(target)){
                    cout<<"Word found."<<endl;
                    cout<<endl;
                }
                else{
                    cout<<"Word not found."<<endl;
                    cout<<endl;
                }

                break;
            }
            case 2:{
                cout<<"What word to delete?"<<endl;
                cin>>target;
                cout<<endl;
                if(tree.delet(target)){
                    cout<<"Word deleted."<<endl;
                }
                else{
                    cout<<"Word not deleted. It doesn't exist."<<endl;
                }
                cout<<endl;
                break;
            }
            case 3:
                return 0;
                break;

        }
        cout<<"Try again? (yes/no)"<<endl;
        cin>>tryagain;
        cout<<endl;
    }
}

