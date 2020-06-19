from cs50 import get_float

change = -1;
# Prompt for non-negative amount of change
while change < 0:
    change = get_float("Change owed: ")

# Convert change from dollars (assumed) to cents to avoid rounding errors
    change = int(change * 100)

# Variables for possible coins
quarter = 25
dime = 10
nickel = 5
penny = 1

# Counter for number of coins returned
coins = 0

if (change >= quarter):
    coins += change // quarter
    change = change % quarter

if (change >= dime):
    coins += change // dime
    change = change % dime

if (change >= nickel):
    coins += change // nickel
    change = change % nickel

if (change >= penny):
    coins += change // penny
    change = change % penny

# Print coins
print(coins)