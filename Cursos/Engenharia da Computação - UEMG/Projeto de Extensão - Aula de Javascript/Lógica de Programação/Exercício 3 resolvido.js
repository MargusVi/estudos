/*
    Crie uma função que dado um número imprima a tabuada desse número. Utilize a estrutura de repetição for.
*/

function tabuada(num) {
    for (let i = 0; i <= 10; i++) {
        console.log(`${num} * ${i} = ${num*i}`);
    }
}

tabuada(2);