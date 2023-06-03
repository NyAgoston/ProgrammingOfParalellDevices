import csv
import matplotlib.pyplot as plt

# Lists to store the data
x1, y1 = [], []
x2, y2 = [], []

with open("data.csv","r") as csv_file:
            
    reader = csv.reader(csv_file,delimiter = " ")
    for line in reader:
        print(line)
        if int(line[0]) == 0:
            n1 = int(line[1])
            t1 = float(line[2])
            x1.append(n1)
            y1.append(t1)
        elif int(line[0]) == 1:
            n2 = int(line[1])
            t2 = float(line[2])
            x2.append(n2)
            y2.append(t2)



# Plotting the first set of data
plt.plot(x1, y1, label='CPU')

# Plotting the second set of data
plt.plot(x2, y2, label='GPU')

# Adding labels and title
plt.xlabel('X Values')
plt.ylabel('Y Values')
plt.title('CPU vs GPU')

# Adding legend
plt.legend()

# Displaying the plot
plt.show()
