#include "mainfunctions.h"

//=======================================================================//
//    Description: This function will validate if the correct number of
//				   arguement has been entered.
//
//    Input: arc - the number of arguements entered in the command line		 
//    Output: true - if correct number of arguements; false otherwise
//======================================================================//
bool validNumArgs(int argc){
	if (argc != REQ_ARGS){

		cout << "You have entered " << argc << " argument" << ((argc > 1 || argc == 0) ? "s " : " ") <<
			"when " << REQ_ARGS << " are required." << endl;
		return false;
	}
	return true;
	
}

//=======================================================================//
//    Description: This function will convert a string arguement into a
//				   cipher value.
//
//    Input: cipherName - the users cipher arguement
//    Output: cipherChoice - the string arguements cipher value 
//======================================================================//

cipherValue stringToValue(string cipherName_){
	cipherValue cipherChoice = UNKNOWN;
    string cipherName = cipherName_;
	
	/* Make input all caps */
	transform(cipherName.begin(), cipherName.end(), cipherName.begin(), ::toupper);

	/* Checks to see if user input chiper exists. */
	if(cipherNames.find(cipherName) == cipherNames.end()){
		/* If it doesn't exist throw exception. */
		throw INVALID_CIPHER_NAME;
	}
	else
	{
		/* If it does exist assign it value from the map. */
		cipherChoice = cipherNames.find(cipherName)->second;
	}

	return cipherChoice;
}

//=======================================================================//
//    Description: This function will find and set the proper
//				   cipher class.
//
//    Input: cipher - cipher refrence that will be assigned
//			 cipherChoice - cipher value that determines what
// 							class to choose.
//    Output: none
//======================================================================//

void findCipher(CipherInterface* &cipher, const char* cipherName_,const char* choiceEncDec_, unsigned char** cryptoKey) {
    string cipherName = cipherName_;
    string choiceEncDec = choiceEncDec_;
	setCipher(cipher, stringToValue(cipherName), choiceEncDec,  cryptoKey);
}

//=======================================================================//
//    Description: This function will set the proper cipher instance.
//
//    Input: cipher - cipher refrence that will be assigned
//			 cipherChoice - cipher value that determines what
// 							class to choose.
//    Output: none
//======================================================================//

void setCipher(CipherInterface* &cipher, cipherValue cipherChoice, string choiceEncDec_, unsigned char** cryptoKey){
	/* Assigns the peoper cipher instance. */
    unsigned char *temp = (unsigned char *)malloc((unsigned int)34*sizeof(unsigned char));
	memset(temp, 0 ,34);
	switch (cipherChoice) {
		case AES_:
			cipher = new AES();
            if(choiceEncDec_ == "ENC"){
			    temp[0] = '0';
			    strcpy((char*)temp+1, (char*)*cryptoKey);
				*cryptoKey= temp;
            }
            else if(choiceEncDec_ == "DEC"){
			    temp[0] = '1';
			    strcpy((char*)temp+1, (char*)*cryptoKey);
				*cryptoKey= temp;
            }
			break;
		case DES_: 
			cipher = new DES();
			break;
		default:
			break;
	}
	/* if cipher is null failed to allocate */
	if (!cipher)
	{
		fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",
			__FILE__, __FUNCTION__, __LINE__);
		exit(-1);
	}
}

//=======================================================================//
//    Description: This function will read a file and assign it to a 
//				   a string named text.
//
//    Input: filename - the file name to look for
//			 text - the location in which the file will be read into
//    Output: none
//======================================================================//
 void readFile(char* filename,  string &text){
    ifstream myFile(filename);
	if (myFile.fail())
	{
		cout << "Unable to open file" << endl;
		throw INVALID_INPUT_FILE;
	}
}
//=======================================================================//
//	Description: Prints out enc/dec text into a file
//               
//	Input: fileName - the file will be name this string
//		   text - the dec/enc data

//	Output: none
//======================================================================//
void writeFile(char* fileName, string &text){
	//Prints out to a file 
    ofstream oFile;
    oFile.open(fileName);
	if(oFile.fail()){
		cout << "Unable to create file " << endl;
		throw INVALID_OUTPUT_FILE;
	}
	else{
		oFile << text << endl;
	}   
	oFile.close();
}

//=======================================================================//
//	Description: This function converts a string to all capital letters
//
//	Input: str - string that will be made into all caps
//
//	Output: none
//======================================================================//
void toUpperString(string  &str){
	/* Sets users key to all caps */
	transform(str.begin(), str.end(), str.begin(), ::toupper);
}
