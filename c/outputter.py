import time
with open("output.txt", "w",0) as out:
    while True:
        with open("animals.txt", 'r') as file:
            all_lines = file.readlines()
            for line in all_lines:
                    out.write(line.strip() + "\n")
                    time.sleep(0.1)