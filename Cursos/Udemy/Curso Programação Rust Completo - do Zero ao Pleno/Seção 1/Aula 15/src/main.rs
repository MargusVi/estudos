use std::io::{self, Write};

fn convert_to_int(data_input: &str) -> i32 {
    data_input.trim().parse::<i32>().unwrap()
}

fn status_de_aprovacao(nota_media: i32) -> String {
    if nota_media >= 6 {
        "aprovado".to_string()
    } else if (3..6).contains(&nota_media) {
        "em recuperação".to_string()
    } else {
        "reprovado".to_string()
    }
}

fn main() {
    let mut nota_media_aluno_1 = String::new();
    let mut nota_media_aluno_2 = String::new();
    let mut nota_media_aluno_3 = String::new();

    print!("Insira a nota média do 1° aluno: ");
    let _ = io::stdout().flush();
    io::stdin()
        .read_line(&mut nota_media_aluno_1)
        .expect("Erro ao ler nota_media_aluno_1...");
    println!(
        "Aluno 1 {}!\n",
        status_de_aprovacao(convert_to_int(&nota_media_aluno_1))
    );

    print!("Insira a nota média do 2° aluno: ");
    let _ = io::stdout().flush();
    io::stdin()
        .read_line(&mut nota_media_aluno_2)
        .expect("Erro ao ler nota_media_aluno_2...");
    println!(
        "Aluno 2 {}!\n",
        status_de_aprovacao(convert_to_int(&nota_media_aluno_2))
    );

    print!("Insira a nota média do 3° aluno: ");
    let _ = io::stdout().flush();
    io::stdin()
        .read_line(&mut nota_media_aluno_3)
        .expect("Erro ao ler nota_media_aluno_3...");
    println!(
        "Aluno 3 {}!\n",
        status_de_aprovacao(convert_to_int(&nota_media_aluno_3))
    );
}
