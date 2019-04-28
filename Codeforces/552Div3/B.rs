use std::collections::HashMap;
use std::io::stdin;

fn read_int() -> i32 {
    let mut line = String::new();
    stdin().read_line(&mut line).unwrap();
    return line.trim().parse().unwrap();
}

fn read_ints() -> Vec<i32> {
    let mut line = String::new();
    stdin().read_line(&mut line).unwrap();
    return line
        .trim()
        .split(" ")
        .map(|x| x.parse::<i32>().unwrap())
        .collect();
}

fn uniq_nums(v: Vec<i32>) -> Vec<i32> {
    let mut dict = HashMap::new();
    for num in v {
        dict.insert(num, true);
    }

    let mut uniqs = Vec::<i32>::new();
    for key in dict.keys() {
        uniqs.push(*key);
    }
    uniqs.sort();
    return uniqs;
}

fn case_2(v: Vec<i32>) {
    assert_eq!(v.len(), 2);

    let mid = (v[0] + v[1]) / 2;
    if mid - v[0] == v[1] - mid {
        println!("{}", mid - v[0]);
    } else {
        println!("{}", v[1] - v[0]);
    }
}

fn case_3(v: Vec<i32>) {
    assert_eq!(v.len(), 3);
    if v[2] - v[1] == v[1] - v[0] {
        println!("{}", v[2] - v[1]);
    } else {
        println!("-1")
    }
}

fn main() {
    let n = read_int();
    let nums = read_ints();
    let mut uniqs = uniq_nums(nums);

    match uniqs.len() {
        1 => println!("0"),
        2 => case_2(uniqs),
        3 => case_3(uniqs),
        _ => println!("-1"),
    }
}
