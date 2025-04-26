public class main {
    public static void main(String[] args) {
        Agenda agenda = new Agenda();

        PessoaFisica pFisica1 = new PessoaFisica("Fulano", "Rua Z, 1", "fulano@gmail.com", "123.456.789-00", "01/01/1980", "Solteiro");
        PessoaFisica pFisica2 = new PessoaFisica("Ciclano", "Rua X, 2", "ciclano@outlook.com", "987.654.321-00", "02/02/1990", "Casada");
        PessoaJuridica pJuridica1 = new PessoaJuridica("Beltrano Ltda", "Praça Y, 3", "rh@beltrano.com.br", "12.345.678/0001-00", "123456", "Beltrano Ltda");
        PessoaJuridica pJuridica2 = new PessoaJuridica("Cipriano Tech", "Avenida K, 4", "box@cipriano.com.br", "98.765.432/0001-00", "654321", "Cipriano Tech Ltda");

        agenda.adicionarContato(pFisica1);
        agenda.adicionarContato(pFisica2);
        agenda.adicionarContato(pJuridica1);
        agenda.adicionarContato(pJuridica2);

        System.out.println("Contatos inseridos:");
        agenda.visualizarContatos();

        agenda.ordenarContatos();

        System.out.println("\nContatos ordenados:");
        agenda.visualizarContatos();
    }
}