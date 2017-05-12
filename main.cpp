#include <iostream>
#include "Minimax.h"
#include "Field.h"

int main()
{
    auto field = new Field(3);

    field->printField();

    auto minimax = new Minimax();

    std::cout << minimax->execute(field, 9, true, true);

    return 0;
}
