// 문자열의 길이 N.
// 시간복잡도 O(N).
use std::io;

fn main() {
    let mut line = String::new();
    let stdin = io::stdin();
    stdin
        .read_line(&mut line)
        .expect("No line");

    let n: usize = line
        .trim()
        .parse()
        .expect("No number");

    let mut printbuf = String::new();
    for _i in 0..n {
        line.clear();
        stdin
            .read_line(&mut line)
            .expect("No line");
        let trimmed_line = line.trim();

        let mut flag: i8 = 0;
        for c in trimmed_line.chars() {
            if c == '(' {
                flag += 1;
            } else {
                flag -= 1;
            }

            if flag < 0 {
                break;
            }
        }

        if flag == 0 {
            printbuf.push_str(format!("YES\n").as_str());
        } else {
            printbuf.push_str(format!("NO\n").as_str());
        }
    }

    print!("{printbuf}");
}
