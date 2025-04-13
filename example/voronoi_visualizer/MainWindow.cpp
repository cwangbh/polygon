#include "MainWindow.h"



void MainWindow::primary_edges_only()
{
  glWidget_->setPrimaryEdgesOnly(true);
  glWidget_->setInternalEdgesOnly(false);
}

void MainWindow::internal_edges_only()
{
  glWidget_->setPrimaryEdgesOnly(false);
  glWidget_->setInternalEdgesOnly(true);
}

void MainWindow::browse()
{
  QString new_path = QFileDialog::getExistingDirectory(
      0, tr("Choose Directory"), file_dir_.absolutePath());
  if (new_path.isEmpty())
  {
    return;
  }
  file_dir_.setPath(new_path);
  update_file_list();
}

void MainWindow::build()
{
  file_name_ = file_list_->currentItem()->text();
  QString file_path = file_dir_.filePath(file_name_);
  message_label_->setText("Building...");
  glWidget_->build(file_path);

  QString status = QString("Loaded %1 points, %2 segments").arg(glWidget_->get_point_count()).arg(glWidget_->get_segment_count());
  message_label_->setText(status + "\nDouble click the item to build voronoi diagram:");
  setWindowTitle(tr("Voronoi Visualizer - ") + file_path);
}

void MainWindow::print_scr()
{
  if (!file_name_.isEmpty())
  {
    QImage screenshot = glWidget_->grabFramebuffer(); // Correct method name
    QString output_file = file_dir_.absolutePath() + tr("/") +
                          file_name_.left(file_name_.indexOf('.')) + tr(".png");
    screenshot.save(output_file, 0, -1);
  }
}

QGridLayout *MainWindow::create_file_layout()
{
  QGridLayout *file_layout = new QGridLayout;

  message_label_ = new QLabel("Double click item to build voronoi diagram:");

  file_list_ = new QListWidget();
  file_list_->connect(file_list_,
                      SIGNAL(itemDoubleClicked(QListWidgetItem *)),
                      this,
                      SLOT(build()));

  QCheckBox *primary_checkbox = new QCheckBox("Show primary edges only.");
  connect(primary_checkbox, SIGNAL(clicked()),
          this, SLOT(primary_edges_only()));

  QCheckBox *internal_checkbox = new QCheckBox("Show internal edges only.");
  connect(internal_checkbox, SIGNAL(clicked()),
          this, SLOT(internal_edges_only()));

  QPushButton *browse_button =
      new QPushButton(tr("Browse Input Directory"));
  connect(browse_button, SIGNAL(clicked()), this, SLOT(browse()));
  browse_button->setMinimumHeight(50);

  QPushButton *print_scr_button = new QPushButton(tr("Make Screenshot"));
  connect(print_scr_button, SIGNAL(clicked()), this, SLOT(print_scr()));
  print_scr_button->setMinimumHeight(50);

  file_layout->addWidget(message_label_, 0, 0);
  file_layout->addWidget(file_list_, 1, 0);
  file_layout->addWidget(primary_checkbox, 2, 0);
  file_layout->addWidget(internal_checkbox, 3, 0);
  file_layout->addWidget(browse_button, 4, 0);
  file_layout->addWidget(print_scr_button, 5, 0);

  return file_layout;
}

void MainWindow::update_file_list()
{
  QFileInfoList list = file_dir_.entryInfoList();
  file_list_->clear();
  if (file_dir_.count() == 0)
  {
    return;
  }
  QFileInfoList::const_iterator it;
  for (it = list.begin(); it != list.end(); it++)
  {
    file_list_->addItem(it->fileName());
  }
  file_list_->setCurrentRow(0);
}
