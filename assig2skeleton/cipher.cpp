#include "mainfunctions.h"

using namespace std;

int main(int argc, char** argv)
{
	/* Declaring all local variables. */
	CipherInterface* cipher = NULL;
	char* cipherName_;
	char* inputFileName;
	char* outFileName;
	char* choiceEncDec_;
	unsigned char* cryptoKey;
	unsigned char* cipherText;
	unsigned char* plainText;
	ifstream inFile;
  	ofstream oFile;
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
		
		/* Attempt to find and set proper cipher */
		findCipher(cipher, cipherName_, choiceEncDec_, &cryptoKey);

		/* Convert to string for comparisons */
		string Choice = choiceEncDec_;
		toUpperString(Choice);
		string cipherName = cipherName_;
		toUpperString(cipherName);


		/* Sets cipher key */
		keyIsSet = cipher->setKey(cryptoKey);

		if (keyIsSet) {
			/*=============== Read in text file ============*/
			inFile.open((char*)inputFileName);
			oFile.open((char*)outFileName);

			/* Check is file opened successfully */
			if(!inFile.is_open())
			{
				printf("Error opening file: %s\n", inputFileName);
				throw INVALID_INPUT_FILE;
			}

			/* Check is file opened successfully */
			if(!oFile.is_open())
			{
				printf("Error opening file: %s\n", outFileName);
				throw INVALID_OUTPUT_FILE;
			}

			stringstream buffer;
			buffer << inFile.rdbuf();
  			string text(buffer.str());
  			int fileSize = text.length() - 1;
			unsigned char* newBlock = new unsigned char;
  			unsigned char* txtBuffer = new unsigned char[17];


			/* Perform encryption */
			if(Choice == "ENC"){
				if(cipherName == "AES"){
					for(int i = 0; i < fileSize; i += 16)
					{
						memset(newBlock, 0, 16);

						for(int j = 0; j < 16; j++){
							newBlock[j] = text[i + j];
						}
						cout << i << endl;

						memset(txtBuffer, 0, 16);

						txtBuffer = cipher->encrypt(newBlock);

						for(int j = 0; j < 16; j++){
							oFile << txtBuffer[i];
						}
						

						oFile.flush();
					}

					printf("AES Encryption Was Successful!\n");
				}
				else if(cipherName == "DES"){
					for(int i = 0; i < fileSize; i += 8)
					{
						for(int j = 0; j < 8; j++)
							newBlock[j] = text[i + j];

						txtBuffer = cipher->decrypt(newBlock);

						for(int j = 0; j < 8; j++)
							oFile << txtBuffer[j];
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
					for(int i = 0; i < fileSize; i += 16)
					{
						memset(newBlock, 0, 16);

						for(int j = 0; j < 16; j++){
							newBlock[j] = text[i + j];
						}
							
						memset(txtBuffer, 0, 16);

						txtBuffer = cipher->decrypt(newBlock);

						for(int j = 0; j < 16; j++){
							oFile << txtBuffer[j];
						}
									
						oFile.flush();
					}

					printf("AES Decryption Was Successful!\n");
				}
				else if (cipherName == "DES"){
					for(int i = 0; i < fileSize; i += 8)
					{
						for(int j = 0; j < 8; j++){
							newBlock[j] = text[i + j];
						}
							
						txtBuffer = cipher->encrypt(newBlock);

						for(int j = 0; j < 8; j++){
							oFile << txtBuffer[j];
						}
							
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
