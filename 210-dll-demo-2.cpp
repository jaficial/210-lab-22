// COMSC-210 | Lab 22 | Jed Aficial
// github link: https://github.com/jaficial/210-lab-22

#include <iostream>
#include <iomanip>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void push_back(int value) {
        Node* newNode = new Node(value);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(int value) {
        Node* newNode = new Node(value);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }

    void delete_val(int value) {
        if (!head) return; // Empty list

        Node* temp = head;
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; // Value not found

        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }

        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }

        delete temp;
    }

    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty\n";
            return;
        }
        cout << setw(4) << "";
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    // Head node is popped and deleted
    void pop_front(){
        Node *temp = head->next;
        temp->prev = nullptr;
        delete head;
        head = temp;
    }

    // Tail node is popped and deleted
    void pop_back(){
        Node *temp = tail->prev;
        temp->next = nullptr;
        delete tail;
        tail = temp;
    }
    
    void delete_pos(int pos){ // receives int to reference the node
        Node* current = head; // current will be used to traverse the linked list
        Node* temp_head = head; // temp head node

        if (pos == 0){ // if position is the head node, head node gets deleted
            Node* temp = current;
            current = head->next;
            delete head;
            current->prev = nullptr;
            head = current;
            return;
        }
	
        for (int i = 0; i <= pos; i++){ // The "current" node is used to traverse the linked list
		    if (current->next == nullptr){ // If the position is the tail node
			    Node *temp = current->prev; // contains previous node before tail
                temp->next = nullptr;
                delete tail;
                tail = temp;
                return;
            }

		    else if (i == pos){ // contains the function to delete the node
                Node *temp_nx = current->next;
                head = current; // NOTE: Use head node to delete the node from linked list
                current = current->prev;
                current->next = temp_nx;
                delete head;
                head = temp_head;
                return;
		    }

		    else { // Loop is traverses the list
                Node *temp_pr = current; //  temp node holds current as the previous node
                current = current->next; // current is assigned the next node 
                current->prev = temp_pr; // current->prev is assigned the original current (which is now the previous one)
		    }
	    } 
    }
    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program //
int main() {
    srand(time(0));
    DoublyLinkedList list;
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;
    int tail_index = size - 1;

    cout << "The size of the array will be: " << size << " elements long\n\n";
    for (int i = 0; i < size; ++i)
        list.push_back(rand() % (MAX_NR-MIN_NR+1) + MIN_NR);

    cout << "This is the linked list before popping the head:\n";    
    list.print();
    cout << endl;

    list.pop_front();
    cout << "This is the linked list after popping the head:\n";
    list.print();
    cout << endl;
    tail_index--;

    cout << "This will now be the linked list after popping the tail:\n";
    list.pop_back();
    list.print();
    cout << endl;
    tail_index--;

    int pos = 3;
    cout << "To test the \"delete_pos()\" function, the element in the 2nd index position will be deleted:\n";
    list.delete_pos(2);
    list.print();
    cout << endl;
    tail_index--;

    cout << "Now the head of the list will be deleted using the \"delete_pos()\" function:\n";
    list.delete_pos(0);
    list.print();
    cout << endl;
    tail_index--;

    cout << "Now the tail of the list will be deleted using the \"delete_pos()\" function:\n";
    list.delete_pos(tail_index);
    list.print();
    cout << endl;

    list.~DoublyLinkedList();
    return 0;
}