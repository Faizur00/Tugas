// Interfaces for type safety
interface NumberChecker {
    check(numbers: number[]): string[];
}

interface NumberCheckerFactory {
    createEvenOddChecker(): NumberChecker;
    createPositiveNegativeChecker(): NumberChecker;
}

// Singleton Factory
class NumberCheckerFactoryImpl implements NumberCheckerFactory {
    private static instance: NumberCheckerFactoryImpl;

    private constructor() {}

    static getInstance(): NumberCheckerFactoryImpl {
        if (!NumberCheckerFactoryImpl.instance) {
            NumberCheckerFactoryImpl.instance = new NumberCheckerFactoryImpl();
        }
        return NumberCheckerFactoryImpl.instance;
    }

    createEvenOddChecker(): NumberChecker {
        return new EvenOddChecker();
    }

    createPositiveNegativeChecker(): NumberChecker {
        return new PositiveNegativeChecker();
    }
}

// Concrete Checker: Even/Odd
class EvenOddChecker implements NumberChecker {
    check(numbers: number[]): string[] {
        return numbers.map(num => num % 2 === 0 ? `${num} is even` : `${num} is odd`);
    }
}

// Concrete Checker: Positive/Negative (for Abstract Factory demonstration)
class PositiveNegativeChecker implements NumberChecker {
    check(numbers: number[]): string[] {
        return numbers.map(num => num >= 0 ? `${num} is positive` : `${num} is negative`);
    }
}

// Legacy Checker (Simulating an incompatible interface)
class LegacyNumberChecker {
    checkNumbers(numbers: number[]): { number: number, isEven: boolean }[] {
        return numbers.map(num => ({ number: num, isEven: num % 2 === 0 }));
    }
}

// Adapter: Converts LegacyNumberChecker to NumberChecker interface
class LegacyCheckerAdapter implements NumberChecker {
    private legacyChecker: LegacyNumberChecker;

    constructor(legacyChecker: LegacyNumberChecker) {
        this.legacyChecker = legacyChecker;
    }

    check(numbers: number[]): string[] {
        return this.legacyChecker.checkNumbers(numbers).map(
            result => `${result.number} is ${result.isEven ? 'even' : 'odd'}`
        );
    }
}

// Decorator: Adds logging to any NumberChecker
class LoggingNumberCheckerDecorator implements NumberChecker {
    private wrapped: NumberChecker;

    constructor(wrapped: NumberChecker) {
        this.wrapped = wrapped;
    }

    check(numbers: number[]): string[] {
        console.log(`Processing numbers: ${numbers.join(', ')}`);
        const result = this.wrapped.check(numbers);
        console.log(`Result: ${result.join(', ')}`);
        return result;
    }
}

// Proxy: Validates input before delegating to NumberChecker
class NumberCheckerProxy implements NumberChecker {
    private checker: NumberChecker;

    constructor(checker: NumberChecker) {
        this.checker = checker;
    }

    check(numbers: number[]): string[] {
        if (!Array.isArray(numbers) || numbers.some(num => typeof num !== 'number' || isNaN(num))) {
            throw new Error('Invalid input: Array must contain only valid numbers');
        }
        return this.checker.check(numbers);
    }
}

function main() {
    // Get singleton factory instance
    const factory = NumberCheckerFactoryImpl.getInstance();

    // Create even/odd checker, wrap with decorator and proxy
    const checker: NumberChecker = new NumberCheckerProxy(
        new LoggingNumberCheckerDecorator(
            factory.createEvenOddChecker()
        )
    );

    // Test the checker
    const numbers: number[] = [1, 2, 3, 4, 5];
    console.log(checker.check(numbers));
}

main();
