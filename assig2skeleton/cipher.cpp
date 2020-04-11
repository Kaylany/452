#include "mainfunctions.h"

using namespace std;

int main(int argc, char** argv)
{
	/**
	 * TODO: Replace the code below	with your code which can SWITCH
	 * between DES and AES and encrypt files. DO NOT FORGET TO PAD
	 * THE LAST BLOCK IF NECESSARY.
	 *
	 * NOTE: due to the incomplete skeleton, the code may crash or
	 * misbehave.
	 */


	/* Declaring all local variables. */
	CipherInterface* cipher = NULL;
	char* cipherName;
	const unsigned char* cryptoKey;
	char* inputFileName;
	char* outFileName;
	const unsigned char* choiceEncDec;
	const unsigned char* cipherText;
	const unsigned char* plainText;
	bool keyIsSet = false;


	try {
		/* Checks for invalid number of arguements */
		if(validNumArgs(argc)){
			/* Assigns values if valid number of arguments */
			cipherName = argv[1];
			cryptoKey = (unsigned char*) argv[2];
			choiceEncDec = (unsigned char*) argv[3];
			inputFileName = argv[4];
			outFileName =  argv[5];
		}
		else{
			throw INVALID_FORMAT;
		}

		/* Attempt to find and set proper cipher */
		findCipher(cipher, cipherName);

		/* Sets cipher key*/
		keyIsSet = cipher->setKey(cryptoKey);

		if (keyIsSet) {
			/* Perform encryption */
			toUpperString(choiceEncDec);
			if(choiceEncDec == "ENC"){
				readFile(inputFileName, plainText);
				cipherText = cipher->encrypt(plainText);
				writeFile(outFileName, cipherText);
				cout << "Encrypted Text is: " << cipherText << endl;

			}
			else if(choiceEncDec == "DEC"){
				/* Perform decryption */
				readFile(inputFileName, cipherText);
				plainText = cipher->decrypt(cipherText);
				writeFile(outFileName, plainText);
				cout << "Decrypted Text is: " << plainText << endl;
			}
			else{
				throw INVALID_CRYPT;
			}
		} 
		else
		{
			throw INVALID_KEY;
		}
	}
	catch (ExceptionError error) {
		displayExeptionError(error);
	}
	return 0;
}
