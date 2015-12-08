#ifndef EFFECT_H
#define EFFECT_H

class Effect {
public:
	virtual int getAtkNet() = 0;
	virtual int getDefNet() = 0;
	virtual ~Effect() = 0;
};

#endif
