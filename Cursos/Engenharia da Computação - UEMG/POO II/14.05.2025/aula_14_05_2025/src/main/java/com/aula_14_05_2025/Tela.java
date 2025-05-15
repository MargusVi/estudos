package com.aula_14_05_2025;
import java.text.ParseException;

import javax.swing.JButton;
import javax.swing.JFormattedTextField;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JSpinner;
import javax.swing.SpinnerListModel;
import javax.swing.SpinnerNumberModel;
import javax.swing.text.MaskFormatter;
/**
 *
 * @author Marcos
 */
public class Tela extends JFrame {
    private final JPanel painel;
    private final JLabel jlLogin, jlCep, jlOpcoes;
    private final JPasswordField jpfLogin;
    private final JButton jbImprimir;
    private JFormattedTextField jftxCep, jftxMaiusc;
    private final JSpinner jspOpcoes, jspIntervalo;
    
    // public Tela() throws ParseException {
    //     painel = new JPanel();  
    //     jlLogin = new JLabel("Login: ");
    //     jpfLogin = new JPasswordField();
    //     jbImprimir = new JButton("Imprimir");
    //     jlCep = new JLabel("CEP: ");
    //     jftxCep = new JFormattedTextField(new MaskFormatter("##.###-###"));
    // }
    public Tela() {
        painel = new JPanel();  
        jlLogin = new JLabel("Login: ");
        jpfLogin = new JPasswordField();
        jbImprimir = new JButton("Imprimir");
        jlCep = new JLabel("CEP: ");
        try {
            jftxCep = new JFormattedTextField(new MaskFormatter("##.###-###"));
            jftxMaiusc = new JFormattedTextField(new MaskFormatter("UUUU"));
        } catch (ParseException e) {
            System.out.println(e.getMessage());
        }
        jlOpcoes = new JLabel("Opções: ");
        jspOpcoes = new JSpinner(new SpinnerListModel(new String[]{"Opção 1", "Opção 2", "Opção 3", "Opção 4", "Opção 5"}));
        jspIntervalo = new JSpinner(new SpinnerNumberModel(50, 0, 100, 5));
    }
    public void configurarJanela(){
        setVisible(true);
        setTitle("Aula 14/05");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(300, 200);
        setResizable(true);
        setLocation(600,300);
        add(painel);
        configurarPainel();
    }
    public void configurarPainel(){
        painel.setLayout(null);
        jlLogin.setBounds(10, 10, 50, 20);
        painel.add(jlLogin);
        jpfLogin.setBounds(65, 10, 100, 20);
        painel.add(jpfLogin);
        jbImprimir.setBounds(170, 10, 100,20);
        painel.add(jbImprimir);
        jlCep.setBounds(10, 40, 50, 20);
        painel.add(jlCep);
        jftxCep.setBounds(65, 40, 90, 20);
        painel.add(jftxCep);
        jftxMaiusc.setBounds(170, 40, 50, 20);
        painel.add(jftxMaiusc);
        jlOpcoes.setBounds(10, 80, 50, 20);
        painel.add(jlOpcoes);
        jspOpcoes.setBounds(65, 80, 90, 20);
        painel.add(jspOpcoes);
        jspIntervalo.setBounds(170, 80, 70, 20);
        painel.add(jspIntervalo);
        jbImprimir.addActionListener(evento -> {
            // System.out.println("Senha: " + jpfLogin.getPassword()[0]);
            char[] retorno = jpfLogin.getPassword();
            String senha = new String(retorno);
            System.out.println("Senha: " + senha);
            System.out.println("CEP: " + jftxCep.getText());
            System.out.println("JFTX usando 'U': " + jftxMaiusc.getText());
            System.out.println("Opções: " + jspOpcoes.getValue().toString() + ", " + jspIntervalo.getValue().toString());
        });
    }
}
