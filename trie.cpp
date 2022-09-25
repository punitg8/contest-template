struct Node{
    Node* link[2];
    ll count = 0;
    void insertKey(ll num, Node* toinsert){
        link[num]=toinsert;
    }
    bool containsKey(ll num){
        return link[num]!=NULL;
    }
    Node* getKey(ll num){
        return link[num];
    }
};

class Trie{
    private: Node* root;
    public:
    Trie(){
        root=new Node();
    }
    void insert(ll num){
        vector<ll> bin(32,0);
        ll pos=31;
        while(num!=0){
            bin[pos--]=num%2;
            num/=2;
        }
        Node* current=root;
        for(ll i=0;i<bin.size();i++){
            if(!current->containsKey(bin[i])){
                current->insertKey(bin[i],new Node());
            }
            current=current->getKey(bin[i]);
            if(bin[i]==1) current->count++;
        }
    }
    ll countNum(vector<ll> &bin){
        Node* current=root;
        ll ans=0;
        for(ll i=0;i<bin.size();i++){
            if(current->containsKey(bin[i])){
                current=current->getKey(bin[i]);
            }else{
                return 0;
            }
        }
        return current->count;
    }
};
