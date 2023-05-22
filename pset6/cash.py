from cs50 import get_float

# Solicita ao usuário o valor do troco devido
while True:
    change_owed = get_float("Change owed: ")
    if change_owed >= 0:
        break

# Converte o valor do troco em centavos
cents = round(change_owed * 100)

# Calcula o número mínimo de moedas necessárias para o troco
quarters = cents // 25
dimes = (cents % 25) // 10
nickels = ((cents % 25) % 10) // 5
pennies = ((cents % 25) % 10) % 5

# Imprime o número mínimo de moedas
print(quarters + dimes + nickels + pennies)