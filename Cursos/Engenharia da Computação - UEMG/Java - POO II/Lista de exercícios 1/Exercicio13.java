//13) Escreva um programa que leia 3 números inteiros e imprima na tela os valores em ordem decrescente.

import java.util.Scanner;

public class Exercicio13 {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int opcao;

        do {
            int num1, num2, num3, aux;
            System.out.print("\nDigite um número inteiro: ");
            num1 = scan.nextInt();
            System.out.print("Digite outro número inteiro: ");
            num2 = scan.nextInt();
            System.out.print("Digite outro número inteiro: ");
            num3 = scan.nextInt();

            if(num1 < num2) {
                aux = num1;
                num1 = num2;
                num2 = aux;
            }
            if(num2 < num3) {
                aux = num2;
                num2 = num3;
                num3 = aux;
            }
            if(num1 < num2) {
                aux = num1;
                num1 = num2;
                num2 = aux;
            }

            System.out.println("\n" + num1);
            System.out.println(num2);
            System.out.println(num3);

            System.out.println("\nDeseja executar novamente?");
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