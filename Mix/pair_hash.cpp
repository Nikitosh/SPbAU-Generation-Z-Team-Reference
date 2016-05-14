struct MyHash {
  size_t operator()(const pair<int,int> &t) const {
    return t.first * 239017 + t.second;
  }
};
