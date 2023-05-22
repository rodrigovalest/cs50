import cs50

altura = cs50.get_int("Digite a altura da pirâmide: ")

for i in range(altura):
    for a in range(altura - i - 1):
        print(" ", end="")
    for b in range(i + 1):
        print("#", end="")
    for c in range(i + 1):
        print("#", end="")
    print()