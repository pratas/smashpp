#include <algorithm>
#include <fstream>
#include "tbl64.hpp"
#include "exception.hpp"
using namespace smashpp;

Table64::Table64 (u8 k_) : k(k_) {
  try { tbl.resize(4ull<<(k<<1u)); }    // 4<<2k = 4*2^2k = 4*4^k = 4^(k+1)
  catch (std::bad_alloc& b) { error("failed memory allocation."); }
}

void Table64::update (u32 ctx) {
  ++tbl[ctx];
}

u64 Table64::query (u32 ctx) const {
  return tbl[ctx];
}

void Table64::dump (ofstream& ofs) const {
  ofs.write((const char*) &tbl[0], tbl.size());
//  ofs.close();
}

void Table64::load (ifstream& ifs) const {
  ifs.read((char*) &tbl[0], tbl.size());
}

#ifdef DEBUG
u64 Table64::count_empty () const {
  return static_cast<u64>(std::count(begin(tbl), end(tbl), 0));
}

u64 Table64::max_tbl_val () const {
  return *std::max_element(begin(tbl), end(tbl));
}

void Table64::print () const {
  constexpr u8 context_width {12};
  cerr.width(context_width);  cerr<<std::left<<"Context";
  cerr << "Count\n";
  cerr << "-------------------\n";
  u32 i {0};
  for (const auto& c : tbl) {
    cerr.width(context_width);  cerr<<std::left<<i++;
    cerr << c << '\n';
  }
}
#endif