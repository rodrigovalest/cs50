import csv
from sys import argv

if len(argv) != 3:
    print("ERRO: arquivos não encontrados. Digite: 'python dna.py databases/ sequences/'")

strbases = {
    'AGATC' : 0,
    'TTTTTTCT' : 0,
    'AATG' : 0,
    'TCTAG' : 0,
    'GATA': 0,
    'TATC' : 0,
    'GAAA': 0,
    'TCTG' : 0
}

chaves = list(strbases.keys())

with open(argv[1], "r") as sequence:
    all_bases = sequence.read()

    for a in range(len(chaves)):
        list_bases = [0 for i in range(len(all_bases))]

        for i in range(len(all_bases) - len(chaves[a])):
            chunck_bases = all_bases[i:i + len(chaves[a])]
            
            if chunck_bases == chaves[a]:
                list_bases[i] = list_bases[i - len(chaves[a])] + 1

        longest_sequence = 0

        for j in range(len(all_bases)):
            if list_bases[j] > longest_sequence:
                longest_sequence = list_bases[j]

        strbases[chaves[a]] = longest_sequence
        longest_sequence = 0

with open(argv[2], "r") as database:
    file = csv.reader(database)
    person = 'Not match'

    for linha in file:
        check = [False for i in range(len(linha))]

        if linha[0] == 'name':
            continue

        for i in range(1, len(linha) - 1, 1):
            if int(linha[i]) == int(strbases[chaves[i - 1]]):
                print(True)
                check[i] = True 
            else:
                check[i] = False

        if check == True:
            print(linha[0])
            break

        # for i in range(check):
        #     if check[] == 