#define W 10
#define H 10

#define UP    0
#define RIGHT 1
#define DOWN  2
#define LEFT  3

String Letters = "ABCDEFGHIJ";
char grid[W][H];

void parseAndPlace(String input) {

  // Get prefix (TASK / NOT)
  int colon = input.indexOf(':');
  if (colon == -1) return;

  String type = input.substring(0, colon);
  String data = input.substring(colon + 1);

  // Remove ending dot
  if (data.endsWith(".")) {
    data.remove(data.length() - 1);
  }

  int start = 0;
  int count = 0;   // coordinate index


  while (start < data.length()) {

    int s1 = data.indexOf('/', start);
    int s2 = data.indexOf(',', start);

    int sep;

    if (s1 == -1) sep = s2;
    else if (s2 == -1) sep = s1;
    else sep = min(s1, s2);

    if (sep == -1) sep = data.length();

    String coord = data.substring(start, sep);

    // ----- Convert -----

    char letter = coord.charAt(0);
    int number  = coord.substring(1).toInt();

    int x = Letters.indexOf(letter);
    int y = number - 1;

    // ----- Decide what to place -----

    char symbol = 'O'; // default empty

    if (type == "NOT") {
      symbol = 'X';          // walls
    }

    else if (type == "TASK") {

      if (count == 0) symbol = 'R';   // Robot
      if (count == 1) symbol = 'G';   // Goal
    }


    // ----- Place on grid -----

    if (x >= 0 && x < W && y >= 0 && y < H) {
      grid[x][y] = symbol;
    }
    count++;
    start = sep + 1;
  }
}


int dx[4] = { 0, 1, 0, -1 }; // x change
int dy[4] = { -1, 0, 1, 0 }; // y change, y+ down




// ---------------- BFS MEMORY ----------------

bool visited[W][H];


// For path reconstruction
struct Prev {
  byte x;
  byte y;
};

Prev prev[W][H];


// Queue
struct Node {
  byte x;
  byte y;
};

Node queue[W * H];
int qStart, qEnd;


// -------------------------------------------


void findStartGoal(int &sx, int &sy, int &gx, int &gy) {

  for (int x = 0; x < W; x++) {
    for (int y = 0; y < H; y++) {

      if (grid[x][y] == 'R') {
        sx = x;
        sy = y;
      }

      if (grid[x][y] == 'G') {
        gx = x;
        gy = y;
      }
    }
  }
}


// -------------------------------------------
// BFS WITHOUT DIRECTIONS
// -------------------------------------------

bool findGridPath(
  int sx, int sy,
  int gx, int gy,
  byte pathX[],
  byte pathY[],
  int &pathLen
) {

  // Clear visited
  for (int x = 0; x < W; x++)
    for (int y = 0; y < H; y++)
      visited[x][y] = false;


  qStart = 0;
  qEnd   = 0;


  // Start
  queue[qEnd++] = { (byte)sx, (byte)sy };
  visited[sx][sy] = true;

  prev[sx][sy] = { 255, 255 }; // start marker


  // BFS
  while (qStart < qEnd) {

    Node cur = queue[qStart++];


    // Goal
    if (cur.x == gx && cur.y == gy) break;


    for (int d = 0; d < 4; d++) {

      int nx = cur.x + dx[d];
      int ny = cur.y + dy[d];


      if (nx < 0 || nx >= W || ny < 0 || ny >= H)
        continue;

      if (grid[nx][ny] == 'X')
        continue;

      if (visited[nx][ny])
        continue;


      visited[nx][ny] = true;

      prev[nx][ny] = { cur.x, cur.y };

      queue[qEnd++] = { (byte)nx, (byte)ny };
    }
  }


  // No path
  if (!visited[gx][gy]) return false;


  // -------- Rebuild path --------

  pathLen = 0;

  int cx = gx;
  int cy = gy;


  while (!(cx == sx && cy == sy)) {

    pathX[pathLen] = cx;
    pathY[pathLen] = cy;

    Prev p = prev[cx][cy];

    cx = p.x;
    cy = p.y;

    pathLen++;
  }


  // Add start
  pathX[pathLen] = sx;
  pathY[pathLen] = sy;
  pathLen++;


  // Reverse path
  for (int i = 0; i < pathLen / 2; i++) {

    byte tx = pathX[i];
    byte ty = pathY[i];

    pathX[i] = pathX[pathLen - 1 - i];
    pathY[i] = pathY[pathLen - 1 - i];

    pathX[pathLen - 1 - i] = tx;
    pathY[pathLen - 1 - i] = ty;
  }


  return true;
}


// -------------------------------------------
// PATH → COMMANDS
// -------------------------------------------

void pathToCommands(
  byte pathX[],
  byte pathY[],
  int len,
  int startDir,
  String &out
) {

  out = "";
  int dir = startDir;

  for (int i = 1; i < len; i++) {

    int dxm = pathX[i] - pathX[i - 1];
    int dym = pathY[i] - pathY[i - 1];

    int neededDir;

    if (dxm == 1)       neededDir = RIGHT;
    else if (dxm == -1) neededDir = LEFT;
    else if (dym == 1)  neededDir = DOWN;
    else if (dym == -1) neededDir = UP;

    // Rotate to needed direction
    while (dir != neededDir) {

      // Decide shortest turn
      int diff = (neededDir - dir + 4) % 4;

      if (diff == 1) {       // one step clockwise
        out += 'R';
        dir = (dir + 1) % 4;
      }
      else if (diff == 3) {  // one step counter-clockwise
        out += 'L';
        dir = (dir + 3) % 4;
      }
      else if (diff == 2) {  // 180 degrees
        out += "RR";
        dir = (dir + 2) % 4;
      }
    }

    // Move forward
    out += 'F';
  }
}



// -------------------------------------------

void setup() {

  Serial.begin(9600);
  delay(1000);

  // Init grid
  for (int x = 0; x < W; x++)
    for (int y = 0; y < H; y++)
      grid[x][y] = 'O';


  String TASK = "TASK:A1/J8";
  String NOT  = "NOT:B1.";
  while(true){
  if (Serial.available()){
    TASK=Serial.readStringUntil('\n');
    TASK.trim();
    NOT=Serial.readStringUntil('\n');
    NOT.trim();
    break;
  }}
  Serial.println(TASK);
  Serial.println(NOT);
  parseAndPlace(TASK);
  parseAndPlace(NOT);

  int sx, sy, gx, gy;

  findStartGoal(sx, sy, gx, gy);


  byte pathX[W * H];
  byte pathY[W * H];

  int pathLen;


for (int y = 0; y < H; y++) {
  for (int x = 0; x < W; x++) {

    Serial.print(grid[x][y]);
    Serial.print(" ");
  }
  Serial.println();
}

  if (!findGridPath(sx, sy, gx, gy, pathX, pathY, pathLen)) {

    Serial.println("No path!");
    return;
  }


  String commands;

  int startDir = UP;


  pathToCommands(pathX, pathY, pathLen, startDir, commands);


  Serial.print("Commands: ");
  Serial.println(commands);
}


void loop() {
}

