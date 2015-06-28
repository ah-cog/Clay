#ifndef patchmesh_H
#define patchmesh_H

#include "RF24.h" // Tmrh20 RF24 library
#include <Arduino.h> // for byte data type

class patchmesh{

public:

	int nodeID; // node ID #
	int numNodes; // total # of ID's

	patchmesh(void);
	bool init(int newID, RF24 radio); // intitializes radio and assigns ID

	bool send(int i); // broadcasts an int
	bool send(char c); // broadcasts a char
	int read(int i); // reads an int
	char read(char c); // reads in char

	bool connection(void); // checks if any other radios around
	int getID(void); // returns ID
	int getNodes(void); // returns number of nodes



private:
	byte address; // pipe address
	RF24 radio; // instance of radio ***BROKEN***

};


#endif patchmesh_H