use std::io;

#[derive(Clone)]
#[derive(Copy)]
enum Operator {
    ADD,
    SUB,
    MUL,
    DIV,
}

impl Operator {
    fn operate(&self, a: i32, b: i32) -> i32 {
        match self {
            Operator::ADD => a + b,
            Operator::SUB => a - b,
            Operator::MUL => a * b,
            Operator::DIV => a / b,
        }
    }
}

const OPERATORS: [Operator; 4] = [Operator::ADD, Operator::SUB, Operator::MUL, Operator::DIV];

fn main() {
    let mut line = String::new();

    io::stdin()
        .read_line(&mut line)
        .expect("No line");

    let mut iters = line.split_whitespace();

    let num_count: usize = iters
        .next()
        .expect("No number")
        .parse()
        .expect("Failed to parse number");

    line.clear();
    io::stdin()
        .read_line(&mut line)
        .expect("No line");

    iters = line.split_whitespace();

    let mut numbers: Vec<i32> = vec![0; num_count];
    for i in 0..num_count {
        numbers[i] = iters
            .next()
            .expect("No number.")
            .parse()
            .expect("Failed to parse number.");
    }

    line.clear();
    io::stdin()
        .read_line(&mut line)
        .expect("No line");
    iters = line.split_whitespace();

    let mut operators_count: [u8; 4] = [1; 4];
    for i in 0..4 {
        let op_count: u8 = iters
            .next()
            .expect("No number")
            .parse()
            .expect("Failed to parse number");
        operators_count[i as usize] = op_count;
    }

    let mut result: [i32; 2] = [-1000000000, 1000000000];
    let mut permut = Vec::<Operator>::new();

    permutation(&mut result, &mut permut, &numbers, num_count - 1, &mut operators_count);

    println!("{}\n{}", result[0], result[1]);
}

fn permutation(
    result: &mut [i32; 2],
    permut: &mut Vec<Operator>, 
    numbers: &Vec<i32>,
    permut_len: usize,
    operators: &mut [u8; 4]) {
    if permut.len() == permut_len {
        let mut a = numbers[0];
        for i in 0..permut_len {
            a = permut[i].operate(a, numbers[i + 1]);
        }
        if a > result[0] {
            result[0] = a;
        }

        if a < result[1] {
            result[1] = a;
        }
        return;
    }

    for i in 0..4 {
        if operators[i] > 0 {
            operators[i] -= 1;
            permut.push(OPERATORS[i]);
            permutation(result, permut, numbers, permut_len, operators);
            permut.pop();
            operators[i] += 1;
        }
    }
}
