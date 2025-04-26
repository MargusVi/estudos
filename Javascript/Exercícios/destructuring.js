const person = {
    name: 'Jhon',
    lastname: 'Doe'
}

const {name: fname, lastname: lname} = person;

console.log(fname)
console.log(lname)
console.log(person)

//Maneira mais rápida de criar variáveis a partir de objetos



let arr = ['nome1', 'nome2', 'nome3']

let [nomeA, nomeB, nomeC] = arr
console.log(nomeB)