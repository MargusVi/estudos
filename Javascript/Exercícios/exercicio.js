let arr = [1, 2, 3, 4, 5]

arr.forEach(element => {
    if(element % 2 != 0)
    {
        console.log(element)
    }
});

console.log(arr[1])

let arr2 = [6, 7]

console.log(arr.length)
console.log(arr2.length)


let onibus = {
    rodas: 8,
    passageiros: 40,
    portas: 1
}

console.log(onibus)

onibus.janelas = 20

delete onibus.portas

console.log(onibus)



let arr3 = ["Ronan", "Alan", "Ellen", "Marcos", "Lucas"]

arr3.forEach(element => {
    if(element == "Marcos") {
        console.log("Seu nome está no array!\n")
    }
});

if(arr3.includes("Marcos")) {
    console.log("Seu nome está no array!\n")
} else {
    console.log("Nome não encontrado!")
}

if(arr3.length >= 5) {
    console.log("Muitos elementos\n")
}


let calculadora = {
    soma: function(a, b) {
        return a + b
    },
    sub: function(a, b) {
        return a - b
    },
    div: function(a, b) {
        return a / b
    },
    mult: function(a, b) {
        return a * b
    }
}


console.log(calculadora.soma(3, 4),
calculadora.sub(3, 4),
calculadora.div(3, 4),
calculadora. mult(3, 4))