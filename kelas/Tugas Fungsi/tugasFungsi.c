#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned int id;
    unsigned int pin;
    unsigned int balance;
}User;

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

    scanf("%i", &iPilihan);

    if (iPilihan < 0 || iPilihan > 3) {
        printf("Invalid Input. coba lagi.\n");
        fnUserMenu();
    }
    return iPilihan;
}

void fnConfirmAnother(void)
{
    char cConfirmation;
    printf("Do you want to do another process [y/n]? ");
    scanf(" %c", &cConfirmation);

    if (cConfirmation == 'y' || cConfirmation == 'Y') {
        fnUserMenu();
    } else if (cConfirmation == 'n' || cConfirmation == 'N') {
        printf("Terima kasih telah menggunakan layanan kami.\n");
        exit(0);
    } else {
        printf("Invalid input. Please try again.\n");
        fnConfirmAnother();
    }
}

int fnUserValidation(void)
{
    unsigned int uCardId, uPinNumber;
    printf("Enter your Card ID:  ");
    scanf("%u", &uCardId);

    printf("\nEnter your PIN number: ");
    scanf("%u", &uPinNumber);

    int iStructSize = sizeof(users)/ sizeof users[0];
    for (int i = 0; i < iStructSize; i++){
        if (users[i].id == uCardId && users[i].pin == uPinNumber){
            return i;
        }
    }
    printf("\nNo user data found, process terminated\n");
    return -1;
}

void fnDisplayBalance(int iIndex)
{
    int iUserBalance = users[iIndex].balance;

    printf("Sisa saldo anda:    \n");
    printf("%i\n", iUserBalance);

    fnConfirmAnother();
}

void fnWithdrawBalance(int iIndex)
{
    unsigned int uWBalance;
    unsigned int uUserBalance = users[iIndex].balance;

    printf("Jumlah yang ingin ditarik:  \n");
    scanf("%u", &uWBalance);

    if (uWBalance > uUserBalance) {
        printf("Saldo anda tidak cukup\n");
        exit(0);
    }

    unsigned int* pBalance = &users[iIndex].balance;
    *pBalance -= uWBalance;
    printf("Penarikan berhasil. Sisa saldo anda: %u\n", users[iIndex].balance);

    fnConfirmAnother();
}

void fnDepositBalance(int iIndex)
{
    unsigned int uDBalance;
    unsigned int uUserBalance = users[iIndex].balance;

    printf("Jumlah yang ingin dimasukkan:   \n");
    scanf("%u", &uDBalance);

    unsigned int* pBalance = &users[iIndex].balance;
    *pBalance = uUserBalance + uDBalance;

    printf("Berhasil menyetor, saldo anda sebesar: %u\n", users[iIndex].balance);

    fnConfirmAnother();
}

int main(void)
{
    int iUserIndex = 1;

    int iUserChoice = fnUserMenu();

    if (iUserChoice == 1) {
        fnDisplayBalance(iUserIndex);
    }
    else if (iUserChoice == 2) {
        fnWithdrawBalance(iUserIndex);
    }
    else if (iUserChoice == 3) {
        fnDepositBalance(iUserIndex);
    }
    else{
        printf("Terima kasih telah menggunakan layanan kami.\n");
    }
    return 0;
}
