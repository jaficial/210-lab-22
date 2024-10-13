#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

/* REQUIREMENTS:
    CREATE delete_pos(): Deletes a node by its position, not by its value. 
                         Should be able to also delete the head or tail node
    CREATE pop_front(): Deletes the head node
    CREATE pop_back(): Deletes the tail node
    UPDATE delete(): change name to "delete_val()", keep functionality 
                     in the method that will still delete the head node, even 

*/
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
        if (!current) return;
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

    // WORKS: pops head nodes
    void pop_front(){
        Node *temp = head->next;
        temp->prev = nullptr;
        delete head;
        head = temp;
    }

    // WORKS: pops tail nodes
    void pop_back(){
        Node *temp = tail->prev;
        temp->next = nullptr;
        delete tail;
        tail = temp;
    }
    
    // deleting a node by its position:
    // MIGHT NEED TO ADD A CURRENT NODE TO TRAVERSE THE LINKED LIST
    // HAVE FUNCTION TAKE IN INT INSTEAD OF NODE POINTER
    // NOT WORKING YET, IT ISN'T DELETING THE NODE
    void delete_pos(int pos){ // receives int to reference the node
        Node* current = head; // position will be used to traverse the list
        Node* temp;
        Node* temp_pr;
        Node* temp_nx;
        if (pos == 0){ // WORKS if position is the head node, head node gets deleted
            current = head->next;
            delete head;
            current->prev = nullptr;
            head = current;
            return;
        }
	
	// TRY USING THE HEAD TO TRAVERSE WHEN GETTING BACK 
        for (int i = 0; i < pos; i++){ // NOTE: need to traverse the linked list, use current
		    if (current->next == nullptr){ // for deleting the tail node
			    temp = current->prev;
			    delete tail;
			    tail = temp;
			    tail->next = nullptr;
                return;
		    }

		    else if (i == pos){ // going to be the function that deletes the node. COME BACK HERE
	 		    Node* temp_pr = current->prev;
			    Node* temp_nx = current->next;
			    delete current;
			    current = temp_pr;
			    current = temp_nx;
		}
		    else { // for traversing, use temp_pr and temp_nx to traverse. Come back here when back home.
			    
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
    DoublyLinkedList list;
    //int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;
    int size = 10;
    for (int i = 0; i < size; ++i)
        list.push_back(rand() % (MAX_NR-MIN_NR+1) + MIN_NR);

    cout << "Before popping head: \n";    
    list.print();
    list.pop_front();
    cout << "After popping head: \n";
    list.print();

    cout << "Now will pop the tail: \n";
    list.pop_back();
    list.print();

    cout << "Now to test the delete_pos function: \n";
    
    list.delete_pos(7);
    list.print();


    
    
    // cout << "List forward: ";
    // list.print();

    // cout << "List backward: ";
    // list.print_reverse();

    // cout << "Deleting list, then trying to print.\n";
    // list.~DoublyLinkedList();
    // cout << "List forward: ";
    // list.print();

    return 0;
}
