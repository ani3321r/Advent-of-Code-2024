import re
import os
import sys

file_path = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.join(file_path, os.path.pardir, os.path.pardir))

def open_input_and_strip(file_path):
    with open(file_path, 'r') as file:
        return [line.strip() for line in file]

data = open_input_and_strip("./input.txt")

button_a_pattern = re.compile(r"^Button\sA:\sX\+(?P<a_x>\d+)\,\sY\+(?P<a_y>\d+)$")
button_b_pattern = re.compile(r"^Button\sB:\sX\+(?P<b_x>\d+)\,\sY\+(?P<b_y>\d+)$")
prize_pattern = re.compile(r"^Prize:\sX\=(?P<p_x>\d+)\,\sY\=(?P<p_y>\d+)$")

total_presses = 0
for i in range(0, len(data) - 1, 4):
    button_a = re.match(button_a_pattern, data[i])
    button_b = re.match(button_b_pattern, data[i + 1])
    prize = re.match(prize_pattern, data[i + 2])
    a_x, a_y = int(button_a.group("a_x")), int(button_a.group("a_y"))
    b_x, b_y = int(button_b.group("b_x")), int(button_b.group("b_y"))
    p_x, p_y = int(prize.group("p_x")), int(prize.group("p_y"))

    p_x += 10_000_000_000_000
    p_y += 10_000_000_000_000

    B = int(round(((p_y / a_y) - (p_x / a_x)) / ((-b_x / a_x) + (b_y / a_y)), 0))
    A = int(round((p_x / a_x) - B * (b_x / a_x), 0))

    try:
        assert (A * a_x + B * b_x) == p_x
        assert (A * a_y + B * b_y) == p_y
    except AssertionError:
        continue

    total_presses += 3 * A + B

print(f"The total number of presses is {total_presses}")