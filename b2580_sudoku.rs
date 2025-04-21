use std::io;

// 가로, 세로, 3*3 확인해야 함.
fn main() {
    let mut map: [(bool, Vec<(usize, usize)>); 10] =
        std::array::from_fn(|_| (false, Vec::new()));
    let mut board: [[(u8, bool); 9]; 9] = parse_board(&mut map);

    if !backtrack((0, 0), &mut board, &mut map) {
        println!("Couldn't solve the board");
    }

    for y in 0..board.len() {
        for x in 0..(board[0].len() - 1) {
            print!("{} ", board[y][x].0);
        }
        println!("{}", board[y][8].0);
    }
}

fn backtrack(
    (mut y, mut x): (usize, usize),
    board: &mut [[(u8, bool); 9]; 9], 
    map: &mut [(bool, Vec<(usize, usize)>); 10],
    ) -> bool {
    if x == 9 { // the end of the row
        y += 1; // go to next
        x = 0;
    }
    if y == 9 { // end
        return true;
    }


    if board[y][x].1 { // if immutable
        return backtrack((y, x + 1), board, map);
    }

    for n in 1..(10 as usize) {
        if is_valid(n, (y, x), map) {
            board[y][x].0 = n as u8;
            map[n].0 = true;
            (map[n].1).push((y, x));
            if backtrack((y, x + 1), board, map) {
                return true;
            } else {
                (map[n].1).pop();
                if (map[n].1).len() == 0 {
                    map[n].0 = false;
                }
            }
        }
    }
    return false;
}

fn is_valid(
    val: usize, 
    coord: (usize, usize), 
    map: &[(bool, Vec<(usize, usize)>); 10]
    ) -> bool {

    if map[val].0 {
        for it in (map[val].1).iter() {
            if it.0 == coord.0 || it.1 == coord.1 
                || (it.0 / 3 == coord.0 / 3 && it.1 / 3 == coord.1 / 3) {
                return false;
            }
        }
    }
    return true;
}

fn parse_board(map: &mut [(bool, Vec<(usize, usize)>); 10]) -> [[(u8, bool); 9]; 9] {
    let mut line = String::new();
    let mut board: [[(u8, bool); 9]; 9] = [[(0, false); 9]; 9];

    for y in 0..(9 as usize) {
        line.clear();
        io::stdin()
            .read_line(&mut line)
            .expect("Failed to read line");

        let mut iters = line.split_whitespace();
        for x in 0..(9 as usize) {
            board[y][x].0 = iters
            .next()
            .expect("No number.")
            .parse()
            .expect("Failed to parse a number");
            let n = board[y][x].0;
            if n != 0 {
                board[y][x].1 = true; // immutable
                map[n as usize].0 = true;
                (map[n as usize].1).push((y, x));
            }
        }
    }

    board
}
