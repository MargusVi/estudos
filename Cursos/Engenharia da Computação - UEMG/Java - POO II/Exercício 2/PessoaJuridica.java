public class PessoaJuridica extends Contato {
    private String cnpj;
    private String inscricaoEstadual;
    private String razaoSocial;

    public PessoaJuridica(String nome, String endereco, String email, String cnpj, String inscricaoEstadual, String razaoSocial) {
        super(nome, endereco, email);
        this.cnpj = cnpj;
        this.inscricaoEstadual = inscricaoEstadual;
        this.razaoSocial = razaoSocial;
    }

    public String getCnpj() {
        return cnpj;
    }

    public String getInscricaoEstadual() {
        return inscricaoEstadual;
    }

    public String getRazaoSocial() {
        return razaoSocial;
    }

    @Override
    public String getIdentificador() {
        return cnpj;
    }

    @Override
    public String toString() {
        return super.toString() + ", CNPJ: " + cnpj + ", Inscrição Estadual: " + inscricaoEstadual + ", Razão Social: " + razaoSocial;
    }
}