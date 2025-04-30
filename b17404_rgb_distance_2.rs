//RGB거리에는 집이 N개 있다. 거리는 선분으로 나타낼 수 있고, 1번 집부터 N번 집이 순서대로 있다.

//집은 빨강, 초록, 파랑 중 하나의 색으로 칠해야 한다. 각각의 집을 빨강, 초록, 파랑으로 칠하는 비용이 주어졌을 때, 아래 규칙을 만족하면서 모든 집을 칠하는 비용의 최솟값을 구해보자.
//
//1번 집의 색은 2번, N번 집의 색과 같지 않아야 한다.
//N번 집의 색은 N-1번, 1번 집의 색과 같지 않아야 한다.
//i(2 ≤ i ≤ N-1)번 집의 색은 i-1번, i+1번 집의 색과 같지 않아야 한다.
use std::io;

#[derive(Debug)]
#[derive(Copy)]
#[derive(Clone)]
#[derive(PartialEq)]
enum Colors {
    R = 0,
    G = 1,
    B = 2,
}

const RGB: [Colors; 3] = [Colors::R, Colors::G, Colors::B];

fn main() {
    let (n, cost_rgb) = parse_data();

    let mut memo: Vec<Vec<(Option<u16>, Option<Colors>)>> = vec![vec![(None, None); 3]; n];

    let min = set_color_price(0, n, None, None, &cost_rgb, &mut memo);
    println!("{min}");
}

// [dynamic programming]
// 재귀 호출의 시점: RGB에서 가져와 비교하는 색상이 이전 i의 색상과 다를 때.
// 최소 가격을 구하려면?: n = 3
//  i = 2일 때: 이전 i의 색상과 다른 두 색상 중 가격이 작은 것.
//  i = 1일 때: 이전 i의 색상과 다른 두 색상 중 가격이 작은 것 + i = 2에서 반환한 값.
//  ...
// memo[i][prev] -> prev 색상으로 시작하고 first가 같은 조합 중 가장 작은 가격을 저장.
// RB* != GB* -> memo 활용 불가.
fn set_color_price(
    i: usize,
    n: usize,
    prev: Option<Colors>,
    mut first: Option<Colors>,
    cost_rgb: &Vec<Vec<u16>>,
    memo: &mut Vec<Vec<(Option<u16>, Option<Colors>)>>) -> u16 {

    if i == n {
        return 0;
    }

    if let Some(p) = prev { // prev가 존재하고 (i > 0)
        if let Some(min_cost) = memo[i][p as usize].0 { // memo한 것이 존재한다면
            if first == memo[i][p as usize].1 { // (초반부에 prev와 first가 같은 조합이 있었다면)
                return min_cost; // 재귀의 깊이를 더하지 않고 반환.
            }
        }
    }

    let mut min_cost = u16::MAX;
    for color in RGB {
        let some_color = Some(color);
        if i == 0 {
            first = some_color;
        }

        if some_color != prev && (i != n - 1 || some_color != first) {
            let cost = cost_rgb[i][color as usize] + 
                set_color_price(i + 1, n, some_color, first, cost_rgb, memo);
            min_cost = min_cost.min(cost);
        }
    }

    if let Some(p) = prev {
        memo[i][p as usize].0 = Some(min_cost); // i-1==p일 때, i번째 단계의 최솟값은 min이다.
                               // (p 외의 다른 두 경우 for문으로 살펴봄.
        memo[i][p as usize].1 = first;
    }

    min_cost
}

fn parse_data() -> (usize, Vec<Vec<u16>>) {
    let stdin = io::stdin();
    let mut line = String::new();

    stdin
        .read_line(&mut line)
        .expect("No line");

    let n: usize = line
        .trim()
        .parse()
        .expect("Failed to parse a number");

    let mut cost_rgb: Vec<Vec<u16>> = vec![vec![0; 3]; n];
    for i in 0..n {
        line.clear();
        stdin
            .read_line(&mut line)
            .expect("No line");

        let mut iters = line.split_whitespace();

        for j in 0..(3 as usize) {
            cost_rgb[i][j] = iters
                .next()
                .expect("No number")
                .parse()
                .expect("Failed to parse a number");
        }
    }

    (n, cost_rgb)
}
