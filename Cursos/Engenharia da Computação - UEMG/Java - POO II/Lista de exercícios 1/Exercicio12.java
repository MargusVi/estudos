//12) Escreva um programa que leia um número inteiro e exiba o seu módulo.

import java.util.Scanner;

public class Exercicio12 {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int opcao;

        do {
            int num, original;
            System.out.print("\nDigite um número inteiro: ");
            num = scan.nextInt();
            
            if(num >= 0) {
                System.out.println("O módulo de " + num + " é " + num);
            } else {
                original = num;
                num = num * (-1);
                System.out.println("O módulo de " + original + " é " + num);
            }

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