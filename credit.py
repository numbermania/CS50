# Get card number as a string
num = str(input("Number: "))

# String to store card type or INVALID
card_type = "INVALID"

# Check if card has the correct number of digits
if len(num) not in (15, 16, 13):
    print(card_type)
    exit(0)

# Run Luhn's Algorithm
    # From second to last digit, multiple by 2, add the product's digits together
    # Sum all other digits and add to previous
    # Total should be a multiple of 10
total = 0
# Second to last digits (substring to exclude last digit)
for i in range(len(num) - 2, -1, -2):
    product = str(int(num[i]) * 2)  #cast the each product as the string to iterate over
    for char in product:
        total += int(char)

# Sum all other digits and add to previous
for i in range(len(num) - 1, -1, -2):
    total += int(num[i])

# Determine if multiple of 10 (VALID)
if total % 10 != 0:
    print(card_type)
    exit(0)

# Card number is valid, sort into different types:
    # AMEX (15), start with 34 or 37
    # MASTERCARD (16) start with 51, 52, 53, 54, 55
    # VISA (13 or 16) starts with 4
# AMEX
if len(num) == 15:
    # Check first 2 digits = 34 or 37
    if int(num[:2]) in (34, 37):
        card_type = "AMEX"
# VISA
elif len(num) == 13:
    # Check if first digit = 4
    if int(num[:1]) == 4:
        card_type = "VISA"
# MASTERCARD OR VISA
elif len(num) == 16:
    # VISA - Check if first digit = 4
    if int(num[:1]) == 4:
        card_type = "VISA"
    # MASTERCARD - Check first 2 digits between 51 - 55
    elif int(num[:2]) in range(51, 56):
        card_type = "MASTERCARD"

print(card_type)