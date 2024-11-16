#include <stdio.h>
#include <string.h>

#define MAX_BUF  256
#define IV 0b11001011

unsigned char initKey();
unsigned char processKey(unsigned char);

void encode(unsigned char*, unsigned char*, unsigned char, int);
void decode(unsigned char*, unsigned char*, unsigned char, int);

unsigned char encryptByte(unsigned char, unsigned char, unsigned char);
unsigned char decryptByte(unsigned char, unsigned char, unsigned char);
unsigned char cShiftRight(unsigned char);
unsigned char cShiftLeft(unsigned char);

int readBytes(unsigned char*, int);
unsigned char getBit(unsigned char, int);
unsigned char setBit(unsigned char, int);
unsigned char clearBit(unsigned char, int);


int main()
{
  char str[8];
  int  choice;
	unsigned char pt[MAX_BUF];
  unsigned char ct[MAX_BUF];
  unsigned char key;
  int numBytes = 0;  
  int input;
  int size = 0;

  printf("\nYou may:\n");
  printf("  (1) Encrypt a message \n");
  printf("  (2) Decrypt a message \n");
  printf("  (0) Exit\n");
  printf("\n  what is your selection: ");
  fgets(str, sizeof(str), stdin);
  sscanf(str, "%d", &choice);


  switch (choice) {
    
    case 1:
   	 	key = initKey();
   	 	
   	 	while(1){
   	 		if(key == 0){
   	 			key = initKey();
   	 		}
   	 		else{
   	 			break;
   	 		}
   	 	}
   	 	
    	printf("Enter plaintext: ");
    	fgets(pt, MAX_BUF, stdin);
    	
    	numBytes = readBytes(pt, MAX_BUF);
    	
    	encode(pt, ct, key, numBytes);
   		
    	printf("Ciphertext: ");
			for (int i = 0; i < numBytes; i++) {
    		printf("%03d ", ct[i]);
			}
			printf("\n");

      break;



    case 2:
    
   	 	key = initKey();
   	 	
   	 	while(1){
   	 		if(key == 0){
   	 			key = initKey();
   	 		}
   	 		else{
   	 			break;
   	 		}
   	 	}
   	 	
    	printf("Enter ciphertext: ");
			while (1) {
				scanf("%d", &input);
				if(input == -1){
					break;
				}				
		    ct[size] = input;
		    size++;
    	}    	
   	
   	
    	decode(ct, pt, key, size);
    	printf("Plaintext: %s \n", pt);
 
      break;



    default:

      break;
  }

  return(0);
}

/*
  Function:  readBytes
  Purpose:   reads characters from the standard output
      out:   the buffer containing the bytes read
       in:   the capacity of the buffer (maximum size)
   return:   the number of bytes actually read from the user
*/
int readBytes(unsigned char* buffer, int max)
{
  int num = 0;

  fgets((char*)buffer, max, stdin);
  num = strlen((char*)buffer) - 1;
  buffer[num] = '\0';

  return num;
}

/*
  Function:  getBit
  Purpose:   retrieve value of bit at specified position
       in:   character from which a bit will be returned
       in:   position of bit to be returned
   return:   value of bit n in character c (0 or 1)
*/
unsigned char getBit(unsigned char c, int n)
{
	return( (c & (1 << n)) >> n );
}

/*
  Function:  setBit
  Purpose:   set specified bit to 1
       in:   character in which a bit will be set to 1
       in:   position of bit to be set to 1
   return:   new value of character c with bit n set to 1
*/
unsigned char setBit(unsigned char c, int n)
{
	return( c | (1 << n) );
}

/*
  Function:  clearBit
  Purpose:   set specified bit to 0
       in:   character in which a bit will be set to 0
       in:   position of bit to be set to 0
   return:   new value of character c with bit n set to 0
*/
unsigned char clearBit(unsigned char c, int n)
{
	return( c & (~(1 << n)) );
}


/*
  Function:  cShiftRight
  Purpose:   perform a circular right shift on a given byte
       in:   the current byte to be shifted
   return:   the result of the circular right shift
*/
unsigned char cShiftRight(unsigned char currByte){
	unsigned char carry = 0; 
	carry = getBit(currByte,0); 
	currByte >>= 1;
	
	if (carry == 1) {
  	currByte = setBit(currByte, 7); 
  }
  
	return currByte;	
}

/*
  Function:  cShiftLeft
  Purpose:   perform a circular left shift on a given byte
       in:   the current byte to be shifted
   return:   the result of the circular left shift
*/
unsigned char cShiftLeft(unsigned char currByte){
	unsigned char carry = 0; 
	carry = getBit(currByte,7);
	 
	currByte <<= 1;
	
	if (carry == 1) {
  	currByte = setBit(currByte, 0); 
	}
	
	return currByte;
}


/*
  Function:  initKey
  Purpose:   Initialize  all bits of the user entered partial key
   return:   the initialized key
*/
unsigned char initKey(){
	unsigned char partialKey;
	int tmpNum;
	int secondPos = 0;

	printf("Enter a number 1-15 to use as your partial key: ");
  scanf("%d", &tmpNum);
   
   
  if (tmpNum < 1 || tmpNum > 15) {
  	printf("Invalid input, please enter a number between 1 and 15.\n");
   	return 0;
  }
  
	else{
		partialKey = tmpNum << 4;
		for(int i = 7; i >=4; i--){
			secondPos = (i - 1) % 4;
			if (getBit(partialKey, i) == 0){
				partialKey = setBit(partialKey, secondPos);
			}
			else{
				partialKey = clearBit(partialKey, secondPos);
			}
		}
		
  	return partialKey;
  }
}


/*
  Function:  processKey
  Purpose:   process the key by circular left shifting the bits a certain number of times based on the current decimal value
       in:   the current key 
   return:   the processed key
*/
unsigned char processKey(unsigned char currKey){

	if(currKey % 3 == 0){
		for(int i = 0; i < 3; i++){
			 currKey = cShiftLeft(currKey);
		}
	}
	else{
		for(int i = 0; i < 2; i++){
			 currKey = cShiftLeft(currKey);
		}	
	}
	
	return currKey;
}


/*
  Function:  encryptByte
  Purpose:   encrypt a byte of plaintext using the provided key through and XOR of the current byte of plaintext with the previous ciphertext byte or IV
       in:   plaintext byte to be encrypted
       in:   current key
       in:   previous ciphertext byte or IV
   return:   the encrypted ciphertext byte
*/
unsigned char encryptByte(unsigned char pt, unsigned char key, unsigned char prev){
	unsigned char tempByte = 0;
	unsigned char result = 0;
	unsigned char keyBit = 0;
	int mirrorPos = 0;
	

	for(int i = 0; i < 8; i++){
		
		keyBit = getBit(key,i);
		
		
		if(keyBit == 1){
			prev = cShiftRight(prev);
		}
		
		mirrorPos = 7 - i;
		
		
		result = (getBit(pt, i)) ^ (getBit(prev, mirrorPos));
		
		
		if(result == 1){
			tempByte = setBit(tempByte, i);
		}
		
	}
	
	return tempByte; 
	
}


/*
  Function:  encode
  Purpose:   encode a message  of plaintext using the specified key and the previous byte of cyphertext
       in:   pointer to the plaintext message
       in:   pointer to the resulting ciphertext
       in:   encryption key
       in:   number of bytes in the message of plaintext
*/
void encode(unsigned char *pt, unsigned char *ct, unsigned char key, int numBytes){
	for(int i = 0; i < numBytes; i++){
		
		key = processKey(key);
	
		if(i == 0){
			ct[i] = encryptByte(pt[i], key, IV);
		}
		else{
			ct[i] = encryptByte(pt[i], key, ct[i - 1]);
		}
	}
}


/*
  Function:  decryptByte
  Purpose:   decrypt a byte of ciphertext using the provided key through and XOR of the current byte of ciphertext with the previous ciphertext byte or IV
       in:   ciphertext byte to be decrypted
       in:   current key
       in:   previous ciphertext byte (or IV)
   return:   the decrypted plaintext byte
*/
unsigned char decryptByte(unsigned char ct, unsigned char key, unsigned char prev){
	unsigned char tempByte = 0;
	unsigned char result = 0;
	unsigned char keyBit = 0;
	int mirrorPos = 0;
	
	for(int i = 0; i < 8; i++){
		
		keyBit = getBit(key,i);
		
		if(keyBit == 1){
			prev = cShiftRight(prev);
		}
		
		mirrorPos = 7 - i;
		
		result = (getBit(ct,i)) ^ (getBit(prev, mirrorPos));
		
		if(result){
			tempByte = setBit(tempByte, i);
		}
		
	}
	
	return tempByte; 
}


/*
  Function:  decode
  Purpose:   decode ciphertext one byte at a time using the specified key
       in:   pointer to the ciphertext
       in:   pointer to store the resulting plaintext
       in:   decryption key
       in:   number of bytes in the ciphertext
*/
void decode(unsigned char *ct, unsigned char *pt, unsigned char key, int numBytes){
		for(int i = 0; i < numBytes; i++){
		
			key = processKey(key);
		
			if(i == 0){
				pt[i] = decryptByte(ct[i], key, IV);
			}
			else{
				pt[i] = decryptByte(ct[i], key, ct[i - 1]);
			}
	}
}



