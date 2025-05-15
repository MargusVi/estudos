//45) Dada uma sequência de n números (vetor de inteiros), imprimí-la na ordem inversa que foi realizada a leitura.

import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;

public class Exercicio45 {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int opcao;
        
        do {
            int qtde;
            List<Integer> num = new ArrayList<Integer>();

            System.out.print("\nQuantos números serão digitados? ");
            qtde = scan.nextInt();

            for(int i = 0; i < qtde; i++) {
                System.out.print("Digite o " + (i+1) + "° número: ");
                num.add(scan.nextInt());
            }

            System.out.println("\n");

            for(int i = num.size()-1; i >= 0; i--) {
                System.out.println(num.get(i));
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
