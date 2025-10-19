import random
from abc import ABC, abstractmethod
#Nomor 1: Abstraction & Contract - Kelas Induk Abstrak
class Enemy():
    def __init__(self, hp, level:int, x:float):
        self.hp = hp
        self.level = level
        self.damage = 1.5*level
        self.x = x 
    
    def move_right(self):
        new_x = self.x + 10.0
        print(f"moving from {self.x} to {new_x}")
        self.x = new_x
        
    def move_left(self):
        new_x = self.x - 10.0
        print(f"moving from {self.x} to {new_x}")
        self.x = new_x
        
    def attack(self):
        print(f"attacking, deal {self.damage} damage")
        return self.damage
    
    def describe(self):
        pass
    
    def get_hit(self, damage:int):
        self.hp = self.hp - damage
        print(f"attacked, current hp: {self.hp}")

    @abstractmethod
    def describe(self):
        pass

#Nomor 2: Constructor & Inheritance - Kelas Anak Pertama
#Nomor 3: Encapsulation & Validation - Atribut terenkapsulasi dengan Setter/Getter
class Golem(Enemy):
    def __init__(self, hp, level, x):
        super().__init__(hp, level, x)
        self.type = "Golem"
        self._resistance_factor = 0.5
    
    def get_resistance_factor(self):
        return self._resistance_factor
    
    def set_resistance_factor(self, resistance_factor: float):
        if 0.0 <= resistance_factor <= 1.0:
            self._resistance_factor = resistance_factor
        else:
            raise ValueError("Resistance factor must be between 0.0 and 1.0")
    
    def describe(self):
        print(f"enemy detail: \n Type: {self.type} \n hp: {self.hp} \n level: {self.level} \n resistance: {self._resistance_factor*100}%")
    
    def get_hit(self, damage: int):
        reduced_damage = max(0, damage * self._resistance_factor)
        self.hp = self.hp - reduced_damage
        print(f"Attacked! Resistance reduced damage to {reduced_damage:.2f}, current hp: {self.hp:.2f}")
        return reduced_damage

#Nomor 4: Polymorphism Setup - Kelas Anak Kedua dengan implementasi berbeda
class Demon_Spirit(Enemy):
    def __init__(self, hp, level, x, y):
        super().__init__(hp, level, x)
        self.y = y
        self.type = "Demon Spirit"
    
    def move_left(self):
        fly_chance = random.random()
        new_x = self.x - 10
        new_y = self.y
        if fly_chance >= 0.7:
            new_y = self.y + 3.0
            print(f"Flying! moving from ({self.x},{self.y}) to ({new_x},{new_y})")
        else:
            print(f"moving from ({self.x},{self.y}) to ({new_x},{new_y})")
        
        self.x = new_x
        self.y = new_y
        
    def move_right(self):
        fly_chance = random.random()
        new_x = self.x + 10
        new_y = self.y
        if fly_chance >= 0.7:
            new_y = self.y + 3.0
            print(f"Flying! moving from ({self.x},{self.y}) to ({new_x},{new_y})")
        else:
            print(f"moving from ({self.x},{self.y}) to ({new_x},{new_y})")
        
        self.x = new_x
        self.y = new_y
    
    def describe(self):
        print(f"enemy detail: \n Type: {self.type} \n hp: {self.hp} \n level: {self.level} \n position: ({self.x}, {self.y}) \n ability: can fly")

#Nomor 5: Polymorphism Demonstration - Fungsi independen
def demonstrasi_perilaku(objek):
    objek.describe()

def enemy_move_right(enemy):
    try:
        enemy.move_right()
    except AttributeError as e:
        raise e

def enemy_move_left(enemy):
    try:
        enemy.move_left()
    except AttributeError as e:
        raise e

def enemy_hit(enemy, damage_taken):
    try:
        return enemy.get_hit(damage_taken)
    except AttributeError as e:
        raise e

def enemy_attack(enemy):
    try:
        return enemy.attack()
    except AttributeError as e:
        raise e

def main():
    player_hp = 100
    player_damage = 15
    
    golem = Golem(hp=80, level=5, x=0.0)
    demon = Demon_Spirit(hp=60, level=4, x=100.0, y=0.0)
    
    print("--- Enemy 1 Status ---")
    demonstrasi_perilaku(golem)
    print()
    
    print("--- Enemy 2 Status ---")
    demonstrasi_perilaku(demon)
    print()
    
    print("GOLEM ENCOUNTER")
    print()
    
    print(f"Player HP: {player_hp}")
    print("Golem approaching")
    enemy_move_right(golem)
    enemy_move_right(golem)
    print()
    
    print("Player attacks Golem!")
    enemy_hit(golem, player_damage)
    print()
    
    if golem.hp > 0:
        print("Golem counter-attacks!")
        damage_dealt = enemy_attack(golem)
        player_hp -= damage_dealt
        print(f"Player HP: {player_hp:.2f}")
    print()
    
    print("Testing Encapsulation: Adjusting Golem's resistance")
    print(f"Current resistance: {golem.get_resistance_factor()}")
    golem.set_resistance_factor(0.3)
    print(f"New resistance: {golem.get_resistance_factor()}")
    print()
    
    print("Player attacks again with reduced resistance!")
    enemy_hit(golem, player_damage)
    print()
    
    if golem.hp > 0:
        print("Golem attacks back!")
        damage_dealt = enemy_attack(golem)
        player_hp -= damage_dealt
        print(f"Player HP: {player_hp:.2f}")
    else:
        print("GOLEM DEFEATED! ")
    print()
    
    print("BATTLE PHASE: DEMON SPIRIT ENCOUNTER")
    print()
    
    print(f"Player HP: {player_hp:.2f}")
    print("Demon Spirit approaching from the right")
    enemy_move_left(demon)
    enemy_move_left(demon)
    print()
    
    print("Player attacks Demon Spirit!")
    enemy_hit(demon, player_damage)
    print()
    
    if demon.hp > 0:
        print("Demon Spirit counter-attacks!")
        damage_dealt = enemy_attack(demon)
        player_hp -= damage_dealt
        print(f"Player HP: {player_hp:.2f}")
    print()
    
    print("Player launches final attack!")
    enemy_hit(demon, player_damage)
    print()
    
    if demon.hp > 0:
        print("Demon Spirit retaliates!")
        damage_dealt = enemy_attack(demon)
        player_hp -= damage_dealt
        print(f"Player HP: {player_hp:.2f}")
    else:
        print("DEMON SPIRIT DEFEATED! ")
    print()
    
    print("BATTLE SUMMARY")
    print(f"Final Player HP: {player_hp:.2f}")
    print(f"Golem HP: {max(0, golem.hp):.2f}")
    print(f"Demon Spirit HP: {max(0, demon.hp):.2f}")
    print()
    
    if player_hp > 0:
        print("Victory!!")
    else:
        print("You Lose!")

if __name__ == "__main__":
    main()


def fname():
    pass
