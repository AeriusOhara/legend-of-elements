#ifndef __FIELDMANAGER_H
#define __FIELDMANAGER_H
#include <vector>
#include "ui.h"

class fieldManager{
public:
	void swapBlocks(std::vector<block>& blocks, UI& ui);
	void pollField(std::vector<block>& blocks);
};

#endif