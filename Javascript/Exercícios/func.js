function funcaoCompleta(idade)
{
    console.log("Hello, World!");
    console.log(`Você tem ${idade} anos.`);
    if(idade >= 18)
    {
        console.log("Você pode tirar a carteira de motorista!\n");
    }
    else
    {
        console.log("Você ainda não pode tirar a carteira de motorista.\n");
    }

    let soma = idade + 10;
    console.log(`Daqui a 10 anos você terá ${soma} anos.`);

    let num = Math.random();
    return num;
}

let num = funcaoCompleta(21);
console.log(num);