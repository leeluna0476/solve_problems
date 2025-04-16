use std::io;
use std::collections::VecDeque;

fn main() {
    let (n, m, mut grid): (i32, i32, Vec<Vec<i32>>) = parse_data_to_grid();

    let mut queue: VecDeque<(i32, i32, i32)> = VecDeque::<(i32, i32, i32)>::new();

    for y in 0..n {
        for x in 0..m {
            if grid[y as usize][x as usize] == 1 {
                queue.push_back((y, x, 0));
            }
        }
    }

    let days = spread_one(&mut queue, &mut grid, (n, m));

    println!("{days}");
}

fn spread_one(queue: &mut VecDeque<(i32, i32, i32)>, grid: &mut Vec<Vec<i32>>, (n, m): (i32, i32)) -> i32 {
    let mut max_days: i32 = 0;
    const DELTAS: [(i32, i32); 4] = [(-1, 0), (1, 0), (0, -1), (0, 1)];

    while !queue.is_empty() {
        let (y, x, day) = queue.pop_front().unwrap();
        max_days = if max_days < day { day } else { max_days };

        for (dy, dx) in DELTAS {
            let (y, x) = (y + dy, x + dx);
            if y >= 0 && y < n && x >= 0 && x < m {
                if grid[y as usize][x as usize] == 0 {
                    grid[y as usize][x as usize] = 1;
                    queue.push_back((y, x, day + 1));
                }
            }
        }
    }

    'out: for y in 0..n {
        for x in 0..m {
            if grid[y as usize][x as usize] == 0 {
                max_days = -1;
                break 'out;
            }
        }
    }

    max_days
}

fn parse_data_to_grid() -> (i32, i32, Vec<Vec<i32>>) {
    let mut line = String::new();
    io::stdin()
        .read_line(&mut line)
        .expect("Failed to read line.");

    let mut iters = line.split_whitespace();

    let m: i32 = iters
        .next()
        .expect("No number.")
        .parse()
        .expect("Failed to parse the first number.");

    let n: i32 = iters
        .next()
        .expect("No number.")
        .parse()
        .expect("Failed to parse the second number.");

    let mut grid: Vec<Vec<i32>> = vec![vec![0; m as usize]; n as usize];

    for y in 0..n {
        line.clear();
        io::stdin()
            .read_line(&mut line)
            .expect("Failed to read line");

        iters = line.split_whitespace();
        for x in 0..m {
            grid[y as usize][x as usize] = iters
            .next()
            .expect("No number.")
            .parse()
            .expect("Failed to parse a number");
        }
    }

    (n, m, grid)
}
