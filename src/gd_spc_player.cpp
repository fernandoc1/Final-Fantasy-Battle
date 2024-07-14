#include "gd_spc_player.h"
#include <godot_cpp/core/class_db.hpp>

#include <godot_cpp/classes/file_access.hpp>

using namespace godot;

void GDSpcPlayer::_bind_methods() {
}

GDSpcPlayer::GDSpcPlayer() {
	this->generator = new AudioStreamGenerator();
	this->playback = this->generator->instantiate_playback();

	this->spcData = FileAccess::get_file_as_bytes("res://Audio/test.spc");
	this->snes_spc = new SNES_SPC;
	this->snes_spc->init();
	this->filter = new SPC_Filter;
	snes_spc->load_spc(this->spcData.ptr(), this->spcData.size());

	/* Most SPC files have garbage data in the echo buffer, so clear that */
	this->snes_spc->clear_echo();

	/* Clear filter before playing */
	this->filter->clear();

	this->generator->set_mix_rate(SNES_SPC::sample_rate * 2);

}

GDSpcPlayer::~GDSpcPlayer() {
	delete this->generator;
	// Add your cleanup here.
}

void GDSpcPlayer::_ready() {
	this->fillBuffer();
}

void GDSpcPlayer::fillBuffer() {
	int framesPerBuffer = 2048;
	PackedVector2Array array;
	array.resize(framesPerBuffer);

	snes_spc->play(framesPerBuffer, (short*)array.ptrw());
	filter->run((short*)array.ptrw(), framesPerBuffer);

	this->playback->push_buffer(array);
}

void GDSpcPlayer::_process(double delta) {
	this->fillBuffer();
}

/*
extends Node

var sample_hz = 22050.0 # Keep the number of samples to mix low, GDScript is not super fast.
var pulse_hz = 440.0
var phase = 0.0

var playback: AudioStreamPlayback = null # Actual playback stream, assigned in _ready().

func _fill_buffer():
	var increment = pulse_hz / sample_hz

	var to_fill = playback.get_frames_available()
	while to_fill > 0:
		playback.push_frame(Vector2.ONE * sin(phase * TAU)) # Audio frames are stereo.
		phase = fmod(phase + increment, 1.0)
		to_fill -= 1


func _process(_delta):
	_fill_buffer()


func _ready():
	# Setting mix rate is only possible before play().
	$Player.stream.mix_rate = sample_hz
	$Player.play()
	playback = $Player.get_stream_playback()
	# `_fill_buffer` must be called *after* setting `playback`,
	# as `fill_buffer` uses the `playback` member variable.
	_fill_buffer()


func _on_frequency_h_slider_value_changed(value):
	%FrequencyLabel.text = "%d Hz" % value
	pulse_hz = value


func _on_volume_h_slider_value_changed(value):
	# Use `linear_to_db()` to get a volume slider that matches perceptual human hearing.
	%VolumeLabel.text = "%.2f dB" % linear_to_db(value)
	$Player.volume_db = linear_to_db(value)

*/