//
// Created by nonnt66 on 08/01/25.
//
#define KnutSuggestion 0.6180339887
#include <fstream>
#include <iostream>

using namespace std;

template<class K, class V>
class Element{
private:
    K key;
    V value;
    bool isDeleted;

public:
    Element(K k, V v){
        this->key = k;
        this->value = v;
        isDeleted = false;
    }

    void setKey(K k){
        this->key = k;
    }

    void setValue(V v){
        this->value = v;
    }

    void setDeleted(bool b){
        this->isDeleted = b;
    }

    K getKey(){
        return this->key;
    }

    V getValue(){
        return this->value;
    }

    bool getIsDeleted(){
        return this->isDeleted;
    }

    void PrintElement(){
        std::cout<< this->key << ": " << this->value << std::endl;
    }
};


template<class K, class V>
class HashTable {
private:
    Element<K,V> **hashtable;
    int dimension;
    std::ifstream FileI;
    std::ofstream FileO;

    unsigned int DivisionMethod(K k){
        return (k % this->dimension);
    }

    unsigned int MultiplicationMethod(K k){
        unsigned int kA= k*KnutSuggestion;
        return (this->dimension*(kA % 1));
    }

    unsigned int HashFunction(K key, int i){
        return (DivisionMethod(key) + i) % this->dimension;
        //return (MultiplicationMethod(key) + i) % this->dimension;
    }

public:
    HashTable(int dim, std::string file_input, std::string file_output){
        this->dimension = dim;
        hashtable = new Element<K,V>*[this->dimension];
        //setTable(new Element<K, V> * [getDim()]);
        for(int i=0; i<dimension; i++){
            hashtable[i] = nullptr;
        }

        FileI.open(file_input.c_str(), std::ios::in);
        if(!FileI){
            std::cout << "Errore nell'apertura del file IN.txt\n" << std::endl;
        }

        FileO.open(file_output.c_str(), std::ios::out);
        if(!FileO){
            std::cout << "Errore nell'apertura del file OUT.txt\n" << std::endl;
        }
    }

    void setTable(Element<K,V> **newTable){
        this->hashtable = newTable;
    }

    int getDim(){
        return this->dimension;
    }

    void HashInsert(Element<K,V> *element){
        int i=0;
        while(i != dimension){
            int j = HashFunction(element->getKey(),i);
            if(hashtable[j] == nullptr || hashtable[j]->getIsDeleted() == true){
                hashtable[j] = element;
                std::cout << "item inserted at index: " << j << std::endl;
                if(element->getIsDeleted() == true){
                    element->setDeleted(false);
                }
                return;
            }else i++;
        }
        std::cout << "Is not possible to insert item...Failed !!!" << std::endl;
    }

    void HashFind(K key){
        int i = 0;
        while(i != this->dimension){
            int j = HashFunction(key,i);
            if(hashtable[j]->getKey() == key && hashtable[j]->getIsDeleted() == false){
                std::cout << "CHIAVE TROVATA: " << hashtable[j]->getValue() << std::endl;
                return;
            }else if(hashtable[j] == nullptr){
                std::cout << "LA CHIAVE NON E' PRESENTE" << std::endl;
                return;
            }else if(hashtable[j]->getIsDeleted() == true && hashtable[j]->getKey() != key){
                i++;
            }else if(hashtable[j]->getKey() == key && hashtable[j]->getIsDeleted() == true){
                std::cout << "LA CHIAVE NON E' PRESENTE" << std::endl;
                return;
            }else i++;
        }
        std::cout << "LA CHIAVE NON E' PRESENTE" << std::endl;
    }

    void HashDelete(K key){
        int i = 0;
        while(i != this->dimension){
            int j = HashFunction(key,i);
            if(hashtable[j]->getKey() == key){
                hashtable[j]->setDeleted(true);
                return;
            }else i++;
        }
    }

    void PrintTable(){
        for(int i=0; i<dimension; i++){
            if(hashtable[i] != nullptr && hashtable[i]->getIsDeleted() == false){
                hashtable[i]->PrintElement();
                FileO << hashtable[i]->getKey() << " " << hashtable[i]->getValue() << std::endl;
            }
        }
    }

    void LoadTable(){
        int key;
        std::string value;
        while(FileI >> key >> value){
            Element<K,V> *new_element = new Element<K,V>(key,value);
            HashInsert(new_element);
        }
        FileI.close();
    }

};




int main()
{
    /*Element<int,string> *one = new Element<int,string>(1,"ONE");
    Element<int,string> *two = new Element<int,string>(2,"TWO");
    Element<int,string> *three = new Element<int,string>(3,"THREE");
    Element<int,string> *four = new Element<int,string>(4,"FOUR");
    Element<int,string> *five = new Element<int,string>(5,"FIVE");
    HashTable<int,string> *hash_t = new HashTable<int,string>(10);
    hash_t->HashInsert(one);
    hash_t->HashInsert(two);
    hash_t->HashInsert(three);
    hash_t->HashInsert(four);
    hash_t->HashInsert(five);
    hash_t->PrintTable();
    hash_t->HashFind(three->getKey());
    hash_t->HashDelete(three->getKey());
    hash_t->HashDelete(one->getKey());
    hash_t->PrintTable();
    hash_t->HashFind(three->getKey());*/
    HashTable<int,string> *hash_t = new HashTable<int,string>(10,"IN.txt","OUT.txt");
    hash_t->LoadTable();
    hash_t->PrintTable();
    hash_t->HashFind(7);
    hash_t->HashDelete(7);
    hash_t->PrintTable();
    hash_t->HashFind(7);
}
