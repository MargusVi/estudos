//3) Faça um programa para pagamento de comissão de vendedores de peças, levando-se em consideração que sua comissão será de 5% do total da venda e que você tem os seguintes dados:
// - Identificação do vendedor
// - Código da peça
// - Preço unitário da peça
// - Quantidade vendida

import java.util.Scanner;
import java.text.DecimalFormat;

public class Exercício3 {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int opcao;

        do {
            String idVend;
            float precoPeca, comissao, total;
            int codPeca, qtde;
            java.text.DecimalFormat df = new DecimalFormat("00.00");
            System.out.print("\nDigite a identificação do vendedor: ");
            idVend = scan.nextLine();
            System.out.print("Digite o código da peça: ");
            codPeca = scan.nextInt();
            System.out.print("Digite o preço unitário da peça: R$");
            precoPeca = scan.nextFloat();
            System.out.print("Digite a quantidade vendida: ");
            qtde = scan.nextInt();
            total = precoPeca * qtde;
            comissao = (float) (total * 0.05);

            System.out.println("\nIdentificação do vendedor: " + idVend);
            System.out.println("Código da peça: " + codPeca);
            System.out.println("Preço unitário da peça: R$" + df.format(precoPeca));
            System.out.println("Quantidade vendida: " + qtde);
            System.out.println("Total: R$" + total);
            System.out.println("Comissão: R$" + df.format(comissao));

            System.out.println("\nDeseja realizar um novo cálculo?");
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