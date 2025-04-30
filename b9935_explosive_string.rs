use std::io;

fn main() {
    let (raw_str, explosive_str) = parse_data();
    let raw_len = raw_str.len();
    let explosive_len = explosive_str.len();
    let mut stack = raw_str.clone();
    stack.clear();

    let bytes = raw_str.as_bytes();
    let mut real_len = 0;
    for i in 0..raw_len {
        stack.push(bytes[i] as char);
        real_len += 1;
        if real_len >= explosive_len && &stack[real_len - explosive_len..] == &explosive_str[..] {
            stack.drain((real_len - explosive_len)..);
            real_len -= explosive_len;
        }
    }
    if real_len == 0 {
        println!("FRULA");
    } else {
        println!("{stack}");
    }
}

fn parse_data() -> (String, String) {
    let stdin = io::stdin();

    let mut line = String::new();
    stdin
        .read_line(&mut line)
        .expect("No line");


    let mut explosive_str = String::new();
    stdin
        .read_line(&mut explosive_str)
        .expect("No line");

    (line.trim().to_string(), explosive_str.trim().to_string())
}
