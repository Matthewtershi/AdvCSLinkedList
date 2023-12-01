

#include "slist.h"
#include "slist.cpp"
#include <cmath>
#include <fstream>
#include <iostream>

using namespace std;

Node* simpleSortTotal(Node *head);
void swapNodes (Node *a, Node *b);
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);

int main() {
	ifstream infile;
	char cNum[10];
	//Airport *airportArr[13500];
	int airportCount;
  LinkedList ll;
  
  string reference = "Austin Bergstrom International Airport";
  string line;
  char code[32], name[32], type[32], temp[32], temp2[32], temp3[32], temp4[32], temp5[32], temp6[32], temp7[32];
  double latitude, longitude, tempInt;
  
	infile.open("airport-codes_US.csv", ifstream::in);
	if (infile.is_open()) {
		int c = 0;
    //getline( infile, line );
    while (getline(infile, line)) {
      if (c < 22337) {
        /* Assuming CSV format: orderDate,region,rep,item,unit,price */
      
        if (sscanf(line.c_str(), "%[^,],%[^,],%[^,],%lf,%lf",
            code, type, name, &latitude, &longitude) == 5) {
        }

        //cout << code << " "<< type << " "<< name << " " << latitude << " " << longitude << endl;
          
        Airport *newAirport = new Airport(code, name, type, latitude, longitude);
        Node *newNode = new Node(*newAirport);

        //cout << name << endl; // print names of all airports
        ll.insert(newNode);
        
      } else {
        //cout << "ALL AIRPORTS Instantiated" << endl;
        break;
      }

      c++;
    }
    airportCount = c - 1;
    
    Node *current = ll.head;
    float refx;
    float refy;
    
    while (current) {
      if (current->data.name == reference) {
        refx = current -> data.latitude;
        refy = current -> data.longitude;
      }
      //cout << node -> data.name << endl;
      current = current -> next;
    }
    //ll.printList(ll.head);

    //cout << "AUSTIN FOUND" << endl;


    /* Calculating distance ----------------- */
    Node *temp = ll.head;
    float x;
    float y;
    //Airport *furthestAirport = new Airport("", "", "", 0.0, 0.0);
    //float maxDist = 0;
    while (temp) {
      x = temp -> data.latitude;
      y = temp -> data.longitude;
      float distance = distanceEarth(refx, refy, x, y);
      temp -> data.distance = distance;
      // if (temp->data.name == "Sanford Fargo Medical Center Heliport") {
      //   cout << temp -> data.name << " " << temp->data.distance << endl;
      // }
      //cout << temp -> data.name << " " << temp->data.distance << endl;
      temp = temp -> next;
    }

    //ll.printList(ll.head);
    /* Calculating distance ----------------- */

    Node *final = simpleSortTotal(ll.head);

    ll.printList(final);

    delete temp;
    delete current;

    //cout << "Furthest Airport: " << furthestAirport->name << " " << furthestAirport -> distance << endl;

    infile.close();
	} else {
		cout << "Error opening file";
	}
}
const double pi = 3.14159265358979323846;
const double earthRadiusKm = 6371.0;


// This function converts decimal degrees to radians
double deg2rad(double deg) {
	return (deg * pi / 180);
}

//  This function converts radians to decimal degrees
double rad2deg(double rad) {
	return (rad * 180 / pi);
}

/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */

double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
	double lat1r, lon1r, lat2r, lon2r, u, v;
	lat1r = deg2rad(lat1d);
	lon1r = deg2rad(lon1d);
	lat2r = deg2rad(lat2d);
	lon2r = deg2rad(lon2d);
	u = sin((lat2r - lat1r) / 2);
	v = sin((lon2r - lon1r) / 2);
	return 2.0 * earthRadiusKm *
		asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

void swapNodes(Node *a, Node *b) {
  Airport temp = a->data;
  a->data = b->data;
  b->data = temp;
}

Node* simpleSortTotal(Node *head) {
	if (!head) {
    cout << "Invalid List!" << endl;
    return NULL;
  }

  bool swapped;
  Node *temp;
  Node *prev = NULL;

  do {
    swapped = false; 
    temp = head;

    while (temp->next != prev) {
      if (temp->data.distance > temp->next->data.distance) {
        swapNodes(temp, temp->next);
        swapped = true;
      }
      temp = temp->next;
    }
    prev = temp;
  } while (swapped);

  return head;
}
