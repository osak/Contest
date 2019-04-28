use std::collections::HashMap;
use std::io::stdin;

#[derive(Copy, Clone)]
struct Student {
    skill: u32,
    team: u32,
    left: Option<usize>,
    right: Option<usize>,
}

fn read_ints() -> Vec<u32> {
    let mut line = String::new();
    stdin().read_line(&mut line).unwrap();
    return line.trim().split(" ").map(|x| x.parse().unwrap()).collect();
}

fn read_params() -> (i32, u32) {
    let ints = read_ints();
    return (ints[0] as i32, ints[1]);
}

fn main() {
    let (n, k) = read_params();
    let skills = read_ints();

    let bound = |i: i32| -> Option<usize> {
        if 0 <= i && i < n {
            Some(i as usize)
        } else {
            None
        }
    };

    let mut students: Vec<Student> = Vec::new();
    let mut student_by_skill = HashMap::new();
    for i in 0..n {
        let left = bound(i - 1);
        let right = bound(i + 1);

        let student = Student {
            skill: skills[i as usize],
            team: 0,
            left: left,
            right: right,
        };
        students.push(student);
        student_by_skill.insert(student.skill as usize, i as usize);
    }

    let mut turn = 1;
    for skill in (1..=n as usize).rev() {
        let idx = student_by_skill[&skill];
        {
            let st = students.get_mut(idx).unwrap();
            if st.team != 0 {
                continue;
            }
            st.team = turn;
        }

        let mut leftmost = None;
        {
            let mut cur = students.get(idx).unwrap().clone();
            for _i in 0..k {
                match cur.left {
                    Some(nidx) => {
                        let next = students.get_mut(nidx).unwrap();
                        next.team = turn;
                        cur = next.clone();
                    }
                    _ => break,
                }
            }
            leftmost = cur.left;
        }
        let mut rightmost = None;
        {
            let mut cur = students.get_mut(idx).unwrap().clone();
            for _i in 0..k {
                match cur.right {
                    Some(nidx) => {
                        let next = students.get_mut(nidx).unwrap();
                        next.team = turn;
                        cur = next.clone();
                    }
                    _ => break,
                }
            }
            rightmost = cur.right;
        }
        leftmost.map(|li| students.get_mut(li).unwrap().right = rightmost);
        rightmost.map(|ri| students.get_mut(ri).unwrap().left = leftmost);
        turn = if turn == 1 { 2 } else { 1 }
    }

    let ans = students
        .iter()
        .map(|s| s.team.to_string())
        .collect::<Vec<String>>()
        .join("");
    println!("{}", ans);
}
