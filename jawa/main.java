import java.util.Scanner;

public class main{
    public static double celcToFahr(Double celcius){
        return (celcius * 9/5) + 32;
    }

    public static double fahrToCelc(Double fahrenheit){
        return (fahrenheit - 32) * 5/9;
    }
    
    public static void printConversion(Double from, Double to, Integer choice){
        if(choice == 1){
            System.out.printf("Conversion from %.2f°C to %.2f°F", from, to);
        }
        else if(choice == 2){
            System.out.printf("Conversion from %.2f°F to %.2f°C", from, to);
        }
    }

    public static void main(String[] args){
        Scanner input = new Scanner(System.in);
        System.out.println("1. Celcius to Fahrenheit");
        System.out.println("2. Fahrenheit to Celcius");
        System.out.print("Pick a choice: ");
        double choice = input.nextInt();

        if(choice == 1){
            System.out.print("Give an input: ");
            double temp = input.nextDouble();
            double result = celcToFahr(temp);
            printConversion(temp, result, 1);
        }
        else if(choice == 2){
            System.out.print("Give an input: ");
            double temp = input.nextDouble();
            double result = fahrToCelc(temp);
            printConversion(temp, result, 2);
        }
    }
}