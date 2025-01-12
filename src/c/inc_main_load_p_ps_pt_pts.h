#define MOVE_LAYER(layer, x, y, w, h) layer_set_frame(layer, GRect(x, (y)-obstruction_shift, w, h))
#define MOVE_TEXT_LAYER(layer, x, y, w, h) MOVE_LAYER(text_layer_get_layer(layer), x, y, w, h)

static void move_layers(void) {
	MOVE_LAYER(background_paint_layer, 0, 0, 144, 168);
	MOVE_LAYER(s_image_layer_hour_1, 4, 94, 26, 41);
	MOVE_LAYER(s_image_layer_hour_2, 37, 94, 26, 41);
	MOVE_LAYER(s_image_layer_minute_1, 80, 94, 26, 41);
	MOVE_LAYER(s_image_layer_minute_2, 111, 94, 26, 41);
#ifdef COMPILE_WITH_SECONDS
	MOVE_LAYER(s_image_layer_second_1, 113, 137, 10, 15);
	MOVE_LAYER(s_image_layer_second_2, 126, 137, 10, 15);
#endif
	MOVE_TEXT_LAYER(text_sunrise_layer, 7, 152, 50, 30);
	MOVE_TEXT_LAYER(text_sunset_layer, 110, 152, 50, 30);
	MOVE_TEXT_LAYER(connection_layer, 47, 152, 50, 34);
	MOVE_TEXT_LAYER(battery_runtime_layer, 2, 15+2, 45, 15+20);

	Layer *battery_layer;
#ifdef PBL_PLATFORM_APLITE
	battery_layer = inverter_layer_get_layer(s_battery_layer_fill);
#else
	battery_layer = effect_layer_get_layer(s_battery_layer_fill);
#endif
	BatteryChargeState battery = battery_state_service_peek();
	MOVE_LAYER(battery_layer, 3, 21, (int)38*battery.charge_percent/100, 11);

	MOVE_TEXT_LAYER(Date_Layer, 5, 63, 134, 30);
	MOVE_TEXT_LAYER(cwLayer, 72, 135, 64, 20);
	MOVE_TEXT_LAYER(moonLayer_IMG, 51, NightMode ? 21 : 15, 33, 33);

	MOVE_TEXT_LAYER(weather_layer_1_temp, 50, 10, 94, 30);
	MOVE_TEXT_LAYER(weather_layer_3_location, 0, -1, 110, 17);
	MOVE_TEXT_LAYER(weather_layer_4_last_update, 111, -1, 33, 17);
	MOVE_TEXT_LAYER(weather_layer_7_string_1, 86, 54-15, 144-86-2, 30);
	MOVE_TEXT_LAYER(weather_layer_7_string_2, 0, 50, 84, 17); //TODO
	MOVE_TEXT_LAYER(text_TimeZone_layer, 5, 132, 100, 20); //TODO
#ifndef PBL_PLATFORM_APLITE
	MOVE_LAYER(bitmap_layer_get_layer(s_health_bmp_layer), 0,137,15,14);
	MOVE_TEXT_LAYER(text_layer_health, 14+10, 132, 100, 20); //TODO
	MOVE_LAYER(s_layer_health_up_down, 14, 140, 10, 10);
#endif
}

static void create_layers(void) {
  background_paint_layer = layer_create(GRectZero);
  layer_set_update_proc(background_paint_layer, layer_update_callback_background);
  layer_add_child(main_window_layer, background_paint_layer);
  
  s_image_layer_hour_1 = layer_create(GRectZero);
  layer_set_update_proc(s_image_layer_hour_1, layer_update_callback_hour_1);
  layer_add_child(main_window_layer, s_image_layer_hour_1);
  s_image_layer_hour_2 = layer_create(GRectZero);
  layer_set_update_proc(s_image_layer_hour_2, layer_update_callback_hour_2);
  layer_add_child(main_window_layer, s_image_layer_hour_2);
  
  s_image_layer_minute_1 = layer_create(GRectZero);
  layer_set_update_proc(s_image_layer_minute_1, layer_update_callback_minute_1);
  layer_add_child(main_window_layer, s_image_layer_minute_1);
  s_image_layer_minute_2 = layer_create(GRectZero);
  layer_set_update_proc(s_image_layer_minute_2, layer_update_callback_minute_2);
  layer_add_child(main_window_layer, s_image_layer_minute_2);
  
#ifdef COMPILE_WITH_SECONDS
  s_image_layer_second_1 = layer_create(GRectZero);
  layer_set_update_proc(s_image_layer_second_1, layer_update_callback_second_1);
  layer_add_child(main_window_layer, s_image_layer_second_1);
  s_image_layer_second_2 = layer_create(GRectZero);
  layer_set_update_proc(s_image_layer_second_2, layer_update_callback_second_2);
  layer_add_child(main_window_layer, s_image_layer_second_2);
#endif
  
  
  GColor textcolor = GColorWhite;
    
  // Sunrise Text
  text_sunrise_layer = text_layer_create(GRectZero); 
  text_layer_set_text_color(text_sunrise_layer, textcolor);
  text_layer_set_background_color(text_sunrise_layer, GColorClear );
  text_layer_set_font(text_sunrise_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  layer_add_child(main_window_layer, text_layer_get_layer(text_sunrise_layer));
  
  // Sunset Text
  text_sunset_layer = text_layer_create(GRectZero); 
  text_layer_set_text_color(text_sunset_layer, textcolor);
  text_layer_set_background_color(text_sunset_layer, GColorClear );
  text_layer_set_font(text_sunset_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  layer_add_child(main_window_layer, text_layer_get_layer(text_sunset_layer));      
  
  // Connection
  connection_layer = text_layer_create(GRectZero);
  text_layer_set_text_color(connection_layer, textcolor);
  text_layer_set_background_color(connection_layer, GColorClear);
  text_layer_set_font(connection_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  text_layer_set_text_alignment(connection_layer, GTextAlignmentCenter);
  text_layer_set_text(connection_layer, "----");
  layer_add_child(main_window_layer, text_layer_get_layer(connection_layer));
  
  // Battery state / runtime:
  battery_runtime_layer = text_layer_create(GRectZero);
  text_layer_set_text_color(battery_runtime_layer, textcolor);
  text_layer_set_background_color(battery_runtime_layer, GColorClear);
  text_layer_set_font(battery_runtime_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  text_layer_set_text_alignment(battery_runtime_layer, GTextAlignmentCenter);
  text_layer_set_text(battery_runtime_layer, "100%\n0:00 d");
  layer_add_child(main_window_layer, text_layer_get_layer(battery_runtime_layer));
  
  #ifdef PBL_PLATFORM_APLITE
    //fill battery with an InverterLayer
    s_battery_layer_fill = inverter_layer_create(GRectZero);
    layer_set_hidden(inverter_layer_get_layer(s_battery_layer_fill), true);
    layer_add_child(main_window_layer, inverter_layer_get_layer(s_battery_layer_fill));
  #else //else use effect layer on basalt
    s_battery_layer_fill = effect_layer_create(GRectZero);
    effect_layer_add_effect(s_battery_layer_fill, effect_invert_color, (void *)0b00000000); //use global inverter color
    layer_set_hidden(effect_layer_get_layer(s_battery_layer_fill), true);
    layer_add_child(main_window_layer, effect_layer_get_layer(s_battery_layer_fill));
  #endif
  
  
  
  // Date text
  Date_Layer = text_layer_create(GRectZero);
  text_layer_set_text_color(Date_Layer, textcolor);
  text_layer_set_background_color(Date_Layer, GColorClear );
  text_layer_set_font(Date_Layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_text_alignment(Date_Layer, GTextAlignmentCenter);
  layer_add_child(main_window_layer, text_layer_get_layer(Date_Layer));
  
  // Calendar Week
  cwLayer = text_layer_create(GRectZero); //64 = label_width = 144-72-2*4 = display_width - display_width/2 - 2*Space
  text_layer_set_text_color(cwLayer, textcolor);
  text_layer_set_background_color(cwLayer, GColorClear );
  text_layer_set_font(cwLayer, fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD));
  text_layer_set_text_alignment(cwLayer, GTextAlignmentLeft);
  layer_add_child(main_window_layer, text_layer_get_layer(cwLayer));
  set_cwLayer_size();
  
  // Moon phase
  moonLayer_IMG = text_layer_create(GRectZero);
  text_layer_set_text_color(moonLayer_IMG, textcolor);
  text_layer_set_background_color(moonLayer_IMG, GColorClear);
  text_layer_set_font(moonLayer_IMG, pFontMoon);
  text_layer_set_text_alignment(moonLayer_IMG, GTextAlignmentCenter);
  layer_add_child(main_window_layer, text_layer_get_layer(moonLayer_IMG));
  
  // --- Weather Layers: ---
  
  // Create temperature Layer
  weather_layer_1_temp = text_layer_create(GRectZero);
  text_layer_set_background_color(weather_layer_1_temp, GColorClear);
  text_layer_set_text_color(weather_layer_1_temp, textcolor);
  text_layer_set_text_alignment(weather_layer_1_temp, GTextAlignmentRight);
  text_layer_set_text(weather_layer_1_temp, "---");
  text_layer_set_font(weather_layer_1_temp, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD)); //FONT_KEY_BITHAM_30_BLACK
	layer_add_child(main_window_layer, text_layer_get_layer(weather_layer_1_temp));
  
  // Create location name Layer
  weather_layer_3_location = text_layer_create(GRectZero);
  text_layer_set_background_color(weather_layer_3_location, GColorClear);
  text_layer_set_text_color(weather_layer_3_location, textcolor);
  text_layer_set_text_alignment(weather_layer_3_location, GTextAlignmentCenter);
  text_layer_set_text(weather_layer_3_location, "---" /*"Loading Weather ..."*/);
  text_layer_set_font(weather_layer_3_location, fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD));
	layer_add_child(main_window_layer, text_layer_get_layer(weather_layer_3_location));
  
  // Create last updated Layer
  weather_layer_4_last_update = text_layer_create(GRectZero);
  text_layer_set_background_color(weather_layer_4_last_update, GColorClear);
  text_layer_set_text_color(weather_layer_4_last_update, textcolor);
  text_layer_set_text_alignment(weather_layer_4_last_update, GTextAlignmentCenter);
  text_layer_set_text(weather_layer_4_last_update, "---");
  text_layer_set_font(weather_layer_4_last_update, fonts_get_system_font(FONT_KEY_GOTHIC_14));
	layer_add_child(main_window_layer, text_layer_get_layer(weather_layer_4_last_update));
  
  // Create String_1 Layer
  weather_layer_7_string_1 = text_layer_create(GRectZero); //TODO
  text_layer_set_background_color(weather_layer_7_string_1, GColorClear);
  text_layer_set_text_color(weather_layer_7_string_1, textcolor);
  text_layer_set_text_alignment(weather_layer_7_string_1, GTextAlignmentCenter);
  text_layer_set_text(weather_layer_7_string_1, "---\n---");
  text_layer_set_font(weather_layer_7_string_1, fonts_get_system_font(FONT_KEY_GOTHIC_14));
	layer_add_child(main_window_layer, text_layer_get_layer(weather_layer_7_string_1));
  
  // Create String_2 Layer
  weather_layer_7_string_2 = text_layer_create(GRectZero); //TODO
  text_layer_set_background_color(weather_layer_7_string_2, GColorClear);
  text_layer_set_text_color(weather_layer_7_string_2, textcolor);
  text_layer_set_text_alignment(weather_layer_7_string_2, GTextAlignmentCenter);
  text_layer_set_text(weather_layer_7_string_2, "--- / ---");
  text_layer_set_font(weather_layer_7_string_2, fonts_get_system_font(FONT_KEY_GOTHIC_14));
	layer_add_child(main_window_layer, text_layer_get_layer(weather_layer_7_string_2));
  
  // Create TimeZone Layer
  text_TimeZone_layer = text_layer_create(GRectZero); //TODO
  text_layer_set_background_color(text_TimeZone_layer, GColorClear);
  text_layer_set_text_color(text_TimeZone_layer, textcolor);
  text_layer_set_text_alignment(text_TimeZone_layer, GTextAlignmentLeft);
  text_layer_set_text(text_TimeZone_layer, " ");
  text_layer_set_font(text_TimeZone_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18));
	layer_add_child(main_window_layer, text_layer_get_layer(text_TimeZone_layer));

  // Create Health_BMP Layer:
  #ifndef PBL_PLATFORM_APLITE
    s_health_bmp_layer = bitmap_layer_create(GRectZero);
    bitmap_layer_set_alignment(s_health_bmp_layer, GAlignBottomLeft);
    layer_add_child(main_window_layer, bitmap_layer_get_layer(s_health_bmp_layer));

    text_layer_health = text_layer_create(GRectZero); //TODO
    text_layer_set_background_color(text_layer_health, GColorClear);
    text_layer_set_text_color(text_layer_health, textcolor);
    text_layer_set_text_alignment(text_layer_health, GTextAlignmentLeft);
    text_layer_set_text(text_layer_health, " ");
    text_layer_set_font(text_layer_health, fonts_get_system_font(FONT_KEY_GOTHIC_18));
  	layer_add_child(main_window_layer, text_layer_get_layer(text_layer_health));

    s_layer_health_up_down = layer_create(GRectZero);
    layer_set_update_proc(s_layer_health_up_down, layer_update_callback_health_up_down);
    layer_add_child(main_window_layer, s_layer_health_up_down);
  #endif

	move_layers();
    
  // --- END ---
}
