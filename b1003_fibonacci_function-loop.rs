use std::io;

struct Fibonacci;

impl Fibonacci {
    fn count_zero_and_one(n: usize) -> (u32, u32) {
        if n == 0 {
            return (1, 0);
        }

        let mut memo: Vec<(u32, u32)> = vec![(0, 0); n + 1];
        memo[0].0 = 1;
        memo[1].1 = 1;

        for i in 2..=n {
            memo[i].0 = memo[i - 1].0 + memo[i - 2].0;
            memo[i].1 = memo[i - 1].1 + memo[i - 2].1;
        }

        memo[n]
    }
}

fn main() {
    let mut line = String::new();
    let stdin = io::stdin();
    stdin
        .read_line(&mut line)
        .expect("No line");

    let t: u8 = line.trim().parse().expect("Failed to parse T");

    let mut printbuf = String::new();
    for _i in 0..t {
        line.clear();
        stdin
            .read_line(&mut line)
            .expect("No line");
        let n: usize = line.trim().parse().expect("Failed to parse T");
        let (z, o) = Fibonacci::count_zero_and_one(n);
        printbuf.push_str(&format!("{z} {o}\n"));
    }
    print!("{printbuf}");
}

// Z_0 = 1, Z_1 = 0, Z_i = Z_{i-1} + Z_{i-2} (2 <= i <= n)
// O_0 = 0, O_1 = 0, O_i = O_{i-1} + O_{i-2} (2 <= i <= n)
// 시간복잡도:
//  0과 1이 출력되는 횟수 각각 n + 1번 계산.
//  -> O(n)
