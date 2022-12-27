
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{   
    int i, j;
    int game_running = 1, on_food = 0;
    int snakey, snakex, heady, headx, lasty, lastx;
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
        heady = rand() % (n_rows-1);
        headx = rand() % (n_cols-1);
        if (grid[heady][headx] != 0)
        {
            snake_body[0][0] = heady;
            snake_body[0][1] = headx;
        }  
    }
    while (grid[heady][headx] == 0);

    // Printing the initial step counter
    puts("");
    puts("Step count: 0");

    // Printing the initial state of the grid with
    // a border around it.
    // Using ANSI escape codes to color the snake
    // and fruits on the grid.
    grid[heady][headx] = 1;
    printf("#");
    for (j = 0; j < n_cols; j++)
        printf("###");
    printf("#");
    puts("");
    for (i = 0; i < n_rows; i++)
    {
        printf("#");
        for (j = 0; j < n_cols; j++)
            if (grid[i][j] > 0)
                printf("\e[31m%3d\e[0m", grid[i][j]);
            else if (grid[i][j] == 0)
                printf("\e[32m%3d\e[0m", grid[i][j]);
            else
                printf("   ");
        printf("#\n");
    }
    printf("#");
    for (j = 0; j < n_cols; j++)
        printf("###");
    printf("#\n");
    grid[heady][headx] = -1;

    // The loop of the game
    while(game_running)
    {   
        // Putting a newline before each step for ease of play
        // Also printing the number of the current step
        puts("");
        printf("Step count: %d\n", num_of_steps);

        // Now ask user for the direction, for the head movement
        // Ask again if user gives an undefined answer
        head_direction = ' ';
        while (head_direction == ' ')
        {
            printf("Which direction(L/R/U/D)? ");
            scanf(" %c", &head_direction);
            switch (head_direction)
            {
                case 'l':
                    headx--;
                    break;
                case 'r':
                    headx++;
                    break;
                case 'u':
                    heady--;
                    break;
                case 'd':
                    heady++;
                    break;

                case 'L':
                    headx--;
                    break;
                case 'R':
                    headx++;
                    break;
                case 'U':
                    heady--;
                    break;
                case 'D':
                    heady++;
                    break;

                default:
                    puts("Undefined direction. Try again.");
                    head_direction = ' ';
            }
        }

        // Moving body sections other than the head
        for (i = snake_len-1; i > 0; i--)
        {
            snakey = snake_body[i-1][0];
            snakex = snake_body[i-1][1];
            snake_body[i][0] = snakey;
            snake_body[i][1] = snakex;
        }
        // Then moving the head
        snake_body[0][0] = heady;
        snake_body[0][1] = headx; 

        // Checking if snake's head is on food or not.
        // Snake grows in the next step if it's head
        // touches the food.
        if (on_food == 1)
        {
            snake_len++;
            snake_body[snake_len-1][0] = lasty;
            snake_body[snake_len-1][1] = lastx;
            on_food = 0;

        }
        if (grid[heady][headx] == 0)
        {
            on_food = 1;
            lasty = snake_body[snake_len-1][0];
            lastx = snake_body[snake_len-1][1];
            food_count++;

            // Also game over if there are no food left on the grid
            if (total_food == food_count)
                game_running = 0;
        }

        // Testing for a wall crashing
        if (heady < 0 || heady > n_rows-1)
            game_running = 0;
        if (headx < 0 || headx > n_cols-1)
            game_running = 0;

        // Checking the grid for an overlap between snake's
        // head and the body.
        for (i = 1; i < snake_len; i++)
            if (heady == snake_body[i][0] && headx == snake_body[i][1])
                game_running = 0;


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
    printf("#");
    for (j = 0; j < n_cols; j++)
        printf("###");
    printf("#");
    puts("");
    for (i = 0; i < n_rows; i++)
    {
        printf("#");
        for (j = 0; j < n_cols; j++)
            if (grid[i][j] > 0)
                printf("\e[31m%3d\e[0m", grid[i][j]);
            else if (grid[i][j] == 0)
                printf("\e[32m%3d\e[0m", grid[i][j]);
            else
                printf("   ");
        printf("#\n");
    }
    printf("#");
    for (j = 0; j < n_cols; j++)
        printf("###");
    printf("#\n");

        // Removing the snake from the grid
        for (i = 0; i < snake_len; i++)
        {
            snakey = snake_body[i][0];
            snakex = snake_body[i][1];
            grid[snakey][snakex] = -1;
        }

        if (game_running)
            num_of_steps++;
         
    }

    // Game over. So a GAME OVER screen
    puts("");
    puts("GAME OVER");
    printf("You have survived for %d steps.\n", num_of_steps);
    printf("Your snake have grown to size %d.\n", snake_len);
    printf("You have eaten %d food(s).\n", food_count);
    printf("%d food(s) remained on the grid.\n", total_food-food_count);

    return 0;
}