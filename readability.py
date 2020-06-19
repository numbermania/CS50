import string
import re

# Get user input text
text = input("Text: ")

# Count upper or lower letters in text, exclude spaces, punctuation, digits, systems
letters = 0.0

for char in text:
    if char in string.ascii_letters:
        letters += 1
# print(f"Letters: {letters}")

# Count words, anything separated by a space use split() function
word_list = text.split()
words = float(len(word_list))
# print(word_list)
# print(f"Words: {words}")

# Count sentences, anything that ends with . ! ?
sentence_list = re.split('\.|\!|\?', text)
sentences = float(len(sentence_list) - 1)
# print(sentence_list)
# print(f"Sentences: {sentences}")

# Calculate Coleman-Liau index
# L = average number of letters per 100 words
L = letters / words * 100

# S = average number of sentences per 100 words
S = sentences / words * 100

index = round(0.0588 * L - 0.296 * S - 15.8)

# Print appropriate grade, handling index < 1 and index > 16
if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")

