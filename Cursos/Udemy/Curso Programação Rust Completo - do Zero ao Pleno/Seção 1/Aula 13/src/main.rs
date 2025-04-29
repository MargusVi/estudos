use std::io::{self, Write};

fn convert_to_int(data_input: &str) -> i32 {
    data_input.trim().parse::<i32>().unwrap()
}

fn main() {
    let mut entrada_fatorial = String::new();

    print!("Insira o número base para o fatorial: ");
    let _ = io::stdout().flush();
    io::stdin()
        .read_line(&mut entrada_fatorial)
        .expect("Erro ao ler entrada_fatorial...");

    let mut num: i128 = convert_to_int(&entrada_fatorial).into();
    let mut fatorial: i128 = 1;

    while num > 1 {
        fatorial *= num;
        num -= 1;
    }

    println!("{}! = {}", entrada_fatorial.trim(), fatorial);
}
