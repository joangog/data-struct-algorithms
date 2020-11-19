#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>

using namespace std;

class Node{

    private:

        int key;
        char color;
        Node* parent;
        Node* lchild;
        Node* rchild;
        Node* brother;

    public:

        int brank;

        Node(int key){
            brank=0;
            color='0';
            parent=NULL;
            lchild=NULL;
            rchild=NULL;
            brother=NULL;
            this->key=key;
        }

        int getkey(){
            return key;
        }
        char getcolor(){
            return color;
        }
        Node* getparent(){
            return parent;
        }
        Node* getlchild(){
            return lchild;
        }
        Node* getrchild(){
            return rchild;
        }
        Node* getbrother(){
            return brother;
        }

        void setcolor(char color){
            this->color=color;
        }
        void setparent(Node* parent){
            this->parent=parent;
        }
        void setlchild(Node* lchild){
            this->lchild=lchild;
        }
        void setrchild(Node* rchild){
            this->rchild=rchild;
        }
        void setbrother(Node* brother){ //anagkaio otan theloume na anaferthoume sto allo paidi tou patera tou komvou mas, alla den kseroume an einai aristero h dexi paidi
            this->brother=brother;
        }
};

class RedBlackTree{

    private:

        Node* root;


    public:

        vector<Node*> childless;

        RedBlackTree(){
            root=NULL;
        }

        Node* getroot(){
            return root;
        }

        void draw(Node *startnode,int space,int i){ //synartisi ektiposis tree
            //ksekiname apo ton dexiotero katotero komvo kai meta ektyponoume ta aristera paidia tou, anevainontas sthn synexeia ston patera kai ektyponontas pali ta aristera paidia anadromika

            if (startnode==NULL) //otan teleiosei to tree
                return; //vges apo ton anadromiko kyklo

            space+=5; //kathe fora tha afksanetai h apostasi ton arithmon ( oso pio xamila sto tree einai, toso pio megali i apostasi apo tin akri tis othonis
            i++;
            //ektyponoume dexio paidi
            draw(startnode->getrchild(), space, i);
            cout<<endl;
            for (int i = 0; i < space; i++) //afinoume thn katallhlh apostasi apo tin akri tis othonis
                cout<<" ";

            if(startnode->getcolor()=='r'){
                cout<<"R";
            }
            else if(startnode->getcolor()=='b'){
                cout<<"B";
            }
            cout<<startnode->getkey()<<" d="<<i;

            //ektyponoume aristero paidi
            draw(startnode->getlchild(), space, i);
            cout<<endl;
        }

        int setrank(Node* startnode){
            Node* firstnode=startnode;
            while(startnode->getparent()!=NULL){
                if(startnode->getcolor()=='b'){
                    (firstnode->brank)++;
                }
                startnode=startnode->getparent();
            }
            return firstnode->brank;
        }

        /*
        void check(){
            setrank(root,0);
            for(int i=0;i<childless.size();i++){
                cout<<childless[i]->brank<<endl;
            }
        }
        */

        void colorflip(Node* startnode){ //enallagh xrwmatwn
            startnode->getparent()->setcolor('b'); // p(x)=black
            startnode->getparent()->getparent()->setcolor('r'); // p(p(x))=red
            startnode->getparent()->getbrother()->setcolor('b'); // b(p(x)=black
        }
        void rightrotation(Node* startnode){ //dexia peristrofi (voithitiki synartisi)

            /*          G                  P
                       /  \               /  \
                      P    U      =>     N    G
                     /  \                    /  \
                    N    B                  B    U
            */

            Node *N=startnode;//neos komvos
            Node *B=(startnode->getbrother()); //aderfos komvou B=b(N)
            Node *P=(startnode->getparent()); //pateras komvou P=p(N)
            Node *U=(startnode->getparent()->getbrother()); //theios komvou U=b(p(x))
            Node *G=(startnode->getparent()->getparent()); //pappous komvou G=p(p(x))
            Node *GG=(startnode->getparent()->getparent()->getparent()); //propappous komvou G=p(p(p(x)))


            //gia kathe komvo orizoume 1)poios o pateras/2)se poion einai paidi kai 3)poios o aderfos

            //komvos P

            if(G!=root){ //an to G den einai riza, diladi yparxei propappous GG)

                P->setparent(GG); //p(P)=GG

                if(GG->getlchild()==G){ //o proppapous tou komvou den tha exei pia paidi (eite aristero eite dexi analoga) ton pappou alla ton patera tou komvou
                    GG->setlchild(P); // lc(GG)=P
                    if(GG->getrchild()!=NULL){ //an yparxei dexi paidi tou proppapou
                        P->setbrother(GG->getrchild()); // b(P)=rc(GG) (to dexi paidi tou propappou tha ginei aderfos you patera)
                        GG->getrchild()->setbrother(P); // b(rc(GG))=P
                    }
                }
                else if(GG->getrchild()==G){
                    GG->setrchild(P); // rc(GG)=P
                    if(GG->getlchild()!=NULL){ //an yparxei aristero paidi tou proppapou
                        P->setbrother(GG->getlchild()); // b(P)=lc(GG) (to aristero paidi tou propappou tha ginei aderfos tou patera)
                        GG->getlchild()->setbrother(P); // b(lc(GG))=P
                    }
                }
            }
            else{ //an to G einai riza
                P->setparent(NULL);
                root=P; // kane tora to P riza
            }

            //komvos N
            N->setbrother(G); // b(N)=G (o pappous tou komvou tha ginei aderfos tou komvou)

            //komvos G
            G->setparent(P);//p(G)=P (o pappous tha exei patera ton patera tou komvou)
            P->setrchild(G);  //rc(P)=G
            G->setbrother(N); //b(G)=N (o komvos tha ginei aderfos tou pappou)

            //komvos B (an yparxei)
            G->setlchild(B); //lc(G)=B (den to vazoume mesa stin if oste otan ton B den yparxei(NULL), lc(G)=NULL
            if(B!=NULL){
                B->setparent(G); //p(B)=G (o pappous tha ginei pateras tou aderfou)
                B->setbrother(U); //b(B)=U (o theios tha ginei aderfos tou aderfou)
            }

            //komvos U (an yparxei)
            if(U!=NULL){
                U->setbrother(B); //b(U)=B (o aderfos tha ginei aderfos tou theiou)
            }

        }
        void leftrotation(Node* startnode){ //aristeri peristrofi (voithitiki synartisi)

            /*          G                  P
                       /  \               /  \
                      U    P       =>    G    N
                          /  \          /  \
                         B    N        U    B
            */

            Node *N=startnode;//neos komvos
            Node *B=(startnode->getbrother()); //aderfos komvou B=b(N)
            Node *P=(startnode->getparent()); //pateras komvou P=p(N)B
            Node *U=(startnode->getparent()->getbrother()); //theios komvou U=b(p(x))
            Node *G=(startnode->getparent()->getparent()); //pappous komvou G=p(p(x))
            Node *GG=(startnode->getparent()->getparent()->getparent()); //propappous komvou G=p(p(p(x)))

            //gia kathe komvo orizoume 1)poios o pateras/2)se poion einai paidi kai 3)poios o aderfos

            //komvos P

            if(G!=root){ //an to G den einai riza, diladi yparxei propappous GG)

                P->setparent(GG); //p(P)=GG

                if(GG->getlchild()==G){ //o proppapous tou komvou den tha exei pia paidi (eite aristero eite dexi analoga) ton pappou alla ton patera tou komvou
                    GG->setlchild(P); // lc(GG)=P
                    if(GG->getrchild()!=NULL){ //an yparxei dexi paidi tou proppapou
                        P->setbrother(GG->getrchild()); // b(P)=rc(GG) (to dexi paidi tou propappou tha ginei aderfos you patera)
                        GG->getrchild()->setbrother(P); // b(rc(GG))=P
                    }
                }
                else{
                    GG->setrchild(P); // rc(GG)=P
                    if(GG->getlchild()!=NULL){ //an yparxei aristero paidi tou proppapou
                        P->setbrother(GG->getlchild()); // b(P)=lc(GG) (to aristero paidi tou propappou tha ginei aderfos tou patera)
                        GG->getlchild()->setbrother(P); // b(lc(GG))=P
                    }
                }
            }
            else{ //an to G einai riza
                P->setparent(NULL);
                root=P; // kane tora to P riza
            }

            //komvos N
            N->setbrother(G); // b(N)=G (o pappous tou komvou tha ginei aderfos tou komvou)

            //komvos G
            G->setparent(P);//p(G)=P (o pappous tha exei patera ton patera tou komvou)
            P->setlchild(G);  //lc(P)=G
            G->setbrother(N); //b(G)=N (o komvos tha ginei aderfos tou pappou)

            //komvos B (an yparxei)
            G->setrchild(B); //rc(G)=B (den to vazoume mesa stin if oste otan ton B den yparxei(NULL), rc(G)=NULL
            if(B!=NULL){ //ean yparxei aderfos
                B->setparent(G); //p(B)=G (o pappous tha ginei pateras tou aderfou)
                B->setbrother(U); //b(B)=U (o theios tha ginei aderfos tou aderfou)
            }

            //komvos U (an yparxei)
            if(U!=NULL){ //ean yparxei theios
                U->setbrother(B); //b(U)=B (o aderfos tha ginei aderfos tou theiou)
            }

        }
        void rotation(Node* startnode){ //geniki synartisi peristrofis

            Node* N=startnode; //neos komvos
            Node* P=(startnode->getparent()); //pateras komvou P=p(N)
            Node* G=(startnode->getparent()->getparent()); //pappous komvou G=p(p(x))

            // aplh aristerh peristrofh
            if(G->getrchild()!=NULL && startnode==G->getrchild()->getrchild()){ //an N kai P dexia paidia (elegxoume gia NULL pointer giati allios exoume provlima otan theloume na paroume thn idiothta anyparktou stoixeiou)

            /*         G(b)               P(b)
                       /  \               /  \
                     U(b) P(r)    =>    G(r) N(r)
                          /  \          /  \
                        B(?) N(r)     U(b) B(?)
            */

                leftrotation(N);

                P->setcolor('b');
                G->setcolor('r');
            }

            //aplh dexia peristrofh
            else if(G->getlchild()!=NULL && startnode==G->getlchild()->getlchild()){ //an N kai P aristera paidia

            /*         G(b)               P(b)
                       /  \               /  \
                     P(r) U(b)    =>    N(r) G(r)
                     /  \                    /  \
                   N(r) B(?)               B(?) U(b)
            */

                rightrotation(N);

                P->setcolor('b');
                G->setcolor('r');
            }

            //diplh peristrofh (prota dexia meta aristera)
            else if(G->getrchild()!=NULL && startnode==G->getrchild()->getlchild()){ //an N aristero kai P dexio paidi

            /*         G(b)               G(b)                  N(b)
                       /  \               /  \                /      \
                     U(b) P(r)    =>    U(b) N(r)    =>    G(r)      P(r)
                          /  \               /  \         /    \    /    \
                        N(r) B(?)         LC(?) P(r)    U(b) LC(?) RC(?) B(?)
                        /  \                   /  \
                     LC(?) RC(?)            RC(?) B(?)
            */

                if(N->getlchild()==NULL){ // h if xrhsimopoihtai se periptosi pou to N den exei aristero paidi, esto na theoriso kapio temp node os atristero paidi ths, voithitika. Ayto moy epitrepei na epanaxrisimopoihso me eksipno tropo tis synarthseis leftrotation kai rightrotation apofevgontas polles grammes kodika
                    Node temp(0);
                    N->setlchild(&temp);  // dhmioyrgoyme thn sxesh aristeroy paidiou tou temp os pros to N
                    temp.setparent(N);
                    if(N->getrchild()!=NULL){ //ean yparxei dexio paidi tou N orise to aderfo tou temp
                        temp.setbrother(N->getrchild());
                        N->getrchild()->setbrother(&temp);
                    }

                    rightrotation(N->getlchild()); //kanoume thn dexia peristrofi pano sto temp

                    N->setlchild(NULL); //diagrafoume to temp
                    temp.setparent(NULL);
                    if(N->getrchild()!=NULL){ //ean yparxei dexio paidi tou N orise to aderfo tou temp
                        temp.setbrother(NULL);
                        N->getrchild()->setbrother(NULL);
                    }
                }

                else{ //allios an to N exei aristero paidi
                    rightrotation(N->getlchild()); //apla efarmozoume thn dexia peristrofi sto aristero paidi
                }

                leftrotation(P); //aristerh peristrofi os pros P

                N->setcolor('b');
                G->setcolor('r');
            }

            //diplh peristrofh (prota aristera meta dexia)
            else if(G->getlchild()!=NULL && startnode==G->getlchild()->getrchild()){ //an N dexio kai P aristero paidi

            /*         G(b)               G(b)                  N(b)
                       /  \               /  \                /      \
                     P(r) U(b)    =>    N(r) U(b)    =>    P(r)      G(r)
                     /  \               /  \              /    \    /    \
                   B(?) N(r)          P(r) RC(?)        B(?) LC(?) RC(?) U(b)
                        /  \          /  \
                     LC(?) RC(?)    B(?) LC(?)
            */


                if(N->getrchild()==NULL){ // h if xrhsimopoihtai se periptosi pou to N den exei dexio paidi, esto na theoriso kapio temp node os dexio paidi ths, voithitika. Ayto moy epitrepei na epanaxrisimopoihso me eksipno tropo tis synarthseis leftrotation kai rightrotation apofevgontas polles grammes kodika
                    Node temp(0);
                    N->setrchild(&temp);  // dhmioyrgoyme thn sxesh dexiou paidiou tou temp os pros to N
                    temp.setparent(N);
                    if(N->getlchild()!=NULL){ //ean yparxei aristero paidi tou N orise to aderfo tou temp
                        temp.setbrother(N->getlchild());
                        N->getlchild()->setbrother(&temp);
                    }
                    leftrotation(N->getrchild()); //kanoume thn aristeri peristrofi pano sto temp

                    N->setrchild(NULL); //diagrafoume to temp
                    temp.setparent(NULL);
                    if(N->getlchild()!=NULL){ //ean yparxei dexio paidi tou N orise to aderfo tou temp
                        temp.setbrother(NULL);
                        N->getlchild()->setbrother(NULL);
                    }

                }
                else{ //allios an to N exei dexio paidi
                    leftrotation(N->getrchild()); //apla efarmozoume thn aristeri peristrofi sto dexi paidi
                }

                rightrotation(P);// dexia peristrofi os pros P

                N->setcolor('b');
                G->setcolor('r');
            }
        }
        void colorfix (Node* startnode){
            if(root->getcolor()=='r'){ //an h riza einai kokkinh kanthn mavrh
                root->setcolor('b');
            }

            if(startnode->getparent()==NULL){ //an o komvos den exei patera diladi einai riza, kai einai kokkinos, kane ton mavro
               if(startnode->getcolor()=='r'){
                    startnode->setcolor('b');
                }
            }

            else if(startnode->getparent()!=NULL && startnode->getparent()->getparent()!=NULL ){ //an o komvos exei patera kai pappou , diladi o pateras tou den einai riza oute o komvos einai riza

                if(startnode->getcolor()=='r' && startnode->getparent()->getcolor()=='r' && startnode->getparent()->getparent()->getcolor()=='b' ){ //an o komvos kai o pateras tou einai kokkinoi, kai o pappous einai mavros

                    if(startnode->getparent()->getbrother()==NULL || startnode->getparent()->getbrother()->getcolor()=='b' ){ //an o theios tou komvou einai mavros  h NULL
                        rotation(startnode);
                    }

                    else if(startnode->getparent()->getbrother()->getcolor()=='r'){ //an o theios tou komvou einai kokkinos
                        colorflip(startnode); //kane enallagh xromaton
                        if(startnode->getparent()->getparent()!=NULL || startnode->getparent()->getparent()!=root){ //an o pappous tou komvou den einai riza h NULL
                            return colorfix(startnode->getparent()->getparent()); //synexise thn anadromh gia ton pappou tou komvou
                        }
                    }
                }
            }
            return;
        }


        bool search(int key, Node* startnode){ //anazitisi komvou me kleidi key
            if(startnode==NULL){
                return false;
            }
            else{
                if(key==startnode->getkey()){ //an to key einai iso me to key tou startnode
                    startnode->brank=setrank(startnode);
                    cout<<startnode->brank<<endl;
                    return true;
                }
                else if(key<startnode->getkey()){ //an to key mikrotero apo to key tou startnode
                    search(key, startnode->getlchild()); //tote kane anazitisi apo to aristero paidi
                }
                else{ //an to key megalitero apo to key tou startnode
                    search(key, startnode->getrchild()); //tote kane anazitisi apo to dexio paidi
                }
            }
        }
        void place(Node &newnode, Node* startnode){ //topothetisi neou komvou (voithitiki synartisi) (xrhisimopoioume anafora sto newnode dioti den tha einai pote null)
            if(startnode==NULL){ // an to tree einai adeio
                root=&newnode; // h riza tha einai o neos komvos
                newnode.setcolor('b'); //h riza einai panta mavri
                return;
            }
            else{ //an to tree den einai adeio
                if(newnode.getkey()<startnode->getkey()){ //an to key tou neou komvou einai mikrotero apo to key tou startnode
                    if(startnode->getlchild()==NULL){ // an to startnode einai fyllo
                        startnode->setlchild(&newnode); // kane ton komvo aristero paidi tou
                        newnode.setparent(startnode);
                        if(startnode->getrchild()!=NULL){ //kai an exei aderfo orise ton
                            newnode.setbrother(startnode->getrchild());
                            startnode->getrchild()->setbrother(&newnode);
                        }
                        newnode.setcolor('r'); //kathe neos komvos pou topothetitai tha einai kokkinos
                        return;
                    }
                    else{
                        place(newnode, startnode->getlchild()); //allios synexise thn diadikasia sto aristero paidi tou startnode
                    }
                }
                else if(newnode.getkey()>startnode->getkey()){ //an to key tou neou komvou einai megalitero apo to key tou startnode
                    if(startnode->getrchild()==NULL){ // an to startnode einai fyllo
                        startnode->setrchild(&newnode); // kane ton komvo dexio paidi tou
                        newnode.setparent(startnode);
                        if(startnode->getlchild()!=NULL){ //kai an exei aderfo orise ton
                            newnode.setbrother(startnode->getlchild());
                            startnode->getlchild()->setbrother(&newnode);
                        }
                        newnode.setcolor('r'); //kathe neos komvos pou topothetitai tha einai kokkinos
                        return;

                    }
                    else{
                        place(newnode, startnode->getrchild()); //allios synexise thn diadikasia sto dexio paidi tou startnode
                    }
                }
            }
        }
        void insert(Node &newnode){ // eisagwgh neou komvou
                place(newnode,root); //valto sto tree
                colorfix(&newnode); //kane diorthosi
        }
};

vector<int> loadfile(string filename){ // synartisi gia anoigma arxeiou (string h char*)

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

int main(){

    RedBlackTree tree;

    vector<int> keyvec=loadfile("integers.txt"); //kanoume load to arxeio se pinaka me keys
    vector<Node> nodevec; //pinakas komvon

    for(int i=0;i<keyvec.size();i++){
        Node temp= Node(keyvec[i]); //ftiaxnoume komvous me to kathe key
        nodevec.push_back(temp); //tous vazoume ston pinaka komvon
    }

    for(int i=0;i<keyvec.size();i++){
        tree.insert(nodevec[i]); //vazoume tous komvous sto tree

    }

    tree.search(498542,tree.getroot());
    //tree.draw(tree.getroot(),0,0); //apeikonisi tree
}
