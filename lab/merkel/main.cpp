/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: michael
 *
 * Created on June 6, 2016, 4:11 PM
 */

#include <cstdlib>

#include <iostream>
#include <sstream>

#include "GeneralHashFunctions.h"

using namespace std;
string stringify( unsigned int, unsigned int );

int main( int argc, char** argv ) {

	string data[4];
	data[0] = "Then out spake brake Horatius, The Captain of the Gate:";
	data[1] = "To every man upon this earth Death cometh soon or late.";
	data[2] = "And how can man die better Than facing fearful odds,";
	data[3] = "For the ashes of his fathers, And the temples of his Gods.";

	unsigned int hashed[7];

	//root, l2 left, l2 right, l3 left, l3 mid-left, l3 mid-right, l3 right
	for ( int i = 3; i < 7; i++ ) {
		unsigned int v = RSHash( data[i - 3] );
		//cout << data[i-3] << " = " << v << endl;
		hashed[i] = v;
	}
	cout << "0-0: " << hashed[3] << endl;
	cout << "0-1: " << hashed[4] << endl;
	cout << "1-0: " << hashed[5] << endl;
	cout << "1-1: " << hashed[6] << endl;

	//hash l2 left
	string s = stringify( hashed[3], hashed[4] );
	hashed[1] = RSHash( s );
	cout << "0: " << hashed[1] << endl;

	//hash l2 right
	s = stringify( hashed[5], hashed[6] );
	hashed[2] = RSHash( s );
	cout << "1: " << hashed[2] << endl;

	//hash root
	s = stringify( hashed[1], hashed[2] );
	hashed[0] = RSHash( s );
	cout << "top: " << hashed[0] << endl;
	
	cout << "\nTree view\n";
	cout << "\t\t\t" << hashed[0] << endl;
	cout << "\t" << hashed[1] << "\t";
	cout << "\t\t" << hashed[2] << "\n";
	cout << hashed[3] << "\t";
	cout << hashed[4] << "\t";
	cout << hashed[5] << "\t";
	cout << hashed[6] << "\n\n";

	//check the hashes
	cout << "checking L1" << endl;
	unsigned int l3h = RSHash( data[0] ); //0-0
	s = stringify( l3h, hashed[4] );
	unsigned int l2h = RSHash( s ); // 0
	s = stringify( l2h, hashed[2] );
	unsigned int top = RSHash( s );
	cout << "\tchecking: " << top << " " << ( ( hashed[0] == top ) ? "matches" : "failed" ) << endl;
	
	
	cout << "checking L2" << endl;
	l3h = RSHash( data[1] ); //0-1
	s = stringify( hashed[3], l3h );
	l2h = RSHash( s ); // 0
	s = stringify( l2h, hashed[2] );
	top = RSHash( s );
	cout << "\tchecking: " << top << " " << ( ( hashed[0] == top ) ? "matches" : "failed" ) << endl;
	
	cout << "checking L3" << endl;
	l3h = RSHash( data[2] ); //1-0
	s = stringify( l3h, hashed[6] );
	l2h = RSHash( s ); // 1
	s = stringify( hashed[1], l2h );
	top = RSHash( s );
	cout << "\tchecking: " << top << " " << ( ( hashed[0] == top ) ? "matches" : "failed" ) << endl;
	
	cout << "checking L3" << endl;
	l3h = RSHash( data[3] ); //1-0
	s = stringify( hashed[5], l3h  );
	l2h = RSHash( s ); // 1
	s = stringify( hashed[1], l2h );
	top = RSHash( s );
	cout << "\tchecking: " << top << " " << ( ( hashed[0] == top ) ? "matches" : "failed" ) << endl;
	

	return 0;
	/*
 	 7189210071243114024
 	 7189210071243114024
	 
				top
		  0			     1
	 0-0	0-1		1-0		1-1
	 */
	
}

string stringify( unsigned int i, unsigned int j ) {
	stringstream ss;
	ss << i << j;
	return ss.str( );
}

