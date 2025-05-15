package com.aula_07_05_2025;
import java.awt.BorderLayout;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
/**
 *
 * @author Marcos
 */
public class Tela extends JFrame {
    private final JPanel painel;
    private final JButton[] jbBotoes;
    
    public Tela(){
        painel = new JPanel();
        jbBotoes = new JButton[5];
        for (int i = 0; i < 5; i++) {
            jbBotoes[i] = new JButton("Botão " + (i + 1));
        }
        
    }
    public void configurarJanela(){
        setVisible(true);
        setTitle("Aula 07/05");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(300, 300);
        setResizable(true);
        setLocation(600,300);
        add(painel);
        configurarPainel();
    }
    public void configurarPainel(){
        // painel.setLayout(new FlowLayout(FlowLayout.RIGHT, 50, 50));
        // painel.setLayout(new GridLayout(3, 2, 2, 2));
        painel.setLayout(new BorderLayout(0, 0));
        // for (int i = 0; i < 5; i++) {
        //     painel.add(jbBotoes[i]);
        // }
        painel.add(jbBotoes[0], BorderLayout.NORTH);
        painel.add(jbBotoes[1], BorderLayout.SOUTH);
        painel.add(jbBotoes[2], BorderLayout.WEST);
        painel.add(jbBotoes[3], BorderLayout.EAST);
        painel.add(jbBotoes[4], BorderLayout.CENTER);
    }
}
