#include "pathfinderpanel.h"
#include "ui_pathfinderpanel.h"

PathFinderPanel::PathFinderPanel(QWidget* parent)
  : QWidget(parent)
  , ui(new Ui::PathFinderPanel)
{
  ui->setupUi(this);
  ui->algo_combobox->addItem("");
  ui->algo_combobox->addItem("Flood fill");
  ui->algo_combobox->addItem("Voronoi fill");
  ui->algo_combobox->addItem("Dijkstra");

  connect(ui->algo_combobox,
          QOverload<int>::of(&QComboBox::currentIndexChanged),
          this,
          [=](int index) {
            actionOnButton(index); // Call the function which uses i and j here
          });
  connect(ui->spinBox_height,
          QOverload<int>::of(&QSpinBox::valueChanged),
          this,
          [=](int value) {
            changeHeight(value); // Call the function which uses i and j here
          });
  connect(ui->spinBox_width,
          QOverload<int>::of(&QSpinBox::valueChanged),
          this,
          [=](int value) {
            changeWidth(value); // Call the function which uses i and j here
          });
  connect(ui->radioButton_work,
          &QRadioButton::toggled,
          this,
          [=]() {
            setModeWork(); // Call the function which uses i and j here
          });
  connect(ui->radioButton_edit,
          &QRadioButton::toggled,
          this,
          [=]() {
            setModeEdit(); // Call the function which uses i and j here
          });
}

PathFinderPanel::~PathFinderPanel()
{
  delete ui;
}

void
PathFinderPanel::actionOnButton(int index)
{
  algo curAlgo = static_cast<algo>(index);
  emit SigAlgoSelected(curAlgo);


}

void
PathFinderPanel::changeWidth(int width)
{
  emit SigChangeWidth(width);
}

void
PathFinderPanel::changeHeight(int height)
{
  emit SigChangeHeight(height);
}

void
PathFinderPanel::setModeWork()
{
    if (ui->radioButton_work->isChecked()) {
    ui->algo_combobox->setEnabled(true);
    ui->spinBox_width->setEnabled(false);
    ui->spinBox_height->setEnabled(false);
    emit SigModeWork();
  }

}

void
PathFinderPanel::setModeEdit()
{
  if (ui->radioButton_edit->isChecked()) {
    ui->algo_combobox->setEnabled(false);
    ui->spinBox_width->setEnabled(true);
    ui->spinBox_height->setEnabled(true);
    emit SigModeEdit();
  }

}
