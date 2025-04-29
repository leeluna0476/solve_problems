use std::io::{self, Write, BufWriter};
use std::collections::HashSet;

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

    let mut in_use: Vec<bool> = vec![false; 10001];
    let mut permuts = HashSet::<Vec<usize>>::new();
    let mut result: Vec<usize> = Vec::<usize>::new();

    let mut writer = BufWriter::new(io::stdout().lock());

    backtrack(&numbers, &mut in_use, &mut result, &mut permuts, (n, m), &mut writer);
}

fn backtrack(
    numbers: &Vec<usize>,
    in_use: &mut Vec<bool>,
    result: &mut Vec<usize>,
    permuts: &mut HashSet<Vec<usize>>,
    (n, m): (usize, usize),
    writer: &mut impl Write) {
    if result.len() == m {
        let mut presult: Vec<usize> = vec![];
        let mut n;
        for i in 0..(m - 1) {
            n = numbers[result[i]];
            presult.push(n);
        }
        n = numbers[result[m - 1]];
        presult.push(n);
        if permuts.contains(&presult) == false {
            for i in 0..(m - 1) {
                write!(writer, "{} ", presult[i]).unwrap();
            }
            writeln!(writer, "{}", presult[m - 1]).unwrap();
            permuts.insert(presult);
            return;
        }
    }

    for i in 0..n {
        if in_use[i] == false {
            result.push(i);
            in_use[i] = true;
            backtrack(numbers, in_use, result, permuts, (n, m), writer);
            result.pop();
            in_use[i] = false;
        }
    }
}
