// problem link: https://leetcode.cn/problems/regions-cut-by-slashes/description/

#define SIDE 32

// the application of Union.
// the main thought:

// for a little square (1 * 1), it has 4 triangles:
//  - - 
// |\/|
// |/\|
//  - -
// 4 triangles are divided by 2 lines, so we can use a 2 * 2 matrix to represent the square.

// back to the problem. If we meet NOTHING, then the four triangles are CONNECTED.
// if we meet a '/', then the upper and left triangles are connected, and the right and down
// triangles are connected.
// if we meet a '\', then the upper and right triangles are connected, and the left and down
// triangles are connected.
// Furthermore, no matter what we meet, the upper triangle and the down triangle of 
// the square ABOVE are connected, and the lesft triangle and the right triangle of 
// the square LEFT are connected.

// Then, we can use Union to solve the problem.

int root[2 * SIDE][2 * SIDE];
int rcnt;

typedef struct Loc {
    int x;
    int y;
} Loc;

int calcRoot(int x, int y, int side) { return x * side + y; }

Loc calcLoc(int r, int side) {
    Loc loc;
    loc.x = r / side;
    loc.y = r % side;
    return loc;
}

void init(int side) {
    for (int i = 0; i < side; i++) {
        for (int j = 0; j < side; j++) {
            root[i][j] = calcRoot(i, j, side);
        }
    }
    rcnt = side * side;
}

int findRoot(int x, int y, int side) {
    if (root[x][y] != calcRoot(x, y, side)) {
        Loc loc = calcLoc(root[x][y], side);
        root[x][y] = findRoot(loc.x, loc.y, side);
    }
    return root[x][y];
}

void merge(int x1, int y1, int x2, int y2, int side) {
    int r1 = findRoot(x1, y1, side);
    int r2 = findRoot(x2, y2, side);
    if (r1 != r2) {
        Loc loc = calcLoc(r2, side);
        root[loc.x][loc.y] = r1;
        rcnt--;
    }
}

int isValid(int x, int y, int side) {
    return x >= 0 && x < side && y >= 0 && y < side;
}

int regionsBySlashes(char** grid, int gridSize) {
    int side = gridSize;
    init(2 * side);
    for (int i = 0; i < side; i++) {
        for (int j = 0; j < side; j++) {
            // printf("cur cnt: %d\n", rcnt);
            int leftx = 2 * i, lefty = 2 * j;
            int upx = 2 * i, upy = 2 * j + 1;

            int downx = 2 * i + 1, downy = 2 * j;
            int rightx = 2 * i + 1, righty = 2 * j + 1;
            
            int updownx = upx - 1, updowny = upy - 1;
            int leftrightx = leftx + 1, leftrighty = lefty - 1;
            if (grid[i][j] == ' ') {
                // in a tiny square.
                merge(leftx, lefty, downx, downy, 2 * side);
                merge(leftx, lefty, upx, upy, 2 * side);
                merge(leftx, lefty, rightx, righty, 2 * side);
            } else if (grid[i][j] == '/') {
                merge(leftx, lefty, upx, upy, 2 * side);
                merge(rightx, righty, downx, downy, 2 * side);
            }
            else if(grid[i][j] == '\\'){
                merge(leftx, lefty, downx, downy, 2 * side);
                merge(rightx, righty, upx, upy, 2 * side);
            }
            if (isValid(updownx, updowny, 2 * side)) {
                merge(updownx, updowny, upx, upy, 2 * side);
            }
            if (isValid(leftrightx, leftrighty, 2 * side)) {
                merge(leftrightx, leftrighty, leftx, lefty, 2 * side);
            }
        }
    }
    return rcnt;
}