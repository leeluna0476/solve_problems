use std::io;

struct Fibonacci;

impl Fibonacci {
    fn count_zero_and_one(n: usize) -> (u32, u32) {
        let mut zero: (u32, u32) = (1, 0);
        let mut one: (u32, u32) = (0, 1);

        for _i in 0..n {
            let new_zero = zero.1 + zero.0;
            let new_one = one.1 + one.0;

            zero.0 = zero.1;
            zero.1 = new_zero;

            one.0 = one.1;
            one.1 = new_one;
        }

        (zero.0, one.0)
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
        let n: usize = line.trim()
            .parse()
            .expect("Failed to parse T");
        let (z, o) = Fibonacci::count_zero_and_one(n);
        printbuf.push_str(&format!("{z} {o}\n"));
    }
    print!("{printbuf}");
}

// Z_0 = 1, Z_1 = 0, Z_i = Z_{i-1} + Z_{i-2} (2 <= i <= n)
// O_0 = 0, O_1 = 0, O_i = O_{i-1} + O_{i-2} (2 <= i <= n)
// 시간복잡도:
//  각 단계마다 2번 연산. -> O(1)의 연산을 n+1번 수행.
//  -> O(n)
// 공간복잡도:
//  고정된 튜플의 크기.
//  -> O(1)
