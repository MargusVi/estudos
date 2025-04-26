//60) Escreva um programa que calcule e retorne o salário atualizado através do método REAJUSTE. O método deve receber o valor do salário e o índice de reajuste.

import java.util.Scanner;
import java.text.DecimalFormat;

public class Exercicio61 {
    public static float REAJUSTE(float salario, float reajuste) {
        return (salario + (salario * (reajuste / 100)));
    }

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int opcao;
        
        do {
            float salario, reajuste, novoSalario;

            java.text.DecimalFormat df = new DecimalFormat("00.00");

            System.out.print("Digite o salário atual: R$");
            salario = scan.nextFloat();
            System.out.print("Digite o índice de reajuste (%): ");
            reajuste = scan.nextInt();

            novoSalario = REAJUSTE(salario, reajuste);

            System.out.println("\nSeu salário reajustado é R$" + df.format(novoSalario) + ".");

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
