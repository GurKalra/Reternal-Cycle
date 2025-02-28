#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INVENTORY_SIZE 5

typedef struct Item {
    char* name;
    char* description;
}Item;

typedef struct Room {
    char* name;
    char* description;
    struct Room* north;
    struct Room* south;
    struct Room* east;
    struct Room* west;
    Item* items[INVENTORY_SIZE];
    int itemCount;
}Room;

typedef struct Player {
    Room* currentRoom;
    Item* inventory[INVENTORY_SIZE];
    int numberOfItems;
}Player;

void addItem(Player* p, Item* item) {
    if (p->numberOfItems < INVENTORY_SIZE) {
        p->inventory[p->numberOfItems] = item;
        p->numberOfItems++;
        printf("\n[INFO] You picked up: %s\n", item->name);
    }
    else {
        printf("\n[ERROR] Inventory full! Drop an item first.\n");
    }
}

void showInventory(Player* p) {
    printf("\n[INVENTORY]:\n");
    if (p->numberOfItems == 0)
        printf(" - (empty)\n");
    else {
        for (int i = 0; i < p->numberOfItems; i++)
            printf("%d. %s\n", i + 1, p->inventory[i]->name);
    }
}

void dropItem(Player* p, int index) {
    if (p->numberOfItems == 0) {
        printf("\n[ERROR] Inventory is empty!\n");
        return;
    }

    if (index < 0 || index >= p->numberOfItems) {
        printf("\n[ERROR] Invalid item number! Choose between 1 and %d.\n", p->numberOfItems);
        return;
    }

    printf("\n[INFO] You dropped: %s\n", p->inventory[index]->name);

    for (int i = index; i < p->numberOfItems - 1; i++) {
        p->inventory[i] = p->inventory[i + 1];
    }

    p->inventory[p->numberOfItems - 1] = NULL;
    p->numberOfItems--;
}

void useItem(Player* p, char* itemName) {
    for (int i = 0; i < p->numberOfItems; i++) {
        if (strcmp(p->inventory[i]->name, itemName) == 0) {

            if (strcmp(itemName, "Health Pack") == 0) {
                printf("\n[INFO] You use the Health Pack. You feel rejuvenated!\n");
            }
            else if (strcmp(itemName, "Keycard") == 0) {
                printf("\n[INFO] You swipe the Keycard. A door unlocks nearby!\n");
            }
            else {
                printf("\n[INFO] You use the %s, but nothing happens...\n", itemName);
            }

            for (int j = i; j < p->numberOfItems - 1; j++) {
                p->inventory[j] = p->inventory[j + 1];
            }
            p->inventory[p->numberOfItems - 1] = NULL;
            p->numberOfItems--;
            return;
        }
    }
    printf("\n[ERROR] You don't have this item!\n");
}

void pickupItem(Player* p, char* itemName) {
    if (p->numberOfItems >= 5) {
        printf("\n[ERROR] Inventory full!\n");
        return;
    }

    for (int i = 0; i < p->currentRoom->itemCount; i++) {
        if (strcmp(p->currentRoom->items[i]->name, itemName) == 0) {
            p->inventory[p->numberOfItems++] = p->currentRoom->items[i];

            printf("\n[INFO] You picked up: %s\n", itemName);

            for (int j = i; j < p->currentRoom->itemCount - 1; j++) {
                p->currentRoom->items[j] = p->currentRoom->items[j + 1];
            }
            p->currentRoom->items[p->currentRoom->itemCount - 1] = NULL;
            p->currentRoom->itemCount--;

            return;
        }
    }
    printf("\n[ERROR] Item not found in this room!\n");
}

void showRoomItems(Room* room) {
    printf("\n[ITEMS IN ROOM]: ");
    if (room->itemCount == 0) {
        printf("(None)\n");
    }
    else {
        for (int i = 0; i < room->itemCount; i++) {
            printf("%s ", room->items[i]->name);
        }
        printf("\n");
    }
}

void go(Player* p, char direction[100]) {
    if (strcmp(direction, "north") == 0) {
        if (p->currentRoom->north != NULL) {
            p->currentRoom = p->currentRoom->north;
            printf("\n[INFO] You move north...\n");
        }
        else {
            printf("\n[ERROR] You can't go that way!\n");
        }
    }
    else if (strcmp(direction, "south") == 0) {
        if (p->currentRoom->south != NULL) {
            p->currentRoom = p->currentRoom->south;
            printf("\n[INFO] You move south...\n");
        }
        else {
            printf("\n[ERROR] You can't go that way!\n");
        }
    }
    else if (strcmp(direction, "east") == 0) {
        if (p->currentRoom->east != NULL) {
            p->currentRoom = p->currentRoom->east;
            printf("\n[INFO] You move east...\n");
        }
        else {
            printf("\n[ERROR] You can't go that way!\n");
        }
    }
    else if (strcmp(direction, "west") == 0) {
        if (p->currentRoom->west != NULL) {
            p->currentRoom = p->currentRoom->west;
            printf("\n[INFO] You move west...\n");
        }
        else {
            printf("\n[ERROR] You can't go that way!\n");
        }
    }
    else {
        printf("\n[ERROR] Invalid direction! Use: north, south, east, or west.\n");
    }
}

void showAvailableDirections(Room* room) {
    printf("\n[Available Directions]: ");
    if (room->north) printf("[North] ");
    if (room->south) printf("[South] ");
    if (room->east)  printf("[East] ");
    if (room->west)  printf("[West] ");
    printf("\n");
}

int main() {
    Item healthPack = { "Health Pack", "Restores your health." };
    Item keycard = { "Keycard", "Unlocks a door." };

    Room crashSite = { "Crash Site", "You wake up at the site of a spaceship crash.", NULL, NULL, NULL, NULL, {&healthPack}, 1 };
    Room alienRuins = { "Alien Ruins", "Ancient alien structures tower over you.", NULL, NULL, NULL, NULL, {&keycard}, 1 };
    Room mysteriousGateway = { "Mysterious Gateway", "A portal shimmers in the distance.", NULL, NULL, NULL, NULL, {NULL}, 0 };

    crashSite.north = &alienRuins;
    alienRuins.south = &crashSite;
    alienRuins.east = &mysteriousGateway;
    mysteriousGateway.west = &alienRuins;

    Player player = { &crashSite, {NULL}, 0 };

    char input[100], command[10], arg[50];

    printf("\n[COMMANDS]:\n");
    printf("- go [direction] (north, south, east, west)\n");
    printf("- inventory (view inventory)\n");
    printf("- pickup [item] (pick up an item)\n");
    printf("- drop [item number] (drop an item from inventory)\n");
    printf("- use [item] (use an item)\n");
    printf("- quit (exit the game)\n");

    while (1) {
        printf("\n----------------------------------");
        printf("\n[LOCATION]: %s", player.currentRoom->name);
        printf("\n[DESCRIPTION]: %s", player.currentRoom->description);
        showAvailableDirections(player.currentRoom);
        showRoomItems(player.currentRoom);
        printf("\n----------------------------------\n");

        printf("\nWhat would you like to do?\n");
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%s %s", command, arg);

        switch (command[0]) {
        case 'g': // go
            if (strcmp(command, "go") == 0) go(&player, arg);
            break;
        case 'i': // inventory
            if (strcmp(command, "inventory") == 0) showInventory(&player);
            break;
        case 'p': // pickup
            if (strcmp(command, "pickup") == 0) pickupItem(&player, arg);
            break;
        case 'd': // drop
            if (strcmp(command, "drop") == 0) {
                int itemIndex = atoi(arg) - 1;
                dropItem(&player, itemIndex);
            }
            break;
        case 'u': // use
            if (strcmp(command, "use") == 0) useItem(&player, arg);
            break;
        case 'q': // quit
            if (strcmp(command, "quit") == 0) {
                printf("\n[EXIT] Exiting the game... See you next time!\n");
                return 0;
            }
            break;
        default:
            printf("\n[ERROR] Invalid command!\n");
            break;
        }
    }
    return 0;
}
