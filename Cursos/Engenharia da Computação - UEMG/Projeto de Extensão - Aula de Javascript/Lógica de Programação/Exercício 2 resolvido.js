/*
    Transforme o algoritmo de médias feito na aula passada em uma função.
*/

function media(nota1, nota2, nota3) {
    let media = ((nota1 + nota2 + nota3) / 3).toFixed(1);

    console.log(`A média do aluno é ${media}.`);

    if(media < 5) {
        console.log("Reprovado!");
    } else if(media >= 5 && media < 7) {
        console.log("Em recuperação");
    } else if(media >= 7) {
        console.log("Aprovado!")
    }
}

media(10, 6, 4);