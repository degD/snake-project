
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{   
    int i, j;
    int game_running = 1, on_food = 0;
    int snakey, snakex, lasty, lastx;
    int num_of_steps = 1, snake_len = 1;
    int total_food, food_count = 0, foody, foodx;
    int n_rows, n_cols;
    char head_direction;
    time_t t;

    // Seeding the rand() function
    srand((unsigned) time(&t));

    // Welcoming the player
    puts("SNAKE GROWTH GAME");

    // Getting grid length and height, then defining the grid
    printf("Enter grid row number: ");
    scanf("%d", &n_rows);
    printf("Enter grid column number: ");
    scanf("%d", &n_cols);
    int grid[n_rows][n_cols];

    // Clearing the grid before the use
    for (i = 0; i < n_rows; i++)
        for (j = 0; j < n_cols; j++)
            grid[i][j] = -1;

    // Defining an array for snake.
    // Snake's head will be located using snakey, snakex coordinates.
    // The head will locomote by user input. By each step, all 
    // sections, other than the head, will move to the coordinates 
    // of sections before them.
    int snake_body[n_rows*n_cols][2];

    // Generating food on grid, asks user to retry if
    // amount of food be more than the size of the grid.
    while (food_count == 0)
    {
        printf("How many food do you want on grid? ");
        scanf("%d", &food_count);
        if (food_count > n_rows*n_cols-1)
        {
            puts("The amount of food cannot fit the grid.");
            puts("Please try again.");
            food_count = 0;
        }
    }
    total_food = food_count;
    while (food_count > 0)
    {
        foody = rand() % (n_rows-1);
        foodx = rand() % (n_cols-1);
        if (grid[foody][foodx] == 0)
            continue;
        
        grid[foody][foodx] = 0;
        food_count--;
    }

    // Randomly selecting snake start location
    do 
    {
        snakey = rand() % (n_rows-1);
        snakex = rand() % (n_cols-1);
        if (grid[snakey][snakex] != 0)
        {
            snake_body[0][0] = snakey;
            snake_body[0][1] = snakex;
        }  
    }
    while (grid[snakey][snakex] == 0);

    // The loop of the game
    while(game_running)
    {   
        // Putting a newline before each step for ease of play
        // Also printing the number of the current step
        puts("");
        printf("Step number: %d\n", num_of_steps);

        // Add snake body to grid
        for (i = 0; i < snake_len; i++)
        {
            snakey = snake_body[i][0];
            snakex = snake_body[i][1];
            grid[snakey][snakex] = i+1;
        }

        // Printing the grid. Also adds a border around the grid.
        // First, prints the top border. Then prints left
        // and right border sections while printing rows of the grid.
        // Finally, prints the bottom of the border.
        for (j = 0; j < n_cols+2; j++)
            printf("X");
        puts("");
        for (i = 0; i < n_rows; i++)
        {
            printf("X");
            for (j = 0; j < n_cols; j++)
                if (grid[i][j] != -1)
                    printf("%d", grid[i][j]);
                else
                    printf(" ");
            printf("X\n");
        }
        for (j = 0; j < n_cols+2; j++)
            printf("X");
        puts("");

        // Removing the snake from the grid
        for (i = 0; i < snake_len; i++)
        {
            snakey = snake_body[i][0];
            snakex = snake_body[i][1];
            grid[snakey][snakex] = -1;
        }

        // Moving body sections other than the head
        for (i = snake_len-1; i > 0; i--)
        {
            snakey = snake_body[i-1][0];
            snakex = snake_body[i-1][1];
            snake_body[i][0] = snakey;
            snake_body[i][1] = snakex;
        }        

        // Now ask user for the direction, for the head movement
        printf("Which direction(L/R/U/D)? ");
        scanf(" %c", &head_direction);
        switch (head_direction)
        {
            case 'l':
                snake_body[0][1]--;
                break;
            case 'r':
                snake_body[0][1]++;
                break;
            case 'u':
                snake_body[0][0]--;
                break;
            case 'd':
                snake_body[0][0]++;
                break;
        }

        // Testing for a wall crashing
        snakey = snake_body[0][0];
        snakex = snake_body[0][1];
        if (snakey < 0 || snakey > n_rows-1)
            game_running = 0;
        if (snakex < 0 || snakex > n_cols-1)
            game_running = 0;

        // Checking if snake's head is on food or not.
        // Snake grows in the next step if it's head
        // touches the food.
        if (on_food == 0)
        {
            snakey = snake_body[0][0];
            snakex = snake_body[0][1];
            if (grid[snakey][snakex] == 0)
            {
                on_food = 1;
                lasty = snake_body[snake_len-1][0];
                lastx = snake_body[snake_len-1][1];
            }
        }
        else
        {
            snake_len++;
            snake_body[snake_len-1][0] = lasty;
            snake_body[snake_len-1][1] = lastx;
            on_food = 0;

            // Also game over if there are no food left on the grid
            if (total_food == snake_len-1)
                game_running = 0;
        }

        if (game_running)
            num_of_steps++;
    }

    // Game over. So a GAME OVER screen
    puts("");
    puts("GAME OVER");
    printf("You have survived for %d steps.\n", num_of_steps);
    printf("Your snake have grown to size %d.\n", snake_len);
    printf("You have eaten %d food(s).\n", snake_len-1);
    printf("%d food(s) remained on the grid.\n", total_food-(snake_len-1));

    return 0;
}