"""
Original: https://gist.github.com/rhoboro/3b6cc1bc9184645d35b70d9756c3603e
"""
import sys
import os
from pathlib import Path

def extract(filename, basedir):
    """必要な行だけを出力する"""
    outputFile = None
    counter = 0

    with open(filename) as f:
        for line in f:
            if line.startswith('```cpp'):
                outputFile = open(os.path.join(basedir, str(counter) + ".cpp"), 'w')
                counter += 1
            elif line.startswith('```'):
                if outputFile:
                    outputFile.close()
                outputFile = None
            elif outputFile:
                outputFile.write(line)


def main():
    outputdir = sys.argv[1]
    filenames = sys.argv[2:]
    for filename in filenames:
        basedir = os.path.join(outputdir, Path(filename).stem)
        os.makedirs(basedir, exist_ok=True)
        extract(filename, basedir)

if __name__ == '__main__':
    main()
