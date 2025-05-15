package com.mycompany.aula_30_04;
import java.awt.Color;
import java.awt.Font;
import javax.swing.*;

/**
 *
 * @author Marcos
 */
public class TelatextArea extends JFrame {
    private JPanel painel;
    private JTextArea jtxaObservacao;
    private JScrollPane jspObservacao;
    private JButton jbImprimir, jbFormatar;
    public TelatextArea() {
        painel = new JPanel();
        jtxaObservacao = new JTextArea(0, 0);
        jspObservacao = new JScrollPane(jtxaObservacao);
        jbImprimir = new JButton("Imprimir");
        jbFormatar = new JButton("Formatar");
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
        jspObservacao.setBounds(10, 10, 190, 100);
        jspObservacao.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
        jspObservacao.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
        jtxaObservacao.setLineWrap(true);
        painel.add(jspObservacao);
        jbImprimir.setBounds(10, 120, 90, 20);
        jbImprimir.addActionListener(evento ->{
            String texto = jtxaObservacao.getText();
            JOptionPane.showMessageDialog(this, texto);
        });
        painel.add(jbImprimir);
        jbFormatar.setBounds(110, 220, 90, 20);
        jbFormatar.addActionListener(evento ->{
            jtxaObservacao.setFont(new Font("Arial", Font.BOLD, 16));
            jtxaObservacao.setForeground(Color.MAGENTA);
        });
        painel.add(jbFormatar);
    };
}