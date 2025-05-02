use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let n: usize = lines
        .next()
        .unwrap()
        .unwrap()
        .trim()
        .parse()
        .expect("Invalid number");

    let mut sequence = Vec::<u32>::with_capacity(n);

    for _i in 0..n {
        let num: u32 = lines
            .next()
            .unwrap()
            .unwrap()
            .trim()
            .parse()
            .expect("Invalid number");

        sequence.push(num);
    }

    let mut printbuf = String::new();

    // 시간복잡도:
    // n번 push (printbuf push too)
    // n번 pop (printbuf push too)
    // O(n)
    let mut stack = Vec::<u32>::new();
    let mut the_last = 0;
    for num in sequence {
        for i in (the_last + 1)..=num {
            stack.push(i);
            printbuf.push_str("+\n");
        }
        the_last = u32::max(num, the_last);

        let popped = stack.pop().unwrap();
        if popped > num {
            println!("NO");
            return;
        }
        printbuf.push_str("-\n");
    }

    print!("{printbuf}");
}
