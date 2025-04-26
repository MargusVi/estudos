/*
    Transforme o algoritmo de médias feito na aula passada em uma função.
*/

const nota1 = 10;
const nota2 = 4;
const nota3 = 6;

const media = ((nota1 + nota2 + nota3) / 3).toFixed(1);

console.log(`A média do aluno é ${media}.`);

if(media < 5) {
    console.log("Reprovado!");
} else if(media >= 5 && media < 7) {
    console.log("Em recuperação");
} else if(media >= 7) {
    console.log("Aprovado!")
}