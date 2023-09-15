#ifndef GRIDGAME_H
#define GRIDGAME_H

#include "pathfinderpanel.h"

#include <QPushButton>
#include <QWidget>
#include <vector>

namespace Ui {
class GridGame;
}

struct Point
{
    int x = 0;
    int y= 0;
};

struct status
{
  bool firstClick = false;
  bool secondClick = false;
  Point startPos;
  Point endPos;
  int firstPosition = -1;
  int secondPosition = -1;
  algo curAlgo = algo::no_algo;
  mode curMode = mode::work;

};

class GridGame : public QWidget
{
  Q_OBJECT

public:
  explicit GridGame(QWidget* parent = nullptr);
  ~GridGame();

  void ClearGrid(bool clearWall);

  void InitFirstClick(int y, int x);

  void InitSecondClick(int y, int x);
  void ActivateButtons(algo& curAlgo);

  void ExecuteAlgorithm();
  void SetWidth(int value);
  void SetHeight(int value);
  void SetModeWork();
  void SetModeEdit();

  void InitGrid();

  private:
  int m_WidthButton = 4;
  int m_HeightButton = 4;
  std::vector<int> m_WeightTable;
  std::vector<bool> m_WallTable;

  Ui::GridGame* ui;
  std::vector<QPushButton*> m_ButtonsList;
  status m_StatusButtons;
  void actionOnButton(int x, int y);
  int idx(int x, int y);
  std::vector<std::pair<int,int>> getNeigsOk(std::vector<bool>& matrix,int x, int y);
  void floodFill(std::vector<bool>& matrix, int x, int y);
  void voronoiFill(std::vector<bool>& matrix,int x0, int y0);
  void Dijkstra(int x0, int y0,int x1, int y1);

};

#endif // GRIDGAME_H
