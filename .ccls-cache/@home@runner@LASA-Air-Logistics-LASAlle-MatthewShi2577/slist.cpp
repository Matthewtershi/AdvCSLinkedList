#include "slist.h"
#include <iostream>

using namespace std;

class Airport {
public:
  string code;
  string name;
  string type;
  double latitude;
  double longitude;
  float distance;

  Airport (string c, string n, string t, double lat, double lon) {
    code = c;
    name = n;
    type = t;
    latitude = lat;
    longitude = lon;
  }
};

class Node {

// Constructor
public:
  Airport data;
  Node *next;
  
  Node (Airport d) : data(d) {
    this -> next = NULL;
  }

};

class LinkedList {
public:
  Node *head;
  LinkedList() { head = NULL; }

  /* inserts node at the end of the list */
  void insert(Node *data) {
    Node *next = new Node(*data);
    if (head == NULL) {
      head = next;
      return;
    }

    Node *temp = head;

    while (temp->next != NULL) {
      temp = temp -> next;
    }

    temp -> next = next;
  }

  /* prints out the size of the linkedlist */
  void size() {
    int count = 0;
    Node *temp = head;

    while (temp -> next != NULL) {
      count ++;
      temp = temp->next;
    }

    cout << count << endl;
  }

  void freeList(struct Node* head)
  {
    Node* tmp;
  
     while (head != NULL)
      {
         tmp = head;
         head = head->next;
         free(tmp);
      }
  
  }

  void printList(Node *head) {
    while (head) {
      if (head->data.distance < 100) {
        cout << head->data.name << " " << head->data.distance << " miles from ABA"<< endl;
      }
      //cout << head->data.name << " " << head->data.distance << " " << head->data.latitude << " " << head->data.longitude<< endl;
      head = head->next;
    }
  }
};
