//Orientação a objetos

const cachorro = { //Criando método
    nome: "",
    setNome: function(novoNome) {
        this.nome = novoNome
    },
    getNome: function() {
        return this.nome
    },
    uivar: function() {
        console.log("AUUUUUU")
    },
    rosnar: function() {
        console.log("GRRRRR")
    }
}

cachorro.uivar()
cachorro.rosnar()
cachorro.setNome("Marrom")
console.log(cachorro.getNome())