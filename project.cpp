#include<iostream>
#include<string>
#include<ctime>
using namespace std;

#define DEBUG

template < class T>
class node {
  public:
    node() : left(NULL), right(NULL) {
        data = new T;
    }
    node(const T &var) : left(NULL), right(NULL) {
        data = new T(var);  
    }
    ~node() {
        delete data, delete left, delete right;
        data = NULL, left = NULL, right = NULL;
    }
    node(const node &OG) : left(NULL), right(NULL) {
        data = new T(*OG.data);
    }
    void operator=(const node &OG) { //Assignment Operator Overload to assign node to a node  (Part of Rule of 3)
        *data = *OG.data;
    }
    void operator=(const T &var) {  //Assignment Operator Overload to take literals
        *data = var;
    }
    void setData(T var) {
        *data = var;
    }
    T getData() const {
        return *data;
    }
    friend std::ostream& operator<<(std::ostream& out, const node& n) {
        out << *n.data;
        return out;
    }
    friend std::istream& operator>>(std::istream& in, node& n) {
        in >> *n.data;
        return in;
    }
  protected:
    T    *data;
    node *left;
    node *right;
    template <class U> friend class BinaryTree;
};

template <class T>
class BinaryTree{
  public:
    BinaryTree() : root(NULL), size(0){}
    virtual ~BinaryTree(){                //Destructor                    (Part of Rule of 3)
    #ifdef DEBUG
        cout << "De-allocating Tree here" << endl;
    #endif
        DeleteTree(&root);
        root = NULL;
    }
    BinaryTree(const BinaryTree &b2){     //Copy Constructor Overload     (Part of Rule of 3)
    #ifdef DEBUG
        cout << "Manually copying tree in copy constructor" << endl;
    #endif
        copyTree(b2.root, &(this->root));
    }
    int copyTree(node<T>* currOG, node<T>** currNEW){
        int size = 0;
        if (currOG == NULL) {
            DeleteTree(currNEW);
            return size; 
        }
        *currNEW = new node<T>(*currOG);
        size += copyTree(currOG->left, &(*currNEW)->left);
        size += copyTree(currOG->right, &(*currNEW)->right);
        return ++size;
    }

    //overload | operator to act as mirror :D
    BinaryTree operator|(const BinaryTree& OG){
        #ifdef DEBUG
        cout << "Mirroring Tree!" << endl;
        #endif
        if(OG.root == NULL) return OG;
        DeleteTree(&root);
        this->root = NULL;
        this->size = mirrorTree(OG.root, &(this->root));
        return OG;
    }
    int mirrorTree(node<T>* currOG, node<T>** currNEW){
        int size = 0;

        if (currOG == NULL) {
            DeleteTree(currNEW);
            return size; 
        }
        *currNEW = new node<T>(*currOG);
        size += mirrorTree(currOG->right, &(*currNEW)->left);
        size += mirrorTree(currOG->left, &(*currNEW)->right);
        return ++size;
    }
    void operator=(const BinaryTree &b2){ //Assignment Operator Overload  (Part of Rule of 3)
        #ifdef DEBUG
        cout << "Manually copy tree in assignment operator" << endl;
        #endif
        DeleteTree(&root);
        this->root = NULL;
        this->size = copyTree(b2.root, &(this->root));
    }
    void readnGenerate(const T a[], int arr_size){
        if(arr_size <= 0) return; //empty
        #ifdef DEBUG
        cout << "Generating From: '" << a << "'\nOG Length: 00" << arr_size << endl;
        #endif
        DeleteTree(&root);
        this->size = recInsert(a, arr_size, &root, 1);
        #ifdef DEBUG
        cout << "Total Inserted: "  << this->size << endl;
        #endif
    }
    int recInsert(const T *a, int arrSize, node<T>**curr, int currIndex) {
        int size = 0;
        if ((arrSize < currIndex) || (a[currIndex-1] == '%')) {
            return size;
        }
        
        *curr = new node<T>(a[currIndex-1]);

        size += recInsert(a, arrSize, &(*curr)->left, 2*currIndex);
        size += recInsert(a, arrSize, &(*curr)->right, 1+2*currIndex);
        
        return ++size;
    }

    void inOrderTraversal(node<T>* curr){
        if (curr == NULL) {
            curr = this->root;
        }
        if (curr->left != NULL) {
            inOrderTraversal(curr->left);
        }
        cout << *curr;
        if (curr->right != NULL) {
            inOrderTraversal(curr->right);
        }
    }
    void preOrderTraversal(node<T>* curr){
        if (curr == NULL) {
            curr = this->root;
        }
        cout << *curr;
        if (curr->left != NULL) {
            preOrderTraversal(curr->left);
        }
        if (curr->right != NULL) {
            preOrderTraversal(curr->right);
        }
    }
    void postOrderTraversal(node<T>* curr){
        if (curr == NULL) {
            if (this->root == NULL) {return;}
            curr = this->root;
        }
        if (curr->left != NULL) {
            postOrderTraversal(curr->left);
        }
        if (curr->right != NULL) {
            postOrderTraversal(curr->right);
        }
        cout << *curr;
    }
    int getHeight(node<T> *curr){
        //Compute Height of both subtrees and keep the larger one
        if(curr == NULL) return 0; //base case
        else{
            int lheight = getHeight(curr->left); 
            int rheight = getHeight(curr->right);
            if  (lheight > rheight) return lheight+1;
            else return rheight+1;
        }
    }
    void printSpecificLevel(node<T> *root, int level){
        if(root == NULL) return;
        if(level == 1) cout << *root;
        else if(level > 1){
            printSpecificLevel(root->left, level-1);
            printSpecificLevel(root->right, level-1);
        }
    }
    void printLevelOrderTraversal(){
        for(int i=0; i <= getHeight(root); i++){
            printSpecificLevel(root, i);
        }
    }
  protected:
    node<T> *root;
    int size;
  private:
    void DeleteTree(node<T>** curr){
        if (*curr == NULL) { return; }
        DeleteTree(&(*curr)->left);
        DeleteTree(&(*curr)->right);
        delete *curr;
        *curr = NULL;
    }
};

template<class T>
class OmegaSeamaster {
  public:
    OmegaSeamaster() : BinaryTreeTemp(NULL) {}
    OmegaSeamaster(const OmegaSeamaster &x) :BinaryTreeTemp(NULL) {
        BinaryTreeFunction = x.BinaryTreeFunction;
    }
    void operator=(const OmegaSeamaster &x) {
        this->BinaryTreeFunction = x.BinaryTreeFunction;
    }
    BinaryTree<T>  BinaryTreeFunction;
    BinaryTree<T>* BinaryTreeTemp;
    void Alarm(){
        cout << "Alarm: BOOM!" << endl;
    }
    void Time(){
        time_t t = std::time(0);
        cout << "                      Time: " << localtime(&t)->tm_hour 
             << ":" << localtime(&t)->tm_min 
             << ":" << localtime(&t)->tm_sec << endl;
    }
    void CleanTemp(){
        delete BinaryTreeTemp;
        BinaryTreeTemp = NULL;
    }
    void Draw(){
        cout << "                           ||||                           \n";
        cout << "                   /\\      ||||      /\\                   \n";
        cout << "                   \\/             /| \\/                   \n";
        cout << "               /\\      |\\        / |     /\\               \n";
        cout << "               \\/       \\\\      / /      \\/               \n";
        cout << "                         \\\\    / /                        \n";
        cout << "           ____           \\\\__/ /         ____            \n";
        cout << "          |____|           |__|/         |____|           \n";
        cout << "                            /                             \n";
        cout << "                           /                              \n";
        cout << "               /\\         /              /\\               \n";
        cout << "               \\/        / Omega         \\/               \n";
        cout << "                   /\\   /            /\\                   \n";
        cout << "                   \\/  /    ||       \\/                   \n";
        cout << "                            ||                            " << endl;
    }
    ~OmegaSeamaster(){
        CleanTemp();
    }
};

#ifdef DEBUG
#include<sstream>
#endif
//Client Code Given To Q Branch
int main(void){
#ifdef DEBUG
    cout << "Q BRANCH DEBUG MODE ONLINE. SHOULD HAVE 0 MEMORY LEAKS" << endl;
    //Node Tests
    node<int>* testNode0 = new node<int>;
    testNode0->setData(007);
    node<int> testNode1(*testNode0);
    cout << testNode0->getData() << " = "<< *testNode0 << " = " << testNode1 << " = 7"<< endl;
    *testNode0 = 0;
    cout << *testNode0 << " = 0 and " << *testNode0 << " != " << testNode1 << endl;

    node<string>* testNode2 = new node<string>;
    string agentname = "James Bond";
    stringstream ss(agentname);
    ss >> *testNode2;
    cout << *testNode2 << " ";
    ss >> *testNode2;
    cout << *testNode2 << endl;
    node<float> testNode3 = 0.07f;
    cout << testNode3 << " = 0.07" << endl;
    cout << reinterpret_cast<void*>(testNode2) << " <--Some Memory Address that is not 0" << endl;
    node<int>* testNode4 = testNode0;
    delete testNode4; delete testNode2;
    //Binary Tree Tests
    char testmsg1[] = {'R','O','L','E','X','%', '?','\0'};
    //All % symbols indicate empty spots in a tree and should not be inserted, but skipped instead
    BinaryTree<char> *testTree0 = new BinaryTree<char>;
    BinaryTree<char> *testTree1 = new BinaryTree<char>;
    cout << "Read and Traversal Tests: " << endl;
    testTree0->readnGenerate(testmsg1, string(testmsg1).length());
    cout << "Total Inserted Should be 6 since % was skipped" << endl;
    testTree0->inOrderTraversal(NULL);   cout<<" = EOXRL?"<<endl;
    testTree0->preOrderTraversal(NULL);  cout<<" = ROEXL?"<<endl;
    testTree0->postOrderTraversal(NULL); cout<<" = EXO?LR"<<endl;
    testTree0->printLevelOrderTraversal();cout<<" = ROLEX?"<<endl;
    cout << "End Traversal Tests" << endl;
    cout << "Mirror Test and Traversals:" << endl;
    BinaryTree<char> testTree2; 
    testTree2 | *testTree0; //Mirror
    testTree2.printLevelOrderTraversal();cout<<" = RLO?XE"<<endl;
    testTree2.inOrderTraversal(NULL); cout<<" = ?LRXOE"<<endl;
    testTree2.preOrderTraversal(NULL); cout<<" = RL?OXE"<<endl;
    testTree2.postOrderTraversal(NULL); cout<<" = ?LXEOR"<<endl;
    cout << "End Mirror Traversal Tests" << endl;
    *testTree1 = *testTree0;
    cout << "Assignment Operator Test" << endl;
    testTree1->printLevelOrderTraversal(); cout<<" = ROLEX?"<<endl;
    BinaryTree<char> testTree3(*testTree0);
    cout << "Copy Constructor Test" << endl;
    testTree3.printLevelOrderTraversal(); cout<<" = ROLEX?"<<endl;
    delete testTree0; testTree0 = NULL;
    testTree1->printLevelOrderTraversal();cout<<" = ROLEX?"<<endl;
    delete testTree1; testTree1 = NULL;
    BinaryTree<int> testTree4; cout<<"Align Arrows -->" << flush;
    testTree4.postOrderTraversal(NULL);cout<<"<--"<<endl;
    cout << "Good Job, Agent. End of Debug Section" << endl;
    cout << "\n************************************************" << endl;
#endif

    //Captured Chatter:
    string msg0 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    string msg1 = "Shaken, not Stirred";
    string msg2 = "You were the chosen one!";
    string msg3 = "Bond, James Bond";
    string cryptmsg[6];
    cryptmsg[0] = "C3PO Bot Never Forgets";
    cryptmsg[1] = "adl 3aa .nr..idn erioBe fmno oerRuraw eBnF .isy  acS";
    cryptmsg[2] = "Roaleuue g tfl%x?Oma,Bei";
    cryptmsg[3] = "..R.  ad . nnrin ewsdneiau racSoBforaeBya 3i mo lreF";
    cryptmsg[4] = "nS r   !ef'grAh%!cp osteaeasTeT%%!et";
    cryptmsg[5] = "Wehi er% ?700 s%%%%%%%%%%%%%%%%392aaahuusf%riiffooambnctnas";
    //End of Captured Chatter

    cout << "\nGood evening Mr. Bond, your latest Q Watch v2.01 Beta features a decoder that\n"
         << "will take a level order binary tree list, generate the tree, and then return\n"
         << "all of the available traversals. Using this technology you should be able to\n"
         << "intercept and decipher any potential messages that Spectre's agents may be\n"
         << "attempting to send within your vicinity.\n"
         << "You should find it quite useful in the field. Oh, one word of warning.\n"
         << "The alarm is rather loud. If you know what I mean.\n" << endl;
    OmegaSeamaster<char> myWatch;

    //Cypher Tester
    myWatch.BinaryTreeFunction.readnGenerate(msg0.c_str(), string(msg0).length());
    #ifdef DEBUG
    cout << "LVL : "; myWatch.BinaryTreeFunction.printLevelOrderTraversal();cout<<endl;
    cout << "IN  : "; myWatch.BinaryTreeFunction.inOrderTraversal(NULL);cout<<endl;
    cout << "PRE : "; myWatch.BinaryTreeFunction.preOrderTraversal(NULL);cout<<endl;    
    cout << "POST: "; myWatch.BinaryTreeFunction.postOrderTraversal(NULL);cout<<endl;
    #endif
    myWatch.BinaryTreeTemp = new BinaryTree<char>(myWatch.BinaryTreeFunction);
    myWatch.BinaryTreeFunction | *myWatch.BinaryTreeTemp;
    #ifdef DEBUG
    cout << "LVL : "; myWatch.BinaryTreeFunction.printLevelOrderTraversal();cout<<endl;
    cout << "IN  : "; myWatch.BinaryTreeFunction.inOrderTraversal(NULL);cout<<endl;
    cout << "PRE : "; myWatch.BinaryTreeFunction.preOrderTraversal(NULL);cout<<endl;    
    cout << "POST: "; myWatch.BinaryTreeFunction.postOrderTraversal(NULL);cout<<endl;
    #endif

    myWatch.Time();
    myWatch.Draw();

    //Cryptomsg
    int msgnum = 0;
    for(;;){
        cout << "\nEnter a Frequency from 1-5 to Decrypt. Enter 0 to Exit: " << endl;
        cin >> msgnum; if(msgnum == 0) goto q; if(msgnum < 0 || msgnum > 5) goto BondJamesBond;
        myWatch.BinaryTreeFunction.readnGenerate(cryptmsg[msgnum].c_str(), string(cryptmsg[msgnum]).length());

        cout << "LVL : "; myWatch.BinaryTreeFunction.printLevelOrderTraversal();cout<<endl;
        cout << "IN  : "; myWatch.BinaryTreeFunction.inOrderTraversal(NULL);cout<<endl;
        cout << "PRE : "; myWatch.BinaryTreeFunction.preOrderTraversal(NULL);cout<<endl;    
        cout << "POST: "; myWatch.BinaryTreeFunction.postOrderTraversal(NULL);cout<<endl;

        myWatch.CleanTemp();
        myWatch.BinaryTreeTemp = new BinaryTree<char>(myWatch.BinaryTreeFunction);
        myWatch.BinaryTreeFunction | *myWatch.BinaryTreeTemp;

        cout << "LVL : "; myWatch.BinaryTreeFunction.printLevelOrderTraversal();cout<<endl;
        cout << "IN  : "; myWatch.BinaryTreeFunction.inOrderTraversal(NULL);cout<<endl;
        cout << "PRE : "; myWatch.BinaryTreeFunction.preOrderTraversal(NULL);cout<<endl;    
        cout << "POST: "; myWatch.BinaryTreeFunction.postOrderTraversal(NULL);cout<<endl;
    } BondJamesBond:

    myWatch.Alarm();
    cout << "OmegaLuL" << endl; q:;
    return 007;
}