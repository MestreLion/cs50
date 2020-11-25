import cs50


def get_int(prompt):
    """An alternative to CS50's get_int()"""
    while True:
        try:
            return int(input(prompt))
        except ValueError:
            pass


height = 0

# Ask for input, re-asking if not between 1 and 8 (inclusive)
while not (1 <= height <= 8):
    height = cs50.get_int("Height: ")

for line in range(1, height+1):
    print(' ' * (height - line),
          '#' * line,
          ' ' * 2,
          '#' * line,
          sep="")
