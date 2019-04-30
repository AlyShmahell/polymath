import os
import sys
import subprocess

if __name__ == '__main__':
    results = []
    os.system("mkdir -p build")
    for _ in range(10):
        os.system("g++ src/library_test.cpp -o build/library_test.elf -std=c++11")
        for _ in range(10):
            try:
                output = subprocess.check_output("./build/library_test.elf")
                output = output.decode('utf8').split()[0]
                results.append(output)
                print(f"{output}")
            except KeyboardInterrupt:
                print("\ntests were interrupted by user.")
                sys.exit(0)
    if len(list(set(results))) > 1:
        failed = len([x for x in results if x != "Success!"])
        print("{failed} tests failed.")
        sys.exit(1)
    else:
        print("all tests were successfull.")