from cs50 import get_string

def formula(letras, palavras, frases):
    L = (letras / palavras) * 100
    S = (frases / palavras) * 100

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
    elif char == " ":
        palavras += 1
    elif char == "." or char == "!" or char == "?":
        frases += 1

grade = formula(letras, palavras, frases)

print(grade)