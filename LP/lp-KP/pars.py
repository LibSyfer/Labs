iter = 500001
npt = open('leo_tolstoy.ged', 'r')
iter_max = iter
arr = npt.read().split('\n')
npt.close()
npt = open('leo_tolstoy.ged', 'r')
iterr = []
fam_max = iter
famm = []
chil_quan = 0
chil = []
chil_max = []
b = 0
chil_help = []
with npt as file:
    for num, line in enumerate(file, 1):
        if ("1 NAME") in line:
            iter_max += 1
            iterr.append(num)
        if ("FAM\n") in line:
            fam_max += 1
            famm.append(num)
        if ("CHIL") in line:
            chil_quan += 1
            chil.append(num)
            chil_help.append(0)
            if chil_quan > 1:
                if chil[chil_quan - 1] == chil[chil_quan - 2] + 1:
                    b = chil_quan - 2
                    while chil_help[b] == -1 and b > 0:
                        b -= 1
                    chil_help[b] += 1
                    chil_help[chil_quan - 1] = -1
mot = [None]*chil_quan
fat = [None]*chil_quan
idx = [None]*chil_quan
it = iter
i = 0
name = [None]*(iter_max - iter)
surname = [None]*(iter_max - iter)
sex = [None]*(iter_max - iter)
num = [None]*(iter_max - iter)
while (i < len(iterr)):
    num[i] = it
    it+=1
    i+=1
it = iter
i = 0
while i < len(iterr):
    name[i] = arr[iterr[i]][7:]
    surname[i] = arr[iterr[i]+1][7:]
    i+=1

i = 0
it = iter
j = 0
opt = open('kp.pro', 'w')
while (i < len(famm)):
    while j < len(num):
        if (int(arr[famm[i] + 3][9:15]) == num[j]):
            c = j
        if (int(arr[famm[i] + 2][9:15]) == num[j]):
            b = j
        if (int(arr[famm[i] + 1][9:15]) == num[j]):
            a = j
        j+=1
    mot[i] = b
    fat[i] = a

    idx[i] = int(arr[famm[i] + 3][9:15])
    opt.write('parents('+ "'" + name[c] + ' ' + surname[c] + "'" + ', ' + "'" + name[a] + ' ' + surname[a] + "'" + ', ' + "'" + name[b] + ' ' + surname[b] + "'" +')' +'.\n')
    i +=1
    j = 0
i = 0
j = 0
counter = 0
u = 0
p = 0
while i < len(chil_help):
    if chil_help[i] > 0:
        while j < chil_help[i]:
            j += 1
            while u < len(idx):
                if (int(arr[chil[i] - 1][9:15]) == idx[u]):
                    while counter < len(num):
                        if (int(arr[chil[i] - 1 + j][9:15])  == num[counter]):
                            opt.write('parents('+ "'" + name[counter] + ' ' + surname[counter] + "'" + ', ' + "'" + name[fat[u]] + ' ' + surname[fat[u]] + "'" + ', ' + "'" + name[mot[u]] + ' ' + surname[mot[u]] + "'" +')' +'.\n')
                        counter += 1
                    counter = 0
                u += 1
            u = 0
    i += 1
    j = 0
i = 0
opt.close()
npt.close()
