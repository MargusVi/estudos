package com.lista3;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.math.BigDecimal;
import java.math.MathContext;
import java.math.RoundingMode;
import java.text.DecimalFormat;
import java.text.DecimalFormatSymbols;
import java.util.Locale;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;

/**
 * Calculadora
 * @author Marcos
 */
public class Tela extends JFrame implements ActionListener {

    private final JPanel painelPrincipal;
    private JTextField displayField;

    private final String[] simbolos = {
        "AC / C", "+ / -", "%", "RAIZ Q", "/",
        "7", "8", "9", "X^Y", "*",
        "4", "5", "6", "X^2", "-",
        "1", "2", "3", "X^3", "+",
        "0", ".", "X!", "10^X", "="
    };
    private final JButton[] jbBotoes;

    private String currentInput = "0";
    private double firstOperand = 0;
    private String pendingOperation = "";
    private boolean startNewNumber = true;

    private DecimalFormat df;

    // Constantes para BigDecimal
    private static final int DEFAULT_SCALE = 10;
    private static final MathContext MC = new MathContext(15, RoundingMode.HALF_UP);

    public Tela() {
        painelPrincipal = new JPanel(new BorderLayout(5, 5)); // Painel principal com BorderLayout
        jbBotoes = new JButton[simbolos.length]; // Ajustado para o tamanho de simbolos

        // Configurar DecimalFormat
        DecimalFormatSymbols symbols = new DecimalFormatSymbols(Locale.US);
        df = new DecimalFormat("#.##########", symbols);

        criarComponentes();
    }

    private void criarComponentes() {
        displayField = new JTextField("0", 20);
        displayField.setEditable(false);
        displayField.setHorizontalAlignment(JTextField.RIGHT);
        displayField.setFont(new Font("Arial", Font.BOLD, 28)); // Fonte ajustada
        displayField.setBackground(Color.WHITE);
        displayField.setBorder(BorderFactory.createCompoundBorder(
            displayField.getBorder(),
            BorderFactory.createEmptyBorder(10, 10, 10, 10) // Padding interno
        ));
        painelPrincipal.add(displayField, BorderLayout.NORTH);

        JPanel painelBotoes = new JPanel(new GridLayout(5, 5, 5, 5)); // Usando 5x5 conforme simbolos
        painelPrincipal.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

        for (int i = 0; i < simbolos.length; i++) {
            jbBotoes[i] = new JButton(simbolos[i]);
            jbBotoes[i].setFont(new Font("Arial", Font.PLAIN, 16)); // Fonte ajustada
            jbBotoes[i].addActionListener(this);
            jbBotoes[i].setFocusPainted(false);

            if (simbolos[i].matches("[0-9.]")) {
                jbBotoes[i].setBackground(new Color(240, 240, 240));
            } else if (simbolos[i].equals("=")) {
                jbBotoes[i].setBackground(new Color(255, 153, 0)); // Laranja para o igual
                jbBotoes[i].setForeground(Color.WHITE);
            } else {
                jbBotoes[i].setBackground(new Color(200, 200, 200));
            }
            painelBotoes.add(jbBotoes[i]);
        }
        painelPrincipal.add(painelBotoes, BorderLayout.CENTER);
    }

    public void configurarJanela() {
        setTitle("Calculadora");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setMinimumSize(new Dimension(500, 500));
        setLocationRelativeTo(null);
        setResizable(true);
        add(painelPrincipal);
        setVisible(true);
    }

    private double somar(double num1, double num2) {
        return num1 + num2;
    }
    private double subtrair(double num1, double num2) {
        return num1 - num2;
    }
    private double multiplicar(double num1, double num2) {
        return num1 * num2;
    }
    private double dividir(double num1, double num2) {
        if (num2 == 0) {
            throw new ArithmeticException("Divisão por zero");
        }
        BigDecimal bdNum1 = BigDecimal.valueOf(num1);
        BigDecimal bdNum2 = BigDecimal.valueOf(num2);
        return bdNum1.divide(bdNum2, DEFAULT_SCALE, RoundingMode.HALF_UP).doubleValue();
    }
    private double raizQuadrada(double num) {
        if (num < 0) {
            throw new IllegalArgumentException("Raiz de negativo");
        }
        return Math.sqrt(num);
    }
    private double porcentagem(double valorAtualNoDisplay, Double operandoAnterior, String opPendente) {
        if (operandoAnterior != null && opPendente != null && !opPendente.isEmpty()) {
            return operandoAnterior * (valorAtualNoDisplay / 100.0);
        } else {
            return valorAtualNoDisplay / 100.0;
        }
    }
    private double potenciaXY(double base, double expoente) {
        return Math.pow(base, expoente);
    }
    private double aoQuadrado(double num) {
        return num * num;
    }
    private double aoCubo(double num) {
        return num * num * num;
    }
    private long fatorial(double num) {
        if (num < 0) {
            throw new IllegalArgumentException("Fatorial de negativo");
        }
        int n = (int) Math.round(num);
        if (n != num) {
             throw new IllegalArgumentException("Fatorial de não inteiro");
        }
        if (n > 20) {
            throw new ArithmeticException("Fatorial > 20!");
        }
        if (n == 0 || n == 1) return 1;
        long resultado = 1;
        for (int i = 2; i <= n; i++) resultado *= i;
        return resultado;
    }
    private double dezElevadoA(double expoente) {
        return Math.pow(10, expoente);
    }
    private double inverterSinal(double num) {
        return -num;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        String command = e.getActionCommand();

        try {
            if (command.matches("[0-9]")) {
                handleNumberInput(command);
            } else if (command.equals(".")) {
                handleDecimalInput();
            } else if (command.equals("AC / C")) {
                handleClear();
            } else if (command.equals("+ / -")) {
                handleSignChange();
            } else if (command.equals("%") || command.equals("RAIZ Q") || command.equals("X!") ||
                       command.equals("X^2") || command.equals("X^3") || command.equals("10^X")) {
                handleUnaryOperation(command);
            } else if (command.equals("=") || command.equals("/") || command.equals("*") ||
                       command.equals("-") || command.equals("+") || command.equals("X^Y")) {
                handleBinaryOperation(command);
            }
        } catch (ArithmeticException | IllegalArgumentException ex) {
            displayField.setText("Erro: " + ex.getMessage());
            resetCalculatorStateOnError();
        } catch (Exception ex) {
            displayField.setText("Erro inesperado");
            resetCalculatorStateOnError();
        }
    }

    private void handleNumberInput(String number) {
        if (startNewNumber || currentInput.equals("Erro") || currentInput.contains("Erro:")) {
            currentInput = number;
            startNewNumber = false;
        } else {
            if (currentInput.equals("0") && !number.equals("0")) {
                 currentInput = number;
            } else if (!currentInput.equals("0") || !number.equals("0") || currentInput.contains(".")) {
                 // Permite adicionar mais zeros se já houver um ponto ou se não for o primeiro zero
                 if(currentInput.length() < 16) { // Limita o número de dígitos
                    currentInput += number;
                 }
            }
        }
        displayField.setText(currentInput);
    }

    private void handleDecimalInput() {
        if (startNewNumber || currentInput.equals("Erro") || currentInput.contains("Erro:")) {
            currentInput = "0.";
            startNewNumber = false;
        } else if (!currentInput.contains(".")) {
            if(currentInput.length() < 16) {
                currentInput += ".";
            }
        }
        displayField.setText(currentInput);
    }

    private void handleClear() {
        if (!currentInput.equals("0") && !startNewNumber && !currentInput.isEmpty() && !currentInput.contains("Erro")) {
            currentInput = "0";
            startNewNumber = true;
        } else {
            currentInput = "0";
            firstOperand = 0;
            pendingOperation = "";
            startNewNumber = true;
        }
        displayField.setText(currentInput);
    }

    private void handleSignChange() {
        if (!currentInput.isEmpty() && !currentInput.startsWith("Erro") && !currentInput.equals("0")) {
            double value = Double.parseDouble(currentInput);
            currentInput = df.format(inverterSinal(value));
            displayField.setText(currentInput);
        }
    }

    private void handleUnaryOperation(String operation) {
        if (currentInput.startsWith("Erro")) return;

        double value = Double.parseDouble(currentInput);
        double result = 0;

        switch (operation) {
            case "%":
                Double operandoAnteriorParaPct = null;
                if (!pendingOperation.isEmpty() && startNewNumber) {
                     operandoAnteriorParaPct = firstOperand;
                }
                result = porcentagem(value, operandoAnteriorParaPct, pendingOperation);
                break;
            case "RAIZ Q":
                result = raizQuadrada(value);
                break;
            case "X!":
                result = fatorial(value);
                break;
            case "X^2":
                result = aoQuadrado(value);
                break;
            case "X^3":
                result = aoCubo(value);
                break;
            case "10^X":
                result = dezElevadoA(value);
                break;
        }
        currentInput = df.format(result);
        displayField.setText(currentInput);
        startNewNumber = true;
    }

    private void handleBinaryOperation(String operation) {
        if (currentInput.startsWith("Erro")) {
            handleClear();
            if (currentInput.startsWith("Erro")) return;
        }

        if (!pendingOperation.isEmpty() && !startNewNumber) {
            double secondOperand = Double.parseDouble(currentInput);
            calculate(secondOperand);
        } else if (!pendingOperation.isEmpty() && startNewNumber && operation.equals("=")) {
             if (!currentInput.isEmpty()) {
                double secondOperand = Double.parseDouble(currentInput);
                calculate(secondOperand);
            }

        }
        if(!currentInput.startsWith("Erro")) {
            firstOperand = Double.parseDouble(currentInput);
        }


        if (!operation.equals("=")) {
            pendingOperation = operation;
            startNewNumber = true;
        } else {
            pendingOperation = "";
            startNewNumber = true;
        }
    }

    private void calculate(double secondOperand) {
        double result = 0;
        switch (pendingOperation) {
            case "/": result = dividir(firstOperand, secondOperand); break;
            case "*": result = multiplicar(firstOperand, secondOperand); break;
            case "-": result = subtrair(firstOperand, secondOperand); break;
            case "+": result = somar(firstOperand, secondOperand); break;
            case "X^Y": result = potenciaXY(firstOperand, secondOperand); break;
            default:
                displayField.setText(currentInput);
                return;
        }
        currentInput = df.format(result);
        displayField.setText(currentInput);
        firstOperand = result;
    }

    private void resetCalculatorStateOnError() {
        firstOperand = 0;
        pendingOperation = "";
        startNewNumber = true;
    }
}
