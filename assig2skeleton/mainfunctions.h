#ifndef __MAIN_FUNCTIONS__
#define __MAIN_FUNCTIONS__
#define REQ_ARGS 6	

#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "errorhandling.h"
#include "CipherInterface.h"
#include "AES.h"
#include "DES.h"



using namespace std;

/*
* These are the implamentations of a few helper functions for main
*/

/* Creating a enum values for ciphers. */
enum cipherValue {AES_, DES_, UNKNOWN};

/* Create key-value pair between string and the cipher value. */
const unordered_map<string, cipherValue> cipherNames = { make_pair("AES", AES_), make_pair("DES", DES_) };

/* Function prototypes */
void setChoice(char * choice);
bool validNumArgs(int argc);
void findCipher(CipherInterface* &cipher,const char* cipherName_,const char* choiceEncDec_, unsigned char** cryptoKey);
void setCipher(CipherInterface* &cipher, cipherValue cipherChoice, string choiceEncDec_, unsigned char** cryptoKey);
void readFile(char* filename, string &text);
void writeFile(char* fileName, string &text);
cipherValue stringToValue(string cipherName);
void toUpperString(string &str);

#endif