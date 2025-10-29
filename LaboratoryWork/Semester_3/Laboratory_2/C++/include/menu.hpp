#pragma once
#include "../src/utils/menu.cpp"

enum class MenuOptions {
    Exit,
    ArithmeticExpression,
    InteractionWithSet,
    SetPartition,
    Subarrays,
    CheckBalance,
    ConvolutionMethod,
    LRUCache
};

void startMenu();