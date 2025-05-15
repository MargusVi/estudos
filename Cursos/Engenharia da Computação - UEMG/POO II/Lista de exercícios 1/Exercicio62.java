//62) Escreva um programa que calcule e retorne o valor da hipotenusa através do método HIPOTENUSA. O método recebe o valor da base e da altura de um triângulo.

import java.util.Scanner;
import java.lang.Math;

public class Exercicio62 {
    public static float HIPOTENUSA(float base, float altura) {
        float hipotenusa;
        hipotenusa = (float) Math.sqrt(Math.pow(base, 2) + Math.pow(altura, 2));
        return hipotenusa;
    }

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int opcao;
        
        do {
            float base, altura, hipotenusa;

            System.out.print("Digite a base do triângulo: ");
            base = scan.nextFloat();
            System.out.print("Digite a altura do triângulo: ");
            altura = scan.nextFloat();

            hipotenusa = HIPOTENUSA(base, altura);

            System.out.println("\nA hipotenusa é " + hipotenusa + ".");

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
