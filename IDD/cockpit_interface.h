#pragma once

#include "cockpit_enum.h"

#pragma pack(push, 1)
// 2022.06.22

typedef struct F16_CMFD_BUTTON_TYPE
{
	ON_OFF_TYPE	mfd_btn_1;
	ON_OFF_TYPE	mfd_btn_2;
	ON_OFF_TYPE	mfd_btn_3;
	ON_OFF_TYPE	mfd_btn_4;
	ON_OFF_TYPE	mfd_btn_5;
	ON_OFF_TYPE	mfd_btn_6;
	ON_OFF_TYPE	mfd_btn_7;
	ON_OFF_TYPE	mfd_btn_8;
	ON_OFF_TYPE	mfd_btn_9;
	ON_OFF_TYPE	mfd_btn_10;
	ON_OFF_TYPE	mfd_btn_11;
	ON_OFF_TYPE	mfd_btn_12;
	ON_OFF_TYPE	mfd_btn_13;
	ON_OFF_TYPE	mfd_btn_14;
	ON_OFF_TYPE	mfd_btn_15;
	ON_OFF_TYPE	mfd_btn_16;
	ON_OFF_TYPE	mfd_btn_17;
	ON_OFF_TYPE	mfd_btn_18;
	ON_OFF_TYPE	mfd_btn_19;
	ON_OFF_TYPE	mfd_btn_20;
	UP_CENTER_DOWN_TYPE	mfd_gain_up_btn;
	UP_CENTER_DOWN_TYPE	mfd_brt_up_btn;
	UP_CENTER_DOWN_TYPE	mfd_sys_up_btn;
	UP_CENTER_DOWN_TYPE	mfd_com_up_btn;
}F16_CMFD_BUTTON_TYPE;

typedef struct F16_ICP_BUTTON_TYPE
{
	ON_OFF_TYPE icp_com_1_btn;
	ON_OFF_TYPE icp_com_2_btn;
	ON_OFF_TYPE icp_iff_btn;
	ON_OFF_TYPE icp_list_btn;
	ON_OFF_TYPE icp_a_a_btn;
	ON_OFF_TYPE icp_a_g_btn;
	ON_OFF_TYPE icp_t_ils_1_btn;
	ON_OFF_TYPE icp_alow_2_n_btn;
	ON_OFF_TYPE icp_num_3_btn;
	ON_OFF_TYPE icp_stpt_4_w_btn;
	ON_OFF_TYPE icp_crus_5_btn;
	ON_OFF_TYPE icp_time_6_e_btn;
	ON_OFF_TYPE icp_mark_7_btn;
	ON_OFF_TYPE icp_fix_8_s_btn;
	ON_OFF_TYPE icp_a_cal_9_btn;
	ON_OFF_TYPE icp_m_sel_0_btn;
	ON_OFF_TYPE icp_rcl_btn;
	ON_OFF_TYPE icp_entr_btn;
	UP_CDENTER_DOWN_TYPE icp_cursor_updown_btn;
	RTN_UP_DOWN_SEQ_NOT_PRESS_TYPE icp_joy_btn;
	DRIFT_NORM_WARN_RESET_TYPE icp_dnw_switch;
	ON_OFF_TYPE icp_flir_wx_btn;
	UP_CDENTER_DOWN_TYPE icp_flir_cursor_updown_btn;
	GAIN_LVL_AUTO_TYPE icp_flir_gla_switch;
	int icp_sym_val;
	int icp_brt_val;
	int icp_ret_depr_val;
}F16_ICP_BUTTON_TYPE;

typedef struct F16_THREAT_WARNING_PANEL
{
	ON_OFF_TYPE warn_handoff_btn;
	ON_OFF_TYPE warn_launch_btn;
	ON_OFF_TYPE warn_mode_btn;
	ON_OFF_TYPE warn_on_unknown_btn;
	ON_OFF_TYPE warn_on_sys_test_btn;
	ON_OFF_TYPE warn_tgt_sept_btn;
	int warn_handoff_light_val;
	int warn_launch_light_val;
	int warn_mode_open_light_val;
	int warn_on_unknown_light_val;
	int warn_on_sys_test_light_val;
	int warn_tgt_sept_light_val;
	int warn_handoff_h_light_val;
	int warn_mode_priority_light_val;
	int warn_u_unknown_light_val;
	int warn_sys_test_light_val;
	int warn_tgt_sept1_light_val;
	int warn_tgt_sept2_light_val;
	ON_OFF_TYPE icp_sym_roll_off_switch;
	ON_OFF_TYPE icp_brt_roll_off_switch;
	ON_OFF_TYPE icp_ret_depr_roll_off_switch;
	ON_OFF_TYPE icp_cont_roll_off_switch;
}F16_THREAT_WARNING_PANEL;


typedef struct F16_MASTER_CAUTION_LIGHT
{
	ON_OFF_TYPE	master_caution_btn;
	int	master_caution_light_val;
}F16_MASTER_CAUTION_LIGHT;

typedef struct F16_IFF_IDENT_F_ACK_BUTTON
{
	ON_OFF_TYPE	iff_indent_btn;
	ON_OFF_TYPE	f_ack_btn;
	ON_OFF_TYPE	nvg_left_btn;
	ON_OFF_TYPE	nvg_right_btn;
	int iff_backlight_val;
}F16_IFF_IDENT_F_ACK_BUTTON;



typedef struct F16_MISC
{
	NORM_QUIET_SELENT_TYPE misc_rf_switch;
	OFF_ARM_TYPE misc_laser_switch;
	ON_OFF_TYPE misc_alt_rel_btn;
	ARM_OFF_SIMULATE_TYPE misc_master_switch;
	HDG_SEL_ATT_HOLD_STRG_SEL_TYPE misc_roll_switch;
	ALT_HOLD_AP_OFF_ATT_HOLD_TYPE misc_pitch_switch;
	ON_OFF_TYPE misc_ecm_light;
	ON_OFF_TYPE misc_pitch_solenoid;
	int misc_adv_active_light_val;
	int misc_adv_stby_light_val;
	int misc_backlight_val;
	ON_OFF_TYPE misc_adv_mode_btn;
	int nws_brt_val_1;
	int nws_brt_val_2;
	int nws_brt_val_3;
	int nws_brt_val_4;
}F16_MISC;

typedef struct F16_AR_STATUS_NWS_INDICATOR
{
	int	nws_brt_val;
	int	ar_indexer_rdy_light_val;
	int	ar_indexer_nws_light_val;
	int	ar_indexer_disc_light_val;
}F16_AR_STATUS_NWS_INDICATOR;

typedef struct F16_WARING_LIGHTS
{
	int warn_eng_fire_light_val;
	int warn_engine_light_val;
	int warn_hyd_oil_press_light_val;
	int warn_flcs_light_val;
	int warn_dbu_on_light_val;
	int warn_to_ldg_config_light_val;
	int warn_canopy_light_val;
	int warn_blank_light_val;
}F16_WARING_LIGHTS;



//패널 삭제 
//typedef struct F16_INSTR_MODE_SELECT_PANEL
//{
//	ILS_TCN_TCN_NAV_ILS_NAV_TYPE	instr_mode_switch;
//	NOT_PRESS_PRESS_TYPE	instr_hdg_btn;
//	int	instr_hdg_val;
//	int	insrt_backlight_val;
//}F16_INSTR_MODE_SELECT_PANEL;
//패널 삭제
//typedef struct F16_FUEL_QTY_SEL_PANEL
//{
//	TEST_FORM_RSVR_INT_WING_EXT_WING_EXT_CENTER_TYPE fuel_qty_switch;
//	NORM_WING_FIRST_TYPE	fuel_trans_switch;
//	int	fuel_backlight_val;
//}F16_FUEL_QTY_SEL_PANEL;

typedef struct F16_AOA_INDEXER
{
	int aoa_red_light_val;
	int aoa_green_light_val;
	int aoa_orange_light_val;
	int aoa_brt_val_1;
	int aoa_brt_val_2;
	int aoa_brt_val_3;
	int aoa_brt_val_4;
}F16_AOA_INDEXER;


typedef struct F16_TF_FAIL_WARINING_LIGHT
{
	int	tf_fail_light;
	int	tf_left_down_light;
	int	tf_right_up_light;
	int	tf_right_down_light;
}F16_TF_FAIL_WARINING_LIGHT;

typedef struct F16_OIL_PRESSURE_INDICATOR
{
	int	oil_pressure_ind_val;
	int	oil_pressure_backlight_val;
}F16_OIL_PRESSURE_INDICATOR;

typedef struct F16_NOZ_POS_INDICATOR
{
	int	noz_pos_ind_val;
	int	noz_pos_backlight_val;
}F16_NOZ_POS_INDICATOR;

typedef struct F16_RPM_INDICATOR
{
	int	rpm_ind_val;
	int	rpm_backlight_val;
}F16_RPM_INDICATOR;


typedef struct F16_FTIT_INDICATOR
{
	int	ftit_ind_val;
	int	ftit_backlight_val;
}F16_FTIT_INDICATOR;

//패널 삭제
//typedef struct F16_MRK_BCN_LIGHT
//{
//	on_off_type	mrk_bcn_light;
//
//}F16_MRK_BCN_LIGHT;

typedef struct F16_RUDDER_PEDALS
{
	int	rudder_pedal_1_val;
	int	rudder_pedal_2_val;
	int	rudder_pedal_3_val;
}F16_RUDDER_PEDALS;

typedef struct F16_AIRSPEED_MACH_INDICATOR
{
	int	airs_set_index_val;
}F16_AIRSPEED_MACH_INDICATOR;

typedef struct F16_ATTIDUDE_DIRECTOR_INDICATOR
{
	int	att_arrow_knob_val;
}F16_ATTIDUDE_DIRECTOR_INDICATOR;

typedef struct F16_ALTIMETER
{
	ELECT_PNEU_TYPE	alti_elec_pneu_switch;
	int	alti_left_knob_val;
}F16_ALTIMETER;



typedef struct F16_DATA_ENTRY_DISPLAY
{
	int	data_entry_disp;
}F16_DATA_ENTRY_DISPLAY;

typedef struct F16_FUEL_FLOW_INDICATOR
{
	int	fuel_flow_indicator;
}F16_FUEL_FLOW_INDICATOR;

typedef struct F16_RWR 
{
	int rwr_int_switch_val;
	int rwr_left_right_val;
	int rwr_up_down_val;
}F16_RWR;

typedef struct F16_STANDBY_ATTITUDE_INDICATOR {
	ON_OFF_TYPE sai_pull_switch;
	int sai_pull_to_cage_knob;
}F16_STANDBY_ATTITUDE_INDICATOR;


typedef struct F16_CPD {
	ON_OFF_TYPE cpd_gain_btn;
	ON_OFF_TYPE cpd_left_btn_1;
	ON_OFF_TYPE cpd_left_btn_2;
	ON_OFF_TYPE cpd_left_btn_3;
	ON_OFF_TYPE cpd_left_btn_4;
	ON_OFF_TYPE cpd_left_btn_5;
	ON_OFF_TYPE cpd_left_btn_6;
	UP_CENTER_DOWN_TYPE cpd_left_btn_7;
	ON_OFF_TYPE cpd_left_btn_8;
	UP_CENTER_DOWN_TYPE cpd_sym_btn;
	ON_OFF_TYPE cpd_right_btn_1;
	ON_OFF_TYPE cpd_right_btn_2;
	ON_OFF_TYPE cpd_right_btn_3;
	ON_OFF_TYPE cpd_right_btn_4;
	ON_OFF_TYPE cpd_right_btn_5;
	ON_OFF_TYPE cpd_right_btn_6;
	UP_CENTER_DOWN_TYPE cpd_right_btn_7;
	ON_OFF_TYPE cpd_right_btn_8;
	ON_OFF_TYPE cpd_top_btn_1;
	ON_OFF_TYPE cpd_top_btn_2;
	ON_OFF_TYPE cpd_top_btn_3;
	ON_OFF_TYPE cpd_top_btn_4;
	ON_OFF_TYPE cpd_top_btn_5;
	ON_OFF_TYPE cpd_bottom_btn_1;
	ON_OFF_TYPE cpd_bottom_btn_2;
	ON_OFF_TYPE cpd_bottom_btn_3;
	ON_OFF_TYPE cpd_bottom_btn_4;
	ON_OFF_TYPE cpd_bottom_btn_5;
	ON_OFF_TYPE cpd_crs_hdg_switch;
	int	cpd_display_1[4];
	int cpd_display_2[4];
	int cpd_display_3[8];
	int cpd_display_4[4];
}F16_CPD;

typedef struct CENTER_CONSOLE_TYPE
{
	F16_CPD cpd;
	F16_STANDBY_ATTITUDE_INDICATOR standby_attitude_indicator;
	F16_RWR rwr;
	F16_CMFD_BUTTON_TYPE	cmfd_button_type;
	F16_ICP_BUTTON_TYPE	icp_button_type;
	F16_THREAT_WARNING_PANEL	threat_warning_panel;
	F16_MASTER_CAUTION_LIGHT	master_caution_light;
	F16_IFF_IDENT_F_ACK_BUTTON	iff_ident_f_ack_button;
	F16_MISC	misc;
	F16_AR_STATUS_NWS_INDICATOR	ar_status_nws_indicator;
	F16_WARING_LIGHTS	waring_lights;
	//F16_INSTR_MODE_SELECT_PANEL	instr_mode_select_panel;
	//F16_FUEL_QTY_SEL_PANEL	fuel_qty_sel_panel;
	F16_AOA_INDEXER aoa_indexer;
	F16_TF_FAIL_WARINING_LIGHT	tf_fail_warining_light;
	F16_OIL_PRESSURE_INDICATOR	oil_pressure_indicator;
	F16_NOZ_POS_INDICATOR	noz_pos_indicator;
	F16_RPM_INDICATOR	rpm_indicator;
	F16_FTIT_INDICATOR	ftit_indicator;
	//F16_MRK_BCN_LIGHT	mrk_bcn_light; 패널 삭제
	F16_RUDDER_PEDALS	rudder_pedals;
	//F16_AIRSPEED_MACH_INDICATOR	airspeed_mach_indicator;
	//F16_ATTIDUDE_DIRECTOR_INDICATOR	attidude_director_indicator;
	//F16_ALTIMETER	altimeter;
	F16_DATA_ENTRY_DISPLAY	data_entry_display;
	F16_FUEL_FLOW_INDICATOR	fuel_flow_indicator;
}CENTER_CONSOLE_TYPE;



typedef struct F16_LANDING_GEAR_CONTROL_PANEL
{
	ON_OFF_TYPE lg_emer_store_btn;
	DOWN_UP_TYPE lg_hook_switch;
	OFF_ENABLE_TYPE lg_gnd_jet_switch;
	CHAN_1_CHAN_2_TYPE lg_brake_switch;
	OFF_ON_ANTI_SKID_TYPE lg_park_break_switch;
	CAT_1_CAT_2_TYPE lg_store_conf_switch;
	ON_OFF_TYPE lg_horn_silencer_btn;
	OFF_LANDING_TAXI_TYPE lg_landing_light_switch;
	ON_OFF_TYPE lg_dn_lock_btn;
	ON_OFF_TYPE lg_park_break_solenoid;
	ON_OFF_TYPE lg_wheel_front_light;
	ON_OFF_TYPE lg_wheel_left_light;
	ON_OFF_TYPE lg_wheel_right_light;
	//DOWN_UP_TYPE lg_handle_switch; 스위치 삭제 -
	int lg_backlight_val;
}F16_LANDING_GEAR_CONTROL_PANEL;


typedef struct F16_CMDS_CONTROL_PANEL
{
	OFF_ENABLE_TYPE cmds_rwr_switch;
	OFF_ENABLE_TYPE cmds_jmr_switch;
	OFF_ENABLE_TYPE cmds_mws_switch;
	OFF_ENABLE_TYPE cmds_01_switch;
	OFF_ENABLE_TYPE cmds_02_switch;
	OFF_ENABLE_TYPE cmds_ch_switch;
	OFF_ENABLE_TYPE cmds_fl_switch;
	OFF_ENABLE_TYPE cmds_jett_switch;
	BIT_1_2_3_4_TYPE cmds_prgm_switch;
	OFF_STBY_MAN_SEMI_AUTO_BYP_TYPE cmds_mode_switch;
	int cmds_status_lcd_1_str;
	int cmds_status_lcd_2_str;
	int cmds_status_lcd_3_str;
	int cmds_status_lcd_4_str;
	//public int cmds_status_lcd_5_str;
	//public int cmds_status_lcd_6_str;
	//public int cmds_status_lcd_7_str;
	//public int cmds_status_lcd_8_str;
	int cmds_backlight_val;
}F16_CMDS_CONTROL_PANEL;

typedef struct F16_THREAT_WARNING_AUX_CONTROL_PANEL
{
	ON_OFF_TYPE tw_search_btn;
	ON_OFF_TYPE tw_act_pwr_btn;
	ON_OFF_TYPE tw_low_alt_btn;
	ON_OFF_TYPE tw_sys_pwr_btn;
	int tw_dim_val;
	int tw_search_light;
	int tw_pwr_light;
	int tw_low_alt_light;
	int tw_sys_pwr_light;
	// public OFF_ENABLE_TYPE tw_3_amp_fuse;// 삭제
	// public int tw_backlight_val; //삭제
}F16_THREAT_WARNING_AUX_CONTROL_PANEL;


typedef struct F16_ALT_GEAR_HANDLE
{
	ON_OFF_TYPE	alt_gear_handle;
}F16_ALT_GEAR_HANDLE;

typedef struct F16_SPEED_BRAKE_POSITION_INDICATOR
{
	int	speed_break_indicator;
}F16_SPEED_BRAKE_POSITION_INDICATOR;

typedef struct LEFT_AUX_CONSOLE_TYPE
{
	F16_LANDING_GEAR_CONTROL_PANEL	landing_gear_control_panel;
	F16_CMDS_CONTROL_PANEL	cmds_control_panel;
	F16_THREAT_WARNING_AUX_CONTROL_PANEL	threat_warning_aux_control_panel;
	F16_ALT_GEAR_HANDLE	alt_gear_handle;
	F16_SPEED_BRAKE_POSITION_INDICATOR	speed_brake_position_indicator;
}LEFT_AUX_CONSOLE_TYPE;



typedef struct F16_UHF_BACKUP_CONTROL_PANEL
{
	ON_OFF_TYPE uhf_test_dsp_btn;
	ON_OFF_TYPE uhf_status_btn;
	int uhf_channel_switch;
	A_3_2_TYPE uhf_freq_switch_1;
	int uhf_freq_switch_2;
	int uhf_freq_switch_3;
	int uhf_freq_switch_4;
	NUM_0_25_50_75_TYPE uhf_freq_switch_5;
	OFF_MAIN_BOTH_ADF_TYPE uhf_func_switch;
	T_TONE_TYPE uhf_tone_switch;
	ON_OFF_TYPE uhf_squelch_switch;
	MNL_PRESET_GRD_TYPE uhf_mode_switch;


	int uhf_hid_gd_sq_val;
	int uhf_vol_val;
	int uhf_channel_display_str;
	int uhf_freq_disp_1_str;
	int uhf_freq_disp_2_str;
	int uhf_freq_disp_3_str;
	int uhf_freq_disp_4_str;
	int uhf_freq_disp_5_str;
	int uhf_backlight_val;
	ON_OFF_TYPE uhf_hid_press_btn;
	int uhf_hid_bw_val;
	int uhf_hid_mn_sq_val;


}F16_UHF_BACKUP_CONTROL_PANEL;

typedef struct F16_AUDIO_1_CONTROL_PENEL
{
	int aud_1_comm_1_val;
	int aud_1_comm_2_val;
	ON_OFF_TYPE aud_1_comm_1_mode_btn;
	ON_OFF_TYPE aud_1_comm_2_mode_btn;
	OFF_SQL_GD_TYPE aud_1_comm_1_mode_switch;
	OFF_SQL_GD_TYPE aud_1_comm_2_mode_switch;
	ON_OFF_TYPE aud_1_comm_1_push_tone_btn;
	ON_OFF_TYPE aud_1_comm_2_push_tone_btn;
	int aud_1_secure_voice_val;
	int aud_1_msl_val;
	int aud_1_tf_val;
	int aud_1_threat_val;
	int aud_1_backlight_val;

}F16_AUDIO_1_CONTROL_PENEL;

//패널 삭제
//typedef struct F16_ASPJ_PANEL
//{
//	OFF_MBIT_STBY_ON_TYPE	aspj_mode_switch;
//	NUM_1_2_3_4_TYPE	aspj_submode_switch;
//	OFF_NORM_TYPE	aspj_rcv_switch;
//	MAN_AUTO_TYPE	aspj_chaff_switch;
//	MAN_AUTO_TYPE	aspj_flare_switch;
//	on_off_type	aspj_test_btn_1;
//	on_off_type	aspj_test_btn_2;
//	int	aspj_xmit_light_val;
//	int	aspj_rcv_light_val;
//	int	aspj_hot_light_val;
//	int	aspj_ovrd_light_val;
//	int	aspj_warm_light_val;
//	int	aspj_bit_light_val;
//	int	aspj_backlight_val;
//}F16_ASPJ_PANEL;


typedef struct F16_ELEC_CONTROL_PANEL
{
	OFF_MAIN_PWR_BATT_TYPE elec_main_pwr_switch;
	ON_OFF_TYPE elec_caution_btn;
	int elec_flcs_pmg_light;
	int elec_main_gen_light;
	int elec_stby_gen_light;
	int elec_blank_light;
	int elec_epu_gen_light;
	int elec_epu_pmg_light;
	int elec_to_flcs_light;
	int elec_flcs_rly_light;
	int elec_fail_light;
	int elec_backlight_val;
}F16_ELEC_CONTROL_PANEL;

typedef struct F16_DVR_CONRTOL_PANEL
{
	//on_off_type	avrt_test_btn;
	//OFF_ON_AUTO_TYPE	avtr_avrt_switch;
	//AFT_LEFT_HUD_RIGHT_TYPE	avrt_display_switch;
	//int	avrt_ctvs_light;
	//int	avrt_avtr_light;
	int	avrt_backlight_val;

	HUD_HMD_TYPE dvr_video_select;
	EVENT_MAKR_RECORD_OFF_TYPE dvr_record_switch;

}F16_DVR_CONRTOL_PANEL;
typedef struct F16_FUEL_CONTROL_PANEL
{
	OFF_MASTER_TYPE	fuel_master_switch;
	OFF_TANK_INERTING_TYPE	fuel_tank_switch;
	OFF_NORM_AFT_FWD_TYPE	fuel_eng_feed_switch;
	CLOSE_OPEN_TYPE	fuel_air_refuel_switch;
	int	fuel_backlight_val;
}F16_FUEL_CONTROL_PANEL;

typedef struct F16_IFF_PANEL
{
	OFF_SYBY_LOW_NORM_EMER_TYPE aux_master_switch;
	ZERO_A_B_HOLD_TYPE aux_m_4_code_switch;
	BACK_UP_UFC_TYPE aux_cni_switch;
	M3_OFF_M1_TYPE aux_enable_switch;
	B_A_OUT_TYPE aux_reply_switch;
	AUDIO_OUT_TYPE aux_monitor_switch;
	UP_DOWN_TYPE aux_channel_1_switch;
	UP_DOWN_TYPE aux_channel_2_switch;
	UP_DOWN_TYPE aux_channel_3_switch;
	UP_DOWN_TYPE aux_channel_4_switch;
	int aux_backlight_val;
}F16_AUX_COMM_PANEL;


typedef struct F16_EXT_LIGHTING_CONROL_PANEL
{
	//OFF_1_2_3_4_A_B_C_TYPE	ext_anti_collision_switch;
	FLASH_STEADY_TYPE ext_position_light_switch;
	OFF_BRT_DIM_TYPE ext_wing_trail_switch;
	OFF_BRT_DIM_TYPE ext_fuselage_switch;
	int ext_form_val;
	//public 	OFF_ALL_A_C_FORM_NORM_TYPE	ext_master_switch;
	int ext_refueling_val;
	int ext_backlight_val;
}F16_EXT_LIGHTING_CONROL_PANEL;


typedef struct F16_FLT_CONTROL_PANEL
{
	OFF_BACKUP_TYPE flt_digital_switch;
	EXTEND_NORM_TYPE flt_alt_falps_switch;
	DISABLE_ENABLE_TYPE flt_tf_flyup_switch;
	LOCK_AUTO_TYPE flt_le_flaps_switch;
	OFF_RESET_TYPE flt_flcs_switch;
	OFF_BIT_TYPE flt_bit_switch;
	ON_OFF_TYPE fltt_flcs_solenoid;
	ON_OFF_TYPE flt_run_light;
	ON_OFF_TYPE flt_fail_light;
	int flt_backlight_val;
}F16_FLT_CONTROL_PANEL;
typedef struct F16_MANUAL_TRIM_PANEL
{
	int	manual_pitch_down_val;
	NORM_DISC_TYPE	manual_ap_disc_switch;
	int	manual_roll_motor_val;
	int	manual_pitch_motor_val;
	int	manual_backlight_val;
}F16_MANUAL_TRIM_PANEL;

typedef struct F16_TEST_SWITCH_PANEL
{
	ON_OFF_TYPE test_fire_oheat_btn;
	OFF_OXY_OTY_TYPE test_oxy_oty_switch;
	ON_OFF_TYPE test_mal_ind_btn;
	OFF_PROBE_HEAT_TEST_TYPE test_probe_heat_switch;
	OFF_EPU_GEN_TYPE test_epu_gen_switch;
	TEST_NORM_MAINT_TYPE test_test_switch;
	//	AFT_FWD_TYPE	test_stick_switch;
	int test_pwr_a_light;
	int test_pwr_b_light;
	int test_pwr_c_light;
	int test_pwr_d_light;
	int test_backlight_val;
}F16_TEST_SWITCH_PANEL;

typedef struct F16_ENG_JET_START_CONTROL_PANEL
{
	OFF_START1_START2_TYPE ej_jfs_switch;
	PRI_SEC_TYPE ej_eng_cont_switch;
	AB_RESET_NORM_ENG_DATA_TYPE ej_ane_switch;
	OFF_MAX_POWER_TYPE ej_max_power_switch;
	ON_OFF_TYPE ej_run_light;
	ON_OFF_TYPE ej_reset_solenoid;
	ON_OFF_TYPE ej_power_solenoid;
	int ej_backlight_val;
}F16_ENG_JET_START_CONTROL_PANEL;


typedef struct F16_EPU_CONTROL_PANEL
{
	OFF_ON_NORMAL_TYPE	epu_switch;
	ON_OFF_TYPE	epu_light;
	int	epu_hydrazn_light;
	int	epu_air_light;
	int	epu_backlight_val;
}F16_EPU_CONTROL_PANEL;

typedef struct F16_AUDIO_2_CONTROL_PANEL
{
	ON_OFF_TYPE aud_2_tacan_off_switch;
	ON_OFF_TYPE aud_2_ils_val_off_switch;
	int	aud_2_intercom_val;
	int	aud_2_tacan_val;
	int	aud_2_ils_val;
	OFF_MIC_CIPHER_TYPE	aud_2_hot_switch;
	int	aud_2_backlight_val;
}F16_AUDIO_2_CONTROL_PANEL;

typedef struct F16_MANUAL_CANOPY_CONTROL_HANDLE
{
	int mnual_canopy_handle_val;
}F16_MANUAL_CANOPY_CONTROL_HANDLE;

typedef struct F16_DEFPG_HANDLE {
	int defog_handle;
}DEFPG_HANDLE;

typedef struct F16_ANTI_G_TEST_BUTTON
{
	ON_OFF_TYPE	anti_g_test_btn;
	int	anti_backlight_val;
}F16_ANTI_G_TEST_BUTTON;



typedef struct F16_DEFOG_HANDLE
{
	int	defog_handle;
}F16_DEFOG_HANDLE;

typedef struct F16_CHAFF_FLARE_DISPENSE_BUTTON
{
	ON_OFF_TYPE	chaff_flare_btn;
}F16_CHAFF_FLARE_DISPENSE_BUTTON;

typedef struct F16_REDUCED_IDLE_THRUST_SWITCH
{
	OFF_ARM_TYPE	reduced_thrust_switch;
}F16_REDUCED_IDLE_THRUST_SWITCH;

//typedef struct F16_CANOPY_JETTISON_T_HANDLE
//{
//	NOT_EJECT_EJECT_TYPE	canopy_t_handle;
//}F16_CANOPY_JETTISON_T_HANDLE;


typedef struct F16_MANUAL_PITCH_OVERRIDE_PANEL
{
	OVRD_NORM_TYPE	manual_pitch_switch;
	int	manual_pitch_backlight_val;
}F16_MANUAL_PITCH_OVERRIDE_PANEL;
typedef struct F16_CANOPY_CLOSE_HANDLE
{
	ON_OFF_TYPE canopy_close_handle_limit_switch;
	ON_OFF_TYPE canopy_close_handle_btn;
	ON_OFF_TYPE canopy_close_handle_toggle_1_switch;
	ON_OFF_TYPE canopy_close_handle_toggle_2_switch;


}F16_CANOPY_CLOSE_HANDLE;

typedef struct F16_THROTTLE
{
	ON_OFF_TYPE throttle_block_switch;
	VHF_UHF_IN_OUT_TYPE throttle_com_switch;
	UP_DOWN_TYPE throttle_dog_fight_switch;
	FORWARD_BACKWARD_TYPE throttle_speed_break_switch;
	CURSOR_ENALBLE_TYPE throttle_cursor_switch;
	int throttle_rader_curs_x_val;
	int throttle_rader_curs_y_val;
	int throttle_axis_val;
	int throttle_man_rgn_val;
	int throttle_ant_elv_val;
}F16_THROTTLE;


typedef struct F16_CONSOLE_FLOOD_LIGHT
{
	int	flood_light_1;
	int	flood_light_2;
	int	flood_light_3;
}F16_CONSOLE_FLOOD_LIGHT;



typedef struct LEFT_CONSOLE_TYPE
{
	F16_MANUAL_CANOPY_CONTROL_HANDLE manual_canopy_control_handle;
	F16_DEFOG_HANDLE defog_handle;
	F16_UHF_BACKUP_CONTROL_PANEL	uhf_backup_control_panel;
	F16_AUDIO_1_CONTROL_PENEL	audio_1_control_penel;
	//	F16_ASPJ_PANEL	aspj_panel; //패널 삭제
	F16_ELEC_CONTROL_PANEL	elec_control_panel;
	F16_DVR_CONRTOL_PANEL	dvr_control_panel;
	F16_FUEL_CONTROL_PANEL	fuel_control_panel;
	F16_IFF_PANEL	aux_comm_panel;
	F16_EXT_LIGHTING_CONROL_PANEL	ext_lighting_conrol_panel;
	F16_FLT_CONTROL_PANEL	flt_control_panel;
	F16_MANUAL_TRIM_PANEL	manual_trim_panel;
	F16_TEST_SWITCH_PANEL	test_switch_panel;
	F16_ENG_JET_START_CONTROL_PANEL	eng_jet_start_control_panel;
	F16_EPU_CONTROL_PANEL	epu_control_panel;
	F16_AUDIO_2_CONTROL_PANEL	audio_2_control_panel;
	F16_ANTI_G_TEST_BUTTON	anti_g_test_button;
	F16_CHAFF_FLARE_DISPENSE_BUTTON	chaff_flare_dispense_button;
	F16_REDUCED_IDLE_THRUST_SWITCH	reduced_idle_thrust_switch;
	//	F16_CANOPY_JETTISON_T_HANDLE	canopy_jettison_t_handle;
	F16_CANOPY_CLOSE_HANDLE	canopy_close_handle;
	F16_MANUAL_PITCH_OVERRIDE_PANEL	manual_pitch_override_panel;
	F16_THROTTLE	throttle;
	F16_CONSOLE_FLOOD_LIGHT	console_flood_light;
}LEFT_CONSOLE_TYPE;


typedef struct F16_CAUTION_LIGHT_PANEL
{
	int cau_flcs_fault_light;
	int cau_engine_fault_light;
	int cau_avion_fault_light;
	int cau_seat_not_armed_light;
	int cau_elec_sys_light;
	int cau_sec_light;
	int cau_equip_hot_light;
	int cau_nws_fail_light;
	int cau_probe_heat_light;
	int cau_fuel_oil_hot_light;
	int cau_radar_alt_light;
	int cau_anti_skid_light;
	int cau_cadc_light;
	int cau_inlet_icing_light;
	int cau_iff_light;
	int cau_hook_light;
	int cau_store_conf_light;
	int cau_overheat_light;
	int cau_nuclear_light;
	int cau_oxy_low_light;
	int cau_aft_not_eng_light;
	int cau_eec_light;
	int cau_blank_1_light;
	int cau_cabin_press_light;
	int cau_fwd_fuel_low_light;
	int cau_buc_light;
	int cau_blank_2_light;
	int cau_blank_3_light;
	int cau_aft_fuel_low_light;
	int cau_blank_4_light;
	int cau_blank_5_light;
	int cau_blank_6_light;
}F16_CAUTION_LIGHT_PANEL;


typedef struct F16_STICK
{
	NWS_A_R_DISC_MS_L_STEP_A_G_TOGGLE_A_G_A_A_TYPE stick_nws_btn;
	FWD_AFT_LEFT_RIGHT_TYPE stick_trim_switch;
	ON_OFF_TYPE stick_weapon_release_btn;
	RWS_SAM_TWS_ACM_ACM_boresight_A2G_TYPE stick_tm_fwd_btn;
	STT_TTS_SAM_TWS_SMT_with_no_bug_ACM_TYPE stick_tm_aft_btn;
	GRATER_THAN_0_5_SECOND_TGP_EO_HSD_WITH_DATALINK_TYPE stick_tm_left_btn;
	_1_SECOND_NO_BUG_1_SECOND_BUGGED_TARGET_IRWS_GREATER_ITWS_SMT_ACM_A2G_TYPE stick_tm_right_btn;
	FWD_AFT_LEFT_RIGHT_TYPE stick_dm_switch;
	FWD_AFT_LEFT_RIGHT_TYPE stick_cm_switch;
	ON_OFF_TYPE stick_pinky_btn;
	ON_OFF_TYPE stick_paddle_btn;
	_1_DETENT_2_DETENT_TYPE stick_trigger_switch;
}F16_STICK;


typedef struct F16_EPU_FUEL_QUANTITY_INDICATOR
{
	int epu_fuel_quantity_val;
	int epu_fuel_backlight_val;
}F16_EPU_FUEL_QUANTITY_INDICATOR;



typedef struct F16_LIQUID_OXYGEN_QUANTITY_INDICATOR
{
	int	liquid_oxygen_val;
	int	liquid_backlight_val;
}F16_LIQUID_OXYGEN_QUANTITY_INDICATOR;

typedef struct F16_SYSTEM_A_HYD_PRESS_INDICATOR
{
	int	hyd_a_press_val;
	int	hyd_a_backlight_val;
}F16_SYSTEM_A_HYD_PRESS_INDICATOR;

typedef struct F16_SYSTEM_B_HYD_PRESS_INDICATOR
{
	int	hyd_b_press_val;
	int	hyd_b_backlight_val;
}F16_SYSTEM_B_HYD_PRESS_INDICATOR;

typedef struct F16_HYD_PRESS_LIGHTING_PANEL
{
	int	hyd_press_backlight_val;
}F16_HYD_PRESS_LIGHTING_PANEL;
typedef struct F16_CLOCK
{
	int	clock_knob_big;
	int	clock_knob_small;
}F16_CLOCK;

//typedef struct F16_MAGNETIC_COMPASS
//{
//	int	mag_compass_type;
//}F16_MAGNETIC_COMPASS;

typedef struct F16_FUEL_QUANTITY_INDICATOR
{
	int	fuel_quantity_motor_1;
	int	fuel_quantity_motor_2;
	int	fuel_quantity_backlight_val;
}F16_FUEL_QUANTITY_INDICATOR;

typedef struct F16_PILOT_FAULT_LIST_DISPLAY
{
	int	pilot_fault_list_type;
}F16_PILOT_FAULT_LIST_DISPLAY;

typedef struct RIGHT_AUX_CONSOLE_TYPE
{
	F16_CAUTION_LIGHT_PANEL	caution_light_panel;
	F16_STICK	stick;
	F16_EPU_FUEL_QUANTITY_INDICATOR	epu_fuel_quantity_indicator;
	F16_LIQUID_OXYGEN_QUANTITY_INDICATOR	liquid_oxygen_quantity_indicator;
	F16_SYSTEM_A_HYD_PRESS_INDICATOR	system_a_hyd_press_indicator;
	F16_SYSTEM_B_HYD_PRESS_INDICATOR	system_b_hyd_press_indicator;
	F16_HYD_PRESS_LIGHTING_PANEL	hyd_press_lighting_panel;
	F16_CLOCK	clock;
	//F16_MAGNETIC_COMPASS	magnetic_compass; //패널 삭제 
	F16_FUEL_QUANTITY_INDICATOR	fuel_quantity_indicator;
	//F16_COCKPIT_PRESSURE_ALTIMETER	cockpit_pressure_altimeter; 영상계기 HDMI 협의 필요한듯.
	F16_PILOT_FAULT_LIST_DISPLAY	pilot_fault_list_display;
}RIGHT_AUX_CONSOLE_TYPE;

typedef struct F16_HUD_CONTROL_PANEL
{
	OFF_VV_VAH_VAH_TYPE	hud_vv_vah_switch;
	OFF_ATT_FPM_FPM_TYPE	hud_att_fpm_switch;
	OFF_DED_DATA_PFL_TYPE	hud_ded_data_switch;
	OFF_STBY_PRI_TYPE	hud_depr_ret_switch;
	CAS_TA_GND_SPD_TYPE	hud_cas_switch;
	ALT_RADAR_BARO_AUTO_TYPE	hud_radar_switch;
	DAY_AUTO_BRT_NIGHT_TYPE	hud_day_switch;
	OFF_TEST_STEP_ON_TYPE	hud_test_ste_switch;
	int	hud_backlight_val;
}F16_HUD_CONTROL_PANEL;


typedef struct F16_INTERIOR_LIGHTING_CONTROL_PANEL
{
	int	inter_console_val;
	int	inter_inst_pnl_val;
	int	inter_entry_dis_val;
	int	inter_flood_console_val;
	ON_OFF_TYPE inter_flood_console_high_int_sig;
	int	inter_flood_inst_pnl_val;
	NORM_BRT_DIM_TYPE	inter_mal_ind_switch;
	int	inter_backlight_val;
}F16_INTERIOR_LIGHTING_CONTROL_PANEL;

typedef struct F16_AIR_COND_CONTROL_PANEL
{
	int	airc_temp_ctrl_val;
	ON_OFF_TYPE airc_temp_ctl_off_sig;
	OFF_NORM_DUMP_RAM_TYPE	airc_air_src_switch;
	int	airc_backlight_val;
}F16_AIR_COND_CONTROL_PANEL;

typedef struct AVIONICS_POWER_PANEL {
	OFF_MMC_TYPE	avion_mmc_switch;
	OFF_STA_TYPE	avion_sta_switch;
	OFF_MFD_TYPE	avion_mfd_switch;
	OFF_UFC_TYPE	avion_ufc_switch;
	OFF_STOR_HDG_NORM_NAV_CAL_IN_FLT_ATT_TYPE	avion_egi_switch;
	ZERO_OFF_ON_TYPE	avion_mids_switch;
	OFF_GES_TYPE	avion_ges_switch;
	OFF_DL_TYPE	avion_dl_switch;
	OFF_CPD_TYPE	avion_cpd_switch;
	int avion_backlight_val;

}AVIONICS_POWER_PANEL;

typedef struct F16_AVIONICS_POWER_PANEL
{

	OFF_MMC_TYPE avion_mmc_switch;
	OFF_STA_TYPE avion_sta_switch;
	OFF_MFD_TYPE avion_mfd_switch;
	OFF_UFC_TYPE avion_ufc_switch;
	OFF_STOR_HDG_NORM_NAV_CAL_IN_FLT_ATT_TYPE avion_egi_switch;
	ZERO_OFF_ON_TYPE avion_mids_switch;
	OFF_GES_TYPE avion_ges_switch;
	OFF_DL_TYPE avion_dl_switch;
	OFF_CPD_TYPE avion_cpd_switch;
	int avion_backlight_val;

}F16_AVIONICS_POWER_PANEL;

typedef struct F16_OXYGEN_PANEL
{
	EMERGENCY_NORM_TEST_MASK_TYPE	oxygen_ent_switch;
	NORM_O2_TYPE	oxygen_o2_norm_switch;
	PBG_ON_OFF_TYPE	oxygen_pbg_onoff_switch;
	int	oxygen_supply_motor_val;
	WHITE_BLACK_TYPE	oxygen_flow_light;
	//int	oxygen_supply_backlight_val;
	int	oxygen_backlight_val;
}F16_OXYGEN_PANEL;

typedef struct F16_SNSR_PWR_CONTROL_PANEL
{
	OFF_LEFT_HDPT_TYPE	snsr_left_hdpt_switch;
	OFF_RIGHT_HDPT_TYPE	snsr_right_hdpt_switch;
	OFF_FCR_TYPE	snsr_fcr_switch;
	OFF_RDR_ALT_STBY_TYPE	snsr_rdr_alt_switch;
	int	snsr_backlight_val;
}F16_SNSR_PWR_CONTROL_PANEL;

typedef struct F16_ZEROIZE_PANEL
{
	OFF_OFP_DATA_TYPE	zeroize_switch;
	INNIBIT_NORM_TYPE	zeroize_voice_switch;
	int	zeroize_backlight_val;
}F16_ZEROIZE_PANEL;

typedef struct F16_PLAIN_CHIPHER_PANEL
{
	NORM_CARD1_CARD2_TYPE	plain_switch;
	int	zeroize_backlight_val;
}F16_PLAIN_CHIPHER_PANEL;

typedef struct F16_ENGINE_ANTI_ICE_PANEL
{
	OFF_ON_AUTO_TYPE	eng_anti_engine_switch;
	NORM_UPPER_LOWER_TYPE	eng_anti_iff_switch;
	NORM_UPPER_LOWER_TYPE	eng_anti_uhf_switch;
	int	eng_anti_backlight_val;
}F16_ENGINE_ANTI_ICE_PANEL;

typedef struct F16_SEAT_ADJ_SWITCH
{
	OFF_ON_AUTO_TYPE	seat_adj_switch;
}F16_SEAT_ADJ_SWITCH;

typedef struct F16_DTU
{
	OFF_ON_AUTO_TYPE	dtu;
}F16_DTU;

typedef struct SECURE_VOICE_CONTROL_PANEL {
	ONE_TO_SIX_MAN_OFF_ZALL_REM_OFF_PT_TYPE secure_ent_btn;
	ON_OFF_TYPE secure_right_btn;
	ON_OFF_TYPE secure_up_btn;
	ON_OFF_TYPE secure_esc_btn;
	int secure_ocmi_val;
	int snsr_backlight_val;

}SECURE_VOICE_CONTROL_PANEL;


typedef struct F16_FLOOD_LIGHT
{
	int	flood_light_1;
	int	flood_light_2;
	int	flood_light_3;
	int	flood_light_4;
}F16_FLOOD_LIGHT;

typedef struct RIGHT_CONSOLE_TYPE
{
	F16_HUD_CONTROL_PANEL	hud_control_panel;
	F16_INTERIOR_LIGHTING_CONTROL_PANEL	interior_lighting_control_panel;
	F16_AIR_COND_CONTROL_PANEL	air_cond_control_panel;
	F16_AVIONICS_POWER_PANEL	avionics_power_panel;
	F16_OXYGEN_PANEL	oxygen_panel;
	F16_SNSR_PWR_CONTROL_PANEL	snsr_pwr_control_panel;
	F16_ZEROIZE_PANEL	zeroize_panel;
	F16_PLAIN_CHIPHER_PANEL	plain_chipher_panel;
	F16_ENGINE_ANTI_ICE_PANEL	engine_anti_ice_panel;
	F16_SEAT_ADJ_SWITCH	seat_adj_switch;
	F16_DTU	dtu;
	F16_FLOOD_LIGHT	flood_light;
}RIGHT_CONSOLE_TYPE;

typedef struct F_16_COCKPIT_TO_HOST_TYPE
{
	CENTER_CONSOLE_TYPE	f16_center_console_type;
	LEFT_AUX_CONSOLE_TYPE	f16_left_aux_console_type;
	LEFT_CONSOLE_TYPE	f16_left_console_type;
	RIGHT_AUX_CONSOLE_TYPE	f16_right_aux_console_type;
	RIGHT_CONSOLE_TYPE	f16_right_console_type;
}F_16_COCKPIT_TO_HOST_TYPE;



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//f-15입니다.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct MPD_BUTTON_TYPE
{
	ON_OFF_TYPE S1;
	ON_OFF_TYPE S2;
	ON_OFF_TYPE S3;
	ON_OFF_TYPE S4;
	ON_OFF_TYPE S5;
	ON_OFF_TYPE S6;
	ON_OFF_TYPE S7;
	ON_OFF_TYPE S8;
	ON_OFF_TYPE S9;
	ON_OFF_TYPE S10;
	ON_OFF_TYPE S11;
	ON_OFF_TYPE S12;
	ON_OFF_TYPE S13;
	ON_OFF_TYPE S14;
	ON_OFF_TYPE S15;
	ON_OFF_TYPE S16;
	ON_OFF_TYPE S17;
	ON_OFF_TYPE S18;
	ON_OFF_TYPE S19;
	ON_OFF_TYPE S20;
	ON_OFF_TYPE BRT_UP;
	ON_OFF_TYPE BRT_DOWN;
	ON_OFF_TYPE CONT_UP;
	ON_OFF_TYPE CONT_DOWN;
	ON_OFF_TYPE PWR_ON;
	ON_OFF_TYPE PWR_OFF;

}MPD_BUTTON_TYPE;

typedef struct UFC_BUTTON_TYPE
{
	int Vol_R1_Knob;
	int Vol_R3_Knob;
	int Vol_R2_Knob;
	int Vol_R4_Knob;
	int Brt_Knob;
	LEFT_RIGHT_NORMAL_TYPE Left_Channel_Select_Knob; //change type 19. 01. 13
	LEFT_RIGHT_NORMAL_TYPE Right_Channel_Select_Knob; //change type 19. 01. 13
	ON_OFF_TYPE Left_Channel_Select_Btn;
	ON_OFF_TYPE Right_Channel_Select_Btn;
	UFC_PWR_MODE_TYPE UFC_Pwr_MODE_Switch;
	ON_OFF_TYPE S1;
	ON_OFF_TYPE S2;
	ON_OFF_TYPE S3;
	ON_OFF_TYPE S4;
	ON_OFF_TYPE S5;
	ON_OFF_TYPE S6;
	ON_OFF_TYPE S7;
	ON_OFF_TYPE S8;
	ON_OFF_TYPE S9;
	ON_OFF_TYPE S10;
	ON_OFF_TYPE LEFT_GREC;
	ON_OFF_TYPE RIGHT_GREC;
	ON_OFF_TYPE MARK;
	ON_OFF_TYPE IP;
	ON_OFF_TYPE DOT;
	ON_OFF_TYPE SHF;
	ON_OFF_TYPE AP;
	ON_OFF_TYPE CLR;
	ON_OFF_TYPE DATA;
	ON_OFF_TYPE MENU;
	ON_OFF_TYPE KEY_0;
	ON_OFF_TYPE KEY_1;
	ON_OFF_TYPE KEY_2;
	ON_OFF_TYPE KEY_3;
	ON_OFF_TYPE KEY_4;
	ON_OFF_TYPE KEY_5;
	ON_OFF_TYPE KEY_6;
	ON_OFF_TYPE KEY_7;
	ON_OFF_TYPE KEY_8;
	ON_OFF_TYPE KEY_9;
	ON_OFF_TYPE EMIS_Btn;
}UFC_BUTTON_TYPE;

typedef struct INDICATOR_TYPE
{
	PULL_TO_CAGE_KNOB_TYPE Pull_To_Cage_Knob;
	int Standby_Attitude_Knob_Value;
	int Altimeter_Knob_Value;
	ON_OFF_TYPE Clock_Push_Btn;
	int Clock_Knob_Value;
	int Fuel_Bingo_Knob_Value;
	FUEL_QTY_SELECT_TYPE Fuel_Qty_Select_Switch;

}INDICATOR_TYPE;

typedef struct LEFT_PANEL_TYPE
{
	// MISCELLANEOUS(MISC) CONTROL PANEL 
	AUTO_EMERG_TYPE Left_Inlet_Ramp_Switch;
	AUTO_EMERG_TYPE Right_Inlet_Ramp_Switch;
	ANTI_SKID_TYPE Anti_Skid_Switch;
	AUTO_EMERG_TYPE Roll_Ratio_Switch;
	LDG_TAXI_LIGHT_TYPE LDG_Taxi_Light_Switch;
	
	//CONTROL AUGMENTATION SYSTEM(CAS) CONTROL PANEL 
	ON_OFF_RESET_TYPE Yaw_Switch;
	ON_OFF_RESET_TYPE Roll_Switch;
	ON_OFF_RESET_TYPE Pitch_Switch;
	ON_OFF_TYPE CAS_Bit_Btn;
	TF_TYPE TF_Switch;
	ON_OFF_TYPE TO_Trim_Btn;

	//FUEL CONTROL PANEL 
	FUEL_CONTROL_TYPE Wing_Fuel_Control_Switch;
	FUEL_CONTROL_TYPE CTR_Fuel_Control_Switch;
	FUEL_CONTROL_TYPE Conf_Tank_Fuel_Control_Switch;
	DUMP_TYPE Dump_Switch;
	EXT_TRANS_TYPE Ext_Trans_Switch;
	OPEN_CLOSE_ORIDE_TYPE Slipway_Switch;
	LEFT_RIGHT_NORMAL_TYPE Conf_Tank_Emerg_Trans_Switch;
	
	//THROTTLE QUADRANT
	// change order like iomap
	int Left_Throttle_Position;
	int Right_Throttle_Position;
	ON_OFF_TYPE Left_Throttle_Lift;
	ON_OFF_TYPE Right_Throttle_Lift;
	int Antenna_Elev_Knob;
	MULTIFUNCTION_TYPE HAT_Switch;	// Right_Multifunction Switch
	int TDC_X;
	int TDC_Y;
	ON_OFF_TYPE TDC_Press_Btn;
	POSITION_TYPE CMD_Dispenser_Switch;
	ON_OFF_TYPE Laser_Fire_Btn;		// Left Multifunction Switch
	POSITION_TYPE Flap_Switch;
	POSITION_TYPE Microphone_Switch;
	POSITION_TYPE Speed_Brake_Switch;
	POSITION_TYPE Undesignate_Missle_Reject_Switch;
	POSITION_TYPE Weapon_Mode_Switch;
	POSITION_TYPE Rudder_Trim_Switch;
	THROTTLE_POSITION_TYPE Left_Gate_Switch;  //add 2019.01.02
	THROTTLE_POSITION_TYPE Right_Gate_Switch; //add 2019.01.02

	//EXTERIOR LIGHTS CONTROL PANEL 
	EXTERIOR_LIGHT_TYPE Formation_Mode_Switch;  
	EXTERIOR_LIGHT_TYPE Position_Mode_Switch; 
	FORMATION_LIGHT_TYPE Formation_Light_Switch;
	ON_OFF_TYPE Anti_Collision_Switch;
	VERT_TAIL_FLOOD_LIGHT_TYPE Vert_Tail_Flood_Switch;

	//REMOTE INTERCOMMUNICATIONS CONTROL PANEL
	int Caution_Volume_Knob;	//TEWS VOL CONTROL
	int Launch_Volume_Knob;		//TEWS VOL CONTROL
	int ICS_Volume_Knob;		//ICS/WPN VOL CONTROL
	int WPN_Volume_Knob;		//ICS/WPN VOL CONTROL
	int ILS_Volume_Knob;		//ILS/TACAN VOL CONTROL
	int TACAN_Volume_Knob;		//ILS/TACAN VOL CONTROL
	CRYPTO_TYPE Crypto_Switch;
	ON_OFF_ORIDE_TYPE MIC_Switch;
	ON_OFF_TYPE VM_Tone_Silence_Btn;
	RAD1_ANT_TYPE Rad1_Ant_Switch;
	TONE_TYPE Tone_Switch;
	CIPHER_TEXT_TYPE Cipher_Text_Switch;
	IFF_MODE_TYPE IFF_Mode_Switch;
	IFF_LIGHT_TYPE IFF_Light_Switch;
	IFF_MASTER_TYPE IFF_Master_Switch;

	//SENSOR CONTROL PANEL 
	ON_OFF_STBY_TYPE TF_Radar_Switch;
	RDR_ALT_TYPE Radar_Alt_Switch;
	RADAR_MODE_TYPE Radar_Mode_Switch;
	FDL_TYPE FDL_Switch;
	int Nav_Flir_Gain;
	int Nav_Flir_Level;
	ON_OFF_STBY_TYPE Nav_Flir_Switch;
	ON_OFF_TYPE EGI_1_Switch;
	ON_OFF_TYPE EGI_2_Switch;
	ON_OFF_STBY_TYPE IRST_Switch;
	ON_OFF_TYPE ADCP_Reset_Btn;

	//GND PWR PANEL 
	ON_OFF_AUTO_TYPE Ground_Power_1_Switch; //a on / auto / b on , change type?  2019.01.13 // ON = A ON, AUTO = AUTO, OFF = B ON
	GROUND_PWR_TYPE Ground_Power_2_Switch; //not use off , change type?  2019.01.13 // 2019.01.14 GROND_PWR_TYPE 추가
	GROUND_PWR_TYPE Ground_Power_3_Switch; //not use off , change type?  2019.01.13 // 2019.01.14 GROND_PWR_TYPE 추가
	GROUND_PWR_TYPE Ground_Power_4_Switch; //not use off , change type?  2019.01.13 // 2019.01.14 GROND_PWR_TYPE 추가
	ON_OFF_AUTO_TYPE Ground_Power_PACS_Switch;
	ON_OFF_AUTO_TYPE Ground_Power_ADCPAIU1_Switch;

	//ANTI-G PANEL 
	ON_OFF_TYPE Anti_G_Btn;

	//CANOPY JETTISON HANDLE
	CANOPY_JETTISON_TYPE Canopy_Jettison_Btn;

	CANOPY_LOCK_TYPE Canopy_Lock_Handle;

	//FLYUP ENABLE SWITCH
	ON_OFF_TYPE Flyup_Enable_Switch;
	
	//SEAT ADJUST SWITCH
	POSITION_TYPE Seat_Adjust_Switch;

	//IFF ANTENNA SELECT SWITCH
	IFF_ANTENNA_TYPE IFF_Antenna_Switch;

	//EMERGENCY AIR REFUELING SWITCH 
	OPEN_NORM_TYPE Emerg_Air_Refuel_Switch;

	//ARMAMENT SAFETY OVERRIDE SWITCH
	SEAT_ARMAMENT_TYPE Armament_Override_Switch;

}LEFT_PANEL_TYPE;

typedef struct RIGHT_PANEL_TYPE
{
	//OXYGEN REGULATOR
	OXYGEN_EMERG_TYPE Oxygen_Emerg_Switch;
	OXYGEN_TYPE Oxygen_Switch;
	OXYGEN_SUPPLY_TYPE Oxygen_Supply_Switch;

	//ECS PANEL 
	ON_OFF_TYPE Oxy_Bit_Btn;
	ANTI_FOG_TYPE Anti_Fog_Switch;
	ON_OFF_TYPE	Anti_Ice_Windshield_Switch;
	ON_OFF_TYPE	Anti_Ice_PitotHeat_Switch;
	ON_OFF_TEST_TYPE Anti_Ice_EngHeat_Switch;

	//ENGINE CONTROL PANEL 
	ON_OFF_TYPE	Left_Engine_Gen_Switch;
	ON_OFF_TYPE	Right_Engine_Gen_Switch;
	ENGINE_EMERG_TYPE Engine_EmergeGen_Switch;
	ON_OFF_TYPE Left_Engine_Control_Switch;
	ON_OFF_TYPE Right_Engine_Control_Switch;
	ON_OFF_TYPE Left_Engine_Master_Switch;
	ENGINE_EXTPWR_TYPE Engine_ExtPwr_Switch;
	ON_OFF_TYPE Engine_Starter_Switch;
	ON_OFF_TYPE Right_Engine_Master_Switch;

	//AIR CONDITION CONTROL PANEL
	AIRCOND_TEMP_TYPE Aircond_Temp_Switch;
	AIRCOND_FLOW_TYPE Aircond_Flow_Switch;
	int Temp_Control_Knob;
	AIR_SOURCE_TYPE Air_Source_Switch;

	//EW CONTROL PANEL 
	ON_OFF_TYPE		RWR_Power_Switch;
	RWR_COMBAT_TYPE RWR_Combat_Switch;
	ON_OFF_TYPE		ICS_Power_Switch;
	ICS_SWITCH_TYPE ICS_Stby_Switch;
	CMD_BYPASS_TYPE CMD_Switch;
	CMD_JETTISON_TYPE CMD_Jettison_Switch;

	//INTERIOR LIGHTS CONTROL PANEL 
	int Console_Light_Knob;
	int Inst_Pnl_Light_Knob;
	ON_OFF_TYPE	Inst_Pnl_Light_Off_Switch; //add 19.01.13
	ON_OFF_TYPE	Light_Test_Switch;
	int UFC_Light_Knob;
	ON_OFF_TYPE	Stby_Comp_Switch;
	int Chart_Light_Knob;
	DAY_NIGHT_TYPE Dislplay_Switch;
	int Caution_Light_Knob;
	ON_OFF_TYPE Caution_Light_Reset;
	int Storm_Flood_Light_Knob;
	ON_OFF_TYPE Storm_Flood_BRT_Switch;

	//AERP PANEL 

	//HMD CONTROL PANEL 
	int HMD_Control_Knob;
	ON_OFF_TYPE HMD_Power;

	//CANOPY CONTROL HANDLE
	CANOPY_CONTROL_TYPE Canopy_Control_Switch;

}RIGHT_PANEL_TYPE;

typedef struct MAIN_PANEL_TYPE
{
	//UPFROUNT CONTROL PANEL 
	UFC_BUTTON_TYPE UFC_Panel;

	//MASTER CAUTION LIGHT
	ON_OFF_TYPE Master_Caution_Btn;

	//FIRE WARNING/ EXTINGUISHING PANEL
	DISCHARGE_TYPE	Discharge_Switch;
	ON_OFF_TYPE AMAD_Fire_Btn;
	ON_OFF_TYPE Left_Engine_Fire_Btn;
	ON_OFF_TYPE Right_Engine_Fire_Btn;

	//MULTI-PURPOSE DISPLAY, LEFT
	MPD_BUTTON_TYPE Left_MPD;

	//MULTI-PURPOSE DISPLAY, RIGHT
	MPD_BUTTON_TYPE Right_MPD;

	//HEAD UP DISPLAY CONTROL PANEL
	int Symbol_Brt_Knob;
	SYM_DECLUTTER_TYPE Symbol_Declutter_Switch;
	DAY_NIGHT_TYPE Day_Night_Switch;
	ON_OFF_TYPE Test_Btn; //delete 19.01.13 //don't delete... use this button
	int Video_Brt_Knob;
	int Video_Cont_Knob;
	UFC_MODE_TYPE UFC_Mode_Button; //delete 19. 01. 13 //don't delete.. UFC Mode Button

	//add 19. 01. 13 // 삭제 - UFC_Mode_Button 변수 이용.
	//ON_OFF_TYPE Air_to_Air_Switch;
	//ON_OFF_TYPE Air_to_Ground_Switch;
	//ON_OFF_TYPE Air_to_Nav_Switch;
	//ON_OFF_TYPE Air_to_Inst_Switch;

	//MULTI - PURPOSE COLOR DISPLAY
	MPD_BUTTON_TYPE MPCD;

	//ARMAMENT CONTROL PANEL 
	ARMT_CONTROL_TYPE	ARMT_Control_Switch;
	ON_OFF_TYPE			ARMT_JETT_Switch;  // add 2019.01.02
	ARMT_TYPE			ARMT_Gun_Switch;
	ARMT_TYPE			ARMT_Master_Switch;

	//EMERGENCY JETTISON BUTTON
	ON_OFF_TYPE Emergency_Jettison_Btn;

	//DATA TRANSFER MODULE RECEPTACLE
	ON_OFF_TYPE DTM_Receptacle;

	//ARRESTING HOOK CONTROL SWITCH
	UP_DOWN_TYPE Arresting_Hook_Switch;

	//LANDING GEAR CONTROL HANDLE
	UP_DOWN_TYPE LDG_Gear_Switch;
	ON_OFF_TYPE Warn_Tone_Sil_Btn;
	ON_OFF_TYPE LDG_Nose_Switch;//add 19. 01. 13
	ON_OFF_TYPE LDG_Left_Switch;//add 19. 01. 13
	ON_OFF_TYPE LDG_Right_Switch;//add 19. 01. 13

	//EMERGENCY LANDING GEAR HANDLE
	PULL_PUSH_TYPE Emerg_LDG_Switch;

	//PITCH RATIO SELECT SWITCH
	AUTO_EMERG_TYPE	Pitch_Ratio_Switch;

	//JET FUEL STARTER CONTROL HANDLE/ BRAKE HOLD SWITCH
	JET_STARTER_TYPE JET_Fuel_Starter_Switch;
	ON_OFF_TYPE	Brake_Hold_Switch;

	//EMERGENCY VENT CONTROL HANDLE 
	PULL_PUSH_TYPE Emerg_Vent_Switch;

	//EMERGENCY BRAKE/ STEERING CONTROL HANDLE 
	PULL_PUSH_TYPE Emerg_Brake_Steer_Switch;

	//CIRCUIT BREAKER PANEL
	Circuit_Breaker_Type Center_CB[14];
	/*
	--- Center CB Array Info ---
	0 - AFCS ESS DC(A1)
	1 - AFCS ESS DC(A2)
	2 - AFCS ESS DC(A3)
	3 - LG(A4)
	4 - NWS(A5)
	5 - SPD BK(A6)
	6 - L PITOT HEAT(A7)
	7 - R PITOT HEAT(A8)
	8 - AFCS ESS AC(B1)
	9 - AFCS ESS AC(B2)
	10 - FLAP(B3)
	11 - AFCS DC(B4)
	12 - AFCS DC(B5)
	13 - AFCS DC(B6)
	*/

	//CONTROL STICK
	int Pitch_Stick;
	int Roll_Stick;
	STICK_POSITION_TYPE Stick_Position; //add 0227
	CASTLE_TYPE Castle_Switch;
	TRIM_TYPE Trim_Switch;
	AUTO_ACQUISITION_TYPE Auto_Acquisition_Switch;
	ON_OFF_TYPE Weapon_Release_Btn;
	ON_OFF_TYPE Nose_Gear_Steering_Btn;
	//ON_OFF_TYPE Air_Refueling; // delete 19.01.13
	ON_OFF_TYPE Paddle_Switch;
	STICK_TRIGGER_TYPE Stick_Trigger_Btn;
	ON_OFF_TYPE Stick_Trim_Complete; //add 19.01.13
	
	//RUDDER PEDAL
	int Rudder_Pedal;
	ON_OFF_TYPE Left_Brake_Pedal;
	ON_OFF_TYPE Right_Brake_Pedal;
	ON_OFF_TYPE Rudder_Trim_Complete; //add 19.01.13

	//INDICATOR
	INDICATOR_TYPE Indicator;
	
	UP_DOWN_TYPE Left_Ejection_Handle;
	UP_DOWN_TYPE Right_Ejection_Handle;

	//ON_OFF_TYPE MC_Receptacle; delete 19.01.13
}MAIN_PANEL_TYPE;


#pragma pack(pop)