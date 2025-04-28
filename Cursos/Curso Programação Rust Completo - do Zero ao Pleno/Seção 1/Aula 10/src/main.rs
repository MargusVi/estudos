use std::io::{self, Write};

fn convert_to_int(data_input: &str) -> i32 {
    data_input.trim().parse::<i32>().unwrap()
}

fn main() {
    let mut num1 = String::new();
    print!("Insira o primeiro número: ");
    let _ = io::stdout().flush();
    io::stdin()
        .read_line(&mut num1)
        .expect("Erro ao ler num1...");

    let mut num2 = String::new();
    print!("Insira o segundo número: ");
    let _ = io::stdout().flush();
    io::stdin()
        .read_line(&mut num2)
        .expect("Erro ao ler num1...");

    if convert_to_int(&num1) > convert_to_int(&num2) {
        println!("O número {} é maior que {}", num1.trim(), num2);
    } else {
        println!("O número {} é menor ou igual que {}", num1.trim(), num2)
    }
}
