import sys
import csv


def main():
    # Ensures number of user inputs correct
    # First is csv file of DNA database
    # Second is txt file with DNA sequence to identify
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit()

    # Define global variables for to be used outside of main function
        global SEQ
        global DBASE
        global KEYS

    # Store DNA sequence as a string named seq, stripping new line at end
    with open(sys.argv[2], 'r') as sequence:
        SEQ = str(sequence.read()).rstrip()
    # print(seq)

    # Stores the database csv file as a list of dictionaries named dbase
    DBASE = []
    with open(sys.argv[1], 'r') as database:
        read = csv.DictReader(database)
        for row in read:
            DBASE.append(dict(row))
    # for person in dbase:
    #     print(person)

    # Creates a blank dictionary with default values of keys
    # keys is a list of keys in the dictionary
    KEYS = list(DBASE[0].keys())
    # counts is a dictionary to be updated with STR counts and matching person
    counts = {}
    for k in KEYS:
        counts[k] = ""

    # Update STR counts in counts
    for k in KEYS:
        if k != "name":       # Ignore first item, which is always 'name' and not an STR
            counts[k] = count_str(str(k))

    # Search for person matching STR counts in counts[]
    find_match(counts)

    # Print match
    print(counts['name'])

# Function searchs seq and reports max times s_str is found consectively in seq


def count_str(s_str):
    count = 0      # Default: s_str not found

    # Iterate through each starting position of seq
    for i in range(len(SEQ)):
        for j in range(i + len(s_str), len(SEQ), len(s_str)):     # End of each seq substring
            # If check seq substring against repeating s_str
            sub_len = len(SEQ[i:j]) // len(s_str)
            substring = str(s_str * sub_len)
            if SEQ[i:j] == substring and sub_len > count:
                count = sub_len
    return count

# Function to find person in dbase that matches c's STR counts, updates c's name key with appropriate value


def find_match(counts):
    counts['name'] = "No match"        # Default no one in dbase matches
    match = 0

    # Iterates over dbase to look for match
    for person in DBASE:        # person is dictionary
        # check matches for each STR (avoid name key)
        for k in KEYS:
            if k != "name" and int(counts[k]) == int(person[k]):
                match += 1
            else:
                match = 0

        # It match all keys, match found, update name and break
        if match == len(KEYS) - 1:
            counts['name'] = person['name']
            break


main()