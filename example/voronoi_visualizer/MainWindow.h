#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QDir>
#include <QString>
#include <QListWidget>
#include <QLabel>
#include "GLWidget.h"


class MainWindow : public QWidget
{
  Q_OBJECT

public:
  MainWindow()
  {
    glWidget_ = new GLWidget();
    QHBoxLayout *centralLayout = new QHBoxLayout;
    centralLayout->addWidget(glWidget_);
    centralLayout->addLayout(create_file_layout());
    setLayout(centralLayout);
    update_file_list();
    setWindowTitle(tr("Voronoi Visualizer"));
  }
  virtual ~MainWindow() = default;

private slots:
  void primary_edges_only();
  void internal_edges_only();
  void browse();
  void build();
  void print_scr();

private:
  QGridLayout *create_file_layout();
  void update_file_list();

  QDir file_dir_;
  QString file_name_;
  GLWidget *glWidget_;
  QListWidget *file_list_;
  QLabel *message_label_;
};

#endif // MAINWINDOW_H
