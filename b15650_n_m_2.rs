use std::io::{self, Write, BufWriter};

// print!(), println!()은 버퍼링 없이 호출 즉시 출력을 하기 때문에 느리다...
// write!(), writeln!()을 사용...
// 1부터 N까지의 자연수 중에서 중복없이 M개를 고른 수열.
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

    let mut in_use: Vec<bool> = vec![false; n + 1];
    let mut result: Vec<usize> = Vec::<usize>::new();

    let mut writer = BufWriter::new(io::stdout().lock());

    backtrack(1, &mut in_use, &mut result, (n, m), &mut writer);
}

fn backtrack(start: usize, in_use: &mut Vec<bool>, result: &mut Vec<usize>, (n, m): (usize, usize), writer: &mut impl Write) {
    if result.len() == m {
        for i in 0..(m - 1) {
            write!(writer, "{} ", result[i]).unwrap();
        }
        writeln!(writer, "{}", result[m - 1]).unwrap();
        return;
    }

    for i in start..(n + 1) {
        if in_use[i] == false {
            result.push(i);
            in_use[i] = true;
            backtrack(i, in_use, result, (n, m), writer);
            result.pop();
            in_use[i] = false;
        }
    }
}
