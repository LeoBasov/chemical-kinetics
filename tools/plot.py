#!/usr/bin/env python3

import matplotlib.pyplot as plt
import argparse
import csv

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='plot concentrations')

    parser.add_argument('file_name', type=str)

    args = parser.parse_args()
    names = []
    values = []

    with open(args.file_name, "r", newline='') as file:
        reader = csv.reader(file, delimiter=',')
        first_row = True

        for row in reader:
            if first_row:
                first_row = False
                values = [[] for i in range(len(row))]
                names = [row[i].split("#")[1] for i in range(2, len(row))]
            else:
                for i in range(len(row)):
                    values[i].append(float(row[i]))

    for i in range(2, len(values)):
        plt.plot(values[0], values[i])

    plt.xlabel("time")
    plt.ylabel("concentrations")

    plt.legend(names)

    plt.show()
