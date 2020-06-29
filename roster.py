import sys
import csv
from cs50 import SQL

# Check that house name is provided as a command line argument
if len(sys.argv) != 2:
    print("USage: python roster.py house_name")
    exit()

# Get house entered as string
house = str(sys.argv[1])

# Execute SQL Query for house, sorted by last name then first name
db = SQL("sqlite:///students.db")
# db.execute returns a list of dicts
stu = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", house)

for row in stu:
    # Check if middle name is None
    if row["middle"] == None:
        print(f"{row['first']} {row['last']}, born {row['birth']}")
    else:
        print(f"{row['first']} {row['middle']} {row['last']}, born {row['birth']}")