#ifndef NEW_BACKGAMMON_RANDOMSTRATEGY_H
#define NEW_BACKGAMMON_RANDOMSTRATEGY_H

#include "IStrategy.h"

class RandomStrategy : public IStrategy {
public:
    RandomStrategy();
    ~RandomStrategy();
    TMove Move(const std::vector<int>& table, const std::vector<TMove>& possibleMoves) {
        if (possibleMoves.size() != 0) {
            return possibleMoves[rand() % possibleMoves.size()];
        }

        return{ {} };
	};
};

#endif
