struct Solution;

// 지그재그 인덱스 배치. 각 인덱스의 누적합 배열을 만들어서 각 문자 자리찾기.
    // O(n)
impl Solution {
    pub fn convert(s: String, num_rows: i32) -> String {
        let slen = s.len();
        let mut sidx_map: Vec<i32> = vec![0; slen];
        let mut cumulatives: Vec<i32> = vec![0; num_rows as usize];

        if num_rows == 1 {
            cumulatives[0] = slen as i32;
        } else {
            let mut si: i32 = 0;
            let mut sign: i32 = 1;
            for i in 0..slen {
                sidx_map[i] = si;
                cumulatives[si as usize] += 1;
                if si + 1 == num_rows {
                    sign = -1;
                } else if si == 0 {
                    sign = 1;
                }
                si += sign;
            }
        }

        let mut sum: i32 = 0;
        for i in 0..(num_rows as usize) {
            sum += cumulatives[i];
            cumulatives[i] = sum;
        }

        let s_bytes = s.as_bytes();
        let mut rs = s.clone();
        let rs_bytes = unsafe { rs.as_bytes_mut() };
        for i in (0..slen).rev() {
            cumulatives[ sidx_map[i] as usize ] -= 1;
            let idx = cumulatives[ sidx_map[i] as usize ];
            rs_bytes[idx as usize] = s_bytes[i];
        }

        rs
    }
}

fn main() {
//    let s = String::from("PAYPALISHIRING");
    let s = String::from("AB");
    println!("{}", Solution::convert(s, 1));
}
