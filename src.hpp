

//
// Created by wzj on 2021/12/3.
//

#ifndef FINAL_SRC_HPP
#define FINAL_SRC_HPP

#include <string>
#include <vector>
using namespace std;

class LinkedHashMap;
struct Node{
    Node* next=nullptr;
    Node* timePre=nullptr;
    Node* timeNext=nullptr;

    int key=0;
    string value;
};

struct Data{
    int key;
    string value;
};

vector<Data> traverseByTime(const LinkedHashMap& obj);
vector<Data> traverseByIndex(const LinkedHashMap& obj);

class LinkedHashMap{
// todo: Modify "beg", "current" and related parts in the constructor as you wish.
// todo: 你可以根据自己写链表的习惯修改或删除头尾节点并对应修改构造函数。
public:
    int len;
    Node** array;
    Node* beg;
    Node* current;
    // todo: define a function pointer called "forEachMethod"
    // to be pointed to function "traverseByTime" or "traverseByDict".
    // todo: 定义一个名为forEachMethod的函数指针，用于对应travelByTime和travelByDict函数。
    vector<Data> (*forEachMethod)(const LinkedHashMap&);

    LinkedHashMap(int _len_,bool forEachByTime){
        len=_len_;
        beg=nullptr;
        current=nullptr;
        array=new Node*[len];
        for(int i=0;i<len;i++)
            array[i]=nullptr;
        if(forEachByTime)
            forEachMethod=traverseByTime;
        else
            forEachMethod=traverseByIndex;
    }

    ~LinkedHashMap(){
        // Clean up all nodes in the array
        for(int i = 0; i < len; i++) {
            Node* node = array[i];
            while(node != nullptr) {
                Node* temp = node;
                node = node->next;
                delete temp;
            }
        }
        delete[] array;
    }

    void insert(int key,string value){
        // Create new node
        Node* newNode = new Node();
        newNode->key = key;
        newNode->value = value;
        
        // Insert at the head of the array[key] list
        newNode->next = array[key];
        array[key] = newNode;
        
        // Insert at the end of the time-based doubly linked list
        if(beg == nullptr) {
            beg = newNode;
            current = newNode;
            newNode->timePre = nullptr;
            newNode->timeNext = nullptr;
        } else {
            current->timeNext = newNode;
            newNode->timePre = current;
            newNode->timeNext = nullptr;
            current = newNode;
        }
    }

    void remove(int key,string value){
        // Find the node in the array[key] list
        Node* prev = nullptr;
        Node* node = array[key];
        
        while(node != nullptr) {
            if(node->value == value) {
                // Remove from the array[key] list
                if(prev == nullptr) {
                    array[key] = node->next;
                } else {
                    prev->next = node->next;
                }
                
                // Remove from the time-based doubly linked list
                if(node->timePre != nullptr) {
                    node->timePre->timeNext = node->timeNext;
                } else {
                    beg = node->timeNext;
                }
                
                if(node->timeNext != nullptr) {
                    node->timeNext->timePre = node->timePre;
                } else {
                    current = node->timePre;
                }
                
                // Delete the node
                delete node;
                return;
            }
            prev = node;
            node = node->next;
        }
    }

    vector<string> ask(int key)const{
        vector<string> result;
        Node* node = array[key];
        while(node != nullptr) {
            result.push_back(node->value);
            node = node->next;
        }
        return result;
    }

    vector<Data> forEach()const{
        return forEachMethod(*this);
    }
};

vector<Data> traverseByTime(const LinkedHashMap& obj){
    vector<Data> result;
    Node* node = obj.beg;
    while(node != nullptr) {
        Data data;
        data.key = node->key;
        data.value = node->value;
        result.push_back(data);
        node = node->timeNext;
    }
    return result;
}

vector<Data> traverseByIndex(const LinkedHashMap& obj){
    vector<Data> result;
    // Iterate through array indices in order
    for(int i = 0; i < obj.len; i++) {
        Node* node = obj.array[i];
        // For each key, traverse the list from head to tail
        while(node != nullptr) {
            Data data;
            data.key = node->key;
            data.value = node->value;
            result.push_back(data);
            node = node->next;
        }
    }
    return result;
}

#endif //FINAL_SRC_HPP

