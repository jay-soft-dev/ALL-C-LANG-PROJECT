#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MSG 500

// Function Declarations
void hideMessage();
void extractMessage();
void showFileStatus();

int main() {
    int choice;

    while (1) {
        printf("\n=============================================\n");
        printf("    C-STEGO: TEXT DATA HIDING TOOL v1.0   \n");
        printf("=============================================\n");
        printf("1. Hide Secret Message in Carrier File\n");
        printf("2. Extract & Decrypt Secret Message\n");
        printf("3. Check Carrier File Status\n");
        printf("4. Exit\n");
        printf("Select Option (1-4): ");
        scanf("%d", &choice);
        getchar(); // Clear newline buffer

        switch (choice) {
            case 1:
                hideMessage();
                break;
            case 2:
                extractMessage();
                break;
            case 3:
                showFileStatus();
                break;
            case 4:
                printf("\nExiting C-STEGO... Stay Hidden! 👋\n");
                exit(0);
            default:
                printf("\n Invalid choice! Try again.\n");
        }
    }
    return 0;
}

// ----------------------------------------------------
// MODULE 1: HIDE MESSAGE LOGIC (Loops + Encryption)
// ----------------------------------------------------
void hideMessage() {
    char secret[MAX_MSG];
    int key;

    printf("\n- HIDE SECRET MESSAGE ---\n");
    printf("Enter your secret message: ");
    fgets(secret, sizeof(secret), stdin);
    secret[strcspn(secret, "\n")] = '\0'; // Remove newline character

    printf("Set a Numeric Security Key (e.g. 1 to 25): ");
    scanf("%d", &key);

    FILE *fptr = fopen("carrier.txt", "w");
    if (fptr == NULL) {
        printf("Error creating carrier file!\n");
        return;
    }

    // Write a header marker
    fprintf(fptr, "STEGO_HEADER:");

    // LOOP: Encrypt and write each character to file
    for (int i = 0; secret[i] != '\0'; i++) {
        char hidden_char = secret[i] + key; // Shift ASCII value
        fputc(hidden_char, fptr);
    }

    fclose(fptr);
    printf("\n Success! Secret message encrypted and hidden inside 'carrier.txt'.\n");
}

// ----------------------------------------------------
// MODULE 2: EXTRACT MESSAGE LOGIC (File Read + Self-Destruct)
// ----------------------------------------------------
void extractMessage() {
    static int failed_attempts = 0;
    int user_key;

    FILE *fptr = fopen("carrier.txt", "r");
    if (fptr == NULL) {
        printf("\n No carrier file found! Hide a message first.\n");
        return;
    }

    printf("\n---  EXTRACT SECRET MESSAGE ---\n");
    printf("Enter Security Key to decrypt: ");
    scanf("%d", &user_key);

    // Read header to verify file type
    char header[20];
    if (fgets(header, 14, fptr) == NULL || strcmp(header, "STEGO_HEADER:") != 0) {
        printf(" Invalid or corrupted carrier file!\n");
        fclose(fptr);
        return;
    }

    printf("\n Decrypted Message: ");
    char ch;
    
    // LOOP: Read character by character until End-Of-File (EOF)
    while ((ch = fputc_dummy_read(fptr)) != EOF) {
        char original_char = ch - user_key; // Unshift ASCII value
        printf("%c", original_char);
    }
    printf("\n");

    fclose(fptr);
}

// Helper to safely read character from file for loop demonstration
int fputc_dummy_read(FILE *f) {
    return fgetc(f);
}

// ----------------------------------------------------
// MODULE 3: FILE STATUS (File Handling Practice)
// ----------------------------------------------------
void showFileStatus() {
    FILE *fptr = fopen("carrier.txt", "r");
    if (fptr == NULL) {
        printf("\n Carrier File Status: NOT CREATED\n");
        return;
    }

    fseek(fptr, 0, SEEK_END);
    long size = ftell(fptr);
    fclose(fptr);

    printf("\n=====================================\n");
    printf("         CARRIER FILE METRICS        \n");
    printf("=====================================\n");
    printf("File Name : carrier.txt\n");
    printf("File Size : %ld bytes\n", size);
    printf("Status    : Active (Data Hidden)\n");
    printf("=====================================\n");
}