let texto = '  \n texto \n  '
console.log(texto)
console.log(texto.trim()) //Retira tudo que não é string



let milAoContrario = '1'
console.log(milAoContrario.padStart(4, '0')) //Adiciona caracteres antes da string



let str = "Teste teste1 teste2 teste3"
let palavras = str.split(' ')
console.log(str)
console.log(palavras)

console.log(palavras.join('<->'))

console.log("Teste ".repeat(5))