import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

public class Agenda {
    private ArrayList<Contato> contatos;

    public Agenda() {
        this.contatos = new ArrayList<>();
    }

    public void adicionarContato(Contato contato) {
        contatos.add(contato);
    }

    public void removerContato(Contato contato) {
        contatos.remove(contato);
    }

    public Contato pesquisarPorNome(String nome) {
        for (Contato contato : contatos) {
            if (contato.getNome().equalsIgnoreCase(nome)) {
                return contato;
            }
        }
        return null;
    }

    public Contato pesquisarPorIdentificador(String identificador) {
        for (Contato contato : contatos) {
            if (contato.getIdentificador().equalsIgnoreCase(identificador)) {
                return contato;
            }
        }
        return null;
    }

    public void visualizarContatos() {
        for (Contato contato : contatos) {
            System.out.println(contato);
        }
    }

    public void ordenarContatos() {
        Collections.sort(contatos, new Comparator<Contato>() {
            @Override
            public int compare(Contato c1, Contato c2) { // Ordenar pessoas físicas antes de jurídicas
                if (c1 instanceof PessoaFisica && c2 instanceof PessoaJuridica) {
                    return -1;
                } else if (c1 instanceof PessoaJuridica && c2 instanceof PessoaFisica) {
                    return 1;
                } else {
                    return c1.getIdentificador().compareTo(c2.getIdentificador());
                }
            }
        });
    }
}