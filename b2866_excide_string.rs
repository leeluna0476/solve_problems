use std::io::{self, BufRead};
use std::collections::HashSet;

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let first_line = lines.next().unwrap().unwrap();
    let mut parts = first_line.split_whitespace();
    let r: usize = parts.next().unwrap().parse().unwrap();
    let c: usize = parts.next().unwrap().parse().unwrap();

    let mut a: Vec<String> = vec![String::new(); c];

    for _ in 0..r {
        let line = lines.next().unwrap().unwrap();
        let chars: Vec<char> = line.chars().collect();

        for j in 0..c {
            a[j].push(chars[j]);
        }
    }

    let mut set = HashSet::new();
    let mut top = 0;
    'outer: for t in 1..r {
        for i in 0..c {
            let s: &str = &a[i];
            let substr: &str = &s[t..];
            if set.contains(substr) {
                break 'outer;
            }
            set.insert(substr);
        }
        top += 1;
    };

    println!("{top}");
}
