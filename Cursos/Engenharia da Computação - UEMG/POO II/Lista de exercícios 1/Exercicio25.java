//24) Tendo como dados de entrada a altura e o sexo de uma pessoa, faça um programa que calcule seu peso ideal, utilizando as seguintes fórmulas: (h = altura)
// Para homens: (72.7 * h) - 58
// Para mulheres: (62.1 * h) - 44.7
// 3- Verificar se a média dos dois números é maior ou igual a 7
//4- Sair

import java.util.Scanner;

public class Exercicio25 {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int opcao;
        
        do {
            float altura, pesoIdeal;
            int sexo;

            System.out.print("\nDigite sua altura: ");
            altura = scan.nextFloat();
            System.out.print("Digite seu sexo (1 para masculino e 2 para feminino): ");
            sexo = scan.nextInt();

            if(sexo == 1) {
                pesoIdeal = (float) ((72.7 * altura) - 58);
                System.out.println("Seu peso ideal é " + pesoIdeal + "Kg");
            } else if(sexo == 2) {
                pesoIdeal = (float) ((62.1 * altura) - 44.7);
                System.out.println("Seu peso ideal é " + pesoIdeal + "Kg");
            } else {
                System.out.println("\nOpção inválida.\n");
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
