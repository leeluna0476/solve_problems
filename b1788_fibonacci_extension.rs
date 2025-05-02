// 피보나치 수열:
// F(0) = 0
// F(1) = 1
// F(n) = F(n - 1) + F(n - 2) (n > 1)
//
// 확장.
// F(n) = F(n - 1) + F(n - 2) (|n| <= 1000000)
//
// n:    1 0 -1 -2 -3 -4 -5 -6 -7 -8  ...
// F(n): 1 0  1 -1  2 -3 -5 -8 13 -21 ... (n <= 0)
//
// F(n) = -(|F(n+2)| + |F(n+1)|) : (n <= -1 and |n|은 짝수)
// F(n) =   |F(n+2)| + |F(n+1)|  : (n <= -1 and |n|은 홀수)
// F(n) =   F(n-1) + F(n-2)      : (n >= 2)

use std::io;

fn main() {
    let mut line = String::new();
    io::stdin()
        .read_line(&mut line)
        .expect("No line");

    let n: i32 = line
        .trim()
        .parse()
        .expect("No number");

    let (sign, result) = extended_fibonacci(n);
    
    println!("{sign}\n{result}");
}

fn extended_fibonacci(n: i32) -> (i8, u64) {
    const MOD: u64 = 1_000_000_000;

    if n == 0 || n == 1 {
        return (n as i8, n as u64);
    } else {
        let mut sign = 1;
        let abs_n = n.abs();
        if n < 0 && abs_n % 2 == 0 {
            sign = -1;
        }
        let mut memo: Vec<u64> = vec![0; (abs_n + 1) as usize];
        memo[1] = 1;

        for i in 2..=(abs_n as usize) {
            memo[i] = (memo[i - 1] + memo[i - 2]) % MOD;
        }

        return (sign, memo[abs_n as usize]);
    }
}
