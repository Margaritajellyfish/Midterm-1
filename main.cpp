#include <iostream>
#include <ctime>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20; //define sizes as const

class DoublyLinkedList {
private:
    struct Node {//create node
        int data;
        Node* prev;
        Node* next;
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }//constructor that takes three inputs
    };

    Node* head;
    Node* tail;//pointers that locate first and last node

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; } //constructor

    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }//makeing sure input is valid

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }//when the list is empty

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;//running until the position or when out of order

        if (!temp) {//out of order
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;//elsewise update newnode's two links
        if (temp->next)//if there is a node after newnode, update the link
            temp->next->prev = newNode;
        else
            tail = newNode;//else 
        temp->next = newNode; //update the node before newnode
    }

    void delete_val(int value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;//runing until find value or end

        if (!temp) return; 

        if (temp->prev)//when not the first, update link to skip temp
            temp->prev->next = temp->next;
        else
            head = temp->next; //if first, delete the link to first

        if (temp->next)
            temp->next->prev = temp->prev;//when not the end, update link to skip temp
        else
            tail = temp->prev; //if end, delete the link to end

        delete temp;//the actual node delete
    }

    void delete_pos(int pos) {
        if (!head) {//nothing there
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {//if target position is 1
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){//else find node
            if (!temp) {//nothing
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;//keep running
        }
        if (!temp) {//runs out
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {//if it's the last in list
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;//skip temp in link
        temp->next->prev = tempPrev;
        delete temp;//delete node
    }

    void push_back(int v) {
        Node* newNode = new Node(v);//instantializing node
        if (!tail)//empty
            head = tail = newNode;
        else {
            tail->next = newNode;//link new
            newNode->prev = tail;//link prev
            tail = newNode;//relocate tail
        }
    }
    
    void push_front(int v) {//similar to above
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {//empty
            cout << "List is //empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {//more than one
            head = head->next;//move head to next
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;//delete the only one
        delete temp;//delete data
    }

    void pop_back() {//similar to above
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {//deconstructor to delete nodes and prevent leaking
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {//empty
            cout << "List is empty." << endl;
            return;
        }
        while (current) {//print till no data
            cout << current->data << " ";
            current = current->next;//move forward
        }
        cout << endl;
    }

    void print_reverse() {//similar to above
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    void every_other_element(){
        Node *current = head;
        if(!current){
            cout << "List is empty." << endl;
            return;
        }
    
        while(current){
            cout << current->data << " ";
            current = current->next->next;
        }
        cout << endl;
        }

};

int main() {
    DoublyLinkedList ABC;
    int length = rand() % (MAX_LS - MIN_LS + 1) + MIN_LS;
    for(int i =0; i < length; i++){
        ABC.push_back(rand() % (MAX_NR-MIN_NR+1) + MIN_NR);
    }
    ABC.print();
    ABC.every_other_element();

    
    return 0;
}
