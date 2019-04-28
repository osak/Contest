use std::io::stdin;

struct Params {
    n: u32,
    b: u32,
    a: u32,
}

fn read_ints() -> Vec<u32> {
    let mut line = String::new();
    stdin().read_line(&mut line).unwrap();
    return line.trim().split(" ").map(|x| x.parse().unwrap()).collect();
}

fn read_params() -> Params {
    let ints = read_ints();
    return Params {
        n: ints[0],
        b: ints[1],
        a: ints[2],
    };
}

fn main() {
    let params = read_params();
    let segments = read_ints();
    let mut ans = 0;
    let mut acc = params.a;
    let mut bat = params.b;

    for seg in segments {
        if acc == 0 && bat == 0 {
            break;
        }
        match seg {
            0 => {
                if acc > 0 {
                    acc -= 1;
                } else if bat > 0 {
                    bat -= 1;
                }
            }
            1 => {
                if acc < params.a && bat > 0 {
                    bat -= 1;
                    acc += 1;
                } else if acc > 0 {
                    acc -= 1;
                } else if bat > 0 {
                    bat -= 1;
                }
            }
            _ => panic!("Invalid segment value {}", seg),
        }
        ans += 1;
    }
    println!("{}", ans);
}
