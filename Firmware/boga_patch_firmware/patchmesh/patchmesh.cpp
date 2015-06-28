#include <SPI.h>
#include "RF24.h"
#include <patchmesh.h>

#define PIPE 0xABCDABCD71LL // universal pipe
#define ALL -1
#define HELLO 0
#define ABORT_TIME 500



patchmesh::patchmesh(void){ // constructor

	nodeID = 0; // node ID
	numNodes = 0; // total number of nodes
}

bool patchmesh::init(int newID, RF24 radio){

	if(nodeID == 0 && newID != 0){
		nodeID = newID;
		numNodes = nodeID;
		address = PIPE;

		radio = RF24 radio(9,10);
		radio.begin();
  		radio.enableAckPayload();
  		radio.enableDynamicPayloads();
  		radio.openWritingPipe(address);
  		radio.openReadingPipe(1,address);
  		radio.startListening();

  		return 1;
	}

	return 0;
}

bool patchmesh::send(int i){

	int x = i;
	int flag = 0;

	unsigned long timer = millis();

	radio.stopListening();
	while(!(flag = radio.write(&x, sizeof(int))) && millis()-timer < ABORT_TIME){} // while send is unsuccessful but time remains
	radio.startListening();
	if(flag == 1) return 1;
	else return 0;
}


bool patchmesh::send(char c){

	char x = c;
	int flag = 0;

	unsigned long timer = millis();

	radio.stopListening();
	while(!(flag = radio.write(&x, sizeof(int))) && millis()-timer < ABORT_TIME){} // while send is unsuccessful but time remains
	radio.startListening();
	if(flag == 1) return 1;
	else return 0;

}

int patchmesh::read(int i){ // returns -1 if invalid

	int x;
	if(radio.available()){
		radio.read(&x, sizeof(int));
		return x;
	}

	return -1;
	
}


char patchmesh::read(char c){ // returns null character if invalid

	char x;
	if(radio.available()){
		radio.read(&x, sizeof(int));
		return x;
	}

	return 0;

	
}

bool patchmesh::connection(void){

	unsigned long timer = millis(); // if no connection in half a second, radio can be considered alone
	while(millis()-timer < ABORT_TIME){
		if(radio.available()) return 1;
	}

	return 0;

}


int patchmesh::getID(void){
	return nodeID;
}

int patchmesh::getNodes(void){
	return numNodes;
}
