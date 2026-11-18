#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to simulate a brute force guessing attack
void start_brute_force(char *target_password) {
    char guess[5]; // To store the current combination guess
    long attempts = 0;
    int found = 0;
    printf("please enter only for digit num\n");
    printf("\n[ATTACK] INITIATING BRUTE FORCE ATTACK ON TARGET...\n");

    // Nested loops to generate combinations from 0000 to 9999
    for (char i = '0'; i <= '9' && !found; i++) {
        for (char j = '0'; j <= '9' && !found; j++) {
            for (char k = '0'; k <= '9' && !found; k++) {
                for (char l = '0'; l <= '9' && !found; l++) {
                    
                    // Constructing the guess string
                    guess[0] = i;
                    guess[1] = j;
                    guess[2] = k;
                    guess[3] = l;
                    guess[4] = '\0'; // Null terminator

                    attempts++;

                    // Security check to see if the guess matches target
                    if (strcmp(guess, target_password) == 0) {
                        printf(" SUCCESS: PASSWORD CRACKED SUCCESSFULLY!\n");
                        printf(" MATCH FOUND: %s\n", guess);
                        printf(" TOTAL ATTEMPTS TRIED: %ld\n", attempts);
                        found = 1;
                    }
                }
            }
        }
    }
    if (!found) {
        printf(" FAILURE: PASSWORD OUT OF RANGE FOR THIS SIMULATOR.\n");
    }
}

int main() {
    char password[10];
    printf("BRUTE FORCE ATTACK SIMULATOR\n");

    printf("SET A 4-DIGIT SECRET PASSWORD FOR TARGET (E.G., 4512): ");
    scanf("%s", password);

    // Basic length validation
    if (strlen(password) != 4) {
        printf("ERROR: PLEASE ENTER EXACTLY A 4-DIGIT NUMBER.\n");
        return 1;
    }

    // Launching the simulation
    start_brute_force(password);

    return 0;
}