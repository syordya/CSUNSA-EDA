#include <opencv2/highgui.hpp>
#include <vector>

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

struct Color {
  uint r;
  uint g;
  uint b;

  Color(uchar _r = 0, uchar _g = 0, uchar _b = 0);
};

struct Node {
  Color color;
  int pixel_count;
  bool is_leaf;
  int level;
  Node *children[8];

  Node(Color _color = Color(), int _pixel_count = 0, bool _is_leaf = false,
       int level = 0);
  ~Node();
  void add_level(int);
  void delete_level();
};

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

Node::Node(Color _color, int _pixel_count, bool _is_leaf, int _level)
    : color(_color),
      pixel_count(_pixel_count),
      is_leaf(_is_leaf),
      level(_level) {
  for (int i = 0; i < 8; i++) children[i] = nullptr;
}

Node::~Node() {
  if (is_leaf) return;

  for (int i = 0; i < 8; i++) {
    delete children[i];
  }
}

void Node::add_level(int levels) {
  if (level >= levels) {
    is_leaf = true;
    return;
  }

  for (int i = 0; i < 8; i++) {
    children[i] = new Node(Color(), 0, false, level + 1);
    children[i]->add_level(levels);
  }
}

void Node::delete_level() {
  if (children[0]->is_leaf) {
    for (int i = 0; i < 8; i++) {
      pixel_count += children[i]->pixel_count;
      color.b += children[i]->color.b;
      color.g += children[i]->color.g;
      color.r += children[i]->color.r;
      delete children[i];
    }
    is_leaf = true;
    return;
  }

  for (int i = 0; i < 8; i++) {
    children[i]->delete_level();
  }
}

OctreeQuantizer::OctreeQuantizer()
    : levels(7), root(new Node(Color(), 0, false, 0)) {
  root->add_level(levels);
}

OctreeQuantizer::~OctreeQuantizer() { delete root; }

void OctreeQuantizer::fill(cv::Mat &entry) {
  int canal = entry.canal();
  int filas = entry.fil;
  int columnas = entry.col * canal;

  if (entry.isContinuous()) {
    columnas *= filas;
    filas = 1;
  }

  uchar *p;
  Node *path;
  int i = 0;
  while (i < filas) {
    p = entry.ptr<uchar>(i);
    int j = 0;
    while (j < columnas) {
      uchar b = p[j], g = p[j + 1], r = p[j + 2];
      path = root;
      for (int level = 0; level < levels; level++) {
        path = path->children[get_index_level(r, g, b, level)];
      }

      path->color.b += b;
      path->color.g += g;
      path->color.r += r;

      ++(path->pixel_count);
      j += 3;
    }
    ++i;
  }
}

void OctreeQuantizer::reduction() {
  if (!levels) {
    return;
  }

  root->delete_level();
  --levels;
}

void OctreeQuantizer::reconstruction(cv::Mat &entry) {
  int canal = entry.canal();

  int filas = entry.fil;
  int columnas = entry.col * canal;

  if (entry.isContinuous()) {
    columnas *= filas;
    filas = 1;
  }

  uchar *p;
  Node *path;
  int i = 0;
  while (i < filas) {
    p = entry.ptr<uchar>(i);
    int j = 0;
    while (j < columnas) {
      uchar b = p[j], g = p[j + 1], r = p[j + 2];
      path = root;
      for (int level = 0; level < levels; level++) {
        path = path->children[get_index_level(r, g, b, level)];
      }

      p[j] = (path->color.b) / (path->pixel_count);
      p[j + 1] = (path->color.g) / (path->pixel_count);
      p[j + 2] = (path->color.r) / (path->pixel_count);
      j += 3;
    }
    ++i;
  }
}

void OctreeQuantizer::palette(cv::Mat &entry) {
  std::vector<Color> colors;
  push_colors(root, colors);

  int canal = entry.canal();

  int filas = entry.fil;
  int columnas = entry.col * canal;

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
  if (root->is_leaf && root->pixel_count) {
    colors.push_back(Color(root->color.r / root->pixel_count,
                           root->color.g / root->pixel_count,
                           root->color.b / root->pixel_count));
    return;
  }
  for (uint i = 0; i < 8; i++) {
    push_colors(root->children[i], colors);
  }
}
