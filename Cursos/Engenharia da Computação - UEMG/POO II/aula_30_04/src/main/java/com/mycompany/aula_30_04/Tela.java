package com.mycompany.aula_30_04;
import java.awt.Color;
import java.awt.Font;
import javax.swing.*;
import javax.swing.table.DefaultTableModel;

/**
 *
 * @author Marcos
 */
public class Tela extends JFrame {
    private JPanel painel;
    private JTable jtProduto; 
    private JScrollPane jspProduto;
    private DefaultTableModel modeloProduto;
    private JButton jbAdicionar, jbImprimir;
    public Tela() {
        painel = new JPanel();
        // jtProduto = new JTable(new String[][]{{"1", "1", "1"},{"2", "2", "2"}}, new String[]{"Descrição", "Preço", "Estoque"});
        modeloProduto = new DefaultTableModel(new String[]{"Descrição", "Preço", "Estoque"}, 0);
        jtProduto = new JTable(modeloProduto);
        jspProduto = new JScrollPane(jtProduto);
        jbAdicionar = new JButton("Adicionar");
        jbImprimir = new JButton("Imprimir");
    }
    
    public void configurarJanela(){
        setVisible(true);
        setTitle("Aula 30/04");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setResizable(true);
        setSize(300, 300);
        setLocation(600, 300);
        configurarPainel();
    }
    
    public void configurarPainel() {
        painel.setLayout(null);
        jtProduto.setBounds(10, 10, 160, 100);
        painel.add(jtProduto);
        jbAdicionar.setBounds(10, 120, 90, 20);
        jbAdicionar.addActionListener(evento ->{
            modeloProduto.addRow(new String[]{"Batata", "2,99", "50"});
        });
        painel.add(jbAdicionar);
        jbImprimir.setBounds(110, 120, 90, 20);
        jbImprimir.addActionListener(evento ->{
            int linha = jtProduto.getSelectedRow();
            JOptionPane.showMessageDialog(this, "Descrição: " + jtProduto.getValueAt(linha, 0) + "\nPreço: " + jtProduto.getValueAt(linha, 1) + "\nEstoque: " + jtProduto.getValueAt(linha, 2));
        });
        painel.add(jbImprimir);
    };
}