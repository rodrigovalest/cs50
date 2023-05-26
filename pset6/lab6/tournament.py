# Simulate a sports tournament

import csv
from csv import DictReader
import sys
import random

# Number of simluations to run -> quantos torneios vão acontecer
N = 1000

def main():
    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = dict({})
    # Ler do arquivo csv todos os times e guardar numa dict com "Nome do time" : rating

    counts = dict({})
    # Outro dict, mas com "Nome do time" : quantos torneios ele ganhou

    with open(sys.argv[1], "r") as file:
        tmp_teams = DictReader(file)

        for linha in tmp_teams:
            teams[linha[('team')]] = int(linha[('rating')])
            counts[linha[('team')]] = int(0)

    print(list(teams.keys()))

    simulate_tournament(list(teams.keys()))

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")

def simulate_game(team1, team2):
    # Simula um jogo selecionando, randomicamente, quem ganha 
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    # Pega uma lista de times e simula (randomicamente) quais deles vão ganhar, retornando uma lista de vencedores do round atual
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    # Simula o torneio inteiro usando simulate_round, que, por sua vez, usa simulate_game
    # Entra uma lista com times (assumindo, que a quantidade de times tem base 2)
    """Simulate a tournament. Return name of winning team."""
    for i in range(len(teams)):
        # games = simulate_round(teams)
        # print(games)
        print()

if __name__ == "__main__":
    main()