#include <stdlib.h>
#include "StrList.h"
#include <stdio.h>
#include <string.h>


#define STRING_SIZE 100 // Maximum length of string

typedef struct _node
{
    char  *_data;
    struct _node * _next;
} Node;

typedef struct _StrList 
{
    Node* _head;
    size_t _size;
} StrList;


/*
 * Allocates a new empty StrList.
 * It's the user's responsibility to free it with StrList_free.
 */
StrList* StrList_alloc() {
    // Allocate memory for the new StrList
    StrList* newList = (StrList*)malloc(sizeof(StrList));

    // Check if memory allocation was successful
    if (newList != NULL) {
        // put the head pointer to NULL
        (*newList)._head = NULL;
        // put the size to 0
        (*newList)._size = 0;
    }

    // Return the pointer to the new StrList
    return newList;
}

void StrList_free(StrList* StrList){
    Node* current = StrList->_head;
    Node* temp;

    // Free memory for each node
    while (current != NULL) {
        temp = current->_next;
        free(current);
        current = temp;
    }

    // Free memory for the StrList itself
    free(StrList);
}

size_t StrList_size(const StrList* StrList){
   
    int count = StrList->_size;
    return count;
}

void StrList_insertLast(StrList* StrList, const char* data) {
    // Allocate memory for the new node
    Node* newNode = (Node*)malloc(sizeof(Node)); 
    if (newNode == NULL) {
        // Handle allocation failure
        return;
    }
    
    // Allocate memory for the data string inside the node and copy the string
    newNode->_data = strdup(data);
    if (newNode->_data == NULL) {
        // Handle allocation failure
        free(newNode);
        return;
    }
    
    newNode->_next = NULL; // The new node will be the last node, so its next pointer is NULL

    if (StrList->_head == NULL) {
        // If the list is empty, the new node becomes the _head
        StrList->_head = newNode;
    } else {
        // pass on the list to find the last node
        Node* current = StrList->_head;
        while (current->_next != NULL) {
            current = current->_next;
        }
        // Add the new node to the end of the list
        current->_next = newNode;
    }
    // Update the size of the list
    StrList->_size++;
}

char* StrList_firstData(const StrList* StrList){
    if (StrList->_head != NULL) {
        // Return a pointer to the data in the _head node
        return StrList->_head->_data;
    }
    return NULL;
}

void StrList_print(const StrList* StrList) {
    const Node* current = StrList->_head; // Start from the _head of the list
    if (current==NULL)
    {
        printf("\n");
        
    }
    
    // pass on the list and print each string
    while (current != NULL) {
        if (current->_next!=NULL){
        printf("%s ", current->_data); // Print the string stored in the current node
        current = current->_next; // Move to the next node
    }
    if (current->_next==NULL){
        printf("%s\n", current->_data); // Print the string stored in the current node
        current = current->_next; // Move to the next node
    }
}
}

//Prints the word at the given index to the standard output.
void StrList_printAt(const StrList* StrList, int index) {
     Node* current = StrList->_head; // Start from the _head of the list
    int count = 0;

    // pass on the list until reaching the index
    while (current != NULL && count < index) {
        current = current->_next; // Move to the next node
        count++;
    }

    // Print the word at the given index
    if (current != NULL) {
        printf("%s\n", current->_data); // Print the data of the current node
    }
}

// Return the amount of chars in the list.
int StrList_printLen(const StrList* StrList) {
     Node* current = StrList->_head; // Start from the _head of the list
    int totalChars = 0;

    // pass on the list and sum the length of each string
    while (current != NULL) {
        totalChars += strlen(current->_data); // Add the length of the current string
        current = current->_next; // Move to the next node
    }

    return totalChars;
}

int StrList_count(StrList* StrList, const char* data){
     Node* current = StrList->_head; // Start from the _head of the list
    int count = 0;

    // pass on the list and count occurrences of the specified string
    while (current != NULL) {
        if (strcmp(data, current->_data) == 0) {
            count++;
        }
        current = current->_next;
    }

    return count;
}

void StrList_removeAt(StrList* StrList, int index) {
    Node* current = StrList->_head; // Start from the _head of the list
    Node* prev = NULL;
    int count = 0;

    // pass on the list until reaching the index
    while (current != NULL && count < index) {
        prev = current;
        current = current->_next;
        count++;
    }

    // If the index is valid, remove the node at that index
    if (current != NULL) {
        if (prev == NULL) {
            // If the node to be removed is the _head, update the _head pointer
            StrList->_head = current->_next;
        } else {
            // Otherwise, update the next pointer of the previous node
            prev->_next = current->_next;
        }
        free(current); // Free memory for the removed node
        StrList->_size--; // Update the size of the list
    }
}

StrList* StrList_clone(const StrList* Strlist)
{
    StrList* supercopy= StrList_alloc(); //Allocate memory for the new list
    Node* current = Strlist->_head; // Start from the _head of the original list

    // pass on the original list
    while (current != NULL) {
        // Insert a copy of each string into the cloned list
        StrList_insertLast(supercopy, current->_data);
        current = current->_next; // Move to the next node
    }
    return supercopy;
}

// Reverces the given StrList.
void StrList_reverse(StrList* StrList) {
    Node* prev = NULL;
    Node* current = StrList->_head;
    Node* nextNode = NULL;

    // pass on the list and reverse the pointers
    while (current != NULL) {
        nextNode = current->_next; // Store the next node
        current->_next = prev; // Reverse the pointer
        prev = current; // Move to the next pair of nodes
        current = nextNode;
    }

    StrList->_head = prev; // Update the _head pointer to the new first node
}


//Sort the given list in lexicographical order 
void StrList_sort( StrList* StrList){
    Node *i, *j;
    char temp[STRING_SIZE];

    // Bubble sort algorithm
    for (i = StrList->_head; i != NULL; i = i->_next) {
        for (j = i->_next; j != NULL; j = j->_next) {
            if (strcmp(i->_data, j->_data) > 0) {    // Compare strings and swap if not in order
                strcpy(temp, i->_data);
                strcpy(i->_data, j->_data);
                strcpy(j->_data, temp);
            }
        }
    }
}

 // Checks if the given list is sorted in lexicographical order
 // returns 1 for sorted,   0 otherwise
 
int StrList_isSorted(StrList* StrList){
    // Check if the list is empty or contains only one element
    if (StrList->_size <= 1)  {
        return 1;  // A list with 0 or 1 element is considered sorted
    }
    const Node* current = StrList->_head;
    // pass on the list and compare each string with the next one
    while (current->_next != NULL) {
        // Compare the current string with the next one
        if (strcmp(current->_data, current->_next->_data) > 0) {
            return 0;  // Strings are not in lexicographical order
        }
        current = current->_next;  // Move to the next node
    }

    return 1;  // All strings are in lexicographical order
}

 // Given a string and a list, remove all occurrences of this string in the list.
 
void StrList_remove(StrList* _StrList, const char* data) {
    Node* current = _StrList->_head;
    int index = 0;

    while (current != NULL) {
        if (strcmp(data,current->_data) ==0) {
           
           
            // Current _Node data matches the specified string, remove it
            current=current->_next;
            StrList_removeAt(_StrList, index);
            
        } else {
            // Move to the next _Node
            current = current->_next;
            index++;
        }
    }
}

 //Checks if two _StrLists have the same elements.
  //Returns 0 if they are not equal, and any other number if they are equal.
 
int StrList_isEqual(const StrList* _StrList1, const StrList* _StrList2) {
    // Check if the sizes of the lists are different
    if (StrList_size(_StrList1) != StrList_size(_StrList2)) {
        return 0; // Sizes are different, lists not equal
    }

    // pass on both lists and compare each element
     Node* current1 = _StrList1->_head;
     Node* current2 = _StrList2->_head;

    while (current1 != NULL && current2 != NULL) {
        // Compare the datas of current _Nodes
        if (strcmp(current1->_data, current2->_data) != 0) {
            return 0; // Data at current positions is different, lists are not equal
        }
        // Move to the next _Nodes
        current1 = current1->_next;
        current2 = current2->_next;
    }

    // If both current pointers are NULL at the end of this code, lists are equal
    // if not, the lists are differents
     if(current1 == NULL && current2 == NULL){
        return 1;
     }
     return 0;
}

// Inserts an element at given index
void StrList_insertAt(StrList* StrList, const char* data, int index) {
    // Allocate memory for the new node
    Node* new_Node = (Node*)malloc(sizeof(Node));
    if (new_Node == NULL) {
        // Handle allocation failure
        return;
    }
    
    // Allocate memory for the data string inside the node and copy the string
    new_Node->_data = strdup(data);
    if (new_Node->_data == NULL) {
        // Handle allocation failure
        free(new_Node);
        return;
    }
    
    // Set the next pointer of the new node to NULL
    new_Node->_next = NULL;

    if (index == 0 || StrList->_head == NULL) {
        // Insert at the beginning of the list
        new_Node->_next = StrList->_head;
        StrList->_head = new_Node;
    } else {
        // pass on the list to find the node at index - 1
        Node* current = StrList->_head;
        int currentIndex = 0;
        while (current->_next != NULL && currentIndex < index - 1) {
            current = current->_next;
            currentIndex++;
        }
        // Insert the new node after the current node
        new_Node->_next = current->_next;
        current->_next = new_Node;
    }

    // Increase the size of the list
    StrList->_size++;
}