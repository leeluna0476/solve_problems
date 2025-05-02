// 입력을 알파벳 소문자로만 이루어져 있음.
// 모든 문자가 연속적으로 등장하면 그룹 단어. (aabbc -> group word. abac -> not group word.)
// 주어진 n개의 단어 중 그룹 단어가 몇 개인지 출력하라.
// 문자열의 길이 N. 시간복잡도 O(N).

use std::io;

fn main() {
    let mut line = String::new();
    let stdin = io::stdin();
    stdin
        .read_line(&mut line)
        .expect("No line");

    let n: u8 = line
        .trim()
        .parse()
        .expect("No number");

    let mut count = 0;
    for _i in 0..n {
        line.clear();
        stdin
            .read_line(&mut line)
            .expect("No line");

        let trimmed = line.trim();
        if is_group_word(&trimmed) {
            count += 1;
        }
    }

    println!("{count}");
}

fn is_group_word(s: &str) -> bool {
    let mut alphamap = [false; 26];
    let bytes = s.as_bytes();
    for i in 0..bytes.len() {
        let b = bytes[i];
        if alphamap[(b - b'a') as usize] && b != bytes[i - 1] {
            return false;
        }
        alphamap[(b - b'a') as usize] = true;
    }
    return true;
}
