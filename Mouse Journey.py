x = raw_input().split()
r = eval(x[0]) 
c = eval(x[1])
lab = []
fixed = []
for i in range(r+1):
    row = []
    frow = []
    for j in range (c+1):
        row.append(0)
        frow.append(False)
    lab.append(row)
    fixed.append(frow)

k = int(raw_input())
for i in range(k):
    x = raw_input().split()
    catr = eval(x[0])
    catc = eval(x[1])
    lab[catr][catc] = 0
    fixed[catr][catc] = True

lab[1][1] = 1
fixed[1][1] = True

for i in range(1,r+1):
    for j in range (1,c+1):
        if not fixed[i][j]:
            lab[i][j] = lab[i-1][j] + lab[i][j-1]

print lab[r][c]
