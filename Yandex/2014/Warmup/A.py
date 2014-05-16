#!/usr/bin/env python

def decode(pos):
    col = "abcdefgh".find(pos[0])
    row = int(pos[1]) - 1
    return (row, col)

def king_move_area(pos):
    res = list()
    for dr in range(-1, 2):
        for dc in range(-1, 2):
            if dr == 0 and dc == 0:
                continue
            if pos[0] + dr in range(0, 8) and pos[1] + dc in range(0, 8):
                res.append((pos[0] + dr, pos[1] + dc))
    return res

def rook_move_area(pos, obstacles):
    def each_by(start, delta):
        cur = start
        while True:
            cur += delta
            yield cur

    res = list()
    for r in each_by(pos[0], 1):
        p = (r, pos[1])
        if p[0] >= 8:
            break
        res.append(p)
        if p in obstacles:
            break
    for r in each_by(pos[0], -1):
        p = (r, pos[1])
        if p[0] < 0:
            break
        res.append(p)
        if p in obstacles:
            break
    for c in each_by(pos[1], 1):
        p = (pos[0], c)
        if p[1] >= 8:
            break
        res.append(p)
        if p in obstacles:
            break
    for c in each_by(pos[1], -1):
        p = (pos[0], c)
        if p[1] < 0:
            break
        res.append(p)
        if p in obstacles:
            break
    return res
    
def judge(wk, wr, bk):
    wk_attack = king_move_area(wk)
    if bk in wk_attack:
        return "Strange"
    # wk is not attacking bk
    wr_attack = rook_move_area(wr, [wk])
    bk_move = king_move_area(bk)
    mate = all([bm in (wr_attack+wk_attack) for bm in bk_move])
    if bk in wr_attack:
        # Checked
        if mate:
            return "Checkmate"
        else:
            return "Check"
    # Not checked
    if mate:
        return "Stalemate"
    return "Normal"

(wk, wr, bk) = [decode(pos) for pos in input().split()]
print(judge(wk, wr, bk))
