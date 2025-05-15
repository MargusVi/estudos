package com.mycompany.aula_30_04;
import javax.swing.*;
/**
 *
 * @author Marcos
 */
public class TelaCombo extends JFrame {
    private JPanel painel;
    private JComboBox jcbEstados;
    private JLabel jlEstados;
    private JButton jbAdicionar;
    private JButton jbImprimir;
    public TelaCombo() {
        painel = new JPanel();
        jcbEstados = new JComboBox(new String[]{"Acre", "Minas Gerais", "São Paulo", "Rio de Janeiro"});
        jlEstados = new JLabel("Selecione o seu estado: ");
        jbAdicionar = new JButton("Adicionar");
        jbImprimir = new JButton("Imprimir");
    }
    
    public void configurarJanela(){
        setVisible(true);
        setTitle("Aula 30/04");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(300, 300);
        setLocation(600, 300);
        configurarPainel();
    }
    
    public void configurarPainel() {
        painel.setLayout(null);
        jlEstados.setBounds(10, 10, 120, 20);
        painel.add(jlEstados);
        jcbEstados.setBounds(150,10,100,20);
        painel.add(jcbEstados);
        jbAdicionar.setBounds(40, 30, 90, 20);
        jbAdicionar.addActionListener(evento ->{
            String estado = JOptionPane.showInputDialog(this, "Digite um estado: ");
            jcbEstados.addItem(estado);
        });
        painel.add(jbAdicionar);
        jbImprimir.setBounds(155, 30, 90, 20);
        jbImprimir.addActionListener(evento ->{
            String estado = jcbEstados.getSelectedItem().toString();
            int indice = jcbEstados.getSelectedIndex();
            JOptionPane.showMessageDialog(this, "O índice que foi selecionado: " + indice + "\nCorresponde ao estado: " + estado);
        });
        painel.add(jbImprimir);
    }
}