#include "main.h"

using std::cout;
using std::endl;
using std::cin;

int main(int argc, char **argv) {

    inv inventory;

    item test(0, 5, "Stick", "Cruelly torn from a tree.");

    cout << test.name() << endl;
    cout << test.desc() << endl << endl;

    cout << test.quantity() << endl;

    test.quantity = 23;

    cout << test.quantity() << endl;

    test.quantity += 3;

    cout << test.quantity() << endl;

    test.quantity -= 8;

    cout << test.quantity() << endl;

    test.quantity *= 2;

    cout << test.quantity() << endl;

    test.quantity /= 3;

    cout << test.quantity() << endl;

    if (test.quantity == 13) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }

    inventory.add_item(test);
    inventory.add_item(1, 1, "Box", "It's a cardboard box.");
    inventory.add_item(2, 0, "Car", "It's a decent car.", true);

    cout << inventory[89].name() << endl;
    cout << inventory[0].name() << ": " << inventory[0].quantity() << endl;
    cout << inventory[1].name() << ": " << inventory[1].quantity() << endl;
    cout << inventory[2].name() << ": " << inventory[2].quantity() << endl;

    inventory.remove_item(1);
    cout << inventory[1].name() << ": " << inventory[1].quantity() << endl;

    inventory.update();
    cout << inventory[2].name() << ": " << inventory[2].quantity() << endl;

    return 0;
}
