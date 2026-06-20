#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Function to generate a random password
void generatePassword(int length) { //The function does not return a value.
    char numbers[] = "0123456789"; //Array of numbers
    char lowerCase[] = "abcdefghijklmnopqrstuvwxyz"; //Array of lowercase letters
    char upperCase[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //Array of uppercase letters
    char specialChars[] = "!@#$%^&*()"; //Array of special characters
    char password[length + 1]; // +1 for null terminator
    
    srand((unsigned int)time(NULL)); //Seed the random number generator with the current time

    for (int i = 0; i < length; i++) {
        int category = rand() % 4; // Randomly choose character type
        switch (category) { 
            case 0:
                password[i] = numbers[rand() % 10]; // Generates a random number
                break;
            case 1:
                password[i] = lowerCase[rand() % 26]; // Generates a random lowercase letter
                break;
            case 2:
                password[i] = upperCase[rand() % 26]; // Generates a random uppercase letter
                break;
            case 3:
                password[i] = specialChars[rand() % 10]; // Generates a random special character
                break;
        }
    }
    password[length] = '\0'; // Null-terminate the string

    printf("Generated Password: %s\n", password); //Print the generated password
}

int main() {
    int length;
    printf("Enter the desired password length; ");
    scanf("%d", &length); //Read the desired password length from user input

    if (length > 0) {
        generatePassword(length);
    } else {
        printf("Password length must be greater than zero.\n"); //Error message for invalid length
    }
    
    return 0; //Return 0 to indicate successful execution
}
