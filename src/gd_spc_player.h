#ifndef __GD_SPC_PLAYER_H__
#define __GD_SPC_PLAYER_H__

#include <godot_cpp/classes/node.hpp>

namespace godot {

class GDSpcPlayer : public Node {
	GDCLASS(GDSpcPlayer, Node)

private:
	double time_passed;

protected:
	static void _bind_methods();

public:
	GDSpcPlayer();
	~GDSpcPlayer();

	void _process(double delta) override;
};

}

#endif
