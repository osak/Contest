#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <queue>

using std::vector;
using std::priority_queue;
using std::pair;
using std::make_pair;
using std::swap;

struct Point {
    int r, c;

    Point() : r(0), c(0) {}
    Point(int r_, int c_) : r(r_), c(c_) {}
    Point(const Point &p) : r(p.r), c(p.c) {}

    bool operator ==(const Point &p) const {
        return r == p.r && c == p.c;
    }

    bool operator <(const Point &p) const {
        if (r != p.r) {
            return r < p.r;
        } else {
            return c < p.c;
        }
    }
};

struct Range {
    int min, max;

    int estimation() const {
        return (min + max) / 2;
    }

    int diff() const {
        return max - min;
    }
};

struct Bucket {
    Point top_left;
    int size;
};

int estimated_cost[200][200];
Range cost_range[200][200];
int grid[200][200];
Point prev[200][200];
vector<Point> wells, houses;
bool finished[200][200];
int C;
double default_factor;

const int DR[4] = {0, 1, 0, -1};
const int DC[4] = {1, 0, -1, 0};
const int MAX = 5000 * 20000;

// Post-condition:
//   -  `grid`: min distance from `start`
//   -  `prev`: previous point in the shortest path
void calculate_min_dists(const Point &start) {
    for (int r = 0; r < 200; ++r) {
        for (int c = 0; c < 200; ++c) {
            grid[r][c] = MAX;
        }
    }
    priority_queue<pair<int, Point>> q;
    grid[start.r][start.c] = estimated_cost[start.r][start.c];
    prev[start.r][start.c] = start;
    q.push(make_pair(-grid[start.r][start.c], start));
    while (!q.empty()) {
        const int cost = -q.top().first;
        const Point point = q.top().second;
        q.pop();
        //fprintf(stderr, "%d %d @ %d\n", point.r, point.c, cost);

        if (grid[point.r][point.c] < cost) {
            continue;
        }
        for (int d = 0; d < 4; ++d) {
            const int nr = point.r + DR[d];
            const int nc = point.c + DC[d];
            if (nr < 0 || nr >= 200 || nc < 0 || nc >= 200) {
                continue;
            }
            const int ncost = cost + estimated_cost[nr][nc];
            if (grid[nr][nc] > ncost) {
                grid[nr][nc] = ncost;
                prev[nr][nc] = point;
                q.push(make_pair(-ncost, Point(nr, nc)));
            }
        }
    }
}

// Calculates path to the specified point.
// Pre-condition:
//   - `prev`: set by calculate_min_dists()
vector<Point> path_to(const Point &to) {
    vector<Point> res;
    res.push_back(to);

    Point cur = to;
    while (true) {
        const Point p = prev[cur.r][cur.c];
        if (p == cur) {
            break;
        }
        res.push_back(p);
        cur = p;
    }
    return res;
}

Bucket bucket_at(const Point &p) {
    const Point top_left = Point { (p.r / 20) * 20, (p.c / 20) * 20 };
    return Bucket { top_left, 20 };
}


void input() {
    int N, W, K;
    scanf("%d %d %d %d", &N, &W, &K, &C);

    for (int i = 0; i < W; ++i) {
        int r, c;
        scanf("%d %d", &r, &c);
        wells.push_back(Point(r, c));
    }

    for (int i = 0; i < K; ++i) {
        int r, c;
        scanf("%d %d", &r, &c);
        houses.push_back(Point(r, c));
    }
}

// Drill specified point with trying to estimate better cost
// Post-condition:
//   - Point `p` is drilled.
//   - estimated_cost: Set 0 at point p. Other cells may be updated to reflect the new estimation.
//   - cost_range: Updated according to the result.
// Return: Turns taken to drill this point
int drill(const Point &p, double step_factor = 0.25, double min_step_factor = 0) {
    const Range range = cost_range[p.r][p.c];
    int step = std::min(5000.0, std::max(1.0, std::max(range.max * min_step_factor, (range.max - range.min) * step_factor)));

    int cost = 0;
    int cost_before_break = 0;
    int drill_result;
    int turn = 0;

    cost += std::min(5000, range.min + step);
    ++turn;
    printf("%d %d %d\n", p.r, p.c, std::min(5000, range.min + step));
    fflush(stdout);
    scanf("%d", &drill_result);

    while(drill_result == 0) {
        cost_before_break = cost;
        cost += step;
        ++turn;
        printf("%d %d %d\n", p.r, p.c, step);
        fflush(stdout);
        scanf("%d", &drill_result);
    }
    if (drill_result == 2) {
        exit(0);
    }

    estimated_cost[p.r][p.c] = 0;
    cost_range[p.r][p.c] = Range {0, 0};
    // const Bucket bucket = bucket_at(p);
    // printf("# Update to (%d %d) pos (%d %d)\n", cost, cost_before_break, p.r, p.c);
    for (int dr = -10; dr < 10; ++dr) {
        for (int dc = -10; dc < 10; ++dc) {
            const int r = p.r + dr;
            const int c = p.c + dc;
            if (r < 0 || r >= 200 || c < 0 || c >= 200) {
                continue;
            }
            int dist = std::abs(dr) + std::abs(dc);
            double confidence = dist < 5
                ? 0.95
                : dist < 10
                    ? 0.8
                    : dist < 15
                        ? 0.7
                        : 0.6;
            if (estimated_cost[r][c] != 0) {
                cost_range[r][c].min = std::max(0, std::max(cost_range[r][c].min, (int) (cost_before_break * confidence)));
                // cost_range[r][c].max = std::min(cost_range[r][c].max, (int) std::max((cost_range[r][c].max * (1 - 0.2 * confidence)), cost * (1 + 0.2 * (1 - confidence))));
                cost_range[r][c].max = std::min(5000, std::min(cost_range[r][c].max, (int) (cost * (1 + 0.2 * (1 - confidence)))));
                if (cost_range[r][c].min > cost_range[r][c].max) {
                    int avg = (cost_range[r][c].min + cost_range[r][c].max) / 2;
                    int diff = (cost_range[r][c].min - cost_range[r][c].max);
                    cost_range[r][c].min = std::max(0, avg - diff);
                    cost_range[r][c].max = std::min(5000, avg + diff);
                }
                estimated_cost[r][c] = cost_range[r][c].estimation();
            }
        }
    }

    return turn;
}

// Drill to a well from house. Stops after drilled `steps` cells to allow further optimization.
// Returns true if house is connected to a well.
bool drill_to_well(const Point &house, int steps) {
    calculate_min_dists(house);

    int min_dist = MAX;
    Point min_well;
    for (const Point &w: wells) {
        if (grid[w.r][w.c] < min_dist) {
            min_dist = grid[w.r][w.c];
            min_well = w;
        }
    }

    auto path = path_to(min_well);
    // fprintf(stderr, "Drill from (%d, %d) to (%d, %d)\n", house.r, house.c, min_well.r, min_well.c);
    int turn = 0;

    sort(path.begin(), path.end(), [](const Point &a, const Point &b){return cost_range[a.r][a.c].diff() < cost_range[b.r][b.c].diff(); });
    reverse(path.begin(), path.end());
    bool finished = true;
    for (const Point &p : path) {
        if (estimated_cost[p.r][p.c] == 0) {
            // Already drilled
            continue;
        }
        finished = false;
        // printf("# Range[%d][%d] = (%d, %d)\n", p.r, p.c, cost_range[p.r][p.c].min, cost_range[p.r][p.c].max);
        if (cost_range[p.r][p.c].max - cost_range[p.r][p.c].min <= C/default_factor) {
            turn += drill(p, 1, 0.5);
        } else {
            turn += drill(p, default_factor);
        }
        if (turn >= steps) {
            break;
        }
    }

    return finished;
}

// Post-condition:
//   -  `grid`: destructed
//   -  `prev`: destructed
// Returns the point of house which is estimated to be able to connect to a well at smallest cost.
Point select_nearest_house() {
    int min_cost = MAX;
    Point min_house;

    for (const Point &w : wells) {
        calculate_min_dists(w);
        for (const Point &h : houses) {
            if (finished[h.r][h.c]) {
                // Already connected
                continue;
            }
            if (grid[h.r][h.c] < min_cost) {
                min_cost = grid[h.r][h.c];
                min_house = h;
            }
        }
    }

    return min_house;
}

void initialize() {
    switch(C) {
        case 1:
        case 2:
            default_factor = 0.05;
            break;
        case 4:
        case 8:
            default_factor = 0.1;
            break;
        case 16:
        case 32:
        case 64:
        case 128:
            default_factor = 0.25;
            break;
    }
    for (int r = 0; r < 200; ++r) {
        for (int c = 0; c < 200; ++c) {
            cost_range[r][c] = Range { 0, 5000 };
            estimated_cost[r][c] = cost_range[r][c].estimation();
        }
    }

    for (const Point &p : houses) {
        drill(p, default_factor);
    }

if (true) {
    for (int r = 0; r < 200; r += 40) {
        for (int c = 0; c < 200; c += 40) {
            drill(Point(r, c), default_factor);
        }
    }
}
}

int main() {
    input();
    initialize();

    while (true) {
        const Point h = select_nearest_house();
        if (drill_to_well(h, 20)) {
            finished[h.r][h.c] = true;
        }
    }
    
    return 0;
}