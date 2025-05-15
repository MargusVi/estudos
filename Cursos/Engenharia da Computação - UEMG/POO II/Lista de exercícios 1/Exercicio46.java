//46) Dados dois vetores x e y, ambos com n elementos, determinar o produto escalar desses vetores. Ou seja, realizar a soma dos resultados da multiplicação de x[i] por y[i].

import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;

public class Exercicio46 {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int opcao;
        
        do {
            int qtde, prod, prodEsc = 0;
            List<Integer> x = new ArrayList<Integer>();
            List<Integer> y = new ArrayList<Integer>();

            System.out.print("\nQuantos números serão digitados? ");
            qtde = scan.nextInt();

            for(int i = 0; i < qtde; i++) {
                System.out.print("Digite o " + (i+1) + "° número de x: ");
                x.add(scan.nextInt());
            }
            for(int i = 0; i < qtde; i++) {
                System.out.print("Digite o " + (i+1) + "° número de y: ");
                y.add(scan.nextInt());
            }
            for(int i = 0; i < qtde; i++) {
                prod = x.get(i) * y.get(i);
                prodEsc = prodEsc + prod;
            }

            System.out.println("\nO produto escalar dos dois vetores é " + prodEsc + ".");

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
