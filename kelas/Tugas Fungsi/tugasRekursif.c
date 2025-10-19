#include <stdio.h>

int fnRecursiveFactorial(int iParameter);
void fnRecursiveFibonacchiSequence(int iParameter, int a, int b, int count);


int main(void)
{
    int iParameter;
    printf("Enter a number: ");
    scanf("%d", &iParameter);

    printf("Factorial of %d: %d\n", iParameter, fnRecursiveFactorial(iParameter));
    
    printf("Fibonacchi sequence of %d: ", iParameter);
    fnRecursiveFibonacchiSequence(iParameter, 0, 1, 1);

    return 0;
}


int fnRecursiveFactorial(int iParameter)
{
    if (iParameter == 1) {
        return 1;
    }
    
    return iParameter * fnRecursiveFactorial(iParameter - 1);
}

void fnRecursiveFibonacchiSequence(int baseTerms, int firstTerm, int secondTerm, int currentCount)
{
    if (currentCount > baseTerms) {
        return;
    }
    printf("%i ", firstTerm);
    fnRecursiveFibonacchiSequence(baseTerms, secondTerm, firstTerm + secondTerm, currentCount + 1);
}
