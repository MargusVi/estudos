//60) Escreva um programa que retorne o número do quadrante (1, 2, 3 ou 4) através de um método chamado VERIFICA_QUADRANTE, que deve receber um valor para x e um valor para y.

import java.util.Scanner;

public class Exercicio60 {
    public static int VERIFICA_QUADRANTE(int x, int y) {
        if(x > 0 && y > 0) {
            return 1;
        } else if(x < 0 && y > 0) {
            return 2;
        } else if(x < 0 && y < 0) {
            return 3;
        } else {
            return 4;
        }
    }

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int opcao;
        
        do {
            int x, y, q;

            System.out.print("Digite a coordenada x: ");
            x = scan.nextInt();
            System.out.print("Digite a coordenada y: ");
            y = scan.nextInt();

            q = VERIFICA_QUADRANTE(x, y);

            System.out.println("\n(" + x + ", " + y + ") está no " + q + "° quadrante.");

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
