import sys
import csv
from cs50 import SQL

# Check that csv file is provided as a command line argument
if len(sys.argv) != 2:
    print("USage: python import.py characters.csv")
    exit()

# Create a new database called students
open(f"students.db", "w").close()
db = SQL("sqlite:///students.db")

# Create students table with correct columns
db.execute("CREATE TABLE students (first TEXT, middle TEXT, last TEXT, house TEXT, birth NUMERIC)")

# Open DictReader for csv object
with open(sys.argv[1], 'r') as characters:
    read = csv.DictReader(characters)

    # For each student (row) in the characters.csv
    for row in read:

        # Parse name and insert into first middle last
        full_name = row["name"].split()
        first = full_name[0]
        # If no middle name
        if len(full_name) == 2:
            middle = None
            last = full_name[1]
        else:
            middle = full_name[1]
            last = full_name[2]

        # Insert into database
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", first, middle, last, row["house"], row["birth"])