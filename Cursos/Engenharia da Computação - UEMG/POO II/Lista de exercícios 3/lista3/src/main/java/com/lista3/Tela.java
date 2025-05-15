package com.lista3;
import java.awt.GridLayout;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
/**
 *
 * @author Marcos
 */
public class Tela extends JFrame {
    private final JPanel painel;
    // private final JTextArea jtxaResultado;
    private final String[] simbolos = {"AC / C", "+ / -", "%", "RAIZ Q", "/", "7", "8", "9", "X^Y", "*", "4", "5", "6", "X^2", "-", "1", "2", "3", "X^3", "+", "0", ".", "X!", "10^X", "="};
    private final JButton[] jbBotoes;
    
    public Tela() {
        painel = new JPanel();
        // jtxaResultado = new JTextArea();
        jbBotoes = new JButton[25];
        for (int i = 0; i < 25; i++) {
            jbBotoes[i] = new JButton(simbolos[i]);
        }
    }
    public void configurarJanela() {
        setVisible(true);
        setTitle("Aula 14/05");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(300, 200);
        setResizable(true);
        setLocation(600,300);
        add(painel);
        configurarPainel();
    }
    public void configurarPainel() {
        painel.setLayout(new GridLayout(5, 5, 1, 1));
        for (int i = 0; i < 25; i++) {
            painel.add(jbBotoes[i]);
            jbBotoes[i].addActionListener(evento -> {
                // System.out.println(jbBotoes[i].getName());
            });
        }
    }
}
