#include <opencv2/highgui.hpp>
#include <vector>
class Color {
public:
    uint r, g, b;
    Color(uchar _r = 0, uchar _g = 0, uchar _b = 0);
};


class Node {
public:
    Color color;
    int pixel;
    bool hoja;
    int level;
    Node* hijo[8];
    Node(Color _color = Color(), int _pixel = 0, bool _hoja = false,
        int level = 0);
    ~Node();
    void agregar(int);
    void eliminar();
};

int get_index_level(uchar r, uchar g, uchar b, int level) {
  int index = 0;
  int mask = 0x80 >> level;
  if (r & mask) {
    index |= 4;
  }
  if (g & mask) {
    index |= 2;
  }
  if (b & mask) {
    index |= 1;
  }
  return index;
}

class OctreeQuantizer {
 private:
  int levels;
  Node *root;
  void push_colors(Node *root, std::vector<Color> &colors);

 public:
  OctreeQuantizer();
  ~OctreeQuantizer();
  void fill(cv::Mat &entry);
  void reduction();
  void reconstruction(cv::Mat &entry);
  void palette(cv::Mat &entry);
};

Color::Color(uchar _r, uchar _g, uchar _b) : r(_r), g(_g), b(_b) {}

Node::Node(Color _color, int _pixel, bool _hoja, int _level)
    : color(_color),
      pixel(_pixel),
      hoja(_hoja),
      level(_level) {
  for (int i = 0; i < 8; i++) hijo[i] = nullptr;
}

Node::~Node() {
  if (hoja) return;

  for (int i = 0; i < 8; i++) {
    delete hijo[i];
  }
}

void Node::agregar(int levels) {
  if (level >= levels) {
    hoja = true;
    return;
  }

  for (int i = 0; i < 8; i++) {
    hijo[i] = new Node(Color(), 0, false, level + 1);
    hijo[i]->agregar(levels);
  }
}

void Node::eliminar() {
  if (hijo[0]->hoja) {
    for (int i = 0; i < 8; i++) {
      pixel += hijo[i]->pixel;
      color.b += hijo[i]->color.b;
      color.g += hijo[i]->color.g;
      color.r += hijo[i]->color.r;
      delete hijo[i];
    }
    hoja = true;
    return;
  }

  for (int i = 0; i < 8; i++) {
    hijo[i]->eliminar();
  }
}

OctreeQuantizer::OctreeQuantizer()
    : levels(7), root(new Node(Color(), 0, false, 0)) {
  root->agregar(levels);
}

OctreeQuantizer::~OctreeQuantizer() { delete root; }

void OctreeQuantizer::fill(cv::Mat &entry) {
    int canal = entry.channels();
    int filas = entry.rows;
    int columnas = entry.cols * canal;

  if (entry.isContinuous()) {
    columnas *= filas;
    filas = 1;
  }

  uchar *p;
  Node *ruta;
  int i = 0;
  while (i < filas) {
    p = entry.ptr<uchar>(i);
    int j = 0;
    while (j < columnas) {
      uchar b = p[j], g = p[j + 1], r = p[j + 2];
      ruta = root;
      for (int level = 0; level < levels; level++) {
           ruta = ruta->hijo[get_index_level(p[j + 2], p[j + 1], p[j], level)];
      }

      ruta->color.b += p[j];
      ruta->color.g += p[j + 1];
      ruta->color.r += p[j + 2];

      ++(ruta->pixel);
      j += 3;
    }
    ++i;
  }
}

void OctreeQuantizer::reduction() {
  if (!levels) {
    return;
  }

  root->eliminar();
  --levels;
}

void OctreeQuantizer::reconstruction(cv::Mat &entry) {
  int canal = entry.channels();
  int filas = entry.rows;
  int columnas = entry.cols * canal;

  if (entry.isContinuous()) {
    columnas *= filas;
    filas = 1;
  }

  uchar *p;
  Node *ruta;
  int i = 0;
  while (i < filas) {
    p = entry.ptr<uchar>(i);
    int j = 0;
    while (j < columnas) {
      uchar b = p[j], g = p[j + 1], r = p[j + 2];
      ruta = root;
      for (int level = 0; level < levels; level++) {
        ruta = ruta->hijo[get_index_level(r, g, b, level)];
      }

      p[j] = (ruta->color.b) / (ruta->pixel);
      p[j + 1] = (ruta->color.g) / (ruta->pixel);
      p[j + 2] = (ruta->color.r) / (ruta->pixel);
      j += 3;
    }
    ++i;
  }
}

void OctreeQuantizer::palette(cv::Mat &entry) {
  std::vector<Color> colors;
  push_colors(root, colors);

  int canal = entry.channels();
  int filas = entry.rows;
  int columnas = entry.cols * canal;

  uchar *p;

  uint step_size = filas / colors.size();
  uint step = step_size;
  int c_i = 0;
  for (int i = 0; i < filas; ++i) {
    p = entry.ptr<uchar>(i);
    for (int j = 0; j < columnas; j += 3) {
      p[j] = colors[c_i].b;
      p[j + 1] = colors[c_i].g;
      p[j + 2] = colors[c_i].r;
    }
    if (i > step) {
      ++c_i;
      step += step_size;
    }
  }
}

void OctreeQuantizer::push_colors(Node *root, std::vector<Color> &colors) {
  if (root == nullptr) {
    return;
  }
  if (root->hoja && root->pixel) {
    colors.push_back(Color(root->color.r / root->pixel,
                           root->color.g / root->pixel,
                           root->color.b / root->pixel));
    return;
  }
  for (uint i = 0; i < 8; i++) {
    push_colors(root->hijo[i], colors);
  }
}
