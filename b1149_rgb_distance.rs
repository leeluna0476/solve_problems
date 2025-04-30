use std::io;

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

    let mut memo: Vec<Vec<Option<u16>>> = vec![vec![None; 3]; n];

    let min = set_color_price(0, n, None, &cost_rgb, &mut memo);
    println!("{min}");
}

// [dynamic programming]
// 재귀 호출의 시점: RGB에서 가져와 비교하는 색상이 이전 i의 색상과 다를 때.
// 최소 가격을 구하려면?: n = 3
//  i = 2일 때: 이전 i의 색상과 다른 두 색상 중 가격이 작은 것.
//  i = 1일 때: 이전 i의 색상과 다른 두 색상 중 가격이 작은 것 + i = 2에서 반환한 값.
//  ...
// memo[i][prev] -> prev 색상으로 시작하는 조합 중 가장 작은 가격을 저장.
// RGR, BGR 등 *G*로 같은 꼴일 때... RGR에서 memo[2][G]에 저장한 값 BGR에서 재활용 가능.
// -> cost[0][B] + memo[2][G] -> 새로운 min 후보.
fn set_color_price(
    i: usize,
    n: usize,
    prev: Option<Colors>,
    cost_rgb: &Vec<Vec<u16>>,
    memo: &mut Vec<Vec<Option<u16>>>) -> u16 {

    if i == n {
        return 0;
    }

    if let Some(p) = prev { // prev가 존재하고 (i > 0)
        if let Some(min_cost) = memo[i][p as usize] { // memo한 것이 존재한다면
                                                  // (초반부에 prev가 같은 조합이 있었다면)
            return min_cost; // 재귀의 깊이를 더하지 않고 반환.
        }
    }

    let mut min_cost = u16::MAX;
    for color in RGB {
        if prev.is_none() || Some(color) != prev {
            let cost = cost_rgb[i][color as usize] + 
                set_color_price(i + 1, n, Some(color), cost_rgb, memo);
            min_cost = min_cost.min(cost);
        }
    }

    if let Some(p) = prev {
        memo[i][p as usize] = Some(min_cost); // i-1==p일 때, i번째 단계의 최솟값은 min이다.
                               // (p 외의 다른 두 경우 for문으로 살펴봄.
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


// [brute-force]
// 가능한 모든 RGB 조합을 탐색 후 가격 비교.
//fn set_color_price(colors: &mut [Colors; 3], i: usize, rgbs: &[[u16; 3]]) -> u16 {
//    if i == 3 {
//        let mut price = 0;
//        for i in 0..(3 as usize) {
//            price += rgbs[i][colors[i] as usize];
//        }
//        return price;
//    }
//
//    let mut min = 1000;
//    for j in 0..3 {
//        if i == 0 || RGB[j] != colors[i - 1] {
//            colors[i] = RGB[j];
//            let price_returned = set_color_price(colors, i + 1, rgbs);
//            if price_returned < min {
//                min = price_returned;
//            }
//        }
//    }
//    min
//}
