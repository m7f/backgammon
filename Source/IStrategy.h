#ifndef NEW_BACKGAMMON_ISTRATEGY_H
#define NEW_BACKGAMMON_ISTRATEGY_H

#include <vector>

typedef std::vector<std::pair<int, int>> TMove;

class IStrategy {
public:
	virtual ~IStrategy(){};
	virtual TMove Move(const std::vector<int>& table, const std::vector<TMove>& possibleMoves) = 0;
};

#endif