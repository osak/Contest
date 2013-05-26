// I

import java.math.*;
import java.util.*;

public class Main {
    Scanner scanner;
    ArrayList<BigInteger> roots;
    HashSet<Integer> memo;

    BigInteger val(int x) {
        BigInteger res = new BigInteger("1");
        BigInteger bx = BigInteger.valueOf(x);
        for(BigInteger r : roots) {
            res = res.multiply(bx.subtract(r));
        }
        return res;
    }

    int valsgn(int x) {
        BigInteger res = val(x);
        return res.signum();
    }

    boolean inRange(int a, int x, int b) {
        return a <= x && x <= b;
    }

    int calc(int a, int b, int step) {
        int tag = a*10001+b;
        if(memo.contains(tag)) return 0;
        memo.add(tag);

        if(step == 7) return 1;
        int res = 1;

        int sgna = valsgn(a);
        int prev_a = 2*a - b;
        if(inRange(0, prev_a, 10000) && prev_a < b && prev_a < a) {
            if(valsgn(prev_a)*sgna > 0) res += calc(prev_a, b, step+1);
        }
        int prev_b = 2*b - a;
        if(inRange(0, prev_b, 10000) && prev_b > a && prev_b > b) {
            if(valsgn(prev_b)*sgna < 0) res += calc(a, prev_b, step+1);
        }
        return res;
    }

    void solve() {
        String expr = scanner.nextLine();
        int R = scanner.nextInt();
        scanner.nextLine();

        roots = new ArrayList<BigInteger>();
        int pos = 0;
        while(pos < expr.length()) {
            int next = pos;
            while(next < expr.length() && Character.isDigit(expr.charAt(next))) {
                ++next;
            }
            if(next != pos) {
                String root = expr.substring(pos, next);
                roots.add(new BigInteger(root));
                pos = next;
            } else {
                ++pos;
            }
        }
        roots.remove(roots.size()-1);

        memo = new HashSet<Integer>();
        int ans = 0;
        for(int a = 0; a <= 10000; ++a) {
            int b = 2*R - a;
            if(a < b && b <= 10000) {
                int sgn = valsgn(a) * valsgn(b);
                if(sgn < 0) {
                    ans += calc(a, b, 1);
                }
            }
        }
        System.out.println(ans);
    }

    void run() {
        scanner = new Scanner(System.in);
        int N = scanner.nextInt();
        scanner.nextLine();
        for(int _ = 0; _ < N; ++_) {
            solve();
        }
    }

    public static void main(String[] args) {
        new Main().run();
    }
}
