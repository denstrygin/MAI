import sys
import random
import string

letters = "0123456789 \n"

def errorMessage():
    print("Использование:\n"
    "\tpython3 {0} name_of_text_file1 name_of_text_file2 name_of_dictunary".format(sys.argv[0]))
    quit()

def preprocess_of_text(nameText, count_of_text):
    try:
        text = open(nameText, 'r')
    except FileNotFoundError:
        print("Файл(ы) не найден(ы). Исключение типа FileNotFoundError.")
        quit()
    text2 = open("text" + str(count_of_text) + ".txt", 'w')
    for line in text:
        out_line = ""
        for letter in line:
            if line[0] == "\n":
                continue
            if letter.isalpha() or (letter in letters):
                out_line += letter
        text2.write(out_line)
    text2.close()
    text.close()

def equalazing_texts():
    out_str = ""
    text1 = open("text1.txt", 'r')
    data = text1.read()
    length_of_text1 = len(data)
    text2 = open("text2.txt", 'r')
    data = text2.read()
    length_of_text2 = len(data)
    if length_of_text1 < length_of_text2:
        text2.close()
        text2 = open("text2.txt", "w")
        for i in range(length_of_text1):
            text2.write(data[i])
        length_of_texts = length_of_text1
    elif length_of_text1 > length_of_text2:
        text1.close()
        text1 = open("text1.txt", "r")
        data = text1.read()
        text1.close()
        text1 = open("text1.txt", "w")
        for i in range(length_of_text2):
            text1.write(data[i])
        length_of_texts = length_of_text2
    text1.close()
    text2.close()
    return length_of_texts

def preprocess_of_letters(length_of_texts, n):
    rand_text = open("text" + str(n) + ".txt", "w")
    ltrs = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 \n'
    text = ''.join(random.choice(ltrs) for i in range(length_of_texts))
    rand_text.write(text)
    rand_text.close()

def preprocess_of_text_of_word(length_of_texts, n):
    spnl = [" ", "\n"]
    text = open(sys.argv[3], "r")
    data = text.read()
    data = data.split("\n")
    text2 = open("text" + str(n) + ".txt", "w")
    word_text = ""
    while(len(word_text) != length_of_texts):
        word = random.choice(data)
        word += random.choice(spnl)
        if len(word_text) + len(word) < length_of_texts:
            word_text += word
        else:
            for i in range(length_of_texts - len(word_text)):
                word_text += word[i]
    text2.write(word_text)
    text2.close()

def preprocess():
    if len(sys.argv) != 4:
        errorMessage()
    count_of_text = 1
    preprocess_of_text(sys.argv[1], count_of_text)
    count_of_text += 1
    preprocess_of_text(sys.argv[2], count_of_text)
    length_of_texts = equalazing_texts()
    print("Длина текстов - " + str(length_of_texts))
    preprocess_of_letters(length_of_texts, 3)
    preprocess_of_letters(length_of_texts, 4)
    preprocess_of_text_of_word(length_of_texts, 5)
    preprocess_of_text_of_word(length_of_texts, 6)

def compare(text1, text2):
    file1 = open(text1, "r")
    file2 = open(text2, "r")
    data1 = file1.read()
    data2 = file2.read()
    size = len(data1)
    suc = 0
    for i in range(size):
        if data1[i] == data2[i]:
            suc += 1
    k = suc / size * 100
    file1.close()
    file2.close()
    return(round(k, 2))

def action():
    k = compare("text1.txt", "text2.txt")
    print("Процент совпадения двух осмысленных текстов - " + str(k) + "%")
    k = compare("text2.txt", "text3.txt")
    print("Процент совпадения осмысленного текста и из рандомных букв - " + str(k) + "%")
    k = compare("text1.txt", "text5.txt")
    print("Процент совпадения осмысленного текста и из рандомных слов - " + str(k) + "%")
    k = compare("text3.txt", "text4.txt")
    print("Процент совпадения текста из рандомных букв и из рандомных букв - " + str(k) + "%")
    k = compare("text5.txt", "text6.txt")
    print("Процент совпадения текста из рандомных слов и из рандомных слов - " + str(k) + "%")

def main():
    preprocess() 
    action()   

if __name__ == "__main__":
    main()