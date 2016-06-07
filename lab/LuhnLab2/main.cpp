/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: michael
 *
 * Created on March 21, 2016, 2:00 PM
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

/*
 * 
 */
enum CreditCard { AMEX, VISA, MASTER, DISCOVER, ALL };
struct SizedArr {
	char *cc;
	int size;
};
SizedArr genCC(CreditCard);
char rndDgit( );
CreditCard randType();
char *luhn( char *cc, int size );
void flipDigit( SizedArr );
bool verify( SizedArr );
string typeToString(CreditCard cc);

int main( int argc, char** argv ) {
	srand( time( 0 ) );
	int TIMES = 10000;
	SizedArr cc;
	int results[2] = {0,0};
	//cout << "Type \tOriginal num\tFlipped Value\tValid?\n";
	for( int i = 0; i < TIMES; i ++ ){
		CreditCard type = randType();
		cc = genCC( type );
//		cout << typeToString( type ) << "\t";
//		cout << cc.cc << "\t";
		flipDigit( cc );
//		cout << cc.cc << "\t";
		if( verify( cc ) ) {
			results[0]++;
//			cout << "valid" << endl;
		} else {
			results[1]++;
//			cout << "invalid" << endl;
		}
		
	}
	delete [] cc.cc;
	cout << "flipped two digits\n";
	cout << "Valid: " << results[0] << " - " << ( ( (float)results[0] / (float)TIMES ) * 100 ) << "%" << endl;
	cout << "Invalid: " << results[1] << " - " << ( ( (float)results[1] / (float)TIMES ) * 100 ) << "%" << endl;
	
	results[0] = results[1] = 0;
	for( int i = 0; i < TIMES; i ++ ){
		CreditCard type = randType();
		cc = genCC( type );
//		flipDigit( cc );
		int idx1 = rand() % (cc.size-2);
		int idx2 = rand() % (cc.size-2);
		cc.cc[idx1] ^= cc.cc[idx2];
		cc.cc[idx2] ^= cc.cc[idx1];
		cc.cc[idx1] ^= cc.cc[idx2];
		
		if( verify( cc ) ) {
			results[0]++;
		} else {
			results[1]++;
		}
		
	}
	delete [] cc.cc;
	cout << "transposed\n";
	cout << "Valid: " << results[0] << " - " << ( ( (float)results[0] / (float)TIMES ) * 100 ) << "%" << endl;
	cout << "Invalid: " << results[1] << " - " << ( ( (float)results[1] / (float)TIMES ) * 100 ) << "%" << endl;
	return 0;
}

SizedArr genCC( CreditCard cc ){
	int length = 16;
	int prefixLen = 0;
	char *prefix;
	char *cardNum;
	switch( cc ){
		case VISA :
			length = ( rand() % 2 ) ? 13 : 16 ;
			prefixLen = 1;
			prefix = new char[ prefixLen ];
			prefix[0] = '4';
			break;
		case MASTER :
			length = 16;
			prefixLen = 2;
			prefix = new char[ prefixLen ];
			prefix[0] = '5'; prefix[1] = '1';
			break;
		case DISCOVER :
			length = 16;
			prefixLen = 4;
			prefix = new char[ prefixLen ];
			prefix[0] = '6'; prefix[1] = '0'; prefix[2] = '1'; prefix[3] = '1';
			break;
		case AMEX : 
			prefixLen = 2;
			length = 15;
			prefix = new char[ prefixLen ];
			prefix[0] = '3'; prefix[1] = '4';
			break;
		case ALL:
			length = ( rand() % 2 ) ? 13 : ( rand() % 2 ) ? 15 : 16 ;
			prefixLen = 0;
			break;
	}
	
	cardNum = new char[ length + 1 ]; //for the null pointer
	for ( int i = 0; i < prefixLen; i++ ) { //copy the prefix
		cardNum[i] = prefix[i];
	}
	
	for( int i = prefixLen; i < length - 1; i++ ) {
		cardNum[i] = rndDgit( );
	}
	
	for ( int i = length - 1; i <= length; i++ ) {
		cardNum[i] = '\0';
	}
	if( prefixLen != 0 ){
		delete [] prefix;
	}
	SizedArr sized;
	sized.cc = luhn( cardNum, length - 1 );
	sized.size = length;
	return sized;	
}

char *luhn( char *cc, int size ){
	char doubled[size];
	for( int i = 0; i < size; i++ ){
		doubled[i] = cc[i];
	}
	
	//double every other and minus 9 if needed
	for( int i = size - 1; i >= 0; i-=2 ){
		doubled[i] = ( doubled[i] - 48 ) * 2 + 48;
		if( doubled[i] - 48  > 9 ) { 
			doubled[i] = ( doubled[i] - 48 ) - 9 + 48;
		}
	}
	int total = 0;
	for( int i = 0; i < size; i++ ){
		total += ( doubled[i] - 48 );
	}

	cc[size] = ( ( total * 9 )% 10 ) + 48;
	return cc;
}

char rndDgit( ) {
	return rand( ) % 10 + 48;
}

void flipDigit( SizedArr sa ){
	int idx1 = rand() % (sa.size-2);
	int idx2 = rand() % (sa.size-2);
	sa.cc[idx1] = rndDgit();
	sa.cc[idx2] = rndDgit();
}

bool verify( SizedArr sa ){
	char *cc = sa.cc;
	int size = sa.size;
	size-=1;
	char doubled[size];
	for( int i = 0; i < size; i++ ){
		doubled[i] = cc[i];
	}
	
	//double every other and minus 9 if needed
	for( int i = size - 1; i >= 0; i-=2 ){
		doubled[i] = ( doubled[i] - 48 ) * 2 + 48;
		if( doubled[i] - 48  > 9 ) { 
			doubled[i] = ( doubled[i] - 48 ) - 9 + 48;
		}
	}
	int total = 0;
	for( int i = 0; i < size; i++ ){
		total += ( doubled[i] - 48 );
	}

	return ( cc[size] == ( ( total * 9 )% 10 ) + 48 );
}

CreditCard randType(){
    return static_cast<CreditCard>( rand() % ALL );
}

string typeToString( CreditCard cc ){
	switch( cc ){
		case VISA : return "Visa";
		case AMEX : return "AmEx";
		case MASTER : return "Master";
		case DISCOVER : return "Discover";
		case ALL : return "ALL";
	}
}