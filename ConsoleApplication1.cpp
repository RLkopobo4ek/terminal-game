#include <iostream>
#include <vector>

using namespace std;

class Item {

public:
    Item(int my_ID, int my_health_value, string my_name) {
        ID = my_ID;
        health_value = my_health_value;
        name = my_name;
    }

    int get_health_value() { return health_value; }
    int get_ID() { return ID; }
    string get_name() { return name; }

private:
    int ID;
    int health_value;
    string name;
};

class Enemy {
private:
    string Ename = "";
    int health;
    int damage;
    //int health;
    char symbol;
public:


    Enemy(string n, int dmg, int hp, char sym) {
        damage = dmg;
        health = hp;
        symbol = sym;
        Ename = n;

    }
    void takedamage(int dmg) {
        health -= dmg;
        if (health > 0) {
            health = 0;
        }
    }



    int get_damage() { return damage; }
    int get_health() { return health; }
    string get_name() { return Ename; }


};

class Character {
public:

    Character(string my_location) {
        location = my_location;
    }



    void add_health(int x) {
        health = health + x;
        if (health > 100) {
            health = 100;
        }
    }
    bool playeralive() {
        return health > 0;
    }

    int get_damage() { return damage; }
    int get_health() { return health; }

    void set_damage(int x) {
        if (damage < 1) {
            damage = 1;
        }
    }

    void use_poison(int ID) {
        int L = inventory.size();
        for (int i = 0; i < L; i++) {
            if (inventory[i].get_ID() == ID) {
                add_health(inventory[i].get_health_value());
                remove_from_inventory(i);
                L--;
            }
        }
    }

    


    void attack(Enemy& enemy) {
        enemy.takedamage(damage);
        cout << "Вы наносите" << damage << "урона \n";
    }



    void takedamage(int dmg) {
        health -= dmg;
        if (health < 0) {
            health = 0;
        }
    }

    void add_to_inventory(Item x) {
        inventory.push_back(x);
    }

    void remove_from_inventory(int i) {
        inventory.erase(inventory.begin() + i);
    }

    void print() {
        cout << "health: " << health << "\n";
        cout << "damage: " << damage << "\n";
        cout << "location: " << location << "\n";
        cout << "inventory: [ ";
        int L = inventory.size();
        for (int i = 0; i < L; i++) {
            cout << inventory[i].get_name() << ", ";
        }
        cout << " ]" << "\n";
    }

private:
    int health = 100;
    int damage = 1;
    string location = "";
    vector<Item> inventory = {};
};

class Location {
private:
    int width;
    int height;
    vector<vector<char>> map;
    int playerX, playerY;
    int enemyX, enemyY;
    char playerSymbol;
    char enemySymbol;



public:
    // Конструктор
    Location(int w, int h, char playerSym = '@', char enemySym = 'O') {
        width = w;
        height = h;
        playerSymbol = playerSym;
        enemySymbol = enemySym;
        playerX = width / 2;
        playerY = height / 2;
        enemyX = width / 2;
        enemyY = height / 2;
        generateMap();
    }

    // Генерация карты с контуром
    void generateMap() {
        map.resize(height, vector<char>(width));

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                    map[i][j] = '#';
                }
                else {
                    map[i][j] = '.';
                }
            }
        }
    }

    // Размещение игрока
    void placePlayer(int x, int y) {
        if (x > 0 && x < width - 1 && y > 0 && y < height - 1) {
            playerX = x;
            playerY = y;
        }
    }

    void placeEnemy(int x, int y) {
        if (x > 0 && x < width - 1 && y > 0 && y < height - 1) {
            enemyX = x;
            enemyY = y;
        }
    }



    // Отрисовка локации
    void render() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (i == playerY && j == playerX) {
                    cout << playerSymbol << ' ';
                }
                else if (i == enemyY && j == enemyX) {
                    cout << enemySymbol << ' ';
                }
                else {
                    cout << map[i][j] << ' ';
                }
            }
            cout << endl;
        }
    }
};



int main()
{
    Location one(8, 8, '@', 'O');
    one.placePlayer(4, 6);
    one.placeEnemy(3, 3);
    one.render();
    Enemy yt("s", 10, 100, 'S');
    Character my_char("Home");
    my_char.print();
    Item my_poison(912, 10, "Vasili kotory chuvstvuet sebya Egorom");
    my_char.add_to_inventory(my_poison);
    my_char.takedamage(17);
    my_char.print();
    my_char.use_poison(912);
    cout << yt.get_name();

   

}


