//27) Escreva um programa que leia:
// - a quantidade de números que deverá processar;
// - Vos números que deverá processar, e calcule e exiba, para cada número a ser processado o seu fatorial.

import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;

public class Exercicio27 {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int opcao;
        
        do {
            int qtde;
            List<Integer> num = new ArrayList<Integer>();
            System.out.print("\nDigite quantos números serão processados: ");
            qtde = scan.nextInt();

            for(int i = 0; i < qtde; i++) {
                System.out.print("Digite o " + (i+1) + "° número: ");
                num.add(scan.nextInt());
            }

            System.out.println("\n");

            for(int i = 0; i < num.size(); i++) {
                int fat = 1;
                for(int i2 = num.get(i); i2 > 0; i2--) {
                    fat = fat * i2;
                }
                System.out.println(num.get(i) + "! = " + fat);
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
