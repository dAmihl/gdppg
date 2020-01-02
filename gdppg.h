/* gdppg.h */

#ifndef GdPPG_H
#define GdPPG_H

#include "core/reference.h"
#include <PuzzGen.h>
#include "PPGNodeRef.h"

class GdPPG : public Reference {
    GDCLASS(GdPPG, Reference);

	void initGdPPG();

	Puzzle *currentPuzzle;
	PuzzleGenerator *puzzGen;
	T_PuzzleObjectList objects;
	T_PuzzleEventList events;
	T_PuzzleRuleList rules;

	Ref<PPGNodeRef> map_puzzlegraphnode_for_gdscript(PuzzleGraphNode *node);

protected:
    static void _bind_methods();

public:
	void generate_puzzle();
	void add_object(Variant objectData);
	String get_puzzle_textual_representation();
	Ref<PPGNodeRef> get_puzzle_graph_representation();

    GdPPG();
};

#endif // GdPPG_H
