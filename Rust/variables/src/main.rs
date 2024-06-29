fn main() {
    let name: &str = "Fulano";
    println!("Hello {}!", name);

    let mut age: i32 = 30; // i(nBits) - Define o tamanho máximo do número inteiro
    println!("Age: {}", age);
    age += 1;
    println!("Age: {}", age);

    let unsigned_number: u16 = 12; // u(nbits) - Recebe somente números sem sinal
    println!("Unsigned number: {}", unsigned_number);

    let signed_number: i16 = -12;
    println!("Signed number: {}", signed_number);

    let float_number: f32 = 3.14159;
    println!("Float: {}", float_number);

    let boolean: bool = true;
    println!("Boolean: {}", boolean);
}