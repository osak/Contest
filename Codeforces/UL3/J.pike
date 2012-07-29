int cmp(mapping(string:mixed) a, mapping(string:mixed) b) {
    return a["start"] < b["start"];
}

int main() {
    int N = (int)Stdio.stdin->gets();
    array(mixed) intervals = allocate(N);
    for(int i = 0; i < N; ++i) {
        string line = Stdio.stdin->gets();
        mapping(string:mixed) obj = ([]);
        int last = sizeof(line)-2;
        int s_c = line[0] == '[';
        int e_c = line[-1] == ']';
        array(int) pos = (array(int))(line[1 .. last] / ",");

        obj += ([ "s_c": s_c, "e_c":e_c, "start":pos[0], "end":pos[1] ]);
        intervals[i] = obj;
    }

    Array.sort_array(intervals, cmp);

    int twocol = 0;
    for(int i = 0; i < N; ++i) {
        for(int j = i+1; j < N; ++j) {
            for(int k = j+1; k < N; ++k) {
                if((intervals[i]["end"] > intervals[j]["start"] ||
                    (intervals[i]["end"] == intervals[j]["start"] && intervals[i]["s_c"] && intervals[j]["e_c"])) &&
                   (intervals[j]["end"] > intervals[k]["start"] ||
                    (intervals[j]["end"] == intervals[k]["start"] && intervals[j]["s_c"] && intervals[k]["e_c"]))) {
                    twocol = 1;
                }
            }
        }
    }

    write((twocol ? 2 : 1) + "\n");
    return 0;
}
