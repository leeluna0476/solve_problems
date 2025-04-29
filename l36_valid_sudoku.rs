impl Solution {
    pub fn is_valid_sudoku(board: Vec<Vec<char>>) -> bool {
        const ROWS: usize = 9;
        const COLS: usize = 9;

        let mut map: [(bool, Vec<(usize, usize)>); 10] =
            std::array::from_fn(|_| (false, Vec::new()));

        for y in 0..ROWS {
            for x in 0..COLS {
                let mut elem = board[y][x] as u8;
                if elem != b'.' {
                    elem -= b'0';
                    let eidx = elem as usize;
                    if map[eidx].0 {
                        for (yy, xx) in (map[eidx].1).iter() {
                            if *yy == y || *xx == x || (*yy / 3 == y / 3 && *xx / 3 == x / 3) {
                                return false;
                            }
                        }
                    } else {
                        map[eidx].0 = true;
                    }
                    (map[eidx].1).push((y, x));
                }
            }
        }
        return true;
    }
}
