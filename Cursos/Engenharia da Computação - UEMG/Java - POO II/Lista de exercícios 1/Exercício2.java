//2) Faça um programa que:
// - Leia a cotação do dólar
// - Leia um valor em dólares
// - Converta esse valor para real
// - Mostre o resultado

import java.util.Scanner;
import java.text.DecimalFormat;

public class Exercício2 {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int opcao;

        do {
            float cotDolar, dolar, real;
            java.text.DecimalFormat df = new DecimalFormat("00.00");
            System.out.print("\nDigite a cotação atual do dólar: R$");
            cotDolar = scan.nextFloat();
            System.out.print("Digite um valor em dólares: $");
            dolar = scan.nextFloat();
            real = dolar * cotDolar;
            System.out.println("$" + dolar + " convertido para reais é R$" + df.format(real) + "\n");

            System.out.println("Deseja realizar um novo cálculo?");
            System.out.println("1 - Sim");
            System.out.println("0 - Não");
            System.out.print("Escolha uma opção: ");
            opcao = scan.nextInt();
            if(opcao == 0) {
                System.out.println("\nEncerrando o programa...\n");
            }
            if(opcao != 0 && opcao != 1) {
                System.out.println("\nOpção inválida, encerrando o programa!\n");
            }
        } while(opcao == 1);
    }
}