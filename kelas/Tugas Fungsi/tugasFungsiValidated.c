#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // For UINT_MAX

// Hold User data using struct and array
typedef struct {
    unsigned int id;
    unsigned int pin;
    unsigned int balance;
} User;

// Predefined user data stored in an array of structs
User users[] = {
    {11111111, 222222, 1000000},
    {87654321, 654321, 2000000},
    {11223344, 334455, 1500000},
    {44332211, 554433, 1750000},
    {56789012, 789012, 1200000},
    {21098765, 987654, 1800000},
    {34567890, 678901, 1300000},
    {65432109, 321098, 1600000}
};

// Display menu function
int fnUserMenu(void)
{
    int iPilihan = -1;

    printf("\n============================\n");
    printf("        🏧 ATM Sederhana       \n");
    printf("============================\n");
    printf("[1] 💰 Cek Saldo\n");
    printf("[2] 💵 Tarik Tunai\n");
    printf("[3] 🏦 Setor Tunai\n");
    printf("[0] 🚪 Keluar\n");
    printf("============================\n");
    printf("Pilih menu: ");

    // Validate input to prevent invalid data
    if (scanf("%i", &iPilihan) != 1) {
        printf("Invalid input. Please enter a number.\n");
        while (getchar() != '\n'); // Clear input buffer
        return fnUserMenu(); // Retry
    }

    if (iPilihan < 0 || iPilihan > 3) {
        printf("Invalid Input. coba lagi.\n");
        return fnUserMenu(); // Retry
    }
    return iPilihan;
}

// Callback function to confirm if the user wants to perform another process
void fnConfirmAnother(void)
{
    char cConfirmation;
    printf("Do you want to do another process [y/n]? ");
    if (scanf(" %c", &cConfirmation) != 1) {
        printf("Invalid input. Please try again.\n");
        while (getchar() != '\n'); // Clear input buffer
        fnConfirmAnother(); // Retry
        return;
    }

    if (cConfirmation == 'y' || cConfirmation == 'Y') {
        fnUserMenu();
    } else if (cConfirmation == 'n' || cConfirmation == 'N') {
        printf("Terima kasih telah menggunakan layanan kami.\n");
        exit(0);
    } else {
        printf("Invalid input. Please try again.\n");
        fnConfirmAnother(); // Retry
    }
}

// User validation function
int fnUserValidation(void)
{
    unsigned int uCardId, uPinNumber;

    printf("Enter your Card ID:  ");
    if (scanf("%u", &uCardId) != 1) {
        printf("Invalid input. Please enter a valid number.\n");
        while (getchar() != '\n'); // Clear input buffer
        return fnUserValidation(); // Retry
    }

    printf("\nEnter your PIN number: ");
    if (scanf("%u", &uPinNumber) != 1) {
        printf("Invalid input. Please enter a valid number.\n");
        while (getchar() != '\n'); // Clear input buffer
        return fnUserValidation(); // Retry
    }

    int iStructSize = sizeof(users) / sizeof users[0];
    for (int i = 0; i < iStructSize; i++) {
        if (users[i].id == uCardId && users[i].pin == uPinNumber) {
            return i; // Return the index of the matched user
        }
    }

    printf("\nNo user data found, process terminated\n");
    return -1;
}

// Display Balance function
void fnDisplayBalance(int iIndex)
{
    if (iIndex < 0 || iIndex >= (int)(sizeof(users) / sizeof(users[0]))) {
        printf("Invalid user index. Process terminated.\n");
        exit(0);
    }

    int iUserBalance = users[iIndex].balance;
    printf("Sisa saldo anda:    \n");
    printf("%i\n", iUserBalance);

    fnConfirmAnother();
}

// Withdraw money function
void fnWithdrawBalance(int iIndex)
{
    if (iIndex < 0 || iIndex >= (int)(sizeof(users) / sizeof(users[0]))) {
        printf("Invalid user index. Process terminated.\n");
        exit(0);
    }

    unsigned int uWBalance;
    unsigned int uUserBalance = users[iIndex].balance;

    printf("Jumlah yang ingin ditarik:  \n");
    if (scanf("%u", &uWBalance) != 1 || uWBalance > UINT_MAX) {
        printf("Invalid input. Please enter a valid amount.\n");
        while (getchar() != '\n'); // Clear input buffer
        fnWithdrawBalance(iIndex); // Retry
        return;
    }

    if (uWBalance > uUserBalance) {
        printf("Saldo anda tidak cukup\n");
        exit(0);
    }

    unsigned int* pBalance = &users[iIndex].balance;
    *pBalance -= uWBalance;
    printf("Penarikan berhasil. Sisa saldo anda: %u\n", users[iIndex].balance);

    fnConfirmAnother();
}

// Deposit money function
void fnDepositBalance(int iIndex)
{
    if (iIndex < 0 || iIndex >= (int)(sizeof(users) / sizeof(users[0]))) {
        printf("Invalid user index. Process terminated.\n");
        exit(0);
    }

    unsigned int uDBalance;
    unsigned int uUserBalance = users[iIndex].balance;

    printf("Jumlah yang ingin dimasukkan:   \n");
    if (scanf("%u", &uDBalance) != 1 || uDBalance > UINT_MAX) {
        printf("Invalid input. Please enter a valid amount.\n");
        while (getchar() != '\n'); // Clear input buffer
        fnDepositBalance(iIndex); // Retry
        return;
    }

    unsigned int* pBalance = &users[iIndex].balance;
    *pBalance = uUserBalance + uDBalance;

    printf("Berhasil menyetor, saldo anda sebesar: %u\n", users[iIndex].balance);

    fnConfirmAnother();
}

int main(void)
{
    // Validate the user (commented out for testing purposes)
    // int iUserIndex = fnUserValidation();
    // if (iUserIndex == -1) {
    //     // Exit if validation fails
    //     exit(0);
    // }

    // For testing purposes, using a hardcoded user index
    int iUserIndex = 1;

    // Display user menu and get user choice
    int iUserChoice = fnUserMenu();

    // Perform actions based on user choice
    if (iUserChoice == 1) {
        fnDisplayBalance(iUserIndex); // Display balance
    } else if (iUserChoice == 2) {
        fnWithdrawBalance(iUserIndex); // Withdraw money
    } else if (iUserChoice == 3) {
        fnDepositBalance(iUserIndex); // Deposit money
    } else {
        // Exit the program if the user chooses to quit
        printf("Terima kasih telah menggunakan layanan kami.\n");
    }
    return 0;
}
