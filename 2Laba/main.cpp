#include <iostream>
#include <string>
#include <tuple>
#include <cctype>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

// Bits u need in one char
const int BIT_COUNT = 5;

struct forArray{
    int lenkey;
    string key;
    unsigned long long value;
};

typedef class Patricia{
private:
    struct Node;
    Node *root = nullptr;
    // Search but return 3 nodes
    tuple<Node*, Node*, Node*> SearchE(const string& findKey) const;
    // Search return only 1 node
    Node* Search(const string& findKey) const;
    // Insert node to tree
    void Insert(const string& key, const unsigned long long& value, const size_t& index);
    void ClearNode(Node *node);
    void Show(Node *node, vector <forArray>& savear, int& i);
    // void split(string str, vector<string>& res);
public:
    // Get value from map
    unsigned long long& At(const string& findKey) const;
    // Create node with key value and insert to tree
    void Add(const string& key, unsigned long long value);
    // Delete node from tree
    void Erase(const string& key);
    void Save(string& path);
    void Load(string& path);
    void Clear();
    ~Patricia(){}
} patr;

struct Patricia::Node{
    string key;
    unsigned long long value;
    size_t index;
    Node *right, *left;

    Node(const string& key, const unsigned long long& value, const int& index)
        : key(key), value(value), index(index), left(nullptr), right(nullptr) { }

    ~Node(){}
};



Patricia::Node* Patricia::Search(const string& findKey) const{
    Node *currentNode = root->left, *prevNode = root;

    while(currentNode->index > prevNode->index){
        // Index of char that we need to check
        size_t charIndex = (currentNode->index - 1) / BIT_COUNT;

        // findKey is less than need char
        if(charIndex >= findKey.size()){
          	// Remember prevNode
            prevNode = currentNode;
            // Only '0'
            currentNode = currentNode->left;
            continue;
        }

        char currentChar = findKey[charIndex];
        // How many times should we shift to the right
        int offset = (BIT_COUNT - 1 - ((currentNode->index - 1) % BIT_COUNT));
        // Get current bit
        bool currentBit = (currentChar >> offset) & 1;

        // Remember prevNode
        prevNode = currentNode;
        // If '1' go right, '0' go left
        currentBit  ? currentNode = currentNode->right
                    : currentNode = currentNode->left;
    }
    return currentNode;
}

void Patricia::Add(const string& key, unsigned long long value){
    if(!root){
        root = new Node(key, value, 0);
        root->left = root;
        return;
    }

    Node *foundNode = Search(key);
    if(foundNode->key == key)
        throw runtime_error("Exist\n");

		bool run = true;
    size_t charIndex = 0;
    while(run){
        char foundedKey = (foundNode->key.size() > charIndex ? foundNode->key[charIndex] : '\0');
        char inputKey   = (key.size() > charIndex ? key[charIndex] : '\0');
        for(size_t i = 0; i < BIT_COUNT; ++i){
            bool foundedKeyBit = foundedKey >> (BIT_COUNT - 1 - i) & 1;
            bool inputKeyBit = inputKey >> (BIT_COUNT - 1 - i) & 1;
            if(foundedKeyBit != inputKeyBit){
                Insert(key, value, charIndex * BIT_COUNT + i + 1);
                run = false;
                break;
            }
        }
        ++charIndex;
    }
}

void Patricia::Insert(const string& key, const unsigned long long& value, const size_t& index){
    Node *currentNode = root->left, *prevNode = root;

    while(currentNode->index > prevNode->index && currentNode->index <= index){
        size_t charIndex = (currentNode->index - 1) / BIT_COUNT;
        // FindKey is less than need char
        if(charIndex >= key.size()){
            prevNode = currentNode;
            // Only '0'
            currentNode = currentNode->left;
            continue;
        }
        char currentChar = key[charIndex]; // If findkey.size less than currentNode->index
        int offset = (BIT_COUNT - 1 - ((currentNode->index - 1) % BIT_COUNT));
        bool currentBit = (currentChar >> offset) & 1;

        // Remember prevNode
        prevNode = currentNode;
        // If '1' go right, '0' go left
        currentBit ? currentNode = currentNode->right : currentNode = currentNode->left;
    }
    
    char getCharFromKey = key[(index - 1) / BIT_COUNT];
    bool getBit= getCharFromKey >> (BIT_COUNT - 1 - (index - 1) % BIT_COUNT) & 1;
    Node *newNode = new Node(key, value, index);

    if(prevNode->left == currentNode)
        prevNode->left = newNode;
    else
        prevNode->right = newNode;

    getBit ? (newNode->right = newNode, newNode->left = currentNode) : (newNode->left = newNode, newNode->right = currentNode);
}

unsigned long long& Patricia::At(const string& findKey) const{
    if(!root)
        throw runtime_error("NoSuchWord\n");

    Node* get = Search(findKey);

    if(get->key == findKey)
        return get->value;

    throw runtime_error("NoSuchWord\n");
}

tuple<Patricia::Node*, Patricia::Node*, Patricia::Node*> Patricia::SearchE(const string& findKey) const{
    Node *currentNode = root->left, *prevNode = root, *prevPrevNode = root;
    while(currentNode->index > prevNode->index){
        size_t charIndex = (currentNode->index - 1) / BIT_COUNT;

    // FindKey is less than need char
    if(charIndex == findKey.size()){
        prevPrevNode = prevNode;
        prevNode = currentNode;
        // Only '0'
        currentNode = currentNode->left;
        continue;
    }

    char currentChar = findKey[charIndex];// If findkey.size less than currentNode-&>;index
    int offset = (BIT_COUNT - 1 - ((currentNode->index - 1) % BIT_COUNT));
    bool currentBit = (currentChar >> offset) & 1;

    // Remember prevNode &amp; prevPrevNove
    prevPrevNode = prevNode;
    prevNode = currentNode;
    // If '1' go right, '0' go left
    currentBit ? currentNode = currentNode->right : currentNode = currentNode->left;
}

return make_tuple(currentNode, prevNode, prevPrevNode);

}

void Patricia::Erase(const string& key){
    if(!root) throw runtime_error("NoSuchWord\n");

    // Get delete node, owner delete node and parent owner
    tuple<Node*, Node*, Node*> delOwnerParentTuple = SearchE(key);
    // A
    Node *deleteNode = get<0>(delOwnerParentTuple);
    // Ğ‘
    Node *ownerDeleteNode = get<1>(delOwnerParentTuple);
    // Ğ‘ parent
    Node *parentOwnerDeleteNode = get<2>(delOwnerParentTuple);

    if(deleteNode->key != key){
        throw runtime_error("NoSuchWord\n");
    }
    // If delete node is root and it's one
    if(deleteNode == root && root->left == root){
        delete root;
        root = nullptr;
        return;
    }
 // If delete node is leaf
    if(ownerDeleteNode == deleteNode){
        if(parentOwnerDeleteNode->right == deleteNode)
            if(deleteNode->right == deleteNode)
                parentOwnerDeleteNode->right = deleteNode->left;
            else
                parentOwnerDeleteNode->right = deleteNode->right;
        else
            if(deleteNode->right == deleteNode)
                parentOwnerDeleteNode->left = deleteNode->left;
            else
                parentOwnerDeleteNode->left = deleteNode->right;
        delete deleteNode;
        deleteNode = nullptr;
        return;
    }

    // Get owner owner delete node
    tuple<Node*, Node*, Node*> ownerOwnerTuple = SearchE(ownerDeleteNode->key);
    Node *ownerOwnerDelNode = get<1>(ownerOwnerTuple);

    // Change item from owner delete node to delete node
    deleteNode->key = ownerDeleteNode->key;
    deleteNode->value = ownerDeleteNode->value;
     // If owner delete node is leaf
    if(ownerOwnerDelNode == ownerDeleteNode){
        if(parentOwnerDeleteNode->right == ownerDeleteNode)
            parentOwnerDeleteNode->right = deleteNode;
        else
            parentOwnerDeleteNode->left = deleteNode;
    }
    else{
        // Tie parent owner delete node with child
        if(parentOwnerDeleteNode->right == ownerDeleteNode)
            if(ownerDeleteNode->right == deleteNode)
                parentOwnerDeleteNode->right = ownerDeleteNode->left;
            else
                parentOwnerDeleteNode->right = ownerDeleteNode->right;
        else
            if(ownerDeleteNode->right == deleteNode)
                parentOwnerDeleteNode->left = ownerDeleteNode->left;
            else
                parentOwnerDeleteNode->left = ownerDeleteNode->right;

        if(ownerOwnerDelNode->right == ownerDeleteNode)
            ownerOwnerDelNode->right = deleteNode;
        else
            ownerOwnerDelNode->left = deleteNode;
    }
    delete ownerDeleteNode;
    ownerDeleteNode = nullptr;
}

void Patricia::Clear(){
    if(!root)
        return;
    if(root != root->left)
        ClearNode(root->left);
    delete root;
    root = nullptr;
}

void Patricia::ClearNode(Node *node){
    if((node->left->index > node->index) && (node->left != node) && (node->left != root))
        ClearNode(node->left);
    if((node->right->index > node->index) && (node->right != node) && (node->right != root))
        ClearNode(node->right);

    delete node;
    node = nullptr;
}

void Patricia::Load(string& path)
{
    ifstream fin;
    string str;
    fin.open(path);
    
    while(getline(fin, str)){
        stringstream ss(str);
        int a;
        unsigned long long val;
        string key;
        ss >> a >> key >> val;
        Add(key, val);
    }
}


void Patricia::Save(string& path)
{
        ofstream fout;
        fout.open(path);
    if(root){
        Node *currentNode = root;
        Node *prevNode = nullptr;
        vector <forArray> savear;
        
        forArray info;
        info.lenkey = currentNode->key.length();
        info.key = currentNode->key;
        info.value = currentNode->value;
        savear.push_back(forArray());
        savear[0] = info;
        prevNode = currentNode;
        currentNode = currentNode->left;
        if(prevNode != currentNode){
        int i = 1;
        int& a = i;
        Show(currentNode, savear, a);
        }
        for(auto& k:savear){
        fout << k.lenkey << " " << k.key << " " << k.value << "\n";
        }
    }
}
 
void Patricia::Show(Node *node, vector <forArray>& savear, int& i)
{
    forArray info;
    info.lenkey = node->key.length();
    info.key = node->key;
    info.value = node->value;
    savear.push_back(forArray());
    savear[i] = info;
    // cout <<node->value << "\n"; //ĞŸĞ¾Ñ�ĞµÑ‚Ğ¸Ğ»Ğ¸ ÑƒĞ·ĞµĞ»
    if (node->left->index > node->index){
        Show(node->left, savear, ++i); //Ğ�Ğ±Ğ¾ÑˆĞ»Ğ¸ Ğ»ĞµĞ²Ğ¾Ğµ Ğ¿Ğ¾Ğ´Ğ´ĞµÑ€ĞµĞ²Ğ¾
    } // ĞµÑ�Ğ»Ğ¸ Ğ¿Ğ¾Ğ´Ğ½Ñ�Ğ»Ğ¸Ñ�ÑŒ, Ñ‚Ğ¾ Ğ²Ğ¾Ğ·Ğ²Ñ€Ğ°Ñ‚
    
    if (node->right->index > node->index){
        Show(node->right, savear, ++i); //Ğ�Ğ±Ğ¾ÑˆĞ»Ğ¸ Ğ¿Ñ€Ğ°Ğ²Ğ¾Ğµ Ğ¿Ğ¾Ğ´Ğ´ĞµÑ€ĞµĞ²Ğ¾
    } // ĞµÑ�Ğ»Ğ¸ Ğ¿Ğ¾Ğ´Ğ½Ñ�Ğ»Ğ¸Ñ�ÑŒ, Ñ‚Ğ¾ Ğ²Ğ¾Ğ·Ğ²Ñ€Ğ°Ñ‚
    return;
}


int main(void){
    patr imedy;
    string command;
    while(cin >> command && command != "\x4"){
        if(command == "+"){
            string key; cin >> key;
            transform(key.begin(), key.end(), key.begin(),
            [](unsigned char c){ return tolower(c); });
            // key = tolower(key);
            unsigned long long value; cin >> value;
            try{
                imedy.Add(key, value);
                cout << "OK\n";
            }
            catch(const runtime_error& e){
                cout << e.what();
            }
        }
        else if(command == "-"){
            string key; cin >> key;
            transform(key.begin(), key.end(), key.begin(),
            [](unsigned char c){ return tolower(c); });
            try{
                imedy.Erase(key);
                cout << "OK\n";
            }
            catch(const runtime_error& e){
                cout << e.what();
            }
        }
        else if(command == "clear" || command == "new"){
            imedy.Clear();
        }
        else if(command == "!"){
            string key, path; 
            cin >> key;
            cin >> path;
            if(key == "Save"){
                try{
                    imedy.Save(path);
                    cout << "OK\n";
                }
                catch(const runtime_error& e){
                    cout << e.what();
                }
            }
            
            if(key == "Load"){
                try{
                patr forload;
			    imedy.Clear();
			    forload.Load(path);
                // imedy.Load(path);
                imedy = forload;
                cout << "OK\n";
                }
                catch(const runtime_error& e){
                    cout << e.what();
                }
            }
        }
        else{
            try{
                string key = command;
            transform(key.begin(), key.end(), key.begin(),
            [](unsigned char c){ return tolower(c); });
                unsigned long long imkey = imedy.At(key);
                cout << "OK: "<< imkey << '\n';
            }
            catch(const runtime_error& e){
                cout << e.what();
            }
        }
    }
    imedy.Clear();
    return 0;
}
