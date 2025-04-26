//11) Ler dois valores inteiros para as variáveis A e B, efetuar a troca dos valores de modo que a variável A passe a possuir a variável B, e a variável B passe a possuir a variável A. Apresentar os valores trocados.

import java.util.Scanner;

public class Exercicio11 {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int opcao;

        do {
            String A, B, aux;
            System.out.print("\nDigite a variável A (string): ");
            A = scan.nextLine();
            System.out.print("Digite a variável B (string): ");
            B = scan.nextLine();

            System.out.println("\nOriginal:");
            System.out.println("A - " + A);
            System.out.println("B - " + B);

            aux = A;
            A = B;
            B = aux;

            System.out.println("\nTrocados:");
            System.out.println("A - " + A);
            System.out.println("B - " + B);

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