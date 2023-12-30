typedef enum 
{
    dailyuse,
    fresh,
    food
} Category;
typedef struct 
{
    char name[100];
    Category category;
    int quantity;
} Commodity;