use std::io::{self, Write};

fn convert_to_int(data_input: &str) -> i32 {
    data_input.trim().parse::<i32>().unwrap()
}

fn main() {
    let mut soma = 0;
    let mut num = String::new();

    print!("Insira o número: ");
    let _ = io::stdout().flush();
    io::stdin().read_line(&mut num).expect("Erro ao ler num...");

    let mut num_i32 = convert_to_int(&num);
    while num_i32 != 0 {
        let resto = num_i32 % 10;
        soma += resto;
        num_i32 /= 10;
    }

    println!("Resultado: {}", soma);
}
