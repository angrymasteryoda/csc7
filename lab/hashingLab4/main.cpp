/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: michael
 *
 * Created on April 25, 2016, 10:59 AM
 */

#include <cstdlib>

#include <iostream>
#include <string>
#include "GeneralHashFunctions.h"


using namespace std;

/*
 * 
 */
int main( int argc, char** argv ) {
	std::string key = "Then out spake brave Horatius, The Captain of the Gate: To every man upon this earth Death cometh soon or late. And how can man die better Than facing fearful odds, For the ashes of his fathers, And the temples of his gods.";
//"abcdefghijklmnopqrstuvwxyz1234567890";
	key = "Hello World";

	cout << "General Purpose Hash Function Algorithms Test" << std::endl;
	cout << "By Arash Partow - 2002        " << std::endl;
	cout << "Key: " << key << std::endl;
	cout << " 1. RS-Hash Function Value:   " << RSHash( key ) << std::endl;
	cout << " 2. JS-Hash Function Value:   " << JSHash( key ) << std::endl;
	cout << " 3. PJW-Hash Function Value:  " << PJWHash( key ) << std::endl;
	cout << " 4. ELF-Hash Function Value:  " << ELFHash( key ) << std::endl;
	cout << " 5. BKDR-Hash Function Value: " << BKDRHash( key ) << std::endl;
	cout << " 6. SDBM-Hash Function Value: " << SDBMHash( key ) << std::endl;
	cout << " 7. DJB-Hash Function Value:  " << DJBHash( key ) << std::endl;
	cout << " 8. DEK-Hash Function Value:  " << DEKHash( key ) << std::endl;
	cout << " 9. FNV-Hash Function Value:  " << FNVHash( key ) << std::endl;
	cout << "10. BP-Hash Function Value:   " << BPHash( key ) << std::endl;
	cout << "11. AP-Hash Function Value:   " << APHash( key ) << std::endl;
	return 0;
}

