struct PairHasher {
	size_t operator()(const pair<int, int>& p) const {
		return p.fst * 239017 + p.snd;
	}
};
