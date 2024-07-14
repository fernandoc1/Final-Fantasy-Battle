#ifndef __GD_SPC_PLAYER_H__
#define __GD_SPC_PLAYER_H__

#include <godot_cpp/classes/audio_stream_player.hpp>
#include <godot_cpp/classes/audio_stream_playback.hpp>

namespace godot {

class GDSpcPlayer : public AudioStreamPlayer {
	GDCLASS(GDSpcPlayer, Node)

private:
	double time_passed;
	AudioStreamPlayback* playback;

protected:
	static void _bind_methods();

public:
	GDSpcPlayer();
	~GDSpcPlayer();

	void _process(double delta) override;
};

}

#endif
