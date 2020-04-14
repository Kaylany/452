#include "mainfunctions.h"

using namespace std;

int main(int argc, char** argv)
{
	/* Declaring all local variables. */
	CipherInterface* cipher = NULL;
	string cipherName_;
	string inputFileName;
	string outFileName;
	string choiceEncDec_;
	unsigned char* cryptoKey;
	bool keyIsSet = false;


	try {
		/* Checks for invalid number of arguements */
		if(validNumArgs(argc)){
			/* Assigns values if valid number of arguments */
			cipherName_ = argv[1];
			cryptoKey = (unsigned char*) argv[2];
			choiceEncDec_ = argv[3];
			inputFileName = argv[4];
			outFileName =  argv[5];
		}
		else{
			throw INVALID_FORMAT;
		}

		FILE * inFile = fopen(inputFileName.c_str(), "rb");
  		FILE * oFile = fopen(outFileName.c_str(), "wb");;
		/* Attempt to find and set proper cipher */
		findCipher(cipher, cipherName_.c_str(), choiceEncDec_.c_str(), &cryptoKey);

		/* Convert to string for comparisons */
		string Choice = choiceEncDec_;
		toUpperString(Choice);
		string cipherName = cipherName_;
		toUpperString(cipherName);


		/* Sets cipher key */
		keyIsSet = cipher->setKey(cryptoKey);

		if (keyIsSet) {
			/* Check is file opened successfully */
			if(!inFile)
			{
				perror("Error opening input file\n");
				throw INVALID_INPUT_FILE;
			}

			/* Check is file opened successfully */
			if(!oFile)
			{
				perror("Error opening output file\n");
				throw INVALID_OUTPUT_FILE;
			}
			
			unsigned char newBlock[16];
  			unsigned char *txtBufferAES;
			unsigned char *txtBufferDES;

			/* Perform encryption */
			if(Choice == "ENC"){
				if(cipherName == "AES"){
					while(!feof(inFile)){

						// Read the block size
						int readByte = fread(newBlock, 1, 16, inFile);

						// Pad the data if it is less then 16 bytes
						if(readByte != 0 ){
							for(int i = readByte; i < 16; i++){
								newBlock[i] = '0';
							}
							txtBufferAES = cipher->encrypt((const unsigned char*) newBlock);
							fwrite(txtBufferAES, 1, 16, oFile);
						}
					}

					printf("AES Encryption Was Successful!\n");
				}
				else if(cipherName == "DES"){
					while(!feof(inFile)){
						// Read the block size
						int readByte = fread(newBlock, 1, 8, inFile);

						// Pad the data if it is less then 8 bytes
						if(readByte != 0 ){
							for(int i = readByte; i < 8; i++){
								newBlock[i] = '0';
							}
							txtBufferAES = cipher->encrypt((const unsigned char*) newBlock);
							fwrite(txtBufferAES, 1, 8, oFile);
						}
					}

      				printf("DES Encryption Successful!\n");
				}
				else{
					throw INVALID_CIPHER_NAME;
				}
			}
			/* Perform decryption */
			else if(Choice == "DEC"){
				if(cipherName == "AES"){
					while(!feof(inFile)){
						// Read the block size
						fread(newBlock, 1, 16, inFile);

						txtBufferAES = cipher->decrypt((const unsigned char*) newBlock);

						fwrite(txtBufferAES, 1, 16, oFile);
					}
					printf("AES Decryption Was Successful!\n");
				}
				else if (cipherName == "DES"){
					while(!feof(inFile)){
						// Read the block size
						fread(newBlock, 1, 8, inFile);

						txtBufferDES = cipher->decrypt((const unsigned char*) newBlock);

						fwrite(txtBufferDES, 1, 8, oFile);
					}

					printf("DES Decryption Was Successful!\n");
				}
				else{
					throw INVALID_CIPHER_NAME;
				}
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
