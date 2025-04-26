public abstract class Contato {
    private String nome;
    private String endereco;
    private String email;

    public Contato(String nome, String endereco, String email) {
        this.nome = nome;
        this.endereco = endereco;
        this.email = email;
    }

    public String getNome() {
        return nome;
    }

    public String getEndereco() {
        return endereco;
    }

    public String getEmail() {
        return email;
    }

    public abstract String getIdentificador();

    @Override
    public String toString() {
        return "Nome: " + nome + ", Endereço: " + endereco + ", Email: " + email;
    }
}