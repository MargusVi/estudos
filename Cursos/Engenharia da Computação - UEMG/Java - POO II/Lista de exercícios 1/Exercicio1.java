//1) Faça um programa para calcular o estoque médio de uma peça, sendo que:
//ESTOQUE MÉDIO = (QUANTIDADE_MÍNIMA + QUANTIDADE_MÁXIMA) / 2

import java.util.Scanner;

public class Exercicio1 {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int opcao;

        do {
            float min, max, media;            
            System.out.print("\nQuantidade mínima: ");
            min = scan.nextFloat();
            System.out.print("Quantidade máxima: ");
            max = scan.nextFloat();
            media = (min + max) / 2;
            System.out.println("O estoque médio é " + media + "\n");

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