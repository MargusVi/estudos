//24) Escreva um programa que leia dois números inteiros e apresente as opções para o usuário escolher o que deseja realizar:
// 1- Verificar se um dos números lidos é ou não múltiplo do outro
// 2- Verificar se os dois números lidos são pares
// 3- Verificar se a média dos dois números é maior ou igual a 7
//4- Sair

import java.util.Scanner;

public class Exercicio24 {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int opcao1, opcao2;
        
        do {
            int num1, num2;
            System.out.print("\nDigite um número inteiro: ");
            num1 = scan.nextInt();
            System.out.print("Digite outro número inteiro: ");
            num2 = scan.nextInt();

            do {
                System.out.println("O que deseja fazer?");
                System.out.println("1- Verificar se um dos números lidos é ou não múltiplo do outro");
                System.out.println("2- Verificar se os dois números lidos são pares");
                System.out.println("3- Verificar se a média dos dois números é maior ou igual a 7");
                System.out.println("4- Sair");
                System.out.print("Escolha uma opção: ");
                opcao1 = scan.nextInt();

                switch (opcao1) {
                    case 1:
                        if(num1 % num2 == 0 || num2 % num1 == 0) {
                            System.out.println("Os números são múltiplos um do outro.\n");
                        } else {
                            System.out.println("Os números não são múltiplos um do outro.\n");
                        }
                        break;
                    case 2:
                        if(num1 % 2 == 0 && num2 % 2 == 0) {
                            System.out.println("Os dois números são pares.\n");
                        } else {
                            System.out.println("Pelo menos um dos números não é par.\n");
                        }
                        break;
                    case 3:
                        if((num1 + num2) / 2 >= 7) {
                            System.out.println("A média dos dois números é maior ou igual a 7.\n");
                        } else {
                            System.out.println("A média dos dois números é menor que 7.\n");
                        }
                        break;
                    default:
                        break;
                }
                if(opcao1 < 1 || opcao1 > 4) {
                    System.out.println("Opção inválida!\n");
                }
            } while(opcao1 != 4);

            System.out.println("\nDeseja executar novamente?");
            System.out.println("1 - Sim");
            System.out.println("0 - Não");
            System.out.print("Escolha uma opção: ");
            opcao2 = scan.nextInt();
            if(opcao2 == 0) {
                System.out.println("\nEncerrando o programa...\n");
            }
            if(opcao2 != 0 && opcao2 != 1) {
                System.out.println("\nOpção inválida, encerrando o programa!\n");
            }
        } while(opcao2 == 1);
    }
}
