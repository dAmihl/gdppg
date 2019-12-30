/* gdppg.h */

#ifndef GdPPG_H
#define GdPPG_H

#include "core/reference.h"
#include <PuzzGen.h>

class GdPPG : public Reference {
    GDCLASS(GdPPG, Reference);

	void initGdPPG();

	Puzzle *currentPuzzle;
	PuzzleGenerator *puzzGen;
	T_PuzzleObjectList objects;
	T_PuzzleEventList events;
	T_PuzzleRuleList rules;

protected:
    static void _bind_methods();

public:
	void generate_puzzle();
	void add_object(Variant objectData);
	String get_puzzle_textual_representation();

    GdPPG();
};

#endif // GdPPG_H
