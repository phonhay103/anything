import time
import random

MAX_SCORE = 21
TOTAL_PLAYERS = 4

class Player:
    def __init__ (self, name):
        self.name = name
        self.score = 0

    def updateScore(self, score):
        if self.score + score == MAX_SCORE:
            self.score = MAX_SCORE
            return True
        elif self.score + score> MAX_SCORE:
            self.score = 0
            return False
        else:
            self.score += score
            return False

class VirtualPlayer(Player):
    def __init__ (self, name):
        super().__init__(name)
        self.lose_actions = [
            lambda: print(f'{self.name}: Được lắm'),
            lambda: print(f'{self.name}: GG!'),
            lambda: print(f'{self.name}: Cũng khá đấy!'),
            lambda: print(f'{self.name}: Hên đấy')
        ]

    def lose(self):
        random.choice(self.lose_actions)()

class Dice:
    def __init__(self, prob):
        self.prob = prob
        self.list_values = [1, 2, 3, 4, 5, 6]

    def roll(self):
        return random.choices(self.list_values, self.prob, k=1)[0]

class GM:
    def __init__(self, n_players=4, n_dices=4):
        # Init dices
        self.dices = [
            Dice([0.2, 0.16, 0.16, 0.16, 0.16, 0.16]),
            Dice([0.16, 0.2, 0.16, 0.16, 0.16, 0.16]),
            Dice([0.16, 0.16, 0.2, 0.16, 0.16, 0.16]),
            Dice([0.16, 0.16, 0.16, 0.16, 0.2, 0.16]),
        ]

        # Init Virtual players
        self.players = [
            VirtualPlayer(f'Bot {i-n_players+1}') for i in range(n_players, TOTAL_PLAYERS)
        ]

        # Init players
        for i in range(n_players):
            name = input(f'Nhap ten nguoi choi {i+1}: ')
            self.players.append(Player(name))

        random.shuffle(self.players)

    def getNextPlayer(self):
        currentPlayer = self.players.pop(0)
        self.players.append(currentPlayer)
        return currentPlayer

    def getRandomDice(self):
        return random.choice(self.dices)

    def endGame(self, winner):
        print('\nChúc mừng người chiến thắng: ' + winner.name)
        for player in self.players:
            if isinstance(player, VirtualPlayer):
                player.lose()

    def operation(self):
        turn = 0
        print('\nTurn 1:')
        while True:
            turn += 1
            currentPlayer = self.getNextPlayer()
            score = self.getRandomDice().roll()
            print(f'{currentPlayer.name}: {currentPlayer.score} + ', end='')
            check = currentPlayer.updateScore(score)
            print(f'{score} -> {currentPlayer.score}')
            if check:
                self.endGame(currentPlayer)
                break
            
            if turn % 4 == 0:
                time.sleep(.5)
                print('\nTurn', turn // 4 + 1)

if __name__ == '__main__':
    num_players = int(input('Nhập số lượng người chơi (0-4): '))
    if num_players > TOTAL_PLAYERS:
        num_players = TOTAL_PLAYERS
    elif num_players < 0:
        num_players = 0

    gm = GM(num_players)
    gm.operation()