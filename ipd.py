import random

class Player:
    def __init__(self, strategy):
        self.strategy = strategy
        self.score = 0
        self.history = []

    def play(self, other_player):
        move = self.strategy.play(self, other_player)
        self.history.append(move)
        return move
    
import random

class Player:
    def __init__(self, strategy):
        self.strategy = strategy
        self.score = 0
        self.history = []

    def play(self, other_player):
        move = self.strategy.play(self, other_player)
        self.history.append(move)
        return move
    
def play_round(player1, player2):
    move1 = player1.play(player2)
    move2 = player2.play(player1)

    


 #   print(f"Player 1 ({player1.strategy.__class__.__name__}) move: {move1}")
 #   print(f"Player 2 ({player2.strategy.__class__.__name__}) move: {move2}")


    if move1 == 'c' and move2 == 'c':
        player1.score += 4
        player2.score += 4
    elif move1 == 'c' and move2 == 'd':
        player1.score += 0
        player2.score += 5
    elif move1 == 'd' and move2 == 'c':
        player1.score += 5
        player2.score += 0
    elif move1 == 'd' and move2 == 'd':
        player1.score += 2
        player2.score += 2
        
#    print(f"Player 1 score: {player1.score}")
#    print(f"Player 2 score: {player2.score}")

def play_game(players):
    for i in range(len(players)):
        for j in range(i+1, len(players)):
            for _ in range(10):  
                play_round(players[i], players[j])

if __name__ == "__main__":
    strategy_names = ['AlwaysC', 'AlwaysD', 'RandomChoice', 'TitForTat']

    for n in range(1, 5):
        always_c_count = int(input("Enter the number of AlwaysC players: "))
        always_d_count = int(input("Enter the number of AlwaysD players: "))
        random_choice_count = int(input("Enter the number of RandomChoice players: "))
        tit_for_tat_count = int(input("Enter the number of TitForTat players: "))

        player_counts = {
            'AlwaysC': always_c_count,
            'AlwaysD': always_d_count,
            'RandomChoice': random_choice_count,
            'TitForTat': tit_for_tat_count
        }

        players = [
            Player(AlwaysC()) for _ in range(player_counts['AlwaysC'])
        ] + [
            Player(AlwaysD()) for _ in range(player_counts['AlwaysD'])
        ] + [
            Player(RandomChoice()) for _ in range(player_counts['RandomChoice'])
        ] + [
            Player(TitForTat()) for _ in range(player_counts['TitForTat'])
        ]

        play_game(players)

 
        for strategy in strategy_names:
            scores = [player.score for player in players if type(player.strategy).__name__ == strategy]
            if scores:
                average_score = sum(scores) / len(scores)
                print(f'Average score for {strategy}: {average_score}')
            else:
                print(f'No players with strategy {strategy}')