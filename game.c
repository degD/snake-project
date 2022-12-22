
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{   
    int i, j;
    int game_running = 1;
    int snakey, snakex, head_direction;
    int num_of_steps;
    int food_count, foody, foodx;
    int n_rows, n_cols;
    time_t t;

    // Seeding the rand() function
    srand((unsigned) time(&t));

    // Welcoming the player
    puts("SNAKE GROWTH GAME");
    sleep(1);

    // Getting grid length and height, then defining the grid
    printf("Enter grid row number: ");
    scanf("%d", &n_rows);
    printf("Enter grid column number: ");
    scanf("%d", &n_cols);
    char grid[n_rows][n_cols];

    // Generating food on grid, returning error if food
    // won't fit the grid
    printf("How many food do you want on grid? ");
    scanf("%d", &food_count);
    if (food_count > n_rows*n_cols-1)
    {
        puts("The amount of food cannot fit the grid.");
        return 1;
    }
    while (food_count > 0)
    {
        foody = rand() % (n_rows-1);
        foodx = rand() % (n_cols-1);
        if (grid[foody][foodx] == '0')
            continue;
        
        grid[foody][foodx] = '0';
        food_count--;
    }

    // Randomly selecting snake start location
    do 
    {
        snakey = rand() % (n_rows-1);
        snakex = rand() % (n_cols-1);
        if (grid[snakey][snakex] != '0')
            grid[snakey][snakex] = '1';     
    }
    while (grid[snakey][snakex] == '0');

    // Defining an array for snake.
    // Snake's head will be located using snakey, snakex coordinates.
    // The head will locomote by user input. By each step, all 
    // sections, other than the head, will move as the last directions
    // of the sections before them.
    char snake_body_movement[n_rows*n_cols-1];
    snake_body_movement[0] = '\0';

    // The loop of the game
    sleep(1);
    while(game_running)
    {   
        // Printing the grid
        for (i = 0; i < n_rows+2; i++)
        {
            for (j = 0; j < n_cols+2; j++)
            {
                
            }
        }
        
    }


}