//
//  main.cpp
//  nbccommandline
//
//  Copyright (c) 2013 CuriouScientists. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 1024

int number, as, love, b, batuhanic=0; //We're defining the variables here.
static float sonuc=0;
char numero[1024], tmp[MAX];

int minus = 0-1;


int main(int argc, const char * argv[])
{
BAS1:
	for(as=0; as<100; as++)
        //This is just to leave out 100 empty lines for a neat interface.
		putchar('\n');
	
	printf("Hello!\n"
		   "Thank you for using the Mighty Converter.\n"
		   "\nPlease proceed by declaring the original base of "
		   "your number.\n"
		   "Enter '1' for decimal, '2' for octodecimal, "
		   "'3' for hexadecimal and '0' for binary numbers: ");
	
	int secim_init, secim_event;
	scanf("%d", &secim_init); // What is the base of the input?
	
	if ( secim_init!=0 && secim_init!=1 && secim_init!=2 && secim_init!=3 ) {
		printf("ERROR: BAD INPUT\n");
		goto BAS1;
	}   // To check if the user is putting something irrelevant.
	
BAS2:
	
	printf("\n\nVery Well!\n"
		   "Now, you can enter the desired base "
		   "for the conversion.\nAgain, just use '1' for "
		   "decimal, '2' for octodecimal, '3' for hexadecimal "
		   "and '0' for binary numbers!: ");
	
	scanf("%d", &secim_event);  //Into which base would you like to convert?
	fgets(tmp, MAX, stdin);     //To clear kernel.
	
	if ( secim_event!=0 && secim_event!=1 && secim_event!=2 && secim_event!=3 ) {
		printf("ERROR: BAD INPUT\n");   // Again, we are checking if the user is putting something irrelevant.
		goto BAS2;
	}
	
	for(as=0; as<100; as++)
		putchar('\n');		//100 Empty New Lines!--You know why...
	
	printf("Please enter the number you desire: "); //The code very well explains what we are doing...
	
	switch (secim_init) {   //These switch cases are like menus in a restaurant. secim_init is the initial choice. The cases are how these choices are made. For instance, secim_init case 0 stands for binary. This means like "Hey! Program! The number I enter is in binary base!"
			
		case 0:
		{
			fgets(numero, sizeof(numero), stdin);
			if (strlen(numero) > 0 && numero[strlen(numero)-1] == '\n')
				numero[strlen(numero)-1] = '\0'; // We're just deleting the "side effect" of enter (return) button's "\n" from the string...
			
			for (love=0; love<strlen(numero); love++) {
				if (numero[love]=='.') {
					batuhanic = love + 1;
					break;                      // Now, this is smart. As you know, this program can work with non-integer inputs such as 100101.011. What we are doing here is to determine the linear coordinate of the period. This coordinate is then assigned to my friend's name, Batuhan, to commemorate him :)
				}
			}
			
			if (batuhanic > 1) { // If period is somewhere other than the first digit...
				for (love=0; love<(batuhanic-1); love++) {
					if (numero[love]=='1') {
						sonuc = sonuc + pow(2.0, (double)(batuhanic-2-love));
					} else {
						continue;
					}
				}                       // We are scanning the array elements until the coordinate of the period. If we find "1", we take the relevant powers of 2 and save it to the variable "sonuc".
				
				for (love=batuhanic; love<strlen(numero); love++) {
					if (numero[love]=='1') {
						sonuc = sonuc + pow(2.0, (double)(batuhanic-1-love));       //Now, we are scanning the digits after the period, with the same method.
					} else if (numero[love]=='.') {
						batuhanic = 0;
						goto BAS1;
					}                                                           // If the user puts two periods (either maliciously to cheat the program or just by mistake), program goes back to start.
					else {
						continue;
					}
				}
				
			} else if (batuhanic==1) {
				
				batuhanic = 0;
				goto BAS1; // If, again, user tries to cheat or by mistake puts the period on the first digit, program again goes back to start!
				
			} else {
				
				for (love=0; love<strlen(numero); love++) {
					if (numero[love]=='1') {
						sonuc = sonuc + pow(2.0, (double)(strlen(numero)-1-love)); // If user only works with integers, then yaaaayy. Everything is pretty straightforward!
					} else {
						continue;
					}
				}
			}                       // Until now, we have scanned the binary number and found its value. Now, let's process this number!
			
			switch (secim_event) {
					
				case 0:
					
					printf("\nThe result is %s!\n", numero); // If user again selects binary as an output, program gives the initial value exactly as it is stated.
					break;
					
				case 1:
					
					if (batuhanic>1) {
						printf("\nThe result is %.3f!\n", sonuc);   //If the user chose to convert to decimal....
					} else {
						printf("\nThe result is %d!\n", (int)sonuc);
					}
					
					break;
					
				case 2:
					
					printf("\nThe result is %o!\n", (int)sonuc); //If the user chose to convert to octal.... ('octal' = o)
					
					break;
					
				case 3:
					
					printf("\nThe result is %x!\n", (int)sonuc); // If the user chose to convert to hexadecimal....
					
					break;
					
				default:
					break;
			}
			
			break;
		}
		case 1: //If input is in decimal base!
			
		BAS3:
			
			scanf("%f", &sonuc); //We scan the number.
			
			float floater;
			number = (int)sonuc; // The integer fragment of the number.
			floater = sonuc - number; //The non-integer fragment of the number.
			
			switch (secim_event) { // Soooo...
					
				case 0: //If user wanted to convert to binary...
				{
					static int a;
					
					a = (log10(number)/log10(2))+1;  //We are taking the logarythm of the number on base 2, in order to find the maximum number of digits.
					
					int i, y, x;
					char output[MAX]; // The output string.
					
					for(i=a-1; i>=0; i--) // Now, to calculate the number's value in binary, we are continuously dividing the number into 2.
					{
						x = number/pow(2, i);
						if (x < 1) {
							output[a-(i+1)] = '0'; //If number is larger than 2 to the power of i, we assign "0" to that respective digit.
						} else {
							output[a-(i+1)] = '1'; // Otherwise, we assign 1 to that respective digit. And we go on until the remainder is 0. How do we find the remainder? BELOW!
							y = pow(2, i);
							number %= y; //find the remainder!
						}
					}
					
					if (floater > 0) { //If the user input a non-integer value, we do something similar.
						
						output[a] = '.';
						int z = 0;
						
						for (z=minus; floater>0; z--) { //minus equals minus 1 (-1). It will divide the number by 2 to the power -1 initially.
							
							if (floater < pow(2, z)) {
								output[a-z] = '0';
							} else {
								output[a-z] = '1';
								floater -= pow(2, z);
							}
							
						}
					}
					
					printf("\nThe result is %s\n", output); //AND VICTORY! WE NOW WRITE THE RESULT. THE REMAINING HAS THE SAME LOGIC! HAVE A NICE DAY. IF YOU HAVE QUESTIONS, JUST ASK ;)
					
					break;
				}
				case 1:
				{
					if (floater > 0) {
						
						printf("\nThe result is %.3f!\n", sonuc);
						
					} else {
						
						printf("\nThe result is %d!\n", number);
					}
					
					break;
				}
				case 2:
				{
					printf("\nThe result is %o!\n", number);
					break;
				}
				case 3:
				{
					printf("\nThe result is %x!\n", number);
					break;
				}
				default:
					break;
			}
			
			break;
			
		case 2:
			
		BAS4:
			scanf("%o", &number);
			
			if (number > 131071) {
				printf("\n\nPlease enter a smaller number.\n");
				goto BAS4;
			}
			
			switch (secim_event) {
				case 0:
				{
					b=2;
					static int a;
					
					a = (log10(number)/log10(b))+1;
					
					int i, y, x;
					char output[a];
					
					for(i=a-1; i>=0; i--)
					{
						x = number/pow(2, i);
						if (x < 1) {
							output[a-(i+1)] = '0';
						} else {
							output[a-(i+1)] = '1';
							y = pow(2, i);
							number %= y;
						}
					}
					
					printf("\nThe result is %s\n", output);
					break;
				}
				case 1:
				{
					printf("\nThe result is %d!\n", number);
					
					break;
				}
				case 2:
				{
					printf("\nThe result is %o!\n", number);
					
					break;
				}
				case 3:
				{
					printf("\nThe result is %x!\n", number);
					
					break;
				}
				default:
					break;
			}
			
			break;
			
		case 3:
			
		BAS5:
			scanf("%x", &number);
			
			if (number > 131071) {
				printf("\n\nPlease enter a smaller number.\n");
				goto BAS5;
			}
			
			switch (secim_event) {
				case 0:
				{
					b=2;
					static int a;
					
					a = (log10(number)/log10(b))+1;
					
					int i, y, x;
					char output[a];
					
					for(i=a-1; i>=0; i--)
					{
						x = number/pow(2, i);
						if (x < 1) {
							output[a-(i+1)] = '0';
						} else {
							output[a-(i+1)] = '1';
							y = pow(2, i);
							number %= y;
						}
					}
					
					printf("\nThe result is %s\n", output);
					break;
				}
				case 1:
				{
					printf("\nThe result is %d!\n", number);
					break;
				}
				case 2:
				{
					printf("\nThe result is %o!\n", number);
					break;
				}
				case 3:
				{
					printf("\nThe result is %x!\n", number);
					break;
				}
				default:
				{
					break;
				}
			}
			
			break;
			
		default:
			break;
	}
	
	printf("If you want to quit, please enter '0': ");
	
	int quit;
	scanf("%d", &quit);
	if(quit == 0) {
		return 0;
	}
	
	for(as=0; as<100; as++)
		putchar('\n');
	sonuc=0;
	goto BAS1;
}




