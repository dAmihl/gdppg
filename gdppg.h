/* gdppg.h */

#ifndef GdPPG_H
#define GdPPG_H

#include "core/reference.h"
#include <PuzzGen.h>
#include "PPGNodeRef.h"
#include "PPGUpdateListener.h"

class GdPPG : public Reference {
    GDCLASS(GdPPG, Reference);

	void initGdPPG();

	Puzzle *currentPuzzle;
	PuzzleGenerator *puzzGen;
	T_PuzzleObjectList objects;
	T_PuzzleEventList events;
	T_PuzzleRuleList rules;
	HashMap<String, PuzzleEvent*> events_map;
	HashMap<String, PuzzleObject *> objects_map;
	HashMap<String, PuzzleState *> states_map;

	Ref<PPGNodeRef> map_puzzlegraphnode_for_gdscript(PuzzleGraphNode *node);

	PPGUpdateListener* update_listener;

protected:
    static void _bind_methods();

public:
	void generate_puzzle();
	void add_object(Variant objectData);
	void add_rule(Variant ruleData);
	String get_puzzle_textual_representation();
	Ref<PPGNodeRef> get_puzzle_graph_representation();
	void handle_event(String event_name);


    GdPPG();
};

#endif // GdPPG_H
