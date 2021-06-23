#include <stdio.h> // Standard input/output
#include<string.h> // strlen(), strcpy(), and dealing with strings
#include<stdlib.h> // malloc(), calloc(), free() Memory Allocation
#include<ctype.h>  // toupper(), isalpha(), isspace() Validating Strings

/*-------------------------------------------------------------------------------------------------
(This value can be modified)*/
#define MAXSIZE 255 /*This defines the size of the maximum characters the userInput array can hold
---------------------------------------------------------------------------------------------------*/

//////////FUNCTION LISTS\\\\\\\\\
// Displays the ascii art for all each user selected menu (To indicate which menu user have selected)
void menu(int selectMenu); 

// Checks the string for valid characters and converts it to uppercase (To prevent unnecessary character from being processed resulting in invalid output)
int stringValidator(char userInput[]); //Returns 0 if the user input is valid otherwise Returns 1 

// keys() function gets both of the keys from the user and calls the keyValidator() function to check for its validity (To make sure encryption/decryption process is consistent)
void keys(int* key1, int* key2); //Displays suitable error based on what keyValidator() function returns
int keyValidator(int key1, int key2); //Returns 0 if key is valid
									  //Returns 1 if the key 
									  //Returns 2 if the key exceeds the range of 0-25 

// Encrypts the plaintext into ciphertext with two given keys
void encryption(char userInput[],int key1, int key2); 

// Decrypts the ciphertext into plaintext with two given keys
void decryption(char userInput[],int key1, int key2); 

// Populates the array with all possible key combination (So each key can be passed to decrypting function seperately)
void bruteForce(int *key1, int *key2);

// Creates an array that counts each letters from the user input and analyses it to find out the two most frequent letter from the given ciphertext (Used to bruteforce probability from high to low)
void frequencyAnalyser(char userInput[], int *firstnum, int *secondnum); 

// This uses the stored key from first and second frequent letter and compare them with each other, if the key matches then it prints it out to the user as a possible output
void possibleOutput(int *output1_1,int *output1_2,int *output2_1,int *output2_2,char bruteforceUserInput[]);


//////////MAIN FUNCTION\\\\\\\\\\

void main ()
{ 
	char userInput[MAXSIZE]; 
	
	int key1 = 0, key2 = 0;
	
	int programExit = 1; //Program exit when this turns to 0
	
	int menuChoice = 0;
	int mainMenu = 0; //Menu option 0
	int encryptionMenu = 1; //Menu option 1
	int decryptionMenu = 2; //Menu option 2
	int decryptionMenuNoOptions = 3; //Menu option 3
	
	
	int decryptionChoice = 0; // Choice for decryption menu
	int decryptionOutputChoice = 0; // Choice for decryption output
	
	//Both array combined stores all the possibilities of the keys
	int* bruteforceKey1;  
	int* bruteforceKey2; 
	char* bruteforceUserInput;

	int firstLetter = 0; int secondLetter = 0; // Stores the 2 most frequent letter from the userInput ciphertext
	
	// Stores the key for both first and second most frequent letters found withing the userInput 
	int* possibleoutput1_1; int* possibleoutput1_2; 
	int* possibleoutput2_1; int* possibleoutput2_2; 
	
	// Counter for first and second most frequent letters to process all the possible alphabet from most common to least common
	int firstLetterCounter;
	int secondLetterCounter;
	
	// Counter for array that increments when a key gets stored to prevent unnecessary blank space in array
	int arrfirstLetterCounter;
	int arrsecondLetterCounter;
	
	//Program keeps looping until a part of program finishes i.e when plaintext is encrypted into ciphertext (To ensure the program only exits when it has finished its task)
	do 
	{	
		menu(mainMenu);
		
		// This loop makes sure user only inputs integers to be store inside the int variable (To prevent scanf from trying to store ascii character inside an integer variable leading to an error)
		printf("What would you like to do, please enter the corrosponding number: ");
		while(scanf("%d",&menuChoice) != 1)
		{	
			menu(mainMenu);
			printf("What would you like to do, please enter the corrosponding number: ");
			while(getchar() != '\n');
		}
		getchar(); //scanf() leaves the \n in stdin after it reads the input from the user so to get that \n out from the stdin, getchar() gets used

		switch(menuChoice)
		{
			case 1: //ENCRYPTION
				menu(encryptionMenu);
				
				//|______________PlainText__________________|	
				do
				{  
					printf("\nPlease enter your plaintext: ");
					fgets(userInput,MAXSIZE,stdin);
				}
				while(stringValidator(userInput)==1);
				
				//|_________________Keys____________________|
				keys(&key1,&key2);
				
				//|______________Encryption_________________|
				encryption(userInput,key1,key2);
				
				// Exits the program
				printf("\nThanks for using the program!\n\n");
				programExit = 0;
				
			break;
				
			case 2: //DECRYPTION
				do
				{
					menu(decryptionMenu);
					//Decryption menu selector (So user is not forced to use bruteforce method when they already have the key making the bruteforce useless)
					printf("Enter the corrosponding number: ");
					while(scanf("%d",&decryptionChoice) != 1)
					{	
						menu(decryptionMenu);
						printf("Enter the corrosponding number: ");
						while(getchar() != '\n');
					}
					getchar();
					
					// Decryption with known key
					switch(decryptionChoice)
					{
						case 1: //Known key decryption
							// This loop runs until the user input string is satisfied via stringValidator() function
							menu(decryptionMenuNoOptions);
							printf("\nKnown key decryption selected\n");
							do 
							{
								printf("\nPlease enter your ciphertext: ");
								fgets(userInput,MAXSIZE,stdin);
							}
							while(stringValidator(userInput)==1);
							
							//|______________Keys________________________|
							keys(&key1,&key2);
							//|____________Decryption____________________|
							decryption(userInput,key1,key2);
							
							printf("Your plaintext is: %s\n",userInput);
							printf("With key (%d, %d)\n",key1, key2);
							
							printf("\nThanks for using the program!\n\n");
							programExit = 0;
							
						break;
						
						case 2:// Decryption with bruteforcing
							menu(decryptionMenuNoOptions);
							printf("\nBruteForce Selected\n");
							// Runs the loop until user enters 1 or 2 other inputs dont get accepted to prevent accidental code trigger
							
							do  //This loop runs until the user input is satisfied
							{
								printf("\nPlease enter your ciphertext: ");
								fgets(userInput,MAXSIZE,stdin);
							}
							//|______________StringValidator____________|
							while(stringValidator(userInput)==1);
							
							do
							{
								printf("\n\nWhat type of output you prefer?\n\n");
								printf("\t1. Probability answer from high to low\t\t");
								printf("2. Logical key order from low to high\n");
								printf("\nEnter the corrosponding number:");
								while(scanf("%d",&decryptionOutputChoice) != 1)
								{	
									printf("\n\nWhat type of output you prefer?\n\n");
									printf("\t1. Probability answer from high to low\t\t");
									printf("2. Logical key order from low to high\n");
									printf("\nEnter the corrosponding number:");
									while(getchar() != '\n');
								}
								getchar();
							}
							while(decryptionOutputChoice != 1 && decryptionOutputChoice != 2);
							
							
							// Dynamically creates an array when user selects bruteforce method so memory dont get allocated if the user dont pick bruteforce method (calloc() also turns all the values inside the array to 0 to make it easy for frequency to be incremented)
							bruteforceKey1 = (int*)calloc(312, sizeof(int));	
							bruteforceKey2 = (int*)calloc(312, sizeof(int));
							
							// This dynamically allocates the array to the size of userInput so userInput can easily be copied into this array so it can be passed to the decryption function without getting modified
							bruteforceUserInput = (char*)calloc(strlen(userInput), sizeof(char)); 

							// This checks if all three arrays have been successfully allocated or not (To make sure the pointer is not pointing to null when it wants to be used)
							if (bruteforceKey1 == NULL || bruteforceKey2 == NULL || bruteforceUserInput == NULL) 
							{
								printf("Memory not allocated.\n");
								printf("Exiting the program...\n\n");
								exit(0);
							}
							//Generates all the possible key combination and stores it in bruteforcekey1 & 2 array, when combined its equivalent to one key combination
							bruteForce(bruteforceKey1,bruteforceKey2); 	
							
							
							
							switch(decryptionOutputChoice)
							{
								case 1:
									menu(decryptionMenuNoOptions);
									printf("Probability answer selected");
									
									// Frequency of the userInput gets analysed which returns an integer from 0 - 26 representing alphabet from A to Z
									frequencyAnalyser(userInput,&firstLetter,&secondLetter);
									
									possibleoutput1_1 = (int*)calloc(12, sizeof(int));
									possibleoutput1_2 = (int*)calloc(12, sizeof(int));
									possibleoutput2_1 = (int*)calloc(12, sizeof(int));
									possibleoutput2_2 = (int*)calloc(12, sizeof(int));
			
									// This checks if all four arrays have been successfully allocated or not (Without this the pointer will be null leads to an error in program)
									if (possibleoutput1_1 == NULL || possibleoutput1_2 == NULL || possibleoutput2_1 == NULL || possibleoutput2_2 == NULL) 
									{
										printf("\n\nMemory not allocated.\n\n");
										printf("Exiting the program...\n\n");
										exit(0);
									}
									
									// Sets the both of the counter to 0 before using it to avoid miscalculation when 
									firstLetterCounter = 0;
									secondLetterCounter = 0;
																		
									// This stores most common to least common letters in english alphabet as an integer so it can be easily compared with first and second most frequent letter
									int frequentarr[26] = {'E','T','C','A','O','I','N','S','H','R','L','D','U','M','W','F','G','Y','P','B','V','K','J','X','Q','Z'};
									
									
									printf("\n\nResult for ciphertext: %s \n",userInput);
									
									/*This piece of code uses two most frequent letter and puts it through decryption function with all the possible keys 
									So using the frequentarr[], an assumption is made base on whether the most frequent letter within the ciphertext is equivalent to most common letters in alphabet.*/
									do
									{
										// This tries all the possible alphabet combination from frequentarr[], for both first and second most frequent letters from userInput ciphertext
										// The second counter goes upto 26 then it goes to 0 and and adds up the first counter so get all the possible combination
										if(secondLetterCounter < 26)
										{
											
											arrfirstLetterCounter = 0;
											arrsecondLetterCounter = 0;
											
											for(int i = 0;i<312;i++)
											{
												bruteforceUserInput[0] = firstLetter+65;
												bruteforceUserInput[1] = secondLetter+65;
												decryption(bruteforceUserInput,bruteforceKey1[i],bruteforceKey2[i]);
												
												//Stores the key if the character matches wtih the frequent array for both first and second frequent letter
												if(bruteforceUserInput[0] == frequentarr[firstLetterCounter])
												{
													
													possibleoutput1_1[arrfirstLetterCounter] = bruteforceKey1[i];
													possibleoutput1_2[arrfirstLetterCounter] = bruteforceKey2[i];
													arrfirstLetterCounter++;	
													
												}
												if(bruteforceUserInput[1] == frequentarr[secondLetterCounter])
												{
													possibleoutput2_1[arrsecondLetterCounter] = bruteforceKey1[i];
													possibleoutput2_2[arrsecondLetterCounter] = bruteforceKey2[i];
													
													arrsecondLetterCounter++;									
												}		
											}
											// Copies the userinput to temporary bruteforceUserInput array so even if it gets modified after geting decrypt it can be repopulated after each iteration
											strcpy(bruteforceUserInput,userInput);
											
											
											possibleOutput(possibleoutput1_1,possibleoutput1_2,possibleoutput2_1,possibleoutput2_2,bruteforceUserInput);
											
											secondLetterCounter++;	
										}
										else
										{
											secondLetterCounter = 0;
											firstLetterCounter++;
										}
									}
									while(firstLetterCounter < 26);
									
									// Frees all the memory allocated by the probability section as calloc/malloc dont deallocate the memory automatically
									free(possibleoutput1_1);
									free(possibleoutput1_2);
									free(possibleoutput2_1);
									free(possibleoutput2_2);
									
								break;
								
								case 2:
									menu(decryptionMenuNoOptions);
									printf("Logical key order selected\n\n");

									for(int i = 0;i<312;i++)
									{
										strcpy(bruteforceUserInput,userInput); //Copies the userInput into a temporary string which changes each time it goes through decryption function
										
										printf("%d ",bruteforceKey1[i]);
										printf("%d \n",bruteforceKey2[i]);
			
										// Decrypts the bruteforceUserInput with different key for each iteration and prints it out
										// Once its printed the loop ends and same userInput gets copied into the temporary bruteforce array to it can be decrypted again with a different key
										decryption(bruteforceUserInput,bruteforceKey1[i],bruteforceKey2[i]);
										printf("Your plaintext is: %s\n",bruteforceUserInput);
										printf("With key (%d, %d)\n",bruteforceKey1[i], bruteforceKey2[i]);
										printf("\n");
									}	
								break;
							}

							// This frees the memory used by probability answer or logical key order so other program can use it.
							free(bruteforceKey1); 
							free(bruteforceKey2); 
							free(bruteforceUserInput); 
							
							printf("\nThanks for using the program!\n\n");
							programExit = 0;
						break;
					}
				}
				while(programExit);
				
	
			break;
			
			case 3: //EXIT
				printf("\nThanks for using the program!\n\n");
				programExit = 0;
				break;
						
			default:
			break;
		}
		
	}
	while(programExit);
		
}

//#########################################################################################################
void menu(int selectMenu) 
{
	switch(selectMenu)
	{
	
		case 0: //Main menu
		
			// Clears the console to clean up the previous output to make the program less confusing
			system("clear||@cls");	//cls works for windows cmd whereas clear is for linux bash shell
			
			printf("   ___   __  __ _            _____ _       _\n");
			printf("  / _ \\ / _|/ _(_)          /  __ (_)     | |\n");
			printf(" / /_\\ \\ |_| |_ _ _ __   ___| /  \\/_ _ __ | |__   ___ _ __\n");
			printf(" |  _  |  _|  _| | '_ \\ / _ \\ |   | | '_ \\| '_ \\ / _ \\ '__|\n");
			printf(" | | | | | | | | | | | |  __/ \\__/\\ | |_) | | | |  __/ |\n");
			printf(" \\_| |_/_| |_| |_|_| |_|\\___|\\____/_| .__/|_| |_|\\___|_|\n");
			printf(" \t\t\t\t    | |\n");
			printf(" \t\t\t\t    |_|\n\n");
			
			printf("************************************************************\n\n");
			printf("*\t\t\t 1.Encryption\t\t\t   *\n\n");
			printf("*\t\t\t 2.Decryption\t\t\t   *\n\n");
			printf("*\t\t\t 3.Exit\t\t\t\t   *\n\n");
			printf("************************************************************\n\n");	
		break;
	
		case 1://Encryption 	
		
			system("clear||@cls");	
			
			printf(" _____                            _   _             \n");
			printf("|  ___|                          | | (_)            \n");
			printf("| |__ _ __   ___ _ __ _   _ _ __ | |_ _  ___  _ __  \n");
			printf("|  __| '_ \\ / __| '__| | | | '_ \\| __| |/ _ \\| '_ \\ \n");
			printf("| |__| | | | (__| |  | |_| | |_) | |_| | (_) | | | |\n");
			printf("\\____/_| |_|\\___|_|   \\__, | .__/ \\__|_|\\___/|_| |_|\n");
			printf("                       __/ | |                      \n");
			printf("                      |___/|_|                      \n\n");
			printf("************************************************************\n\n");

		break;
		
		case 2://Decryption
		
			system("clear||@cls");	
			
			printf("______                           _   _             \n");
			printf("|  _  \\                         | | (_)            \n");
			printf("| | | |___  ___ _ __ _   _ _ __ | |_ _  ___  _ __  \n");
			printf("| | | / _ \\/ __| '__| | | | '_ \\| __| |/ _ \\| '_ \\ \n");
			printf("| |/ /  __/ (__| |  | |_| | |_) | |_| | (_) | | | |\n");
			printf("|___/ \\___|\\___|_|   \\__, | .__/ \\__|_|\\___/|_| |_|\n");
			printf("                      __/ | |                      \n");
			printf("                     |___/|_|                      \n");
			
			printf("************************************************************\n\n");
 			printf("*\t\t      Do you know the key?\t\t   *\n\n");
 			printf("*\t\t 1.Yes - Known key decryption\t\t   *\n\n");
			printf("*\t\t 2.No - Brute force decryption\t\t   *\n\n");
			printf("************************************************************\n\n");	

		break;
		
		case 3: //Decryption without the menu
			system("clear||@cls");	
			
			printf("______                           _   _             \n");
			printf("|  _  \\                         | | (_)            \n");
			printf("| | | |___  ___ _ __ _   _ _ __ | |_ _  ___  _ __  \n");
			printf("| | | / _ \\/ __| '__| | | | '_ \\| __| |/ _ \\| '_ \\ \n");
			printf("| |/ /  __/ (__| |  | |_| | |_) | |_| | (_) | | | |\n");
			printf("|___/ \\___|\\___|_|   \\__, | .__/ \\__|_|\\___/|_| |_|\n");
			printf("                      __/ | |                      \n");
			printf("                     |___/|_|                      \n");
			printf("************************************************************\n\n");
			
		break;
	}
}
//#########################################################################################################
int stringValidator(char userInput[])
{
	int i=0;
	while(userInput[i] != '\0')
	{	
	
		// Checks for the input string to see if it contains other character apart from alphabet and space
		if(isalpha(userInput[i]) || isspace(userInput[i] )) //This filters the string which is an alphabet or its a whitespace 
		{
			if(isspace(userInput[i]))
			{	
				if(userInput[i] == ' ')
					userInput[i] = ' ';
				
				else if(userInput[0] == '\n') // Checks if the user enters new line character without any text
					return 1;
				
				else if(userInput[i] == '\n')//Changes the \n at the end of the string to \0				
				{
					userInput[i] = '\0';
					i--;
				}
				
				else
				{
					printf("Only white spaces are allowed\n");
					return 1;
				}
			}
			else // If all the userInput is satisfied then it gets converted to uppercase so it can be proceed further for encryption/decryption
				userInput[i] = toupper(userInput[i]);
				
		}
		else
		{
			printf("Only Alphabets are allowed\n");
			return 1;
		}
		i++;  //The while loop stops just before the \n(last character) so to go to the last value in the error i did i++
	}
	
	printf("\nYour inputted string:\n\n	%s\n\n",userInput); //Shows the user what the string is that they've entered
	
	return 0;
}

//#########################################################################################################
void keys(int* key1, int* key2)
{
	//Stores the user input for key into temp variable (To prevent accidental modification of key within the main function)
	int tempKey1 = 0;
	int tempKey2 = 0;
	do
	{
		// This loop gets the userinput until it gets validated by the keyvalidator function, once its validated then the key gets sent to the mainfunction so it can be passed onto Encryption/Decryption function
		printf("\nEnter your first key from {1,3,5,7,9,11,15,17,19,21,23,25}\n");
		while(scanf("%d",&tempKey1) != 1)
		{
			printf("\nEnter your first key from {1,3,5,7,9,11,15,17,19,21,23,25}\n");
			while(getchar() != '\n');
			
		}
		getchar();
		
		printf("\nEnter your second key between 0 and 25\n");
		while(scanf("%d",&tempKey2) != 1)
		{
			printf("\nEnter your second key between 0 and 25\n");
			while(getchar() != '\n');
		}
		getchar();
		
		if(keyValidator(tempKey1,tempKey2) == 1)
		{
			printf("\nTry Again\n");
		}
		else if(keyValidator(tempKey1,tempKey2) == 2)
		{
			printf("\n\nBoth of the keys must be between 0 to 25 \nTry Again\n\n");
		}

	} // 
	while(keyValidator(tempKey1,tempKey2) == 1 || keyValidator(tempKey1,tempKey2) == 2);

	// After key gets validated, the key within the main code gets modified by the 
	*key1 = tempKey1;
	*key2 = tempKey2;
	
}

//#########################################################################################################

int keyValidator(int key1, int key2)
{
	
	if(key1 > 0 && key1 <= 25 && key2 >= 0 && key2 <=25 ) //Checks wheather the key is between the range or not.
	{
		
		if(key1%2==0||key1==13) //Checks if the key1 is an odd number not including 13 because GCD of Key1 and 26 has to be 1
			return 1;
			
		else
			return 0;
	}
	else
		return 2;
}
//#########################################################################################################

// Takes the pointer to the userinput array and encrypts it using the keys provided by user and prints it out
// When it encounters space it doesnt go through the formula
void encryption(char userInput[],int key1, int key2)	
{
	int i;
	
	// Each character in userInput gets convert it to 0-26 equivalent and it gets sent through this formula for encryption (y = αx+β (mod 26))then the output gets converted back from 0-26 to ascii value of A-Z
	for(i=0;i<strlen(userInput);i++) 
    { 
		if(userInput[i] != ' ')
			userInput[i] = (((userInput[i]-'A')*key1)+key2)%26+'A';	
		else
			userInput[i] = ' ';
    } 
    printf("Your ciphertext is: %s\n",userInput);
	printf("With key (%d, %d)\n",key1, key2);
} 
//#########################################################################################################
// Takes the pointer to the userInput array and decrypts it using the provided key, then the decrypted value replaces the original value that the user inputs
void decryption(char userInput[],int key1, int key2)
{
	int i;
	int loop = 1;
	int x = 1;
	for(i=0;i<strlen(userInput);i++) 
    { 
		// In order to decrypt, multiplicative inverse of alpha(key 1) is required in order to decrypt along side alphabet equivalent from 0-25
		// Each letter gets used within this formula (x = α−1(y−β) mod 26)) then the output gets sent back to the mainfunction so it can be passed to other functions
		if(userInput[i] != ' ')
		{
			while(loop)
			{	
				if((key1*x-1)%26==0)
				loop=0;
				else
				x++;
			}	
			if(userInput[i]-97-key2<0)
				userInput[i]=(x*((userInput[i])-39-key2))%26+65;
			else
				userInput[i]=(x*((userInput[i])-65-key2))%26+65;
		}
		else
		userInput[i] = ' ';
    } 
	
}
//#########################################################################################################
// Bruteforce function takes the pointer of the two array, when both combined it forms key a and b.
void bruteForce(int *key1, int *key2)
{
	
	int counter1,counter2,i;
	
	// Dynamically allocates two temporary array and populates it from 0-25 representing alphabet equivalent
	int* tempkey1;
	tempkey1 = (int*)calloc(26, sizeof(int));
	
	int* tempkey2;
	tempkey2 = (int*)calloc(26, sizeof(int));
	
	if (tempkey1 == NULL || tempkey2 == NULL)
	{
		printf("\n\nMemory not allocated.\n\n");
		printf("Exiting the program...\n\n");
		exit(0);
	}
	
    for (i = 0; i < 26; i++) {
        tempkey1[i] = i;
		tempkey2[i] = i;
    }
	
	counter1 = 0;
	counter2 = 0;
	i = 0;

	// After each iteration counter2 adds up until 26 then it gets resetted back to 0 and counter1 gets add up until it reaches 26 
	// This creates all the possible key combination, upon doing each key also gets sent to keyValidator() function to make sure the key is correct 
	while(counter1 != 26)
	{
		// Keys when they are generated, they both are stored in a tempkey variable and get sent to the keyValidator() function if it doesnt meet the requirement then it wouldnt get sent to the main function 
		// This prevents invalid key from being stored into the bruteforcekey array within main function
		if(keyValidator(tempkey1[counter1],tempkey2[counter2]) == 0)
		{
			
			key1[i] = tempkey1[counter1];
			key2[i] = tempkey2[counter2];
		
			counter2++;
			if(counter2 == 26)  //Resets the counter 
			{
				counter2=0;
				counter1++;
			}
			
			i++;		
		}
		else
		{
			  counter1++;
		}
	}
	

	free(tempkey1);
	free(tempkey2);
}
//#########################################################################################################
// This function takes userInput which gets analysed and the output gets sent back to the main function in a form of first and second most frequent letter
void frequencyAnalyser(char userInput[],int *firstLetter,int *secondLetter) 
{
	int i;
	
	// This dynamically creates an array of size 26 and changes all the values inside the array to 0 so when the next loop encounters a character that matches then it increments it by 1
	int* frequencyArr;
	frequencyArr  = (int*)calloc(26, sizeof(int));
	
	//Creates an array to store the frequency of each letters within the userInput array 
	//(so it can then be analysed to find out the first and second most frequent letters within the whole arrray)
	for(i=0;i<strlen(userInput);i++)
	{
		switch(userInput[i])
		{	
			case 'A': frequencyArr[0] += 1; 
			break;
		
			case 'B': frequencyArr[1] += 1;
			break;
			
			case 'C': frequencyArr[2] += 1;
			break;
			
			case 'D': frequencyArr[3] += 1;
			break;
			
			case 'E': frequencyArr[4] += 1;
			break;
			
			case 'F': frequencyArr[5] += 1;
			break;
			
			case 'G': frequencyArr[6] += 1;
			break;
			
			case 'H': frequencyArr[7] += 1;
			break;
			
			case 'I': frequencyArr[8] += 1;
			break;
			
			case 'J': frequencyArr[9] += 1;
			break;
			
			case 'K': frequencyArr[10] += 1;
			break;
			
			case 'L': frequencyArr[11] += 1;
			break;
			
			case 'M': frequencyArr[12] += 1;
			break;
			
			case 'N': frequencyArr[13] += 1;
			break;
			
			case 'O': frequencyArr[14] += 1;
			break;
			
			case 'P': frequencyArr[15] += 1;
			break;
			
			case 'Q': frequencyArr[16] += 1;
			break;
			
			case 'R': frequencyArr[17] += 1;
			break;
			
			case 'S': frequencyArr[18] += 1;
			break;
			
			case 'T': frequencyArr[19] += 1;
			break;
			
			case 'U': frequencyArr[20] += 1;
			break;
			
			case 'V': frequencyArr[21] += 1;
			break;
			
			case 'W': frequencyArr[22] += 1;
			break;
			
			case 'X': frequencyArr[23] += 1;
			break;
			
			case 'Y': frequencyArr[24] += 1;
			break;
			
			case 'Z': frequencyArr[25] += 1;
			break;
		}	
	}
	
	// After frequency array gets populated according to the userInput, this loop takes the first input and compares it with the next one
	// If the input is larger than the first input then it stores it otherwise it iterates until it reaches end of the array
	int first = frequencyArr[0];
	for(i = 1; i < 26; i++)
	{
		if(frequencyArr[i] > first)
		{
			first = frequencyArr[i];
			*firstLetter = i;
		}
		
	}	
	
	// This second loop compares to the output from the first loop as well as by itself to find out the second most frequent letter
	// In case the largest number happens to appear multiple times then it would get stored as long as its not same as the output form first loop
	int second = 0;
	int secondCounter = 0;
	for(i = 0; i < 26; i++)
	{
		if(frequencyArr[i] > second && frequencyArr[i] <= first)
		{
			secondCounter = i;
			if(secondCounter == (*firstLetter));
			else
			{
				second = frequencyArr[i];
				*secondLetter = i;
			}	
		}
	}
	// Once all the key combination gets sent to the main function the frequency array within the function gets deallocated to free the memory for the other part of the program
	free(frequencyArr);
}
//#########################################################################################################
// This function takes 2 possible key combination array including the bruteforceUserInput
// Once the combination of output key 1 matches with output key 2 then it sends it to the decryption function and prints it out as a possible plaintext
void possibleOutput(int *output1_1,int *output1_2,int *output2_1,int *output2_2,char bruteforceUserInput[])
{
	for(int i = 0;i<12;i++)
	{
		if((output1_1[i] == output2_1[i]) && (output1_2[i] == output2_2[i]))
		{
			decryption(bruteforceUserInput,output1_1[i],output1_2[i]);
			printf("\n\nPossible plaintext: %s\n",bruteforceUserInput);
			printf("With key (%d, %d)\n\n",output1_1[i], output1_2[i]);
		}
	}
}