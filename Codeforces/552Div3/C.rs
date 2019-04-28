use std::cmp::{max, min};
use std::io::stdin;

fn read_ints() -> Vec<u32> {
    let mut line = String::new();
    stdin().read_line(&mut line).unwrap();
    return line.trim().split(" ").map(|x| x.parse().unwrap()).collect();
}

fn main() {
    let mut rations = read_ints();
    let full_weeks = min(rations[0] / 3, min(rations[1] / 2, rations[2] / 2));
    rations[0] -= 3 * full_weeks;
    rations[1] -= 2 * full_weeks;
    rations[2] -= 2 * full_weeks;

    let mut max_more_days = 0;
    for start in 0..7 {
        let mut remain = rations.to_vec();
        for day in 0..7 {
            let idx = match (start + day) % 7 {
                0 | 3 | 6 => 0,
                1 | 5 => 1,
                _ => 2,
            };
            if remain[idx] == 0 {
                max_more_days = max(max_more_days, day);
                break;
            }
            remain[idx] -= 1;
        }
    }

    println!("{}", full_weeks * 7 + max_more_days);
}
