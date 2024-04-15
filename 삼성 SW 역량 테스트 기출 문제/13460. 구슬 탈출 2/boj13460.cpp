#include <iostream>
#include <queue>
#include <string>

using namespace std;

int N, M;
string board[11];
pair<int, int> hole_pos;
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
bool visited[11][11][11][11];
pair<int, int> blue_pos;
pair<int, int> red_pos;
int ans = -1;

void bfs() {
  queue<pair<pair<int, int>, int>> red_q;
  queue<pair<int, int>> blue_q;

  red_q.emplace(make_pair(red_pos, 0));
  blue_q.emplace(blue_pos);

  while (!red_q.empty() && !blue_q.empty()) {
    pair<int, int> cur_r = red_q.front().first;
    int cnt = red_q.front().second;
    pair<int, int> cur_b = blue_q.front();

    visited[cur_r.first][cur_r.second][cur_b.first][cur_b.second] = true;

    red_q.pop();
    blue_q.pop();

    if (cnt >= 10) return;

    if (board[cur_r.first][cur_r.second] == 'O') {
      ans = cnt;
      return;
    }

    for (int i = 0; i < 4; i++) {
      int rnx = cur_r.first;
      int rny = cur_r.second;
      int bnx = cur_b.first;
      int bny = cur_b.second;

      int dr = 0, db = 0;

      // 갈 수 있는 지 먼저 확인 후 진행
      // 특이 사항: 범위 검사 필요 없음

      while (board[rnx + dx[i]][rny + dy[i]] != '#' && board[rnx][rny] != 'O') {
        rnx += dx[i];
        rny += dy[i];
        dr++;
      }

      // 갈 수 있는 지 먼저 확인 후 진행
      while (board[bnx + dx[i]][bny + dy[i]] != '#' && board[bnx][bny] != 'O') {
        bnx += dx[i];
        bny += dy[i];
        db++;
      }

      // 파란공 구멍들어감 -> out
      if (board[bnx][bny] == 'O') continue;

      if (board[rnx][rny] == 'O') {
        ans = cnt + 1;
        return;
      }

      // 같은 위치면 조정
      if (rnx == bnx && rny == bny) {
        if (dr > db) {
          rnx -= dx[i];
          rny -= dy[i];
        } else {
          bnx -= dx[i];
          bny -= dy[i];
        }
      }

      // 2. 이미 방문 -> out
      // 특이 사항:  움직이지 않았는지 확인할 필요 없음
      if (visited[rnx][rny][bnx][bny]) continue;

      red_q.emplace(make_pair(rnx, rny), cnt + 1);
      blue_q.emplace(make_pair(bnx, bny));
    }
  }
}

int main() {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);

  cin >> N >> M;

  // string 배열로 입력 -> 구멍, 공 위치 저장
  for (int i = 0; i < N; i++) {
    cin >> board[i];
    for (int j = 0; j < M; j++) {
      if (board[i][j] == 'R') {
        red_pos = make_pair(i, j);
        board[i][j] = '.';
      } else if (board[i][j] == 'B') {
        blue_pos = make_pair(i, j);
        board[i][j] = '.';
      }
    }
  }

  bfs();

  cout << ans;
}
