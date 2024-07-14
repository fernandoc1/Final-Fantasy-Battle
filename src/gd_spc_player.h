#ifndef __GD_SPC_PLAYER_H__
#define __GD_SPC_PLAYER_H__

#include <godot_cpp/classes/audio_stream_player.hpp>
#include <godot_cpp/classes/audio_stream_generator.hpp>
#include <godot_cpp/classes/audio_stream_generator_playback.hpp>
#include <godot_cpp/classes/audio_stream_playback.hpp>

#include "snes_spc/SNES_SPC.h"
#include "snes_spc/SPC_Filter.h"

namespace godot {

class GDSpcPlayer : public AudioStreamPlayer {
	GDCLASS(GDSpcPlayer, Node)

private:
	AudioStreamGenerator* generator;
	PackedByteArray spcData;
	AudioStreamGeneratorPlayback* playback;

	SNES_SPC* snes_spc;
	SPC_Filter* filter;

	void fillBuffer();

protected:
	static void _bind_methods();

public:
	GDSpcPlayer();
	~GDSpcPlayer();

	void _process(double delta) override;
	void _ready() override;
};

}

#endif
