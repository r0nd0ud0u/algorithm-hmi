#ifndef PATHFINDERPANEL_H
#define PATHFINDERPANEL_H

#include <QWidget>

namespace Ui {
class PathFinderPanel;
}

enum class algo
{
  no_algo,
  floodFill,
  voronoiFill,
  dijkstra
};

enum class mode
{
    work,
    edit
};

class PathFinderPanel : public QWidget
{
  Q_OBJECT

public:
  explicit PathFinderPanel(QWidget* parent = nullptr);
  ~PathFinderPanel();

signals:
  void SigAlgoSelected(algo& curAlgo);
  void SigChangeWidth(int width);
  void SigChangeHeight(int height);
  void SigModeWork();
  void SigModeEdit();

private:
  Ui::PathFinderPanel* ui;
  algo m_CurrentAlgo = algo::no_algo;

  void actionOnButton(int index);
  void changeWidth(int width);
  void changeHeight(int height);
  void setModeWork();
  void setModeEdit();
};

#endif // PATHFINDERPANEL_H
