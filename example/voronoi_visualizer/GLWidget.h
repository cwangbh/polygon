#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMainWindow>
#include <QString>
#include <vector>
#include <boost/polygon/polygon.hpp>
#include <boost/polygon/voronoi.hpp>
#include <QOpenGLWidget> // Changed from QtOpenGL/QGLWidget
#include <QtGui/QtGui>
#include <QOpenGLWidget>
#include <QtWidgets>
#include <QGridLayout> // Add for QGridLayout
#include <QHBoxLayout> // Add for QHBoxLayout
#include <QListWidget> // Add for QListWidget
#include <QCheckBox>   // Add for QCheckBox
#include <QFileDialog> // Add for QFileDialog
#include <QLabel>      // Add for QLabel
#include <QPushButton> // Add for QPushButton
#include <QDir>        // Add for QDir
using namespace boost::polygon;

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
  Q_OBJECT

public:
  explicit GLWidget(QMainWindow *parent = nullptr);

  void setPrimaryEdgesOnly(bool primary_edges_only);

  void setInternalEdgesOnly(bool internal_edges_only);

  int get_point_count();
  int get_segment_count();

  void initializeGL();

  QSize sizeHint() const;

  void build(const QString &file_path);

protected:
  void paintGL();

  void resizeGL(int width, int height);

  void timerEvent(QTimerEvent *e);

private:
  typedef double coordinate_type;
  typedef point_data<coordinate_type> point_type;
  typedef segment_data<coordinate_type> segment_type;
  typedef rectangle_data<coordinate_type> rect_type;
  typedef voronoi_builder<int> VB;
  typedef voronoi_diagram<coordinate_type> VD;
  typedef VD::cell_type cell_type;
  typedef VD::cell_type::source_index_type source_index_type;
  typedef VD::cell_type::source_category_type source_category_type;
  typedef VD::edge_type edge_type;
  typedef VD::cell_container_type cell_container_type;
  typedef VD::cell_container_type vertex_container_type;
  typedef VD::edge_container_type edge_container_type;
  typedef VD::const_cell_iterator const_cell_iterator;
  typedef VD::const_vertex_iterator const_vertex_iterator;
  typedef VD::const_edge_iterator const_edge_iterator;

  static constexpr std::size_t EXTERNAL_COLOR=1;

  void clear();

  void read_data(const QString &file_path);

  void update_brect(const point_type &point);

  void construct_brect();

  void color_exterior(const VD::edge_type *edge);

  void update_view_port();

  void draw_points();

  void draw_segments();

  void draw_vertices();

  void draw_edges();

  void clip_infinite_edge(    const edge_type &edge, std::vector<point_type> *clipped_edge);

  void sample_curved_edge(    const edge_type &edge,
    std::vector<point_type> *sampled_edge);

  point_type retrieve_point(const cell_type &cell);

  segment_type retrieve_segment(const cell_type &cell);

  point_type shift_;
  std::vector<point_type> point_data_;
  std::vector<segment_type> segment_data_;
  rect_type brect_;
  VB vb_;
  VD vd_;
  bool brect_initialized_;
  bool primary_edges_only_;
  bool internal_edges_only_;
  int point_count_;
  int segment_count_;
};

#endif // GLWIDGET_H
