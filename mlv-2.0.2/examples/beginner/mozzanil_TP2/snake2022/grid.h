#define NBL 22
#define NBC 37

void debug(char Mat[NBL][NBC],int l,int c);
int compute_size(int width, int height);
void draw_grid(char grid[NBL][NBC]);

enum Element {WALL, EMPTY, FRUIT};

