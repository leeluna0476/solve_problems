use std::io;

fn main() {
    let mut line = String::new();

    io::stdin()
        .read_line(&mut line)
        .expect("No line");

    let mut iters = line.split_whitespace();

    let n: i32 = iters
        .next()
        .expect("No number")
        .parse()
        .expect("Failed to parse a number");

    let m: i32 = iters
        .next()
        .expect("No number")
        .parse()
        .expect("Failed to parse a number");

    let mut table: Vec<Vec<char>> = vec![vec!['0'; m as usize]; n as usize];

    for y in 0..n {
        line.clear();
        io::stdin()
            .read_line(&mut line)
            .expect("No line");

        let bytes = line.as_bytes();
        for x in 0..m {
            table[y as usize][x as usize] = bytes[x as usize] as char;
        }
    }

    let mut max_sqr = -1;
    let neg_n = 0 - n;
    let neg_m = 0 - m;
    for y in 0..n {
        for x in 0..m {
            for dy in neg_n..n {
                for dx in neg_m..m {
                    if dy == 0 && dx == 0 { continue; }
                    let mut i = y;
                    let mut j = x;
                    let mut s = String::new();
                    while i >= 0 && i < n && j >= 0 && j < m {
                        s.push(table[i as usize][j as usize]);
                        let num = s.parse().expect("Failed to parse a number");
                        if is_perfect_square(num) && num > max_sqr {
                            max_sqr = num;
                        }
                        i += dy;
                        j += dx;
                    }
                }
            }
        }
    }

    println!("{max_sqr}");
}

fn is_perfect_square(n: i32) -> bool {
    let root = (n as f64).sqrt();
    root == root.trunc()
}
