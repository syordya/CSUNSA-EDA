class Point {
  constructor(x, y) {
    this.x = x;
    this.y = y;
  }
}

class Rectangle {
  constructor(x, y, w, h) {
    this.x = x;
    this.y = y;
    this.w = w;
    this.h = h;
  }

  contains(point) {
    return (point.x >= this.x - this.w &&
      point.x < this.x + this.w &&
      point.y >= this.y - this.h &&
      point.y < this.y + this.h);
  }

  intersects(range) {
    return !(range.x - range.w > this.x + this.w ||
      range.x + range.w < this.x - this.w ||
      range.y - range.h > this.y + this.h ||
      range.y + range.h < this.y - this.h);
  }
}

class QuadTree {
  constructor(boundary, n) {
    this.boundary = boundary;
    this.capacity = n;
    this.points = [];
    this.divided = false;
  }

  subdivide() {
    let x = this.boundary.x;
    let y = this.boundary.y;
    let w = this.boundary.w;
    let h = this.boundary.h;

    let ne = new Rectangle(x + w / 2, y + h / 2, w / 2, h / 2);
    this.NE = new QuadTree(ne, this.capacity);
    let nw = new Rectangle(x - w / 2, y + h / 2, w / 2, h / 2);
    this.NO = new QuadTree(nw, this.capacity);
    let se = new Rectangle(x + w / 2, y - h / 2, w / 2, h / 2);
    this.SE = new QuadTree(se, this.capacity);
    let sw = new Rectangle(x - w / 2, y - h / 2, w / 2, h / 2);
    this.SO = new QuadTree(sw, this.capacity);

    this.divided = true;
  }

  insert(point) {

    if (!this.boundary.contains(point)) {
      return;
    }

    if (this.points.length < this.capacity) {
      this.points.push(point);

    } else {
      if (!this.divided) {
        this.subdivide();
      }
      if (this.NE.insert(point)) {
        return;
      } else if (this.NO.insert(point)) {
        return;
      } else if (this.SE.insert(point)) {
        return;
      } else if (this.SO.insert(point)) {
        return;
      }
    }
  }

query(range, found) {

    if (!range.intersects(this.boundary)) {
      return found;
    }

    for (let p of this.points) {
      if (range.contains(p)) {
        found.push(p);
        count++;
      }
    }
    if (this.divided) {
      this.NO.query(range, found);
      this.NE.query(range, found);
      this.SO.query(range, found);
      this.SE.query(range, found);
    }

    return found;
  }

  show() {
    stroke(255);
    noFill();
    strokeWeight(1);
    rectMode(CENTER);
    rect(this.boundary.x, this.boundary.y, this.boundary.w * 2, this.boundary.h * 2);

    if (this.divided) {
      this.NE.show();
      this.NO.show();
      this.SE.show();
      this.SO.show();
    }

    for (let p of this.points) {
      strokeWeight(2);
      point(p.x, p.y);
    }
  }
}