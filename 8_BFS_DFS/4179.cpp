#include <bits/stdc++.h>

using namespace std;

int dx[4] = {0, -1, 0, 1};
int dy[4] = {1, 0, -1, 0};

char oper[1001][1001];

int Jboard[1001][1001];
int Jvis[1001][1001];

int Fboard[1001][1001];
int Fvis[1001][1001];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int r, c;
  // row, column
  cin >> r >> c;
  queue<pair<int, int>> J; // 지훈
  queue<pair<int, int>> F; // 불

  // 지훈과 불이 안 방문했는 곳은 -1로 처리
  for (int i = 0; i < r; i++) {
    fill(Jvis[i], Jvis[i] + c, -1);
    fill(Fvis[i], Fvis[i] + c, -1);
  }
  // 초기 세팅
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      cin >> oper[i][j];
      // 벽 == -1 (지훈과 불이 가지 못함)
      if (oper[i][j] == '#') {
        Jboard[i][j] = -1;
        Fboard[i][j] = -1;
      }
      // 갈 수 있는 곳은 board[i][j] = 0으로 그대로 둠
      else if (oper[i][j] == '.') {
        continue;
      }
      // 진수의 시작점 및 큐 추가
      else if (oper[i][j] == 'J') {
        J.push({i, j});
        Jvis[i][j] = 0;
      }
      // 불의 시작점 및 큐에 추가
      else {
        F.push({i, j});
        Fvis[i][j] = 0;
        // 지훈은 불의 시작점은 가지 못함
        Jboard[i][j] = -1;
      }
    }
  }
  // 지훈
  while (!J.empty()) {
    auto curr = J.front();
    J.pop();
    for (int i = 0; i < 4; i++) {
      int nx = curr.first + dx[i];
      int ny = curr.second + dy[i];
      if (nx < 0 or nx >= r or ny < 0 or ny >= c)
        continue;
      // 방문하지 않았고 갈 수 있다면
      if (Jvis[nx][ny] == -1 && Jboard[nx][ny] != -1) {
        J.push({nx, ny});
        Jvis[nx][ny] = Jvis[curr.first][curr.second] + 1;
      }
    }
  }
  // 불
  while (!F.empty()) {
    auto curr = F.front();
    F.pop();
    for (int i = 0; i < 4; i++) {
      int nx = curr.first + dx[i];
      int ny = curr.second + dy[i];
      if (nx < 0 or nx >= r or ny < 0 or ny >= c)
        continue;
      // 방문하지 않았고 갈 수 있다면
      if (Fvis[nx][ny] == -1 && Fboard[nx][ny] != -1) {
        F.push({nx, ny});
        Fvis[nx][ny] = Fvis[curr.first][curr.second] + 1;
      }
    }
  }

  int result = 0, temp = 0;
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      // 가장자리면에서
      if (i == 0 || j == 0 || i == r - 1 || j == c - 1)
        // 지훈이과 불이 갈 수 있는 곳이고 지훈이 더 빨리 도착하고
        // 이전 도착 시간보다 빠르다면 탈출가능 (최초 등록시)
        if (temp == 0 && Jboard[i][j] == 0 && Fboard[i][j] == 0 &&
            Jvis[i][j] < Fvis[i][j]) {
          //위 조건 만족시 탈출은 가능
          result = Jvis[i][j] + 1;
          temp = 1;
        }
        // 이전의 값보다 현재의 값이 작다면 바꾸어라 (최초 등록 아닐시)
        else if (temp == 1 && Jboard[i][j] == 0 && Fboard[i][j] == 0 &&
                 Jvis[i][j] < Fvis[i][j] && result > Jvis[i][j] + 1) {
          result = Jvis[i][j] + 1;
        }
    }
  }
  // 가장자리에 지훈이 있으면
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if (i == 0 || j == 0 || i == r - 1 || j == c - 1)
        if (Jvis[i][j] == 0)
          result = Jvis[i][j] + 1;
    }
  }
  if (result == 0)
    cout << "IMPOSSIBLE";
  else
    cout << result;

  return 0;
}
