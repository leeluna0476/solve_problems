use std::io;

struct Fibonacci;

impl Fibonacci {
    fn count_zero_and_one(n: u8) -> (u32, u32) {
        let mut memo: Vec<(u32, u32, u32)> = vec![(0, 0, 0); (n + 1) as usize];
        Self::_inner_count_zero_and_one(n, &mut memo);
        (memo[n as usize].1, memo[n as usize].2)
    }

    fn _inner_count_zero_and_one(n: u8, memo: &mut Vec<(u32, u32, u32)>) -> u32 {
        if n == 0 {
            memo[0].1 = 1;
        } else if n == 1 {
            memo[1].0 = 1;
            memo[1].2 = 1;
        } else {
            if memo[n as usize].0 == 0 {
                memo[n as usize].0 = Self::_inner_count_zero_and_one(n - 1, memo) + Self::_inner_count_zero_and_one(n - 2, memo);
                memo[n as usize].1 = memo[(n - 1) as usize].1 + memo[(n - 2) as usize].1;
                memo[n as usize].2 = memo[(n - 1) as usize].2 + memo[(n - 2) as usize].2;
            }
        }
        memo[n as usize].0
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
        let n: u8 = line.trim()
            .parse()
            .expect("Failed to parse T");
        let (z, o) = Fibonacci::count_zero_and_one(n);
        printbuf.push_str(&format!("{z} {o}\n"));
    }
    print!("{printbuf}");
}

// 0 1 1 2 3 5 8 13 21 34 55 89 ...
// 각 단계 아래에 있는 1, 0이 몇 개인지 기록.
// 시간복잡도:
//  _inner_fibonacci는 각 n에 대해 최대 한번 호출됨. if문도 최대 한번 평가됨. -> O(1)의 연산을 n번 수행.
//  -> O(n)
