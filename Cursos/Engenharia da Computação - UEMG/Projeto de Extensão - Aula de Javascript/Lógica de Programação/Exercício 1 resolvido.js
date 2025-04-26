/*
    Elabore um algoritmo que dado duas variáveis: o peso e a altura de um adulto, mostre sua condição de acordo com a tabela abaixo. Utilize if else para validar as condições.

    IMC em adultos:
    - Abaixo de 18.5 = abaixo do peso
    - Entre de 18.5 e 25 = peso normal
    - Entre 25 e 30 = acima do peso
    - Entre 30 e 40 = obeso
    - Acima de 40 = obesidade grave

    Fórmula do IMC: IMC = peso / (altura * altura)
*/

/*
    Agora transforme as variáveis do exercício anterior em um objeto. Modifique o código para que ele funcione.
*/

let pessoa = {
    altura: 1.80,
    peso: 80
}

IMC = pessoa.peso / (pessoa.altura * pessoa.altura);

console.log("Seu IMC é " + IMC + ".");

if(IMC < 18.5) {
    console.log('Abaixo do peso!');
} else if(IMC >= 18.5 && IMC <= 25) {
    console.log('Peso normal!');
} else if(IMC > 25 && IMC <= 30) {
    console.log('Acima do peso');
} else if(IMC > 30 && IMC <= 40) {
    console.log('Obeso!');
} else if(IMC > 40) {
    console.log('Obesidade grave!');
} else {
    console.log('Erro!');
}