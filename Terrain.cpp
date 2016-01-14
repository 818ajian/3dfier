//
//  Terrain.cpp
//
//  Created by Hugo Ledoux on 19/10/15.
//  Copyright © 2015 Hugo Ledoux. All rights reserved.
//

#include "Terrain.h"


Terrain::Terrain (Polygon2* p, std::string pid, int simplification) : TIN(p, pid, simplification)
{}

std::string Terrain::get_obj_f(int offset) {
  std::stringstream ss;
  ss << "usemtl Terrain" << std::endl;
  ss << TopoFeature::get_obj_f(offset);
  return ss.str();
}

TopoClass Terrain::get_class() {
  return TERRAIN;
}

bool Terrain::is_hard() {
  return false;
}


std::string Terrain::get_citygml() {
  return "<EMPTY/>";
}

bool Terrain::lift() {
  std::stringstream ss;
  ss << bg::wkt(*(_p2));
  bg::read_wkt(ss.str(), _p3);
  //-- lift vertices to their median of lidar points
  TopoFeature::lift_vertices_boundary(0.5);
  return true;
}

bool Terrain::buildCDT() {
  int i = 0;
  for (auto& each : _nc) {
    if (each.empty() == false) {
      std::clog << "--not empty nc-- " << this->get_point_elevation(i) << std::endl;
      for (auto& n : each)
        std::clog << "|" << n;
      std::clog << std::endl;

    }
    i++;
  }

  getCDT(&_p3, _vertices, _triangles, _segments, _lidarpts);
  return true;
}
