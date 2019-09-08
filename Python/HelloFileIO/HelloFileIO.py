# Ryan Lee
# Title: HelloFileIO.py

list1 = [i * 2 for i in range(1, 12)]

main_file = open("output.txt", "w+")
file_read = open("text.txt", "r+")

for item in list1:
	main_file.write(str(item) + "\n")

print file_read.readline()
print file_read.read()

main_file.close()
file_read.close()
