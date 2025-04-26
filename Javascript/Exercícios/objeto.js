let objetoA = {
    prop1: 'teste',
    prop2: 'teste2'
}

let objetoB = {
    prop3: 'teste3'
}

objetoA.prop4 = 'teste4'

console.log(objetoA)

delete objetoA.prop4

Object.assign(objetoA, objetoB)

console.log(objetoA)

console.log(Object.keys(objetoA))



//Mutação:
objetoC = objetoA

console.log(objetoC == objetoA)
console.log(objetoC == objetoB)

objetoD = objetoC

console.log(objetoD == objetoA)

console.log(objetoD)

objetoA.prop5 = 'teste5'

console.log(objetoD)