use std::io::{self, Write, BufWriter};

fn main() {
    let mut line = String::new();

    io::stdin()
        .read_line(&mut line)
        .expect("Failed to read line.");

    let mut iters = line.split_whitespace();

    let n: usize = iters
        .next()
        .expect("No number.")
        .parse()
        .expect("Failed to parse N.");

    let m: usize = iters
        .next()
        .expect("No number.")
        .parse()
        .expect("Failed to parse M");

    line.clear();
    io::stdin()
        .read_line(&mut line)
        .expect("Failed to read line.");

    iters = line.split_whitespace();

    let mut numbers: Vec<usize> = vec![0; n];

    for i in 0..n {
        numbers[i] = iters
            .next()
            .expect("No number.")
            .parse()
            .expect("Failed to parse number.");
    }

    numbers.sort();

    let mut result: Vec<usize> = Vec::<usize>::new();

    let mut writer = BufWriter::new(io::stdout().lock());

    backtrack(0, &numbers, &mut result, (n, m), &mut writer);
}

fn backtrack(
    start: usize,
    numbers: &Vec<usize>,
    result: &mut Vec<usize>, 
    (n, m): (usize, usize), 
    writer: &mut impl Write) {
    if result.len() == m {
        for i in 0..(m - 1) {
            write!(writer, "{} ", result[i]).unwrap();
        }
        writeln!(writer, "{}", result[m - 1]).unwrap();
        return;
    }

    for i in start..n {
        let num = numbers[i];
        result.push(num);
        backtrack(i, numbers, result, (n, m), writer);
        result.pop();
    }
}
