/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: michael
 *
 * Created on June 6, 2016, 5:16 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <ctime>

#include "GeneralHashFunctions.h"

using namespace std;
typedef unsigned long long ulong;
int main( int argc, char** argv ) {
	srand( time( 0 ) );
	string msg = "michael risher";
	int SIZE = 9;
	ulong results[] = {0,0,0,0,0,0,0,0,0};
	const string names[] = {"RS-Hash", "JS-Hash", "PJW-Hash", "BKDR-Hash", "SDBM-Hash", "DJB-Hash", "DEK-Hash", "FNV-Hash", "BP-Hash"};
	// function pointers
	unsigned (*hashers[SIZE] )(const string &);
	hashers[0] = RSHash;
	hashers[1] = JSHash;
	hashers[2] = PJWHash;
	hashers[3] = BKDRHash;
	hashers[4] = SDBMHash;
	hashers[5] = DJBHash;
	hashers[6] = DEKHash;
	hashers[7] = FNVHash;
	hashers[8] = BPHash;

	int randNum = rand( );

	for ( int j = 0; j < SIZE; j++ ) {
		for ( int i = 0; i < 10000; i++ ) {
			stringstream convert;
			convert << randNum++;
			string strRand = convert.str( );
			string newMsg = msg + strRand;
			unsigned int v = hashers[j]( newMsg );
			if ( v < 10e1 ) {
				results[0]++;
			} else if ( v < 10e2 ) {
				results[1]++;
			} else if ( v < 10e3 ) {
				results[2]++;
			} else if ( v < 10e4 ) {
				results[3]++;
			} else if ( v < 10e5 ) {
				results[4]++;
			} else if ( v < 10e6 ) {
				results[5]++;
			} else if ( v < 10e7 ) {
				results[6]++;
			} else if ( v < 10e8 ) {
				results[7]++;
			} else if ( v < 10e9 ) {
				results[8]++;
			}

		}
	}

	//look at results
	for ( int i = 0; i < SIZE; ++i ) {
		cout << " hash < 10^" << ( 9 - i ) << ": " << results[i] << endl;
	}
	return 0;
}

