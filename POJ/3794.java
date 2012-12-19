// Name: Extended Normal Order Sort
// Level: 3
// Category: 文字列,多倍長
// Note:

/*
 * パースは4状態くらいのオートマトンでできる．
 * 数値がintには収まらないので工夫が必要．
 */
import java.io.*;
import java.util.*;
import java.math.BigInteger;

enum CharType {
    DIGIT, ASCII
}

class Char implements Comparable<Char> {
    public CharType type;
    public char ch;
    public BigInteger bi;

    public Char(char ch) {
        type = CharType.ASCII;
        this.ch = Character.toUpperCase(ch);
    }
    public Char(BigInteger bi) {
        type = CharType.DIGIT;
        this.bi = bi;
    }

    public int compareTo(Char c) {
        if(type != c.type) return type.compareTo(c.type);
        if(type == CharType.ASCII) return new Character(ch).compareTo(c.ch);
        else if(type == CharType.DIGIT) return bi.compareTo(c.bi);
        return 0;
    }

    public String toString() {
        if(type == CharType.ASCII) return ch + "";
        return bi.toString();
    }
}

public class Main {
    static ArrayList<Char> parse(String str) {
        ArrayList<Char> res = new ArrayList<Char>();
        boolean in_digit = false;
        BigInteger acc = new BigInteger("0");
        int sign = 1;
        for(int i = 0; i < str.length(); ++i) {
            char ch = str.charAt(i);
            if(in_digit) {
                if(Character.isDigit(ch)) {
                    acc = acc.multiply(new BigInteger("10"));
                    acc = acc.add(new BigInteger("" + ch));
                    in_digit = true;
                } else {
                    if(sign == -1) acc = acc.negate();
                    res.add(new Char(acc));
                    res.add(new Char(ch));
                    sign = 1;
                    in_digit = false;
                }
            } else {
                if(Character.isDigit(ch)) {
                    acc = new BigInteger("" + ch);
                    sign = 1;
                    in_digit = true;
                } else if(ch == '+' || ch == '-') {
                    if(i+1 != str.length() && Character.isDigit(str.charAt(i+1))) {
                        sign = (ch == '-') ? -1 : 1;
                        acc = new BigInteger("0");
                        in_digit = true;
                    } else {
                        res.add(new Char(ch));
                        in_digit = false;
                    }
                } else {
                    res.add(new Char(ch));
                    in_digit = false;
                }
            }
        }
        if(in_digit) {
            if(sign == -1) acc = acc.negate();
            res.add(new Char(acc));
        }

        return res;
    }

    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        int N = s.nextInt();
        for(int Q = 1; Q <= N; ++Q) {
            String s1 = s.next();
            String s2 = s.next();
            ArrayList<Char> v1 = parse(s1), v2 = parse(s2);
            int res = 0;
            for(int i = 0; i < v1.size() && i < v2.size(); ++i) {
                //System.out.println(v1.get(i) + " " + v2.get(i));
                res = v1.get(i).compareTo(v2.get(i));
                if(res != 0) break;
            }
            if(res == 0) res = new Integer(v1.size()).compareTo(v2.size());
            if(res < 0) res = -1;
            if(res > 0) res = 1;
            System.out.println(Q + " " + res);
        }
    }
}
