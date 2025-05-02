use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let k: usize = lines
        .next()
        .unwrap()
        .unwrap()
        .trim()
        .parse()
        .expect("Invalid number");

    let mut stack = Vec::<i32>::with_capacity(k.into());
    for _i in 0..k {
        let n: i32 = lines
            .next()
            .unwrap()
            .unwrap()
            .trim()
            .parse()
            .expect("Invalid number");

        if n == 0 {
            stack.pop();
        } else {
            stack.push(n);
        }
    }

    let sum: i32 = stack.iter().sum();

    println!("{sum}");
}
