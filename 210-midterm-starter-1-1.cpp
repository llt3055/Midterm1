// COMSC-210 | Midterm1| Tianyi Cao 
#include <iostream>// Includes the standard input-output stream library
#include <ctime>
#include <cstdlib>

using namespace std;// Uses the standard namespace to avoid std:: prefix


///Named constants to avoid "Magic Numbers"
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    // Struct representing a single node in the list
    struct Node {
        int data;   // Integer variable to store the node's value
        Node* prev; // Pointer to the previous node in the sequence
        Node* next; // Pointer to the next node in the sequence
    // Node constructor to initialize data and optional pointers
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; // Assign the passed value to data member
            prev = p;   // Assign the passed previous pointer
            next = n;   // Assign the passed next pointer
        }
    };

    Node* head; // Pointer to  beginning of the list
    Node* tail; // Pointer to  end of the list

public:
    // Constructor: Initializes head and tail to null for an empty list
    DoublyLinkedList() { head = nullptr; tail = nullptr; }
    // Adds a node after some position
    void insert_after(int value, int position) {
        if (position < 0) { // If position is bad
            cout << "Position must be >= 0." << endl; // Show error
            return; 
        }

        Node* newNode = new Node(value); // Make the node
        if (!head) { // If list is empty
            head = tail = newNode; // Set head and tail
            return;
        }

        Node* temp = head; // Temp pointer
        for (int i = 0; i < position && temp; ++i) // Find position
            temp = temp->next; // Move forward

        // Verify if the requested position actually exists within the list's bounds
        if (!temp) { 
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode; // Reclaim memory to prevent a leak if insertion fails
            return;
        }
        // Pointer redirection for the Doubly Linked structure
        newNode->next = temp->next; // Connect new node forward to temp's successor
        newNode->prev = temp;       // Connect new node backward to temp
        if (temp->next)             // If temp is NOT the current tail
            temp->next->prev = newNode; // Reassign the back-link of the successor
        else
            tail = newNode;         // If temp was tail, new node becomes the new tail
        temp->next = newNode;       // Connect temp forward to the new node, completing the insertion
    }

    // Searches for the first occurrence of a value and removes that node
    void delete_val(int value) {
        if (!head) return; // Cannot delete from an empty list

        Node* temp = head; // Temporary pointer for searching
        
        // Loop until we find the node containing the target value
        while (temp && temp->data != value)
            temp = temp->next;

        // Exit if value was not found in the list
        if (!temp) return; 

        // Update the 'next' pointer of the node before 'temp'
        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        // Update the 'prev' pointer of the node after 'temp'
        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 
        // Release the memory of the target node back to the system
        delete temp;
    }

    // Removes a node based on its numerical 1-indexed position
    void delete_pos(int pos) {
        if (!head) { // Ensure there is data to delete
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) { // reuse pop_front if deleting the first element
            pop_front();
            return;
        }
    
        Node* temp = head; // Traversal pointer
        // Loop until the node at the specified position is reached
        for (int i = 1; i < pos; i++){
            if (!temp) { // Handle out-of-range errors
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(int v) {
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

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
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

    // Destructor: Automatically called to reclaim all dynamically allocated memory
    ~DoublyLinkedList() {
        while (head) { // Iterate through the entire list
            Node* temp = head; // Temporarily store the current head pointer
            head = head->next; // Advance head to the next node in the sequence
            delete temp; // Free memory of the orphaned node to prevent leaks
        }
    }

    // Standard forward traversal printing from head to tail
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next; // Advance forward
        }
        cout << endl;
    }

    // Reverse traversal printing from tail to head
    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev; // Advance backward
        }
        cout << endl;
    }
// New required method: Prints 1st, 3rd, 5th, etc. elements
    void every_other_element() {
    Node* current = head; // Start at the first element
        while (current){ // Loop until we fall off the end of the list
            cout << current->data ; // Print the data of the current node
            if (current->next->next) // Check if a next node exists to skip it
                current = current->next; // Jump node forward
            else {
                // If there is no next node to jump over, we are at the end
                current = nullptr; 
            }             
        }
        cout << endl; // Print a newline for clean formatting
    }
};

// New required method: Prints 1st, 3rd, 5th, etc. elements
   
    

int main() {

    DoublyLinkedList list;
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning
    srand(static_cast<unsigned int>(time(0)));// Seed the random number generator with the current time for variability
    // Fill list using random constants
    int size = rand() % (MAX_LS - MIN_LS );
    for (int i = 0; i < size; i++) {
        list.push_back(rand() % (MAX_NR - MIN_NR ) );
    }
    cout << "Initial List:" << endl; // Demonstrate initial creation
    list.print();
    cout << "\nEvery Other Element:" << endl; // Demonstrate the new every_other_element functionality
    list.every_other_element();

    return 0;
}