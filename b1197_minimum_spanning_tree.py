def get_parent(parent, x):
    stk = list()
    cnt = 0;
    t = x
    while parent[t] != t:
        stk.append([t, parent[t]])
        t = parent[t]
        cnt += 1
    for i in range(cnt - 1, -1, -1):
        t, pt = stk[i]
        parent[t] = parent[pt]
    return parent[x]

def unify_parent(parent, a, b):
    pa = get_parent(parent, a)
    pb = get_parent(parent, b)
    if pa < pb:
        parent[pb] = pa
    elif pb < pa:
        parent[pa] = pb
    else:
        return False
    return True

def kruskal(edges, v):
    parent = [ 0, ]
    for i in range(1, v + 1):
        parent.append(i)
    cnt = 0
    dist = 0
    for a, b, c in edges:
        if unify_parent(parent, a, b):
            dist += c
            cnt += 1
        if cnt == v - 1:
            break
    return dist

v, e = map(int, input().split())
edges = list()
for i in range(e):
    a, b, c = map(int, input().split())
    edges.append([a, b, c])

edges.sort(key=lambda x: x[2]) # time sort: O(eloge)
print(kruskal(edges, v))
