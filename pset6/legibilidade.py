from cs50 import get_string

def formula_coleman_liau(letters, words, sentences):
    L = (letters / words) * 100
    S = (sentences / words) * 100

    grade = int(0.0588 * L - 0.296 * S - 15.8)

    if grade < 1:
        return "Before Grade 1"
    elif grade >= 16:
        return "Grade 16+"
    else:
        return f"Grade {grade}"

text = get_string("Digite um texto: ")

letras = 0
palavras = 0
frases = 0

for char in text:
    if char.isalpha():
        letras += 1
    elif char.isspace():
        palavras += 1
    elif char == "." or char == "?" or char == "!":
        frases += 1

grade_level = formula_coleman_liau(letras, palavras, frases)

print(grade_level)