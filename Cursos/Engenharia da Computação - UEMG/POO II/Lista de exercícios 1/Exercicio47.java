//47) Considere um vetor de 10 números inteiros positivos maiores que zero e um único número inteiro, também positivo e maior que zero. Faça um programa para:
// a. ler pelo teclado o vetor;
// b. ler pelo teclado o número X;
// c. dizer quantos números no vetor são maiores que X, menores que X e iguais a X.

import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;

public class Exercicio47 {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int opcao;
        
        do {
            int X, maior = 0, menor = 0, igual = 0;
            List<Integer> num = new ArrayList<Integer>();

            for(int i = 0; i < 10; i++) {
                System.out.print("Digite o " + (i+1) + "° número de x: ");
                num.add(scan.nextInt());
            }
            System.out.print("Digite o número X: ");
            X = scan.nextInt();

            for(int i = 0; i < 10; i++) {
                if(num.get(i) < X) {
                    menor++;
                } else if(num.get(i) == X) {
                    igual++;
                } else {
                    maior++;
                }
            }

            System.out.println("\n" + menor + " números no vetor são menores que " + X);
            System.out.println(igual + " número no vetor é igual a " + X);
            System.out.println(maior + " números no vetor são maiores que " + X);

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
