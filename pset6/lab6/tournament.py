import csv
import sys
import random

N = 1000

def main():
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = dict({})
    counts = dict({})

    with open(sys.argv[1], "r") as file:
        tmp_teams = csv.DictReader(file)

        for linha in tmp_teams:
            teams[linha[('team')]] = int(linha[('rating')])
            counts[linha[('team')]] = int(0)

    simulate_tournament(teams)

    # ATUALIZAR AS WINS NO COUNTS, SENDO N O NÚMERO DE RODADAS

    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")

def simulate_game(rating1, rating2):
    # rating1 = team1["rating"]
    # rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    winners = []
    temp_teams = list([])

    for i in teams:
        temp_teams.append(i)

    # DAR UM JEITO DE ENVIAR O ('TEAM' : 12312) PARA DENTRO DE SIMULATE_GAME() function, AO INVÉS DE ENVIAR APENAS O RATING CORRESPONDENTE -> só arrumar a gambiarra 
    for i in range(0, len(teams), 2):
        if simulate_game(teams[temp_teams[i]], teams[temp_teams[i + 1]]):
            winners.append(temp_teams[i])
        else:
            winners.append(temp_teams[i + 1])

    return winners


def simulate_tournament(teams):
    winners = simulate_round(teams)
    tmp = dict({})

    while len(winners) > 1:
        for i in range(len(winners)):
            tmp[winners[i]] = teams[winners[i]]

        teams.clear()

        for i in range(len(winners)):
            teams[winners[i]] = tmp[winners[i]]

        tmp.clear()

        winners.clear()
        winners = simulate_round(teams)

    print(winners)

if __name__ == "__main__":
    main()