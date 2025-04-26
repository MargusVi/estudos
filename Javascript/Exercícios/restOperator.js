function imprimirNum(...args) { //Argumento que pode receber uma quantidade maleável de informações
    for(let i = 0; i < args.length; i++) {
        console.log(args[i])
    }
}

let num = 123456662

imprimirNum(num)

let num2 = 321

imprimirNum(num, num2, 1, 2, 3)