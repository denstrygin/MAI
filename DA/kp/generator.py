import random

TEXT_LENGTH = 10000

def generate_random_text(length):
    alphabet = " abcde"
    rand_text = ''.join(random.choice(alphabet) for i in range(length))
    return rand_text

text = generate_random_text(TEXT_LENGTH)
with open("text1", "w") as file:
    file.write(text)