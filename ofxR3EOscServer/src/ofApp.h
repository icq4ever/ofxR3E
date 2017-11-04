#pragma once

#include "ofMain.h"
#include "ofxSharedMemory.h"
#include "r3e.h"
#include "utils.h"

#define ALIVE_SEC 600
#define INTERVAL_MS 100
//#define _USE_MATH_DEFINES

class SPageGameData {
public:

	//////////////////////////////////////////////////////////////////////////
	// Version
	//////////////////////////////////////////////////////////////////////////

	r3e_int32 version_major;
	r3e_int32 version_minor;
	r3e_int32 all_drivers_offset; // Offset to num_cars
	r3e_int32 driver_data_size; // size of the driver data struct

	//////////////////////////////////////////////////////////////////////////
	// Game State
	//////////////////////////////////////////////////////////////////////////

	r3e_int32 game_paused;
	r3e_int32 game_in_menus;

	//////////////////////////////////////////////////////////////////////////
	// High detail
	//////////////////////////////////////////////////////////////////////////

	// High detail player vehicle data
	r3e_playerdata player;

	//////////////////////////////////////////////////////////////////////////
	// Event and session
	//////////////////////////////////////////////////////////////////////////

	r3e_u8char track_name[64];
	r3e_u8char layout_name[64];

	r3e_int32 track_id;
	r3e_int32 layout_id;
	r3e_float32 layout_length;

	// The current race event index, for championships with multiple events
	// Note: 0-indexed, -1 = N/A
	r3e_int32 event_index;
	// Which session the player is in (practice, qualifying, race, etc.)
	// Note: See the r3e_session enum
	r3e_int32 session_type;
	// The current iteration of the current type of session (second qualifying session, etc.)
	// Note: 0-indexed, -1 = N/A
	r3e_int32 session_iteration;

	// Which phase the current session is in (gridwalk, countdown, green flag, etc.)
	// Note: See the r3e_session_phase enum
	r3e_int32 session_phase;

	// If tire wear is active (-1 = N/A, 0 = Off, 1 = 1)
	r3e_int32 tire_wear_active;
	// If fuel usage is active (-1 = N/A, 0 = Off, 1 = 1)
	r3e_int32 fuel_use_active;

	// Total number of laps in the race, or -1 if player is not in race mode (practice, test mode, etc.)
	r3e_int32 number_of_laps;

	// Amount of time remaining for the current session
	// Note: Only available in time-based sessions, -1.0 = N/A
	// Units: Seconds
	r3e_float32 session_time_remaining;

	//////////////////////////////////////////////////////////////////////////
	// Pit
	//////////////////////////////////////////////////////////////////////////

	// Current status of the pit stop
	// Note: See the r3e_pit_window enum
	r3e_int32 pit_window_status;

	// The minute/lap from which you're obligated to pit (-1 = N/A)
	// Unit: Minutes in time-based sessions, otherwise lap
	r3e_int32 pit_window_start;

	// The minute/lap into which you need to have pitted (-1 = N/A)
	// Unit: Minutes in time-based sessions, otherwise lap
	r3e_int32 pit_window_end;

	// If current vehicle is in pitlane (-1 = N/A)
	r3e_int32 in_pitlane;

	// Number of pitstops the current vehicle has performed (-1 = N/A)
	r3e_int32 num_pitstops;

	//////////////////////////////////////////////////////////////////////////
	// Scoring & Timings
	//////////////////////////////////////////////////////////////////////////

	// The current state of each type of flag
	r3e_flags flags;

	// Current position (1 = first place)
	r3e_int32 position;

	r3e_finish_status finish_status;

	// Total number of cut track warnings (-1 = N/A)
	r3e_int32 cut_track_warnings;
	// The number of penalties the car currently has pending of each type (-1 = N/A)
	r3e_cut_track_penalties penalties;
	// Total number of penalties pending for the car
	// Note: See the 'penalties' field
	r3e_int32 num_penalties;

	// How many laps the car has completed. If this value is 6, the car is on it's 7th lap. -1 = n/a
	r3e_int32 completed_laps;
	r3e_int32 current_lap_valid;
	r3e_int32 track_sector;
	r3e_float32 lap_distance;
	// fraction of lap completed, 0.0-1.0, -1.0 = N/A
	r3e_float32 lap_distance_fraction;

	// The current best lap time for the leader of the session
	// Unit: Seconds (-1.0 = N/A)
	r3e_float32 lap_time_best_leader;
	// The current best lap time for the leader of the current/viewed vehicle's class in the current session
	// Unit: Seconds (-1.0 = N/A)
	r3e_float32 lap_time_best_leader_class;
	// Sector times of fastest lap by anyone in session
	// Unit: Seconds (-1.0 = N/A)
	r3e_float32 session_best_lap_sector_times[3];
	// Best lap time
	// Unit: Seconds (-1.0 = N/A)
	r3e_float32 lap_time_best_self;
	r3e_float32 sector_time_best_self[3];
	// Previous lap
	// Unit: Seconds (-1.0 = N/A)
	r3e_float32 lap_time_previous_self;
	r3e_float32 sector_time_previous_self[3];
	// Current lap time
	// Unit: Seconds (-1.0 = N/A)
	r3e_float32 lap_time_current_self;
	r3e_float32 sector_time_current_self[3];
	// The time delta between this car's time and the leader
	// Unit: Seconds (-1.0 = N/A)
	r3e_float32 lap_time_delta_leader;
	// The time delta between this car's time and the leader of the car's class
	// Unit: Seconds (-1.0 = N/A)
	r3e_float32 lap_time_delta_leader_class;
	// Time delta between this car and the car placed in front
	// Unit: Seconds (-1.0 = N/A)
	r3e_float32 time_delta_front;
	// Time delta between this car and the car placed behind
	// Unit: Seconds (-1.0 = N/A)
	r3e_float32 time_delta_behind;

	//////////////////////////////////////////////////////////////////////////
	// Vehicle information
	//////////////////////////////////////////////////////////////////////////

	r3e_driver_info vehicle_info;
	r3e_u8char player_name[64];

	//////////////////////////////////////////////////////////////////////////
	// Vehicle state
	//////////////////////////////////////////////////////////////////////////

	// Which controller is currently controlling the vehicle (AI, player, remote, etc.)
	// Note: See the r3e_control enum
	r3e_int32 control_type;

	// Unit: Meter per second (m/s)
	r3e_float32 car_speed;

	// Unit: Radians per second (rad/s)
	r3e_float32 engine_rps;
	r3e_float32 max_engine_rps;

	// -2 = N/A, -1 = reverse, 0 = neutral, 1 = first gear, ...
	r3e_int32 gear;
	// -1 = N/A
	r3e_int32 num_gears;

	// Physical location of car's center of gravity in world space (X, Y, Z) (Y = up)
	r3e_vec3_f32 car_cg_location;
	// Pitch, yaw, roll
	// Unit: Radians (rad)
	r3e_ori_f32 car_orientation;
	// Acceleration in three axes (X, Y, Z) of car body in local-space.
	// From car center, +X=left, +Y=up, +Z=back.
	// Unit: Meter per second squared (m/s^2)
	r3e_vec3_f32 local_acceleration;

	// Unit: Liters (l)
	// Note: Not valid for AI or remote players
	r3e_float32 fuel_left;
	r3e_float32 fuel_capacity;
	// Unit: Celsius (C)
	// Note: Not valid for AI or remote players
	r3e_float32 engine_water_temp;
	r3e_float32 engine_oil_temp;
	// Unit: Kilopascals (KPa)
	// Note: Not valid for AI or remote players
	r3e_float32 fuel_pressure;
	// Unit: Kilopascals (KPa)
	// Note: Not valid for AI or remote players
	r3e_float32 engine_oil_pressure;

	// How pressed the throttle pedal is 
	// Range: 0.0 - 1.0 (-1.0 = N/A)
	// Note: Not valid for AI or remote players
	r3e_float32 throttle_pedal;
	// How pressed the brake pedal is
	// Range: 0.0 - 1.0 (-1.0 = N/A)
	// Note: Not valid for AI or remote players
	r3e_float32 brake_pedal;
	// How pressed the clutch pedal is 
	// Range: 0.0 - 1.0 (-1.0 = N/A)
	// Note: Not valid for AI or remote players
	r3e_float32 clutch_pedal;

	// DRS data
	r3e_drs drs;

	// Pit limiter (-1 = N/A, 0 = inactive, 1 = active)
	r3e_int32 pit_limiter;

	// Push to pass data
	r3e_push_to_pass push_to_pass;

	// How much the vehicle's brakes are biased towards the back wheels (0.3 = 30%, etc.) (-1.0 = N/A)
	// Note: Not valid for AI or remote players
	r3e_float32 brake_bias;

	//////////////////////////////////////////////////////////////////////////
	// Tires
	//////////////////////////////////////////////////////////////////////////

	// Which type of tires the car has (option, prime, etc.)
	// Note: See the r3e_tire_type enum, deprecated - use the values further down instead
	r3e_int32 tire_type;
	// Rotation speed
	// Uint: Radians per second
	r3e_float32 tire_rps[R3E_TIRE_INDEX_MAX];
	// Range: 0.0 - 1.0 (-1.0 = N/A)
	r3e_float32 tire_grip[R3E_TIRE_INDEX_MAX];
	// Range: 0.0 - 1.0 (-1.0 = N/A)
	r3e_float32 tire_wear[R3E_TIRE_INDEX_MAX];
	// Unit: Kilopascals (KPa) (-1.0 = N/A)
	// Note: Not valid for AI or remote players
	r3e_float32 tire_pressure[R3E_TIRE_INDEX_MAX];
	// Percentage of dirt on tire (-1.0 = N/A)
	// Range: 0.0 - 1.0
	r3e_float32 tire_dirt[R3E_TIRE_INDEX_MAX];
	// Brake temperature (-1.0 = N/A)
	// Unit: Celsius (C)
	// Note: Not valid for AI or remote players
	r3e_float32 brake_temp[R3E_TIRE_INDEX_MAX];
	// Temperature of three points across the tread of the tire (-1.0 = N/A)
	// Unit: Celsius (C)
	// Note: Not valid for AI or remote players
	r3e_float32 tire_temps[R3E_TIRE_INDEX_MAX][R3E_TIRE_TEMP_INDEX_MAX];
	// Which type of tires the car has (option, prime, etc.)
	// Note: See the r3e_tire_type enum
	r3e_int32 tire_type_front;
	r3e_int32 tire_type_rear;
	// Which subtype of tires the car has
	// Note: See the r3e_tire_subtype enum
	r3e_int32 tire_subtype_front;
	r3e_int32 tire_subtype_rear;

	//////////////////////////////////////////////////////////////////////////
	// Damage
	//////////////////////////////////////////////////////////////////////////

	// The current state of various parts of the car
	// Note: Not valid for AI or remote players
	r3e_car_damage car_damage;

	//////////////////////////////////////////////////////////////////////////
	// Additional Info
	//////////////////////////////////////////////////////////////////////////

	// The current state of each type of extended flag
	r3e_flags_extended flags_extended;

	// Yellow flag for each sector; -1 = no data, 0 = not active, 1 = active
	r3e_int32 sector_yellow[3];

	// Distance into track for closest yellow, -1.0 if no yellow flag exists
	// Unit: Meters (m)
	r3e_float32 closest_yellow_distance_into_track;

	// Additional flag info
	r3e_flags_extended_2 flags_extended_2;

	// If the session is time based, lap based or time based with an extra lap at the end
	r3e_session_length_format session_length_format;

	//////////////////////////////////////////////////////////////////////////
	// Driver info
	//////////////////////////////////////////////////////////////////////////

	// Number of cars (including the player) in the race
	r3e_int32 num_cars;

	// Contains name and basic vehicle info for all drivers in place order
	r3e_driver_data all_drivers_data_1[R3E_NUM_DRIVERS_MAX];
};


class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
		
	ofxSharedMemory<SPageGameData *> datas;
	SPageGameData * gameData;

	clock_t clk_start = 0;
	clock_t	clk_last = 0;
	clock_t clk_delta_ms = 0;
	clock_t clk_elapsed = 0;

	int err_code = 0;

	bool isConnected = false;
};
