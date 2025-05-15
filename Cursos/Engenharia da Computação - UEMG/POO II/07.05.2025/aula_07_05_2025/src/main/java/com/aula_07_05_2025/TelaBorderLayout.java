package com.aula_07_05_2025;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.GridLayout;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
/**
 *
 * @author Marcos
 */
public class TelaBorderLayout extends JFrame {
    private final JPanel painel;
    private final JPanel[] regioes;
    private final JButton[] jbBotoesNorte;
    private final JLabel jlEast, jlWest, jlObservacao;
    private final JTextArea jtxaObservacao;
    private final JScrollPane jspObservacao;
    private final JButton[] jbBotoesCentro;
    private final JMenuBar barraMenu;
    private final JMenu jmSobre;
    private final JMenuItem jmiAbout;
    private final JMenuItem jmiOpcoes;
    
    public TelaBorderLayout(){
        painel = new JPanel();
        regioes = new JPanel[5];
        for (int i = 0; i < 5; i++) {
            regioes[i] = new JPanel();
        }
        jbBotoesNorte = new JButton[3];
        for (int i = 0; i < 3; i++) {
            jbBotoesNorte[i] = new JButton("Botão " + (i + 1));
        }
        jlEast = new JLabel("East");
        jlWest = new JLabel("West");
        jlObservacao = new JLabel("Observação: ");
        jtxaObservacao = new JTextArea(10, 20);
        jspObservacao = new JScrollPane(jtxaObservacao);
        jbBotoesCentro = new JButton[6];
        for (int i = 0; i < 6; i++) {
            jbBotoesCentro[i] = new JButton("Botão " + (i + 1));
        }
        barraMenu = new JMenuBar();
        jmSobre = new JMenu("Sobre");
        jmiAbout = new JMenuItem("About");
        jmiOpcoes = new JMenu("Opções");
    }
    public void configurarJanela(){
        setVisible(true);
        setTitle("Aula 07/05");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(300, 300);
        setResizable(true);
        setLocation(600,300);
        add(painel);
        setJMenuBar(barraMenu);
        configurarPainel();
    }
    public void configurarPainel(){
        painel.setLayout(new BorderLayout());
        configurarPainelNorth();
        painel.add(regioes[0], BorderLayout.NORTH);
        configurarPainelEast();
        painel.add(regioes[1], BorderLayout.EAST);
        configurarPainelSouth();
        painel.add(regioes[2], BorderLayout.SOUTH);
        configurarPainelWest();
        painel.add(regioes[3], BorderLayout.WEST);
        configurarPainelCenter();
        painel.add(regioes[4], BorderLayout.CENTER);
        barraMenu.add(jmSobre);
        jmSobre.add(jmiAbout);
        jmSobre.add(jmiOpcoes);
    }
    private void configurarPainelNorth() {
        regioes[0].setLayout(new FlowLayout(FlowLayout.RIGHT, 10, 5));
        regioes[0].setBackground(Color.WHITE);
        for (int i = 0; i < 3; i++) {
            regioes[0].add(jbBotoesNorte[i]);
        }
        jbBotoesNorte[0].addActionListener(evento -> {
            JOptionPane.showMessageDialog(this, "Clicou no botão 1!");
        });
        jbBotoesNorte[1].addActionListener(evento -> {
            jbBotoesNorte[0].setText("Botão clicado");
        });
        jbBotoesNorte[2].addActionListener(evento -> {
            System.exit(0);
        });
    }
    private void configurarPainelEast() {
        regioes[1].setBackground(Color.ORANGE);
        regioes[1].add(jlEast);
    }
    private void configurarPainelSouth() {
        regioes[2].setBackground(Color.RED);
        regioes[2].add(jlObservacao);
        regioes[2].add(jspObservacao);
    }
    private void configurarPainelWest() {
        jlWest.setText("Este é o texto que será utilizado bo BorderLayout West!");
        regioes[3].add(jlWest);
    }
    private void configurarPainelCenter() {
        regioes[4].setLayout(new GridLayout(3, 3));
        regioes[4].setBackground(Color.BLUE);
        for (int i = 0; i < 6; i++) {
            regioes[4].add(jbBotoesCentro[i]);
        }
        jbBotoesCentro[0].addActionListener(evento -> {
            JOptionPane.showMessageDialog(this, "Botão do centro clicado!");
        });
        jbBotoesCentro[1].addActionListener(evento -> {
            String texto = jtxaObservacao.getText();
            JOptionPane.showMessageDialog(this, "Texto do JTextArea do sul:\n" + texto);
        });
        jbBotoesCentro[2].addActionListener(evento -> {
            jbBotoesNorte[1].setForeground(Color.RED);
        });
        jbBotoesCentro[3].addActionListener(evento -> {
            jlEast.setFont(new Font("Arial Black", Font.ITALIC, 20));
        });
        jbBotoesCentro[4].addActionListener(evento -> {
            regioes[4].setBackground(Color.WHITE);
        });
        jbBotoesCentro[5].addActionListener(evento -> {
            regioes[4].setBackground(Color.BLUE);
        });
    }
}
