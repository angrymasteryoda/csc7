/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: michael
 *
 * Created on May 11, 2016, 11:13 AM
 */

#include <cstdlib>
#include <iostream>
#include <cmath>
#include "GeneralHashFunctions.h"
using namespace std;

struct setData{
	unsigned int *set;
	int *bits;
	int *bytes;
};
setData * set( char bitArr[], int nBits, string in );
void setBit( char bitArr[], int nBits, int i, setData *data );

int main( int argc, char** argv ) {
	
	int nBits = 387; //for a 0.1% error with 9 hashes and 20 elems
	const int SIZE = nBits / 8 + 1;
	char bitArray[SIZE];

	cout<<"The number of bits in the array = "<<nBits<<endl;
    cout<<"The size of the byte array = "<<SIZE<<endl;
	cout<<"The bits to set = ";
//	unsigned int bitset = RSHash( "Michael" ) % nBits; //the bit we are setting
	setData *setBits = set( bitArray, nBits, "Michael" );
	
	cout << endl;
	cout<<"The number of bits in the array = "<<nBits<<endl;
    cout<<"The size of the byte array = "<<SIZE<<endl;
	cout<<"The bits to set = ";
	for( int i = 0; i < 9; i++ ){
		cout<<setBits->set[i] << ", ";
	}
	cout<<"\nThe bytes = ";
	for( int i = 0; i < 9; i++ ){
		cout<<setBits->bytes[i] << ", ";
	}
	
	cout<<"\nThe bits = ";
	for( int i = 0; i < 9; i++ ){
		cout<<setBits->bits[i] << ", ";
	}
	
	//find it
	bool set = true;
	for( int i = 0; i < 9; i++ ){
		if( !( ( bitArray[setBits->bytes[i]] >> setBits->bits[i] ) & 1 ) ){
			set = false;
		}
	}
	cout << "\nis set: " << ( set ? "true" : "false" );
	//bool set = ( bitArray[byte] >> bit ) & 1;
//	
//    cout<<"The value of 2^"<<bit<<" = "<<pow(2,bit)<<endl;
//    cout<<"The value of the bitVec = " << (int)(bitArray[byte])<<endl;
//    if(set)cout<<"The bit was set"<<endl;
	delete [] setBits->bits;
	delete [] setBits->set;
	delete [] setBits->bytes;
	delete setBits;
	return 0;
}

setData * set( char bitArr[], int nBits, string in ){
	unsigned int *bitset = new unsigned int[9];
	int i = 0;
	setData *data = new setData;
	data->bits = new int[9];
	data->bytes = new int[9];
	data->set = new unsigned int[9];
	
	data->set[i] = RSHash( in ) % nBits;
	setBit( bitArr, nBits, i, data );
	i++;
	
	data->set[i] = JSHash( in ) % nBits;
	setBit( bitArr, nBits, i, data );
	i++;
	
	data->set[i] = PJWHash( in ) % nBits;
	setBit( bitArr, nBits, i, data );
	i++;
	
	data->set[i] = ELFHash( in ) % nBits;
	setBit( bitArr, nBits, i, data );
	i++;
	
	data->set[i] = BKDRHash( in ) % nBits;
	setBit( bitArr, nBits, i, data );
	i++;
	
	data->set[i] = SDBMHash( in ) % nBits;
	setBit( bitArr, nBits, i, data );
	i++;
	
	data->set[i] = DJBHash( in ) % nBits;
	setBit( bitArr, nBits, i, data );
	i++;
	
	
	data->set[i] = DEKHash( in ) % nBits;
	setBit( bitArr, nBits, i, data );
	i++;
	
	data->set[i] = BPHash( in ) % nBits;
	setBit( bitArr, nBits, i, data );
	i++;
	return data;
}

void setBit( char bitArr[], int nBits, int i, setData *data ){
	
	data->bytes[i] = data->set[i] / 8;
	data->bits[i] = data->bytes[i] % 8;
	//set it
	bitArr[data->bytes[i]] |= 1 << data->bits[i];
}
/*
 * set bit 302
 * 
 * n bits = 1000
 * char array nbits/8 + 1
 * bit shift >> and << 
 * 302/8 = the byte we set
 * 
 * how to size the array
 * false alram rate 
 * = ( ( k*m ) / n )^k
 * k = # hashes
 * m = # elements in list
 * n = size bit vector
 * 
 * true false alram rate
 * (#bitsSet/n)^k
 */


