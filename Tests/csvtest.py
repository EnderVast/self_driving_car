import csv
ls = []
num = 15

with open('img_dir.csv', 'w') as imgdir:
    csv_writer = csv.writer(imgdir)
    for i in range(num):
        ls = []
        j = num - i
        c = "test" + str(i)
        ls.append(c)
        ls.append(j)
        csv_writer.writerow(ls)