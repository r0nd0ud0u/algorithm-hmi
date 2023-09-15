#include "gridgame.h"
#include "ui_gridgame.h"

#include <QDebug>
#include <deque>
#include <queue>

void
GridGame::InitGrid()
{
  for (auto& it : m_ButtonsList) {
    delete it;
    it = nullptr;
  }
  m_ButtonsList.clear();
  m_ButtonsList.resize(m_WidthButton * m_HeightButton);
  m_WallTable.resize(m_HeightButton * m_WidthButton, false);

  for (int x = 0; x < m_WidthButton; x++)
    for (int y = 0; y < m_HeightButton; y++) {
      QPushButton* button = new QPushButton("", this);
      button->setSizePolicy(QSizePolicy::MinimumExpanding,
                            QSizePolicy::MinimumExpanding);
      button->setEnabled(false);
      ui->gridLayout_2->addWidget(button, x, y);
      m_ButtonsList.at(x + m_WidthButton * y) = button;

      connect(button, &QPushButton::clicked, this, [=]() {
        actionOnButton(x, y); // Call the function which uses i and j here
      });
    }
}

GridGame::GridGame(QWidget* parent)
  : QWidget(parent)
  , ui(new Ui::GridGame)
{
  ui->setupUi(this);

  InitGrid();
}

GridGame::~GridGame()
{
  delete ui;
}

void
GridGame::ClearGrid(bool clearWall)
{
  for (int i = 0; i < m_ButtonsList.size(); i++) {
    if (clearWall || m_WallTable[i] == false)
      m_ButtonsList[i]->setStyleSheet("");
  }
  m_StatusButtons.firstClick = false;
  m_StatusButtons.secondClick = false;
  m_StatusButtons.startPos.x = -1;
  m_StatusButtons.startPos.y = -1;
  m_StatusButtons.endPos.x = -1;
  m_StatusButtons.endPos.y = -1;
  m_StatusButtons.firstPosition = -1;
  m_StatusButtons.secondPosition = -1;
}

void
GridGame::InitFirstClick(int y, int x)
{
  m_StatusButtons.firstClick = true;
  m_StatusButtons.startPos.x = x;
  m_StatusButtons.startPos.y = y;
  m_StatusButtons.firstPosition = x + m_WidthButton * y;
  m_ButtonsList.at(x + m_WidthButton * y)
    ->setStyleSheet("background-color : green");
}

void
GridGame::InitSecondClick(int y, int x)
{
  m_StatusButtons.secondClick = true;
  m_StatusButtons.endPos.x = x;
  m_StatusButtons.endPos.y = y;
  m_StatusButtons.secondPosition = x + m_WidthButton * y;
  m_ButtonsList.at(x + m_WidthButton * y)
    ->setStyleSheet("background-color : red");
}

void
GridGame::ExecuteAlgorithm()
{
  std::vector<bool> matrixFloodFill(m_WidthButton * m_HeightButton, false);
  switch (m_StatusButtons.curAlgo) {
    case algo::floodFill:
      floodFill(matrixFloodFill,
                m_StatusButtons.startPos.x,
                m_StatusButtons.startPos.y);
      break;
    case algo::voronoiFill: {
      voronoiFill(matrixFloodFill,
                  m_StatusButtons.startPos.x,
                  m_StatusButtons.startPos.y);
      break;
    }
    case algo::dijkstra:
      Dijkstra(m_StatusButtons.startPos.x,
               m_StatusButtons.startPos.y,
               m_StatusButtons.endPos.x,
               m_StatusButtons.endPos.y);
      break;
    default:
      break;
  }
}

void
GridGame::actionOnButton(int x, int y)
{
  if (m_StatusButtons.curMode == mode::work) {
    if (m_StatusButtons.firstClick == false &&
        m_StatusButtons.secondClick == false) {
      InitFirstClick(y, x);
    } else if (m_StatusButtons.firstClick == true &&
               m_StatusButtons.secondClick == false) {
      InitSecondClick(y, x);
      ExecuteAlgorithm();
    } else if (m_StatusButtons.firstClick == true &&
               m_StatusButtons.secondClick == true) {
      ClearGrid(false);
    }
  } else if (m_StatusButtons.curMode == mode::edit) {
    if (m_WallTable[idx(x, y)] == false) {
      m_WallTable[idx(x, y)] = true;
      m_ButtonsList.at(idx(x, y))->setStyleSheet("background-color : black");
    }
    else{
        m_WallTable[idx(x, y)] = false;
        m_ButtonsList.at(idx(x, y))->setStyleSheet("");
    }

  }
}

void
GridGame::floodFill(std::vector<bool>& matrix, int x, int y)
{
  if (x < 0 || x >= m_WidthButton || y < 0 || y >= m_HeightButton)
    return;
  if (matrix[x + y * m_WidthButton] == true)
    return;

  matrix[x + y * m_WidthButton] = true;
  if (!(x == m_StatusButtons.startPos.x && y == m_StatusButtons.startPos.y) &&
      !(x == m_StatusButtons.endPos.x && y == m_StatusButtons.endPos.y)) {
    m_ButtonsList.at(x + m_WidthButton * y)
      ->setStyleSheet("background-color : orange");
  }
  floodFill(matrix, x + 1, y);
  floodFill(matrix, x - 1, y);
  floodFill(matrix, x, y + 1);
  floodFill(matrix, x, y - 1);
}

int
GridGame::idx(int x, int y)
{
  return x + y * m_WidthButton;
}

std::vector<std::pair<int, int>>
GridGame::getNeigsOk(std::vector<bool>& matrix, int x, int y)
{
  std::vector<std::pair<int, int>> v;
  if (x < 0 || x >= m_WidthButton || y < 0 || y >= m_HeightButton)
    return v;
  if (y < m_HeightButton - 1 && matrix[idx(x, y + 1)] == false &&
      !m_WallTable[idx(x, y)])
    v.push_back(std::make_pair(x, y + 1));
  if (y > 0 && matrix[idx(x, y - 1)] == false && !m_WallTable[idx(x, y)])
    v.push_back(std::make_pair(x, y - 1));
  if (x < m_WidthButton - 1 && matrix[idx(x + 1, y)] == false &&
      !m_WallTable[idx(x, y)])
    v.push_back(std::make_pair(x + 1, y));
  if (x > 0 && matrix[idx(x - 1, y)] == false && !m_WallTable[idx(x, y)])
    v.push_back(std::make_pair(x - 1, y));
  return v;
}

void
GridGame::voronoiFill(std::vector<bool>& matrix, int x0, int y0)
{
  std::deque<std::pair<int, int>> q;
  q.push_back(std::make_pair(x0, y0));
  while (!q.empty()) {
    std::pair<int, int> p = q.front();
    q.pop_front();
    int x = p.first;
    int y = p.second;
    if (!(x == m_StatusButtons.startPos.x && y == m_StatusButtons.startPos.y) &&
        !(x == m_StatusButtons.endPos.x && y == m_StatusButtons.endPos.y)) {
      m_ButtonsList.at(x + m_WidthButton * y)
        ->setStyleSheet("background-color : yellow");
    }
    for (auto n : getNeigsOk(matrix, x, y)) {
      matrix[idx(n.first, n.second)] = true;
      q.push_back(n);
    }
  }
}

/**
 * @brief GridGame::ActivateButtons : clear the grid, set the current algo,
 * if dijsktra algo -> set random weight on each case
 * @param curAlgo : current algorithm
 */
void
GridGame::ActivateButtons(algo& curAlgo)
{
  ClearGrid(true);
  m_StatusButtons.curAlgo = curAlgo;
  for(auto& btn : m_ButtonsList)
      btn->setEnabled(true);

  if (curAlgo == algo::dijkstra) {
    m_WeightTable.resize(m_HeightButton * m_WidthButton);
    srand((unsigned)time(0));
    for (int i = 0; i < m_WeightTable.size(); i++) {
      m_WeightTable[i] = 1 + (rand() % 10);
      m_ButtonsList.at(i)->setText(QString::number(m_WeightTable[i]));
    }
  } else {
    for (int i = 0; i < m_WeightTable.size(); i++)
      m_ButtonsList.at(i)->setText("");
  }
}

void
GridGame::SetWidth(int value)
{
  m_WidthButton = value;
  InitGrid();
  ActivateButtons(m_StatusButtons.curAlgo);
};

void
GridGame::SetHeight(int value)
{
  m_HeightButton = value;
  InitGrid();
  ActivateButtons(m_StatusButtons.curAlgo);
};

/**
 * @brief GridGame::SetModeEdit : activate edit mode, disable green and red
 * points
 */
void
GridGame::SetModeEdit()
{
  m_StatusButtons.curMode = mode::edit;
  if (m_StatusButtons.firstPosition >= 0)
    m_ButtonsList[m_StatusButtons.firstPosition]->setStyleSheet("");
  if (m_StatusButtons.secondPosition >= 0)
    m_ButtonsList[m_StatusButtons.firstPosition]->setStyleSheet("");
};

/**
 * @brief GridGame::SetModeWork : active work mode
 */
void
GridGame::SetModeWork()
{
  m_StatusButtons.curMode = mode::work;
};

struct Node
{
  int x = -1;
  int y = -1;
  int weight = INT_MAX;
};

struct compare
{
  bool operator()(const Node& l, const Node& r) { return l.weight > r.weight; }
};

void
GridGame::Dijkstra(int x0, int y0, int x1, int y1)
{
  std::priority_queue<Node, std::vector<Node>, compare> Q;
  std::vector<int> parent(m_HeightButton * m_WidthButton, -1);

  std::vector<int> distance(
    m_WidthButton * m_HeightButton,
    INT_MAX); // // array to calculate the minimum distance for each node
  std::vector<bool> visited(m_WidthButton * m_HeightButton, false);
  distance[idx(x0, y0)] = 0;

  Node g;
  g.x = x0;
  g.y = y0;
  g.weight = 0;
  Q.push(g);
  while (!Q.empty()) {
    Node curG = Q.top();
    Q.pop();
    int index = idx(curG.x, curG.y);
    int curDist = curG.weight;
    visited.at(index) = true;
    for (auto n : getNeigsOk(visited, curG.x, curG.y)) {
      int v = idx(n.first, n.second);
      int weight = m_WeightTable[v];

      // If there is shorted path to v through u.
      if (distance[v] > curDist + weight) {
        // Updating distance of v
        distance[v] = curDist + weight;
        Node g;
        g.x = n.first;
        g.y = n.second;
        g.weight = distance[v];
        Q.push(g);
        parent[v] = index;
      }
    }
  }
  printf("Vertex \tDistance from Source\n"); // Print the result
  for (int i = 0; i < m_HeightButton * m_WidthButton; ++i)
    qDebug() << "index " << i << " "
             << distance[i]; // The shortest distance from source

  QString pathStr = "";
  int indexOut = idx(m_StatusButtons.endPos.x, m_StatusButtons.endPos.y);
  for (auto p = parent[indexOut]; p != -1; p = parent[p]) {
    pathStr += " <- " + QString::number(p);
    if (!(p == idx(m_StatusButtons.startPos.x, m_StatusButtons.startPos.y)) &&
        !(p == idx(m_StatusButtons.endPos.x, m_StatusButtons.endPos.y))) {
      m_ButtonsList.at(p)->setStyleSheet("background-color : yellow");
    }
  }

  qDebug() << pathStr;
}
