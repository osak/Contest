fn main() {
    use std::io::stdin;

    let mut line = String::new();
    stdin().read_line(&mut line).unwrap();
    let mut nums: Vec<u32> = line
        .trim()
        .split(" ")
        .map(|x| x.parse::<u32>().unwrap())
        .collect();
    nums.sort();

    println!(
        "{} {} {}",
        nums[3] - nums[0],
        nums[3] - nums[1],
        nums[3] - nums[2]
    );
}
