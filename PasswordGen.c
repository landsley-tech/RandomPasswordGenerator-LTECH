#include <stdio.h>
#include <stdint.h>
#include <sys/random.h> // getrandom() - the operating system's secure random source (Linux)

#define MIN_LENGTH 4   // Need at least one character from each of the 4 categories
#define MAX_LENGTH 128 // Cap the length so the password array can't overflow the stack

// Returns a secure random number from 0 to max-1.
// Values that would cause modulo bias are thrown away and redrawn.
unsigned int secureRandom(unsigned int max) {
    uint32_t value;
    uint32_t limit = UINT32_MAX - (UINT32_MAX % max);
    do {
        if (getrandom(&value, sizeof(value), 0) != sizeof(value)) {
            fprintf(stderr, "Error: could not get secure random data.\n");
            return 0;
        }
    } while (value >= limit);
    return value % max;
}

// Function to generate a random password
void generatePassword(int length) {
    const char *categories[] = {
        "0123456789",                 // Numbers
        "abcdefghijklmnopqrstuvwxyz", // Lowercase letters
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ", // Uppercase letters
        "!@#$%^&*()-_=+[]{};:,.?"     // Special characters
    };
    const char *allChars = "0123456789abcdefghijklmnopqrstuvwxyz"
                           "ABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-_=+[]{};:,.?";
    int categorySizes[] = {10, 26, 26, 23};
    int allSize = 85;

    char password[MAX_LENGTH + 1]; // +1 for null terminator

    // Step 1: guarantee one character from each category
    for (int i = 0; i < 4; i++) {
        password[i] = categories[i][secureRandom(categorySizes[i])];
    }

    // Step 2: fill the rest from all characters
    for (int i = 4; i < length; i++) {
        password[i] = allChars[secureRandom(allSize)];
    }

    // Step 3: shuffle (Fisher-Yates) so the guaranteed characters aren't always first
    for (int i = length - 1; i > 0; i--) {
        int j = secureRandom(i + 1);
        char temp = password[i];
        password[i] = password[j];
        password[j] = temp;
    }

    password[length] = '\0'; // Null-terminate the string
    printf("Generated Password: %s\n", password);
}

int main(void) {
    int length;

    printf("Enter the desired password length (%d-%d): ", MIN_LENGTH, MAX_LENGTH);

    // scanf returns 1 only if it successfully read a number
    if (scanf("%d", &length) != 1) {
        printf("Please enter a whole number.\n");
        return 1;
    }

    if (length < MIN_LENGTH || length > MAX_LENGTH) {
        printf("Password length must be between %d and %d.\n", MIN_LENGTH, MAX_LENGTH);
        return 1;
    }

    generatePassword(length);
    return 0;
}
