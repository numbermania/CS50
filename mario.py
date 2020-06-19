from cs50 import get_int

h = -1
# Get height between 1 to 8 inclusive
while h < 1 or h > 8:
    h = get_int("Height: ")

# i iterates through rows
for i in range(1, h + 1):
    # j interates through columns in each row
    # each row has h * 2 + 2 (gap size) chars/columns
    for j in range(1, h * 2 + 3):
        # first half of pyramid
        if j >= 1 and j <= h:
            if j <= h - i:
                print(" ", end = "")
            else:
                print("#", end = "")

        # gaps -> print spaces
        elif j > h and j <= h + 2:
            print(" ", end = "")

        # second half of pyramid
        else:
            if (j - h - 2) <= i:
                print("#", end = "")
            # no padding spaces at the end, go to new line

    # row ends, new line
    print()