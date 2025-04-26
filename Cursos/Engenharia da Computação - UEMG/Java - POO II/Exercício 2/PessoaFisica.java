public class PessoaFisica extends Contato {
    private String cpf;
    private String dataNascimento;
    private String estadoCivil;

    public PessoaFisica(String nome, String endereco, String email, String cpf, String dataNascimento, String estadoCivil) {
        super(nome, endereco, email);
        this.cpf = cpf;
        this.dataNascimento = dataNascimento;
        this.estadoCivil = estadoCivil;
    }

    public String getCpf() {
        return cpf;
    }

    public String getDataNascimento() {
        return dataNascimento;
    }

    public String getEstadoCivil() {
        return estadoCivil;
    }

    @Override
    public String getIdentificador() {
        return cpf;
    }

    @Override
    public String toString() {
        return super.toString() + ", CPF: " + cpf + ", Data de Nascimento: " + dataNascimento + ", Estado Civil: " + estadoCivil;
    }
}