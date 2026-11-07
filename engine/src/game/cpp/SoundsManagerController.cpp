#include "../game_all.h"

void SoundsManagerController::Awake()
{
	if (sm == nullptr)
	{
		Object::DontDestroyOnLoad(gameObject);
		sm = this;
	}
	else if (sm != P<SoundsManagerController>(this))
	{
		Object::Destroy(gameObject);
	}
}

void SoundsManagerController::Start()
{
	auxASPlayer = gameObject->AddComponent<AudioSource>();
	gameObject->AddComponent<AudioReverbFilter>();
	secondLoop = false;
	elementsToLoad = 0;
	loadedElements = 0;
	if (counter != nullptr)
	{
		counter->maxWidth = 300;
	}
}

void SoundsManagerController::Update()
{
	if (ALL_LOADED)
	{
		return;
	}
	loadedElements = 0;
	if (elementsToLoad > 0)
	{
		secondLoop = true;
	}
	loadedThisFrame = 0;
	loadSounds();
	if (counter != nullptr && elementsToLoad > 0)
	{
		String text = String::Empty;
		for (int i = 0; i < 50; i++)
		{
			int num = (int)Mathf::Round(50.0f * ((float)loadedElements / (float)elementsToLoad));
			text = ((i > num) ? (text + S("·")) : (text + S("|")));
		}
		counter->viewText(text, false, true, true, 200, 0.25f, 0.25f, 0.25f);
	}
}

void SoundsManagerController::loadSounds()
{
		door_open_01 = loadSound(door_open_01, S("Sounds/Env/door_open_01"));
		door_open_02 = loadSound(door_open_02, S("Sounds/Env/door_open_02"));
		door_close_01 = loadSound(door_close_01, S("Sounds/Env/door_close_01"));
		door_close_02 = loadSound(door_close_02, S("Sounds/Env/door_close_02"));
		break_window = loadSound(break_window, S("Sounds/Env/break_window"));
		music_action_loop = loadSound(music_action_loop, S("Sounds/Music/SW_Cue13_NightmareSeqLoop1"));
		music_scare_loop = loadSound(music_scare_loop, S("Sounds/Music/SW_Cue13_NightmareSeqLoop3"));
		page_turn_01 = loadSound(page_turn_01, S("Sounds/Env/page_turn_01"));
		page_turn_02 = loadSound(page_turn_02, S("Sounds/Env/page_turn_02"));
		page_turn_03 = loadSound(page_turn_03, S("Sounds/Env/page_turn_03"));
		page_turn_04 = loadSound(page_turn_04, S("Sounds/Env/page_turn_04"));
		book_close = loadSound(book_close, S("Sounds/Env/book_close"));
		locker_01 = loadSound(locker_01, S("Sounds/Env/locker_01"));
		locker_locked = loadSound(locker_locked, S("Sounds/Env/locker_locked"));
		crowbar_pry_open = loadSound(crowbar_pry_open, S("Sounds/Env/crowbar_pry_open"));
		music_explore_5a = loadSound(music_explore_5a, S("Sounds/Music/SW_Cue5_Inside_mixed"));
		music_explore_6a = loadSound(music_explore_6a, S("Sounds/Music/SW_Cue6_Alone_10_17"));
		hay_rustle = loadSound(hay_rustle, S("Sounds/Env/hay_rustle"));
		duct_tape_use = loadSound(duct_tape_use, S("Sounds/Env/duct_tape_use"));
		button_click = loadSound(button_click, S("Sounds/Env/button_click"));
		button_click2 = loadSound(button_click2, S("Sounds/Env/button_click2"));
		engine_die = loadSound(engine_die, S("Sounds/Env/generator_end"));
		engine_run = loadSound(engine_run, S("Sounds/Env/generator"));
		engine_fail = loadSound(engine_fail, S("Sounds/Env/generator_fail"));
		engine_start = loadSound(engine_start, S("Sounds/Env/generator_start"));
		liquid_pour = loadSound(liquid_pour, S("Sounds/Env/liquid_pour_container"));
		liquid_pour_med = loadSound(liquid_pour_med, S("Sounds/Env/liquid_pour_med"));
		lever1 = loadSound(lever1, S("Sounds/Env/lever1"));
		lever2 = loadSound(lever2, S("Sounds/Env/lever2"));
		hydra1 = loadSound(hydra1, S("Sounds/Env/hydra1"));
		hydra2 = loadSound(hydra2, S("Sounds/Env/hydra2"));
		metal_bang1 = loadSound(metal_bang1, S("Sounds/Env/metal_bang1"));
		liquid_pour_small = loadSound(liquid_pour_small, S("Sounds/Env/pour_small"));
		liquid_spill = loadSound(liquid_spill, S("Sounds/Env/liquid_spill"));
		valve = loadSound(valve, S("Sounds/Env/valve"));
		wood_snap = loadSound(wood_snap, S("Sounds/Env/wood_snap"));
		door_lock_unlock = loadSound(door_lock_unlock, S("Sounds/Env/door_lock_unlock"));
		door_locked = loadSound(door_locked, S("Sounds/Env/door_locked"));
		door_lock_unlock = loadSound(door_lock_unlock, S("Sounds/Env/door_open_01"));
		music_explore_1a = loadSound(music_explore_1a, S("Sounds/Music/SW_Cue1_Wasteland_mixed"));
		music_explore_2a = loadSound(music_explore_2a, S("Sounds/Music/SW_Cue2_Investigation_mixed10_17"));
		flies = loadSound(flies, S("Sounds/Env/flies"));
		flies2 = loadSound(flies2, S("Sounds/Env/flies2"));
		gas = loadSound(gas, S("Sounds/Env/gas"));
		rifle_shoot = loadSound(rifle_shoot, S("Sounds/Env/rifle_shoot"));
		rifle_shoot_silenced = loadSound(rifle_shoot_silenced, S("Sounds/Env/rifle_shoot_silenced"));
		metal_thud = loadSound(metal_thud, S("Sounds/Env/metal_thud"));
		metal_thud2 = loadSound(metal_thud2, S("Sounds/Env/metal_thud2"));
		body_thud = loadSound(body_thud, S("Sounds/Env/body_thud"));
		body_slam = loadSound(body_slam, S("Sounds/Env/body_slam"));
		generic_hit = loadSound(generic_hit, S("Sounds/Env/generic_hit"));
		bird_fly = loadSound(bird_fly, S("Sounds/Env/bird_fly"));
		crow1 = loadSound(crow1, S("Sounds/Env/crow1"));
		crow2 = loadSound(crow2, S("Sounds/Env/crow2"));
		crow3 = loadSound(crow3, S("Sounds/Env/crow3"));
		hiss = loadSound(hiss, S("Sounds/Env/hiss"));
		plates_break = loadSound(plates_break, S("Sounds/Env/plates_break"));
		heli_fly = loadSound(heli_fly, S("Sounds/Env/heli_fly"));
		heli_crash = loadSound(heli_crash, S("Sounds/Env/heli_crash"));
		metal_creak1 = loadSound(metal_creak1, S("Sounds/Env/metal_creak1"));
		metal_moan = loadSound(metal_moan, S("Sounds/Env/metal_moan"));
		metal_moan2 = loadSound(metal_moan2, S("Sounds/Env/metal_moan2"));
		metal_door_open = loadSound(metal_door_open, S("Sounds/Env/metal_door_open"));
		metal_door_closed = loadSound(metal_door_closed, S("Sounds/Env/metal_door_closed"));
		music_explore_3a = loadSound(music_explore_3a, S("Sounds/Music/SW_Cue3_Exploration_mixed"));
		music_explore_4a = loadSound(music_explore_4a, S("Sounds/Music/SW_Cue4_CoveringGround_mixed"));
		hose = loadSound(hose, S("Sounds/Items/hose"));
		screw = loadSound(screw, S("Sounds/Env/screw"));
		repair = loadSound(repair, S("Sounds/Env/repair"));
		buzz = loadSound(buzz, S("Sounds/Env/buzz"));
		revolver = loadSound(revolver, S("Sounds/Items/revolver"));
		rope = loadSound(rope, S("Sounds/Items/net"));
		neon_off = loadSound(neon_off, S("Sounds/Env/neon_off"));
		neon_on = loadSound(neon_on, S("Sounds/Env/neon_on"));
		electric = loadSound(electric, S("Sounds/Env/electric"));
		mixer = loadSound(mixer, S("Sounds/Env/mixer"));
		elevator_away = loadSound(elevator_away, S("Sounds/Env/elevator_away"));
		elevator_come = loadSound(elevator_come, S("Sounds/Env/elevator_come"));
		elevator_ding = loadSound(elevator_ding, S("Sounds/Env/elevator_ding"));
		elevator_door = loadSound(elevator_door, S("Sounds/Env/elevator_door"));
		small_powerup = loadSound(small_powerup, S("Sounds/Env/small_powerup"));
		small_powerdown = loadSound(small_powerdown, S("Sounds/Env/small_powerdown"));
		computer_click1 = loadSound(computer_click1, S("Sounds/Env/computer_click1"));
		computer_click2 = loadSound(computer_click2, S("Sounds/Env/computer_click2"));
		fail1 = loadSound(fail1, S("Sounds/Env/fail1"));
		fingerscan = loadSound(fingerscan, S("Sounds/Env/fingerscan"));
		metal_door_locked = loadSound(metal_door_locked, S("Sounds/Env/metal_door_locked"));
		spotlight = loadSound(spotlight, S("Sounds/Env/spotlight"));
		auto_unlock = loadSound(auto_unlock, S("Sounds/Env/auto_unlock"));
		hdd1 = loadSound(hdd1, S("Sounds/Env/hdd1"));
		hdd2 = loadSound(hdd2, S("Sounds/Env/hdd2"));
		hdd3 = loadSound(hdd3, S("Sounds/Env/hdd3"));
		hdd4 = loadSound(hdd4, S("Sounds/Env/hdd4"));
		hdd5 = loadSound(hdd5, S("Sounds/Env/hdd5"));
		hdd6 = loadSound(hdd6, S("Sounds/Env/hdd6"));
		hdd7 = loadSound(hdd7, S("Sounds/Env/hdd7"));
		hdd8 = loadSound(hdd8, S("Sounds/Env/hdd8"));
		hdd9 = loadSound(hdd9, S("Sounds/Env/hdd9"));
		hdd10 = loadSound(hdd10, S("Sounds/Env/hdd10"));
		hdd11 = loadSound(hdd11, S("Sounds/Env/hdd11"));
		wind1 = loadSound(wind1, S("Sounds/Env/wind1"));
		slidedoor = loadSound(slidedoor, S("Sounds/Env/slidedoor"));
		rumble_2s = loadSound(rumble_2s, S("Sounds/Env/rumble_2s"));
		rumble_4s = loadSound(rumble_4s, S("Sounds/Env/rumble_4s"));
		rumble_8s = loadSound(rumble_8s, S("Sounds/Env/rumble_8s"));
		music_explore_5a = loadSound(music_explore_5a, S("Sounds/Music/SW_Cue5_Inside_mixed"));
		music_explore_6a = loadSound(music_explore_6a, S("Sounds/Music/SW_Cue6_Alone_10_17"));
		comp_beeps1 = loadSound(comp_beeps1, S("Sounds/Env/comp_beeps1"));
		comp_beeps2 = loadSound(comp_beeps2, S("Sounds/Env/comp_beeps2"));
		comp_beeps3 = loadSound(comp_beeps3, S("Sounds/Env/comp_beeps3"));
		comp_beeps4 = loadSound(comp_beeps4, S("Sounds/Env/comp_beeps4"));
		comp_beeps5 = loadSound(comp_beeps5, S("Sounds/Env/comp_beeps5"));
		comp_beeps6 = loadSound(comp_beeps6, S("Sounds/Env/comp_beeps6"));
		radarbeep = loadSound(radarbeep, S("Sounds/Env/radarbeep"));
		toolbox1 = loadSound(toolbox1, S("Sounds/Env/toolbox1"));
		toolbox2 = loadSound(toolbox2, S("Sounds/Env/toolbox2"));
		ship_drag = loadSound(ship_drag, S("Sounds/Env/ship_drag"));
		ship_drag2 = loadSound(ship_drag2, S("Sounds/Env/ship_drag2"));
		pisk = loadSound(pisk, S("Sounds/Env/pisk"));
		jet_mono = loadSound(jet_mono, S("Sounds/Env/jet_mono"));
		jet2_mono = loadSound(jet2_mono, S("Sounds/Env/jet2_mono"));
		door_slide = loadSound(door_slide, S("Sounds/Env/door_slide"));
		power_up_small = loadSound(power_up_small, S("Sounds/Env/power_up_small"));
		power_down_small = loadSound(power_down_small, S("Sounds/Env/power_down_small"));
		denied = loadSound(denied, S("Sounds/Env/denied"));
		mouse_click = loadSound(mouse_click, S("Sounds/Env/mouse_click"));
		lamp_on = loadSound(lamp_on, S("Sounds/Env/lamp_on"));
		engine_wrong = loadSound(engine_wrong, S("Sounds/Env/engine_wrong"));
		big_door_open = loadSound(big_door_open, S("Sounds/Env/big_door_open"));
		chorus1 = loadSound(chorus1, S("Sounds/Env/chorus1"));
		chorus2 = loadSound(chorus2, S("Sounds/Env/chorus2"));
		low_rumble = loadSound(low_rumble, S("Sounds/Env/low_rumble"));
		low_rumble2 = loadSound(low_rumble2, S("Sounds/Env/low_rumble2"));
		rrusty_creak_1 = loadSound(rrusty_creak_1, S("Sounds/Env/rrusty_creak_1"));
		rrusty_creak_2 = loadSound(rrusty_creak_2, S("Sounds/Env/rrusty_creak_2"));
		rrusty_creak_3 = loadSound(rrusty_creak_3, S("Sounds/Env/rrusty_creak_3"));
		rrusty_creak_4 = loadSound(rrusty_creak_4, S("Sounds/Env/rrusty_creak_4"));
		fast_creak_1 = loadSound(fast_creak_1, S("Sounds/Env/fast_creak_1"));
		fast_creak_2 = loadSound(fast_creak_2, S("Sounds/Env/fast_creak_2"));
		fast_creak_3 = loadSound(fast_creak_3, S("Sounds/Env/fast_creak_3"));
		slide_1 = loadSound(slide_1, S("Sounds/Env/slide_1"));
		slide_2 = loadSound(slide_2, S("Sounds/Env/slide_2"));
		slide_3 = loadSound(slide_3, S("Sounds/Env/slide_3"));
		unlock = loadSound(unlock, S("Sounds/Env/unlock"));
		keyboard = loadSound(keyboard, S("Sounds/Env/keyboard"));
		pods = loadSound(pods, S("Sounds/Env/pods"));
		power_down_big = loadSound(power_down_big, S("Sounds/Env/power_down_big"));
		power_up_big = loadSound(power_up_big, S("Sounds/Env/power_up_big"));
		glass_crack_1 = loadSound(glass_crack_1, S("Sounds/Env/glass_crack_1"));
		glass_crack_2 = loadSound(glass_crack_2, S("Sounds/Env/glass_crack_2"));
		dumdumdum = loadSound(dumdumdum, S("Sounds/Env/dumdumdum"));
		disk = loadSound(disk, S("Sounds/Env/disk"));
		thunder1 = loadSound(thunder1, S("Sounds/Env/thunder1"));
		thunder2 = loadSound(thunder2, S("Sounds/Env/thunder2"));
		thunder3 = loadSound(thunder3, S("Sounds/Env/thunder3"));
		thunder4 = loadSound(thunder4, S("Sounds/Env/thunder4"));
		thunder5 = loadSound(thunder5, S("Sounds/Env/thunder5"));
		rain_short = loadSound(rain_short, S("Sounds/Env/rain_short"));
		flashlight = loadSound(flashlight, S("Sounds/Items/flashlight1"));
		ui_hover = loadSound(ui_hover, S("Sounds/Env/ui_hover"));
		ui_click = loadSound(ui_click, S("Sounds/Env/ui_click"));
		music_attack = loadSound(music_attack, S("Sounds/Music/SW_Cue7_NightAttack1_3"));
		music_attack2 = loadSound(music_attack2, S("Sounds/Music/SW_Cue8_NickAttack4_2"));
		music_success = loadSound(music_success, S("Sounds/Music/SW_Cue9_Success"));
		digger = loadSound(digger, S("Sounds/Env/digger"));
		metal_locked_1 = loadSound(metal_locked_1, S("Sounds/Env/metal_locked_1"));
		metal_locked_2 = loadSound(metal_locked_2, S("Sounds/Env/metal_locked_2"));
		metal_locked_3 = loadSound(metal_locked_3, S("Sounds/Env/metal_locked_3"));
		cabinet_1 = loadSound(cabinet_1, S("Sounds/Env/cabinet01"));
		wood_crack_1 = loadSound(wood_crack_1, S("Sounds/Env/wood_crack1"));
		wood_crack_2 = loadSound(wood_crack_2, S("Sounds/Env/wood_crack2"));
		wood_crack_3 = loadSound(wood_crack_3, S("Sounds/Env/wood_crack3"));
		fire_start = loadSound(fire_start, S("Sounds/Env/lit"));
		rockbutton = loadSound(rockbutton, S("Sounds/Items/rockbutton"));
		necklace = loadSound(necklace, S("Sounds/Items/necklace"));
		knife = loadSound(knife, S("Sounds/Items/knife"));
		fridge = loadSound(fridge, S("Sounds/Env/fridge"));
		trunk_open = loadSound(trunk_open, S("Sounds/Env/trunk_open"));
		trunk_close = loadSound(trunk_close, S("Sounds/Env/trunk_close"));
		car_start = loadSound(car_start, S("Sounds/Env/car_start"));
		car_drive = loadSound(car_drive, S("Sounds/Env/car_drive"));
		car_drive2 = loadSound(car_drive2, S("Sounds/Env/car_drive2"));
		car_stop = loadSound(car_stop, S("Sounds/Env/car_stop"));
		car_open = loadSound(car_open, S("Sounds/Env/car_open"));
		car_close = loadSound(car_close, S("Sounds/Env/car_close"));
		car_close2 = loadSound(car_close2, S("Sounds/Env/car_close2"));
		car_close3 = loadSound(car_close3, S("Sounds/Env/car_close3"));
		cabinet_open = loadSound(cabinet_open, S("Sounds/Env/cabinet_open"));
		pull_recoil = loadSound(pull_recoil, S("Sounds/Env/pull_recoil"));
		ac = loadSound(ac, S("Sounds/Env/ac"));
		music_game_over = loadSound(music_game_over, S("Sounds/Music/SW_Cue10_sorrowv2"));
		music_sorrow = loadSound(music_sorrow, S("Sounds/Music/SW_Cue11_GameOver"));
		fan = loadSound(fan, S("Sounds/Env/fan"));
		heater2 = loadSound(heater2, S("Sounds/Env/heater2"));
		heater_hiss = loadSound(heater_hiss, S("Sounds/Env/heater_hiss"));
		pyk = loadSound(pyk, S("Sounds/Env/pyk"));
		pyk2 = loadSound(pyk2, S("Sounds/Env/pyk2"));
		blizzard = loadSound(blizzard, S("Sounds/Env/blizzard"));
		double_bang = loadSound(double_bang, S("Sounds/Env/double_bang"));
		rv_engine_loop = loadSound(rv_engine_loop, S("Sounds/Env/rv_engine_idle"));
		rv_engine_start = loadSound(rv_engine_start, S("Sounds/Env/rv_engine_start"));
		rv_engine_fail = loadSound(rv_engine_fail, S("Sounds/Env/rv_engine_fail"));
		door_creak_1 = loadSound(door_creak_1, S("Sounds/Env/door_creak1"));
		door_creak_2 = loadSound(door_creak_2, S("Sounds/Env/door_creak2"));
		door_creak_3 = loadSound(door_creak_3, S("Sounds/Env/door_creak3"));
		door_creak_open = loadSound(door_creak_open, S("Sounds/Env/door_creak_open"));
		rock_hit_1 = loadSound(rock_hit_1, S("Sounds/Env/rock_hit1"));
		rock_hit_2 = loadSound(rock_hit_2, S("Sounds/Env/rock_hit2"));
		rock_hit_3 = loadSound(rock_hit_3, S("Sounds/Env/rock_hit3"));
		rock_rumble_1 = loadSound(rock_rumble_1, S("Sounds/Env/rumble1"));
		rock_rumble_2 = loadSound(rock_rumble_2, S("Sounds/Env/rumble2"));
		rock_rumble_3 = loadSound(rock_rumble_3, S("Sounds/Env/rumble3"));
		nailed = loadSound(nailed, S("Sounds/Env/nailed"));
		sand_pour1 = loadSound(sand_pour1, S("Sounds/Env/sand_pour1"));
		sand_pour2 = loadSound(sand_pour2, S("Sounds/Env/sand_pour2"));
		sand_pour3 = loadSound(sand_pour3, S("Sounds/Env/sand_pour3"));
		sand_pour4 = loadSound(sand_pour4, S("Sounds/Env/sand_pour4"));
		sand_big = loadSound(sand_big, S("Sounds/Env/sand_big"));
		push = loadSound(push, S("Sounds/Env/push"));
		motorbikes = loadSound(motorbikes, S("Sounds/Env/motorbikes"));
		motor_incoming = loadSound(motor_incoming, S("Sounds/Env/motor_incoming"));
		vomit = loadSound(vomit, S("Sounds/Env/vomit"));
		break_glass_big = loadSound(break_glass_big, S("Sounds/Env/break_glass_big"));
		music_main = loadSound(music_main, S("Sounds/Music/SW_CueX_MainMenu_Redo1"));
		music_mystery = loadSound(music_mystery, S("Sounds/Music/SW_Cue15_MysteryTheme_v1"));
		pc_noise = loadSound(pc_noise, S("Sounds/Ambient/pc_sound"));
		underground_1 = loadSound(underground_1, S("Sounds/Ambient/underground_1"));
		ambient_fire_1 = loadSound(ambient_fire_1, S("Sounds/Ambient/fire"));
		ambient_wind_1 = loadSound(ambient_wind_1, S("Sounds/Ambient/ambient_wind_1"));
		ambient_wind_metal = loadSound(ambient_wind_metal, S("Sounds/Ambient/ambient_wind_2"));
		ambient_wind_metal_inside = loadSound(ambient_wind_metal_inside, S("Sounds/Ambient/ambient_wind_metal_inside"));
		ambient_wind_3 = loadSound(ambient_wind_3, S("Sounds/Ambient/ambient_wind_3"));
		ambient_wind_flag = loadSound(ambient_wind_flag, S("Sounds/Ambient/ambient_wind_flag"));
		ambient_wind_forest = loadSound(ambient_wind_forest, S("Sounds/Ambient/forest_wind"));
		ambient_wind_wood = loadSound(ambient_wind_wood, S("Sounds/Ambient/ambient_wind_wood"));
		ambient_ship_crashed = loadSound(ambient_ship_crashed, S("Sounds/Ambient/ambient_ship_crashed"));
		ambient_sparks = loadSound(ambient_sparks, S("Sounds/Ambient/ambient_sparks"));
		suit_breathing = loadSound(suit_breathing, S("Sounds/Ambient/suit_breathing"));
		moon = loadSound(moon, S("Sounds/Ambient/moon"));
		alert1 = loadSound(alert1, S("Sounds/Ambient/alert1"));
		alert2 = loadSound(alert2, S("Sounds/Ambient/alert2"));
		music_emotional = loadSound(music_emotional, S("Sounds/Music/SW_Cue14_emotional"));
		music_scare = loadSound(music_scare, S("Sounds/Music/SW_Cue16_NightmareScare"));
	if (loadedThisFrame == 0 && !ALL_LOADED)
	{
		ALL_LOADED = true;
	}
}

P<AudioClip> SoundsManagerController::loadSound(P<AudioClip> audioClip, String path)
{
	if (!secondLoop)
	{
		elementsToLoad++;
	}
	if (audioClip != nullptr)
	{
		loadedElements++;
		return audioClip;
	}
	if (loadedThisFrame < loadPerFrame)
	{
		audioClip = Resources::Load<AudioClip>(path);
		loadedThisFrame++;
	}
	return audioClip;
}
