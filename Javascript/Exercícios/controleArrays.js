let arr = ['aaa', 'bbb', 'ccc']

let removido = arr.pop() //Retira o último elemento

console.log(arr)
console.log(removido)

arr.push('ddd') //Adiciona o último elemento

console.log(arr)

removido = arr.shift() //Retira o primeiro elemento

console.log(arr)
console.log(removido)

arr.unshift('eee') //Adiciona o primeiro elemento

console.log(arr)



let num = [0, 1, 2, 1, 0]

console.log(num.indexOf(1)) //Primeiro índice que aparece o procurado no array
console.log(num.lastIndexOf(1)) //Último índice que aparece o procurado no array



console.log(arr.slice(1))
console.log(arr.slice(0, 2)) //Cortar o array, indicando o index de início e o index de final
console.log(arr.slice(0, -1))
console.log(arr.slice(0,-2))



arr.forEach(element => {
    console.log(element)
});



console.log(arr.includes('aaa'))
console.log(arr.includes('bbb'))



console.log(arr.reverse())