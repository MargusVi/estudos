import java.util.Scanner;

public class Exercicio23 {
    public static void main(String[] args) {
        int opcao;
        Scanner scan = new Scanner(System.in);
        
        do {
            System.out.println("Calculadora simples\n");
            System.out.println("1- Adição");
            System.out.println("2- Subtração");
            System.out.println("3- Multiplicação");
            System.out.println("4- Divisão");
            System.out.println("5- Sair\n");
            System.out.print("Escolha uma opção: ");

            opcao = scan.nextInt();

            float num1, num2;
            float result;
    
            if(opcao >= 1 && opcao <= 4) {
                System.out.print("\nEntre com o primeiro número: ");
                num1 = scan.nextFloat();
                System.out.print("Entre com o segundo número: ");
                num2 = scan.nextFloat();

                switch (opcao) {
                    case 1:
                        result = num1 + num2;
                        System.out.print(num1 + " + " + num2 + " = " + result + "\n\n");
                        break;
                    case 2:
                        result = num1 - num2;
                        System.out.print(num1 + " - " + num2 + " = " + result + "\n\n");
                        break;
                    case 3:
                        result = num1 * num2;
                        System.out.print(num1 + " * " + num2 + " = " + result + "\n\n");
                        break;
                    case 4:
                        result = num1 / num2;
                        System.out.print(num1 + " / " + num2 + " = " + result + "\n\n");
                        break;
                    default:
                        break;
                }
            } else if(opcao != 5) {
                System.out.print("\nOpção inválida!\n\n");
            }
        } while (opcao != 5);
        if(opcao == 5) {
            System.out.print("Encerrando o programa...\n\n");
        }
    }
}
