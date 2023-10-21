#pragma once

enum SnakeEntity {
    SNAKE,
    FOOD,
    WALL
};

/*SNAKE*/
enum SnakeProperties 
{
    SNAKE_PART,
    SNAKE_DIRECTION
};

enum SnakePart
{
    SNAKE_BODY,
    SNAKE_HEAD,
    SNAKE_TAIL
};

enum SNAKE_DIRECTION
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

/*FOOD*/
enum FoodProperties
{
    FOOD_TYPE
}

enum FoodType
{
    REGULAR,
    BONUS,
    SUPER
}
/*WALL*/

