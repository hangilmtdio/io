#pragma once

#include "sim_std.h"
#include "std_enum.h"

#pragma pack(push, 1)


typedef struct F16_CMFD_BUTTON_TYPE
{
	public ON_OFF_TYPE mfd_btn_1;
	public ON_OFF_TYPE mfd_btn_2;
	public ON_OFF_TYPE mfd_btn_3;
	public ON_OFF_TYPE mfd_btn_4;
	public ON_OFF_TYPE mfd_btn_5;
	public ON_OFF_TYPE mfd_btn_6;
	public ON_OFF_TYPE mfd_btn_7;
	public ON_OFF_TYPE mfd_btn_8;
	public ON_OFF_TYPE mfd_btn_9;
	public ON_OFF_TYPE mfd_btn_10;
	public ON_OFF_TYPE mfd_btn_11;
	public ON_OFF_TYPE mfd_btn_12;
	public ON_OFF_TYPE mfd_btn_13;
	public ON_OFF_TYPE mfd_btn_14;
	public ON_OFF_TYPE mfd_btn_15;
	public ON_OFF_TYPE mfd_btn_16;
	public ON_OFF_TYPE mfd_btn_17;
	public ON_OFF_TYPE mfd_btn_18;
	public ON_OFF_TYPE mfd_btn_19;
	public ON_OFF_TYPE mfd_btn_20;
	public UP_CDENTER_DOWN_TYPE mfd_gain_up_btn;
	public UP_CDENTER_DOWN_TYPE mfd_brt_up_btn;
	public UP_CDENTER_DOWN_TYPE mfd_sys_up_btn;
	public UP_CDENTER_DOWN_TYPE mfd_com_up_btn;
};


typedef struct F16_ICP_BUTTON_TYPE
{
	public ON_OFF_TYPE icp_com_1_btn;
	public ON_OFF_TYPE icp_com_2_btn;
	public ON_OFF_TYPE icp_iff_btn;
	public ON_OFF_TYPE icp_list_btn;
	public ON_OFF_TYPE icp_a_a_btn;
	public ON_OFF_TYPE icp_a_g_btn;
	public ON_OFF_TYPE icp_t_ils_1_btn;
	public ON_OFF_TYPE icp_alow_2_n_btn;
	public ON_OFF_TYPE icp_num_3_btn;
	public ON_OFF_TYPE icp_stpt_4_w_btn;
	public ON_OFF_TYPE icp_crus_5_btn;
	public ON_OFF_TYPE icp_time_6_e_btn;
	public ON_OFF_TYPE icp_mark_7_btn;
	public ON_OFF_TYPE icp_fix_8_s_btn;
	public ON_OFF_TYPE icp_a_cal_9_btn;
	public ON_OFF_TYPE icp_m_sel_0_btn;
	public ON_OFF_TYPE icp_rcl_btn;
	public ON_OFF_TYPE icp_entr_btn;
	public UP_CDENTER_DOWN_TYPE icp_cursor_updown_btn;
	public RTN_UP_DOWN_SEQ_NOT_PRESS_TYPE icp_joy_btn;
	public DRIFT_NORM_WARN_RESET_TYPE icp_dnw_switch;
	public ON_OFF_TYPE icp_flir_wx_btn;
	public UP_CENTER_DOWN_TYPE icp_flir_cursor_updown_btn;
	public GAIN_LVL_AUTO_TYPE icp_flir_gla_switch;
	public int icp_sym_val;
	public int icp_brt_val;
	public int icp_ret_depr_val;

};


typedef struct F16_THREAT_WARNING_PANEL
{

	public ON_OFF_TYPE warn_handoff_btn;
	public ON_OFF_TYPE warn_launch_btn;
	public ON_OFF_TYPE warn_mode_btn;
	public ON_OFF_TYPE warn_on_unknown_btn;
	public ON_OFF_TYPE warn_on_sys_test_btn;
	public ON_OFF_TYPE warn_tgt_sept_btn;
	public int warn_handoff_light_val;
	public int warn_launch_light_val;
	public int warn_mode_open_light_val;
	public int warn_on_unknown_light_val;
	public int warn_on_sys_test_light_val;
	public int warn_tgt_sept_light_val;
	public int warn_handoff_h_light_val;
	public int warn_mode_priority_light_val;
	public int warn_u_unknown_light_val;

	public int warn_sys_test_light_val;

	public int warn_tgt_sept1_light_val;
	public int warn_tgt_sept2_light_val;

	public ON_OFF_TYPE icp_sym_roll_off_switch;
	public ON_OFF_TYPE icp_brt_roll_off_switch;
	public ON_OFF_TYPE icp_ret_depr_roll_off_switch;
	public ON_OFF_TYPE icp_cont_roll_off_switch;

};



typedef struct F16_MASTER_CAUTION_LIGHT
{
	public  ON_OFF_TYPE master_caution_btn;
	public int master_caution_light_val;
};


typedef struct F16_IFF_IDENT_F_ACK_BUTTON
{
	public ON_OFF_TYPE iff_indent_btn;
	public ON_OFF_TYPE f_ack_btn;
	public ON_OFF_TYPE nvg_left_btn;
	public ON_OFF_TYPE nvg_right_btn;
	public int iff_backlight_val;
};




typedef struct F16_MISC
{
	public NORM_QUIET_SELENT_TYPE misc_rf_switch;
	public OFF_ARM_TYPE misc_laser_switch;
	public ON_OFF_TYPE misc_alt_rel_btn;
	public ARM_OFF_SIMULATE_TYPE misc_master_switch;
	public HDG_SEL_ATT_HOLD_STRG_SEL_TYPE misc_roll_switch;
	public ALT_HOLD_AP_OFF_ATT_HOLD_TYPE misc_pitch_switch;
	public ON_OFF_TYPE misc_ecm_light;
	public ON_OFF_TYPE misc_pitch_solenoid;
	public int misc_adv_active_light_val;
	public int misc_adv_stby_light_val;
	public int misc_backlight_val;
	public ON_OFF_TYPE misc_adv_mode_btn;
	public int nws_brt_val_1;
	public int nws_brt_val_2;
	public int nws_brt_val_3;
	public int nws_brt_val_4;

};


typedef struct F16_AR_STATUS_NWS_INDICATOR
{
	public int nws_brt_val;
	public int ar_indexer_rdy_light_val;
	public int ar_indexer_nws_light_val;
	public int ar_indexer_disc_light_val;
};


typedef struct F16_WARING_LIGHTS
{
	public int warn_eng_fire_light_val;
	public int warn_engine_light_val;
	public int warn_hyd_oil_press_light_val;
	public int warn_flcs_light_val;
	public int warn_dbu_on_light_val;
	public int warn_to_ldg_config_light_val;
	public int warn_canopy_light_val;
	public int warn_blank_light_val;
};



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
	public int aoa_red_light_val;
	public int aoa_green_light_val;
	public int aoa_orange_light_val;
	public int aoa_brt_val_1;
	public int aoa_brt_val_2;
	public int aoa_brt_val_3;
	public int aoa_brt_val_4;

};



typedef struct F16_TF_FAIL_WARINING_LIGHT
{
	public  int tf_fail_light;
	public  int tf_left_down_light;
	public  int tf_right_up_light;
	public  int tf_right_down_light;
};


typedef struct F16_OIL_PRESSURE_INDICATOR
{
	public int oil_pressure_ind_val;
	public int oil_pressure_backlight_val;
};



typedef struct F16_NOZ_POS_INDICATOR
{
	public int noz_pos_ind_val;
	public int noz_pos_backlight_val;
};


typedef struct F16_RPM_INDICATOR
{
	public  int rpm_ind_val;
	public  int rpm_backlight_val;
};



typedef struct F16_FTIT_INDICATOR
{
	public int ftit_ind_val;
	public int ftit_backlight_val;
};

//패널 삭제
//typedef struct F16_MRK_BCN_LIGHT
//{
//	ON_OFF_TYPE	mrk_bcn_light;
//
//}F16_MRK_BCN_LIGHT;


typedef struct F16_RUDDER_PEDALS
{
	public int rudder_pedal_1_val;
	public int rudder_pedal_2_val;
	public int rudder_pedal_3_val;
};

//
//typedef struct F16_AIRSPEED_MACH_INDICATOR
//{
//    int airs_set_index_val;
//}; 삭제


typedef struct F16_ATTIDUDE_DIRECTOR_INDICATOR
{
	public  int att_arrow_knob_val;
};



typedef struct F16_ALTIMETER
{
	public ELECT_PNEU_TYPE alti_elec_pneu_switch;
	public int alti_left_knob_val;
};




typedef struct F16_DATA_ENTRY_DISPLAY
{
	public   int data_entry_disp;
};



typedef struct F16_FUEL_FLOW_INDICATOR
{
	public int fuel_flow_indicator;
};




typedef struct F16_RWR
{
	public  int rwr_int_switch_val;
	public  int rwr_left_right_val;
	public int rwr_up_down_val;

};


typedef struct F16_STANDBY_ATTITUDE_INDICATOR
{
	public ON_OFF_TYPE sai_pull_switch;
	public int sai_pull_to_cage_knob;

};



public unsafe struct F16_CPD
{
	public ON_OFF_TYPE cpd_gain_btn;
	public ON_OFF_TYPE cpd_left_btn_1;
	public ON_OFF_TYPE cpd_left_btn_2;
	public ON_OFF_TYPE cpd_left_btn_3;
	public ON_OFF_TYPE cpd_left_btn_4;
	public ON_OFF_TYPE cpd_left_btn_5;
	public ON_OFF_TYPE cpd_left_btn_6;
	public UP_CENTER_DOWN_TYPE cpd_left_btn_7;
	public ON_OFF_TYPE cpd_left_btn_8;
	public UP_CENTER_DOWN_TYPE cpd_sym_btn;
	public ON_OFF_TYPE cpd_right_btn_1;
	public ON_OFF_TYPE cpd_right_btn_2;
	public ON_OFF_TYPE cpd_right_btn_3;
	public ON_OFF_TYPE cpd_right_btn_4;
	public ON_OFF_TYPE cpd_right_btn_5;
	public ON_OFF_TYPE cpd_right_btn_6;
	public UP_CENTER_DOWN_TYPE cpd_right_btn_7;
	public ON_OFF_TYPE cpd_right_btn_8;
	public ON_OFF_TYPE cpd_top_btn_1;
	public ON_OFF_TYPE cpd_top_btn_2;
	public ON_OFF_TYPE cpd_top_btn_3;
	public ON_OFF_TYPE cpd_top_btn_4;
	public ON_OFF_TYPE cpd_top_btn_5;
	public ON_OFF_TYPE cpd_bottom_btn_1;
	public ON_OFF_TYPE cpd_bottom_btn_2;
	public ON_OFF_TYPE cpd_bottom_btn_3;
	public ON_OFF_TYPE cpd_bottom_btn_4;
	public ON_OFF_TYPE cpd_bottom_btn_5;
	public ON_OFF_TYPE cpd_crs_hdg_switch;
	private fixed int cpd_display_1[4];

	public int cpd_display_1_1;
	public int cpd_display_1_2;
	public int cpd_display_1_3;
	public int cpd_display_1_4;


	public int cpd_display_2_1;
	public int cpd_display_2_2;
	public int cpd_display_2_3;
	public int cpd_display_2_4;

	public int cpd_display_3_1;
	public int cpd_display_3_2;
	public int cpd_display_3_3;
	public int cpd_display_3_4;
	public int cpd_display_3_5;
	public int cpd_display_3_6;
	public int cpd_display_3_7;
	public int cpd_display_3_8;

	public int cpd_display_4_1;
	public int cpd_display_4_2;
	public int cpd_display_4_3;
	public int cpd_display_4_4;

	//public fixed int cpd_display_2[4];
	//public fixed int cpd_display_3[8];
	//public fixed int cpd_display_4[4];


}

typedef struct CENTER_CONSOLE_TYPE
{
	public F16_CPD cpd;
	public F16_STANDBY_ATTITUDE_INDICATOR standby_attitude_indicator;
	public F16_RWR rwr;
	public F16_CMFD_BUTTON_TYPE cmfd_button_type;
	public F16_ICP_BUTTON_TYPE icp_button_type;
	public F16_THREAT_WARNING_PANEL threat_warning_panel;
	public F16_MASTER_CAUTION_LIGHT master_caution_light;
	public F16_IFF_IDENT_F_ACK_BUTTON iff_ident_f_ack_button;
	public F16_MISC misc;
	public F16_AR_STATUS_NWS_INDICATOR ar_status_nws_indicator;
	public F16_WARING_LIGHTS waring_lights;
	//public //F16_INSTR_MODE_SELECT_PANEL	instr_mode_select_panel;
	//public //F16_FUEL_QTY_SEL_PANEL	fuel_qty_sel_panel;
	public F16_AOA_INDEXER aoa_indexer;
	public F16_TF_FAIL_WARINING_LIGHT tf_fail_warining_light;
	public F16_OIL_PRESSURE_INDICATOR oil_pressure_indicator;
	public F16_NOZ_POS_INDICATOR noz_pos_indicator;
	public F16_RPM_INDICATOR rpm_indicator;
	public F16_FTIT_INDICATOR ftit_indicator;
	//public //F16_MRK_BCN_LIGHT	mrk_bcn_light; 패널 삭제
	public F16_RUDDER_PEDALS rudder_pedals;
	//public F16_AIRSPEED_MACH_INDICATOR airspeed_mach_indicator;
	 // public F16_ATTIDUDE_DIRECTOR_INDICATOR attidude_director_indicator; //패널삭제
	  // public F16_ALTIMETER altimeter;   // 패널 삭제
	public F16_DATA_ENTRY_DISPLAY data_entry_display;
	public F16_FUEL_FLOW_INDICATOR fuel_flow_indicator;
};




typedef struct F16_LANDING_GEAR_CONTROL_PANEL
{
	public  ON_OFF_TYPE lg_emer_store_btn;
	public  DOWN_UP_TYPE lg_hook_switch;
	public  OFF_ENABLE_TYPE lg_gnd_jet_switch;
	public  CHAN_1_CHAN_2_TYPE lg_brake_switch;
	public  OFF_ON_ANTI_SKID_TYPE lg_park_break_switch;
	public  CAT_1_CAT_2_TYPE lg_store_conf_switch;
	public  ON_OFF_TYPE lg_horn_silencer_btn;
	public  OFF_LANDING_TAXI_TYPE lg_landing_light_switch;
	public  ON_OFF_TYPE lg_dn_lock_btn;
	public  ON_OFF_TYPE lg_park_break_solenoid;
	public  ON_OFF_TYPE lg_wheel_front_light;
	public  ON_OFF_TYPE lg_wheel_left_light;
	public  ON_OFF_TYPE lg_wheel_right_light;
	//public  DOWN_UP_TYPE lg_handle_switch; 스위치 삭제-
	public int lg_backlight_val;
};



typedef struct F16_CMDS_CONTROL_PANEL
{
	public OFF_ENABLE_TYPE cmds_rwr_switch;
	public OFF_ENABLE_TYPE cmds_jmr_switch;
	public OFF_ENABLE_TYPE cmds_mws_switch;
	public OFF_ENABLE_TYPE cmds_01_switch;
	public OFF_ENABLE_TYPE cmds_02_switch;
	public OFF_ENABLE_TYPE cmds_ch_switch;
	public OFF_ENABLE_TYPE cmds_fl_switch;
	public OFF_ENABLE_TYPE cmds_jett_switch;
	public BIT_1_2_3_4_TYPE cmds_prgm_switch;
	public OFF_STBY_MAN_SEMI_AUTO_BYP_TYPE cmds_mode_switch;
	public int cmds_status_lcd_1_str;
	public int cmds_status_lcd_2_str;
	public int cmds_status_lcd_3_str;
	public int cmds_status_lcd_4_str;
	//public int cmds_status_lcd_5_str;
	//public int cmds_status_lcd_6_str;
	//public int cmds_status_lcd_7_str;
	//public int cmds_status_lcd_8_str;
	public int cmds_backlight_val;
};


typedef struct F16_THREAT_WARNING_AUX_CONTROL_PANEL
{
	public ON_OFF_TYPE tw_search_btn;
	public ON_OFF_TYPE tw_act_pwr_btn;
	public ON_OFF_TYPE tw_low_alt_btn;
	public ON_OFF_TYPE tw_sys_pwr_btn;
	public int tw_dim_val;
	public int tw_search_light;
	public int tw_pwr_light;
	public int tw_low_alt_light;
	public int tw_sys_pwr_light;
	// public OFF_ENABLE_TYPE tw_3_amp_fuse;// 삭제
	// public int tw_backlight_val; //삭제
};



typedef struct F16_ALT_GEAR_HANDLE
{
	public ON_OFF_TYPE alt_gear_handle;
};


typedef struct F16_SPEED_BRAKE_POSITION_INDICATOR
{
	public int speed_break_indicator;
};


typedef struct LEFT_AUX_CONSOLE_TYPE
{
	public F16_LANDING_GEAR_CONTROL_PANEL landing_gear_control_panel;
	public F16_CMDS_CONTROL_PANEL cmds_control_panel;
	public F16_THREAT_WARNING_AUX_CONTROL_PANEL threat_warning_aux_control_panel;
	public F16_ALT_GEAR_HANDLE alt_gear_handle;
	public F16_SPEED_BRAKE_POSITION_INDICATOR speed_brake_position_indicator;
};



typedef struct F16_UHF_BACKUP_CONTROL_PANEL
{//24
	public ON_OFF_TYPE uhf_test_dsp_btn;
	public ON_OFF_TYPE uhf_status_btn;
	public int uhf_channel_switch;
	public A_3_2_TYPE uhf_freq_switch_1;
	public int uhf_freq_switch_2;
	public int uhf_freq_switch_3;
	public int uhf_freq_switch_4;
	public NUM_0_25_50_75_TYPE uhf_freq_switch_5;
	public OFF_MAIN_BOTH_ADF_TYPE uhf_func_switch;
	public T_TONE_TYPE uhf_tone_switch;
	public ON_OFF_TYPE uhf_squelch_switch;
	public MNL_PRESET_GRD_TYPE uhf_mode_switch;


	public int uhf_hid_gd_sq_val;
	public int uhf_vol_val;
	public int uhf_channel_display_str;
	public int uhf_freq_disp_1_str;
	public int uhf_freq_disp_2_str;
	public int uhf_freq_disp_3_str;
	public int uhf_freq_disp_4_str;
	public int uhf_freq_disp_5_str;
	public int uhf_backlight_val;
	public ON_OFF_TYPE uhf_hid_press_btn;
	public int uhf_hid_bw_val;
	public int uhf_hid_mn_sq_val;

};


typedef struct F16_AUDIO_1_CONTROL_PENEL
{
	public int aud_1_comm_1_val;
	public int aud_1_comm_2_val;
	public ON_OFF_TYPE aud_1_comm_1_mode_btn;
	public ON_OFF_TYPE aud_1_comm_2_mode_btn;
	public OFF_SQL_GD_TYPE aud_1_comm_1_mode_switch;
	public OFF_SQL_GD_TYPE aud_1_comm_2_mode_switch;
	public ON_OFF_TYPE aud_1_comm_1_push_tone_btn;
	public ON_OFF_TYPE aud_1_comm_2_push_tone_btn;
	public int aud_1_secure_voice_val;
	public int aud_1_msl_val;
	public int aud_1_tf_val;
	public int aud_1_threat_val;
	public int aud_1_backlight_val;
};

//패널 삭제
//typedef struct F16_ASPJ_PANEL
//{
//	OFF_MBIT_STBY_ON_TYPE	aspj_mode_switch;
//	NUM_1_2_3_4_TYPE	aspj_submode_switch;
//	OFF_NORM_TYPE	aspj_rcv_switch;
//	MAN_AUTO_TYPE	aspj_chaff_switch;
//	MAN_AUTO_TYPE	aspj_flare_switch;
//	ON_OFF_TYPE	aspj_test_btn_1;
//	ON_OFF_TYPE	aspj_test_btn_2;
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
	public OFF_MAIN_PWR_BATT_TYPE elec_main_pwr_switch;
	public ON_OFF_TYPE elec_caution_btn;
	public int elec_flcs_pmg_light;
	public int elec_main_gen_light;
	public int elec_stby_gen_light;
	public int elec_blank_light;
	public int elec_epu_gen_light;
	public int elec_epu_pmg_light;
	public int elec_to_flcs_light;
	public int elec_flcs_rly_light;
	public int elec_fail_light;
	public int elec_backlight_val;
};



typedef struct F16_DVR_CONRTOL_PANEL
{
	//ON_OFF_TYPE	avrt_test_btn;
	//OFF_ON_AUTO_TYPE	avtr_avrt_switch;
	//AFT_LEFT_HUD_RIGHT_TYPE	avrt_display_switch;
	//int	avrt_ctvs_light;
	//int	avrt_avtr_light;
	public  int dvr_backlight_val;

	public  HUD_HMD_TYPE dvr_video_select;
	public  EVENT_MAKR_RECORD_OFF_TYPE dvr_record_switch;

};


typedef struct F16_FUEL_CONTROL_PANEL
{
	public OFF_MASTER_TYPE fuel_master_switch;
	public OFF_TANK_INERTING_TYPE fuel_tank_switch;
	public OFF_NORM_AFT_FWD_TYPE fuel_eng_feed_switch;
	public CLOSE_OPEN_TYPE fuel_air_refuel_switch;
	public int fuel_backlight_val;
};


typedef struct F16_IFF_PANEL
{
	public  OFF_SYBY_LOW_NORM_EMER_TYPE aux_master_switch;
	public  ZERO_A_B_HOLD_TYPE aux_m_4_code_switch;
	public  BACK_UP_UFC_TYPE aux_cni_switch;
	public  M3_OFF_M1_TYPE aux_enable_switch;
	public  B_A_OUT_TYPE aux_reply_switch;
	public  AUDIO_OUT_TYPE aux_monitor_switch;
	public  UP_DOWN_TYPE aux_channel_1_switch;
	public  UP_DOWN_TYPE aux_channel_2_switch;
	public  UP_DOWN_TYPE aux_channel_3_switch;
	public  UP_DOWN_TYPE aux_channel_4_switch;
	public  int aux_backlight_val;
};



typedef struct F16_EXT_LIGHTING_CONROL_PANEL
{
	//OFF_1_2_3_4_A_B_C_TYPE	ext_anti_collision_switch;
	public FLASH_STEADY_TYPE ext_position_light_switch;
	public OFF_BRT_DIM_TYPE ext_wing_trail_switch;
	public OFF_BRT_DIM_TYPE ext_fuselage_switch;
	public int ext_form_val;
	//public 	OFF_ALL_A_C_FORM_NORM_TYPE	ext_master_switch;
	public int ext_refueling_val;
	public int ext_backlight_val;
};



typedef struct F16_FLT_CONTROL_PANEL
{
	public  OFF_BACKUP_TYPE flt_digital_switch;
	public  EXTEND_NORM_TYPE flt_alt_falps_switch;
	public  DISABLE_ENABLE_TYPE flt_tf_flyup_switch;
	public  LOCK_AUTO_TYPE flt_le_flaps_switch;
	public  OFF_RESET_TYPE flt_flcs_switch;
	public  OFF_BIT_TYPE flt_bit_switch;
	public  ON_OFF_TYPE fltt_flcs_solenoid;
	public  ON_OFF_TYPE flt_run_light;
	public  ON_OFF_TYPE flt_fail_light;
	public  int flt_backlight_val;
};


typedef struct F16_MANUAL_TRIM_PANEL
{
	public  int manual_pitch_down_val;
	public  NORM_DISC_TYPE manual_ap_disc_switch;
	public  int manual_roll_motor_val;
	public  int manual_pitch_motor_val;
	public  int manual_backlight_val;
};


typedef struct F16_TEST_SWITCH_PANEL
{
	public ON_OFF_TYPE test_fire_oheat_btn;
	public OFF_OXY_OTY_TYPE test_oxy_oty_switch;
	public ON_OFF_TYPE test_mal_ind_btn;
	public OFF_PROBE_HEAT_TEST_TYPE test_probe_heat_switch;
	public OFF_EPU_GEN_TYPE test_epu_gen_switch;
	public TEST_NORM_MAINT_TYPE test_test_switch;
	//	AFT_FWD_TYPE	test_stick_switch;
	public int test_pwr_a_light;
	public int test_pwr_b_light;
	public int test_pwr_c_light;
	public int test_pwr_d_light;
	public int test_backlight_val;
};


typedef struct F16_ENG_JET_START_CONTROL_PANEL
{
	public OFF_START1_START2_TYPE ej_jfs_switch;
	public PRI_SEC_TYPE ej_eng_cont_switch;
	public AB_RESET_NORM_ENG_DATA_TYPE ej_ane_switch;
	public OFF_MAX_POWER_TYPE ej_max_power_switch;
	public ON_OFF_TYPE ej_run_light;
	public ON_OFF_TYPE ej_reset_solenoid;
	public ON_OFF_TYPE ej_power_solenoid;
	public int ej_backlight_val;
};




typedef struct F16_EPU_CONTROL_PANEL
{
	public OFF_ON_NORMAL_TYPE epu_switch;
	public ON_OFF_TYPE epu_light;
	public int epu_hydrazn_light;
	public int epu_air_light;
	public int epu_backlight_val;
};


typedef struct F16_AUDIO_2_CONTROL_PANEL
{
	public ON_OFF_TYPE aud_2_tacan_off_switch;
	public ON_OFF_TYPE aud_2_ils_val_off_switch;


	public int aud_2_intercom_val;
	public int aud_2_tacan_val;
	public int aud_2_ils_val;
	public OFF_MIC_CIPHER_TYPE aud_2_hot_switch;
	public int aud_2_backlight_val;
};


typedef struct F16_MANUAL_CANOPY_CONTROL_HANDLE
{
	public int manual_canopy_handle_val;
};


typedef struct F16_DEFPG_HANDLE
{
	int defog_handle;
};


typedef struct F16_ANTI_G_TEST_BUTTON
{
	public ON_OFF_TYPE anti_g_test_btn;
	public int anti_backlight_val;
};




typedef struct F16_DEFOG_HANDLE
{
	public int defog_handle;
};



typedef struct F16_CHAFF_FLARE_DISPENSE_BUTTON
{
	public ON_OFF_TYPE chaff_flare_btn;
};


typedef struct F16_REDUCED_IDLE_THRUST_SWITCH
{
	public  OFF_ARM_TYPE reduced_thrust_switch;
};

//typedef struct F16_CANOPY_JETTISON_T_HANDLE
//{
//	NOT_EJECT_EJECT_TYPE	canopy_t_handle;
//}F16_CANOPY_JETTISON_T_HANDLE;



typedef struct F16_MANUAL_PITCH_OVERRIDE_PANEL
{
	public OVRD_NORM_TYPE manual_pitch_switch;
	public int manual_pitch_backlight_val;
};



typedef struct F16_CANOPY_CLOSE_HANDLE
{
	public ON_OFF_TYPE canopy_close_handle_limit_switch;
	public ON_OFF_TYPE canopy_close_handle_btn;
	public ON_OFF_TYPE canopy_close_handle_toggle_1_switch;
	public ON_OFF_TYPE canopy_close_handle_toggle_2_switch;


};


typedef struct F16_THROTTLE
{
	public ON_OFF_TYPE throttle_block_switch;
	public VHF_UHF_IN_OUT_TYPE throttle_com_switch;
	public UP_DOWN_TYPE throttle_dog_fight_switch;
	public FORWARD_BACKWARD_TYPE throttle_speed_break_switch;
	public CURSOR_ENALBLE_TYPE throttle_cursor_switch;
	public int throttle_rader_curs_x_val;
	public int throttle_rader_curs_y_val;
	public int throttle_axis_val;
	public int throttle_man_rgn_val;
	public int throttle_ant_elv_val;
};


typedef struct F16_CONSOLE_FLOOD_LIGHT
{
	public int flood_light_1;
	public int flood_light_2;
	public int flood_light_3;
};



typedef struct LEFT_CONSOLE_TYPE
{
	public  F16_MANUAL_CANOPY_CONTROL_HANDLE manual_canopy_control_handle;
	public  F16_DEFOG_HANDLE defog_handle;


	public  F16_UHF_BACKUP_CONTROL_PANEL uhf_backup_control_panel;
	public  F16_AUDIO_1_CONTROL_PENEL audio_1_control_penel;
	//	F16_ASPJ_PANEL	aspj_panel; //패널 삭제
	public  F16_ELEC_CONTROL_PANEL elec_control_panel;
	public  F16_DVR_CONRTOL_PANEL dvr_control_panel;
	public  F16_FUEL_CONTROL_PANEL fuel_control_panel;
	public  F16_IFF_PANEL aux_comm_panel;
	public  F16_EXT_LIGHTING_CONROL_PANEL ext_lighting_conrol_panel;
	public  F16_FLT_CONTROL_PANEL flt_control_panel;
	public  F16_MANUAL_TRIM_PANEL manual_trim_panel;
	public  F16_TEST_SWITCH_PANEL test_switch_panel;
	public  F16_ENG_JET_START_CONTROL_PANEL eng_jet_start_control_panel;
	public  F16_EPU_CONTROL_PANEL epu_control_panel;
	public  F16_AUDIO_2_CONTROL_PANEL audio_2_control_panel;
	public  F16_ANTI_G_TEST_BUTTON anti_g_test_button;

	public  F16_CHAFF_FLARE_DISPENSE_BUTTON chaff_flare_dispense_button;
	public  F16_REDUCED_IDLE_THRUST_SWITCH reduced_idle_thrust_switch;
	//	F16_CANOPY_JETTISON_T_HANDLE	canopy_jettison_t_handle;
	public  F16_CANOPY_CLOSE_HANDLE canopy_close_handle;
	public  F16_MANUAL_PITCH_OVERRIDE_PANEL manual_pitch_override_panel;

	public  F16_THROTTLE throttle;
	public  F16_CONSOLE_FLOOD_LIGHT console_flood_light;
};


typedef struct F16_CAUTION_LIGHT_PANEL
{
	public int cau_flcs_fault_light;
	public int cau_engine_fault_light;
	public int cau_avion_fault_light;
	public int cau_seat_not_armed_light;
	public int cau_elec_sys_light;
	public int cau_sec_light;
	public int cau_equip_hot_light;
	public int cau_nws_fail_light;
	public int cau_probe_heat_light;
	public int cau_fuel_oil_hot_light;
	public int cau_radar_alt_light;
	public int cau_anti_skid_light;
	public int cau_cadc_light;
	public int cau_inlet_icing_light;
	public int cau_iff_light;
	public int cau_hook_light;
	public int cau_store_conf_light;
	public int cau_overheat_light;
	public int cau_nuclear_light;
	public int cau_oxy_low_light;
	public int cau_aft_not_eng_light;
	public int cau_eec_light;
	public int cau_blank_1_light;
	public int cau_cabin_press_light;
	public int cau_fwd_fuel_low_light;
	public int cau_buc_light;
	public int cau_blank_2_light;
	public int cau_blank_3_light;
	public int cau_aft_fuel_low_light;
	public int cau_blank_4_light;
	public int cau_blank_5_light;
	public int cau_blank_6_light;
};


typedef struct F16_STICK
{
	public NWS_A_R_DISC_MS_L_STEP_A_G_TOGGLE_A_G_A_A_TYPE stick_nws_btn;
	public FWD_AFT_LEFT_RIGHT_TYPE stick_trim_switch;
	public ON_OFF_TYPE stick_weapon_release_btn;
	public RWS_SAM_TWS_ACM_ACM_boresight_A2G_TYPE stick_tm_fwd_btn;
	public STT_TTS_SAM_TWS_SMT_with_no_bug_ACM_TYPE stick_tm_aft_btn;
	public GRATER_THAN_0_5_SECOND_TGP_EO_HSD_WITH_DATALINK_TYPE stick_tm_left_btn;
	public _1_SECOND_NO_BUG_1_SECOND_BUGGED_TARGET_IRWS_GREATER_ITWS_SMT_ACM_A2G_TYPE stick_tm_right_btn;
	public FWD_AFT_LEFT_RIGHT_TYPE stick_dm_switch;
	public FWD_AFT_LEFT_RIGHT_TYPE stick_cm_switch;
	public ON_OFF_TYPE stick_pinky_btn;
	public ON_OFF_TYPE stick_paddle_btn;
	public _1_DETENT_2_DETENT_TYPE stick_trigger_switch;
};



typedef struct F16_EPU_FUEL_QUANTITY_INDICATOR
{
	public int epu_fuel_quantity_val;
	public int epu_fuel_backlight_val;
};

typedef struct F16_LIQUID_OXYGEN_QUANTITY_INDICATOR
{
	public int liquid_oxygen_val;
	public int liquid_backlight_val;
};

typedef struct F16_SYSTEM_A_HYD_PRESS_INDICATOR
{
	public int hyd_a_press_val;
	public int hyd_a_backlight_val;
};

typedef struct F16_SYSTEM_B_HYD_PRESS_INDICATOR
{
	public int hyd_b_press_val;
	public int hyd_b_backlight_val;
};


typedef struct F16_HYD_PRESS_LIGHTING_PANEL
{
	public int hyd_press_backlight_val;
};



typedef struct F16_CLOCK
{
	public int clock_knob_big;
	public int clock_knob_small;
};


//패널 삭제
//
//typedef struct F16_MAGNETIC_COMPASS
//{
//   public int mag_compass_type;
//};


typedef struct F16_FUEL_QUANTITY_INDICATOR
{
	public int fuel_quantity_motor_1;
	public int fuel_quantity_motor_2;
	public int fuel_quantity_backlight_val;
};


typedef struct F16_PILOT_FAULT_LIST_DISPLAY
{
	public int pilot_fault_list_display;
};

typedef struct RIGHT_AUX_CONSOLE_TYPE
{
	public  F16_CAUTION_LIGHT_PANEL caution_light_panel;
	public  F16_STICK stick;
	public  F16_EPU_FUEL_QUANTITY_INDICATOR epu_fuel_quantity_indicator;
	public  F16_LIQUID_OXYGEN_QUANTITY_INDICATOR liquid_oxygen_quantity_indicator;
	public  F16_SYSTEM_A_HYD_PRESS_INDICATOR system_a_hyd_press_indicator;
	public  F16_SYSTEM_B_HYD_PRESS_INDICATOR system_b_hyd_press_indicator;
	public  F16_HYD_PRESS_LIGHTING_PANEL hyd_press_lighting_panel;
	public  F16_CLOCK clock;
	// public  F16_MAGNETIC_COMPASS magnetic_compass; //패널 삭제
	public  F16_FUEL_QUANTITY_INDICATOR fuel_quantity_indicator;

	public  F16_PILOT_FAULT_LIST_DISPLAY pilot_fault_list_display;
};


typedef struct F16_HUD_CONTROL_PANEL
{
	public OFF_VV_VAH_VAH_TYPE hud_vv_vah_switch;
	public OFF_ATT_FPM_FPM_TYPE hud_att_fpm_switch;
	public OFF_DED_DATA_PFL_TYPE hud_ded_data_switch;
	public OFF_STBY_PRI_TYPE hud_depr_ret_switch;
	public CAS_TA_GND_SPD_TYPE hud_cas_switch;
	public ALT_RADAR_BARO_AUTO_TYPE hud_radar_switch;
	public DAY_AUTO_BRT_NIGHT_TYPE hud_day_switch;
	public OFF_TEST_STEP_ON_TYPE hud_test_ste_switch;
	public int hud_backlight_val;
};



typedef struct F16_INTERIOR_LIGHTING_CONTROL_PANEL
{
	public int inter_console_val;
	public int inter_inst_pnl_val;
	public int inter_entry_dis_val;
	public int inter_flood_console_val;
	public ON_OFF_TYPE inter_flood_console_high_int_sig;
	public int inter_flood_inst_pnl_val;
	public NORM_BRT_DIM_TYPE inter_mal_ind_switch;
	public int inter_backlight_val;
};


typedef struct F16_AIR_COND_CONTROL_PANEL
{
	public int airc_temp_ctl_val;
	public ON_OFF_TYPE airc_temp_ctl_off_sig;
	public OFF_NORM_DUMP_RAM_TYPE airc_air_src_switch;
	public int airc_backlight_val;
};

typedef struct F16_AVIONICS_POWER_PANEL
{
	public OFF_MMC_TYPE avion_mmc_switch;
	public OFF_STA_TYPE avion_sta_switch;
	public OFF_MFD_TYPE avion_mfd_switch;
	public OFF_UFC_TYPE avion_ufc_switch;
	public OFF_STOR_HDG_NORM_NAV_CAL_IN_FLT_ATT_TYPE avion_egi_switch;
	public ZERO_OFF_ON_TYPE avion_mids_switch;
	public OFF_GES_TYPE avion_ges_switch;
	public OFF_DL_TYPE avion_dl_switch;
	public OFF_CPD_TYPE avion_cpd_switch;
	public int avion_backlight_val;

};



//
//typedef struct F16_AVIONICS_POWER_PANEL
//{
//   public OFF_FCC_TYPE avion_fcc_switch;
//   public OFF_SMS_TYPE avion_sms_switch;
//   public OFF_MFD_TYPE avion_mfd_switch;
//   public OFF_UFC_TYPE avion_ufc_switch;
//   public OFF_STOR_HDG_NORM_NAV_CAL_IN_FLT_ATT_TYPE avion_ins_switch;
//   public OFF_GPS_TYPE avion_gps_switch;
//   public OFF_DL_TYPE avion_dl_switch;
//   public OFF_MAP_TYPE avion_map_switch;
//   public int avion_backlight_val;
//};



typedef struct F16_OXYGEN_PANEL
{
	public EMERGENCY_NORM_TEST_MASK_TYPE oxygen_ent_switch;
	public NORM_O2_TYPE oxygen_o2_norm_switch;
	public PBG_ON_OFF_TYPE oxygen_pbg_onoff_switch;
	public int oxygen_supply_motor_val;
	public WHITE_BLACK_TYPE oxygen_flow_light;
	//int	oxygen_supply_backlight_val;
	public int oxygen_backlight_val;
};


typedef struct F16_SNSR_PWR_CONTROL_PANEL
{
	public OFF_LEFT_HDPT_TYPE snsr_left_hdpt_switch;
	public OFF_RIGHT_HDPT_TYPE snsr_right_hdpt_switch;
	public OFF_FCR_TYPE snsr_fcr_switch;
	public OFF_RDR_ALT_STBY_TYPE snsr_rdr_alt_switch;
	public int snsr_backlight_val;
};



typedef struct F16_ZEROIZE_PANEL
{
	public OFF_OFP_DATA_TYPE zeroize_switch;
	public INNIBIT_NORM_TYPE zeroize_voice_switch;
	public int zeroize_backlight_val;
};


typedef struct F16_PLAIN_CHIPHER_PANEL
{
	public  NORM_CARD1_CARD2_TYPE plain_switch;
	public  int plain_chipher_zeroize_backlight_val;
};


typedef struct F16_ENGINE_ANTI_ICE_PANEL
{
	public  OFF_ON_AUTO_TYPE eng_anti_engine_switch;
	public  NORM_UPPER_LOWER_TYPE eng_anti_iff_switch;
	public  NORM_UPPER_LOWER_TYPE eng_anti_uhf_switch;
	public  int eng_anti_backlight_val;
};


typedef struct F16_SEAT_ADJ_SWITCH
{
	public OFF_ON_AUTO_TYPE seat_adj_switch;
};


typedef struct F16_DTU
{
	public OFF_ON_AUTO_TYPE dtu;
};



typedef struct SECURE_VOICE_CONTROL_PANEL
{
	ONE_TO_SIX_MAN_OFF_ZALL_REM_OFF_PT_TYPE secure_ent_btn;
	ON_OFF_TYPE secure_right_btn;
	ON_OFF_TYPE secure_up_btn;
	ON_OFF_TYPE secure_esc_btn;
	int secure_ocmi_val;
	int snsr_backlight_val;

};


typedef struct F16_FLOOD_LIGHT
{
	public int flood_light_1;
	public int flood_light_2;
	public int flood_light_3;
	public int flood_light_4;
};

typedef struct RIGHT_CONSOLE_TYPE
{
	public F16_HUD_CONTROL_PANEL hud_control_panel;
	public F16_INTERIOR_LIGHTING_CONTROL_PANEL interior_lighting_control_panel;
	public F16_AIR_COND_CONTROL_PANEL air_cond_control_panel;
	public F16_AVIONICS_POWER_PANEL avionics_power_panel;
	public F16_OXYGEN_PANEL oxygen_panel;
	public F16_SNSR_PWR_CONTROL_PANEL snsr_pwr_control_panel;
	public F16_ZEROIZE_PANEL zeroize_panel;
	public F16_PLAIN_CHIPHER_PANEL plain_chipher_panel;
	public F16_ENGINE_ANTI_ICE_PANEL engine_anti_ice_panel;
	public F16_SEAT_ADJ_SWITCH seat_adj_switch;
	public F16_DTU dtu;
	public F16_FLOOD_LIGHT flood_light;
};



typedef struct F_16_COCKPIT_TO_HOST_TYPE
{
	public CENTER_CONSOLE_TYPE f16_center_console_type;
	public LEFT_AUX_CONSOLE_TYPE f16_left_aux_console_type;
	public LEFT_CONSOLE_TYPE f16_left_console_type;
	public RIGHT_AUX_CONSOLE_TYPE f16_right_aux_console_type;
	public RIGHT_CONSOLE_TYPE f16_right_console_type;
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//f-15입니다.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct MPD_BUTTON_TYPE
{
	on_off_type S1;
	on_off_type S2;
	on_off_type S3;
	on_off_type S4;
	on_off_type S5;
	on_off_type S6;
	on_off_type S7;
	on_off_type S8;
	on_off_type S9;
	on_off_type S10;
	on_off_type S11;
	on_off_type S12;
	on_off_type S13;
	on_off_type S14;
	on_off_type S15;
	on_off_type S16;
	on_off_type S17;
	on_off_type S18;
	on_off_type S19;
	on_off_type S20;
	on_off_type BRT_UP;
	on_off_type BRT_DOWN;
	on_off_type CONT_UP;
	on_off_type CONT_DOWN;
	on_off_type PWR_ON;
	on_off_type PWR_OFF;

}MPD_BUTTON_TYPE;

typedef struct UFC_BUTTON_TYPE
{
	int Vol_R1_Knob;
	int Vol_R3_Knob;
	int Vol_R2_Knob;
	int Vol_R4_Knob;
	int Brt_Knob;
	LEFT_RIGHT_NORMAL_TYPE Left_Channel_Select_Knob;
	LEFT_RIGHT_NORMAL_TYPE Right_Channel_Select_Knob;
	on_off_type Left_Channel_Select_Btn;
	on_off_type Right_Channel_Select_Btn;
	UFC_PWR_MODE_TYPE Brt_Switch;
	on_off_type S1;
	on_off_type S2;
	on_off_type S3;
	on_off_type S4;
	on_off_type S5;
	on_off_type S6;
	on_off_type S7;
	on_off_type S8;
	on_off_type S9;
	on_off_type S10;
	on_off_type LEFT_GREC;
	on_off_type RIGHT_GREC;
	on_off_type MARK;
	on_off_type IP;
	on_off_type DOT;
	on_off_type SHF;
	on_off_type AP;
	on_off_type CLR;
	on_off_type DATA;
	on_off_type MENU;
	on_off_type KEY_0;
	on_off_type KEY_1;
	on_off_type KEY_2;
	on_off_type KEY_3;
	on_off_type KEY_4;
	on_off_type KEY_5;
	on_off_type KEY_6;
	on_off_type KEY_7;
	on_off_type KEY_8;
	on_off_type KEY_9;
	on_off_type EMIS_Btn;
}UFC_BUTTON_TYPE;

typedef struct INDICATOR_TYPE
{
	pull_to_cage_knob_type Pull_To_Cage_Knob;
	int Standby_Attitude_Knob_Value;
	int Altimeter_Knob_Value;
	on_off_type Clock_Push_Btn;
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
	on_off_type CAS_Bit_Btn;
	TF_TYPE TF_Switch;
	on_off_type TO_Trim_Btn;

	//FUEL CONTROL PANEL 
	FUEL_CONTROL_TYPE Wing_Fuel_Control_Switch;
	FUEL_CONTROL_TYPE CTR_Fuel_Control_Switch;
	FUEL_CONTROL_TYPE Conf_Tank_Fuel_Control_Switch;
	DUMP_TYPE Dump_Switch;
	EXT_TRANS_TYPE Ext_Trans_Switch;
	OPEN_CLOSE_ORIDE_TYPE Slipway_Switch;
	LEFT_RIGHT_NORMAL_TYPE Conf_Tank_Emerg_Trans_Switch;

	//THROTTLE QUADRANT
	int Left_Throttle_Position;
	int Right_Throttle_Position;
	on_off_type Left_Throttle_Lift;
	on_off_type Right_Throttle_Lift;
	int Antenna_Elev_Knob;
	MULTIFUNCTION_TYPE HAT_Switch;	// Right_Multifunction Switch
	int TDC_X;
	int TDC_Y;
	on_off_type TDC_Press_Btn;
	POSITION_TYPE CMD_Dispenser_Switch;
	on_off_type Laser_Fire_Btn;		// Left Multifunction Switch
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
	on_off_type Anti_Collision_Switch;
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
	on_off_type VM_Tone_Silence_Btn;
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
	on_off_type EGI_1_Switch;
	on_off_type EGI_2_Switch;
	ON_OFF_STBY_TYPE IRST_Switch;
	on_off_type ADCP_Reset_Btn;

	//GND PWR PANEL 
	ON_OFF_AUTO_TYPE Ground_Power_1_Switch;
	GROUND_PWR_TYPE Ground_Power_2_Switch;// change enum type 2019.01.14
	GROUND_PWR_TYPE Ground_Power_3_Switch;// change enum type 2019.01.14
	GROUND_PWR_TYPE Ground_Power_4_Switch; // change enum type 2019.01.14
	ON_OFF_AUTO_TYPE Ground_Power_PACS_Switch;
	ON_OFF_AUTO_TYPE Ground_Power_ADCPAIU1_Switch;

	//ANTI-G PANEL 
	on_off_type Anti_G_Btn;

	//CANOPY JETTISON HANDLE
	CANOPY_JETTISON_TYPE Canopy_Jettison_Btn;

	CANOPY_LOCK_TYPE Canopy_Lock_Handle;

	//FLYUP ENABLE SWITCH
	on_off_type Flyup_Enable_Switch;

	//SEAT ADJUST SWITCH
	UP_DOWN_CTR_TYPE Seat_Adjust_Switch;

	//IFF ANTENNA SELECT SWITCH
	IFF_ANTENNA_TYPE IFF_Antenna_Switch;

	//EMERGENCY AIR REFUELING SWITCH 
	OPEN_NORM_TYPE Emerg_Air_Refuel_Switch;

	//ARMAMENT SAFETY OVERRIDE SWITCH
	SEAT_ARMAMENT_TYPE Seat_Armament_Switch;

}LEFT_PANEL_TYPE;

typedef struct RIGHT_PANEL_TYPE
{
	//OXYGEN REGULATOR
	OXYGEN_EMERG_TYPE	Oxygen_Emerg_Switch;
	OXYGEN_TYPE			Oxygen_Switch;
	OXYGEN_SUPPLY_TYPE	Oxygen_Supply_Switch;

	//ECS PANEL 
	on_off_type Oxy_Bit_Btn;
	ANTI_FOG_TYPE Anti_Fog_Switch;
	on_off_type	Anti_Ice_Windshield_Switch;
	on_off_type	Anti_Ice_PitotHeat_Switch;
	ON_OFF_TEST_TYPE Anti_Ice_EngHeat_Switch;

	//ENGINE CONTROL PANEL 
	on_off_type	Left_Engine_Gen_Switch;
	on_off_type	Right_Engine_Gen_Switch;
	ENGINE_EMERG_TYPE Engine_EmergeGen_Switch;
	on_off_type Left_Engine_Control_Switch;
	on_off_type Right_Engine_Control_Switch;
	on_off_type Left_Engine_Master_Switch;
	ENGINE_EXTPWR_TYPE Engine_ExtPwr_Switch;
	on_off_type Engine_Starter_Switch;
	on_off_type Right_Engine_Master_Switch;

	//AIR CONDITION CONTROL PANEL
	AIRCOND_TEMP_TYPE Aircond_Temp_Switch;
	AIRCOND_FLOW_TYPE Aircond_Flow_Switch;
	int Temp_Control_Knob;
	AIR_SOURCE_TYPE Air_Source_Switch;

	//EW CONTROL PANEL 
	on_off_type		RWR_Power_Switch;
	RWR_COMBAT_TYPE RWR_Combat_Switch;
	on_off_type		ICS_Power_Switch;
	ICS_SWITCH_TYPE ICS_Stby_Switch;
	CMD_BYPASS_TYPE CMD_Switch;
	CMD_JETTISON_TYPE CMD_Jettison_Switch;

	//INTERIOR LIGHTS CONTROL PANEL 
	int Console_Light_Knob;
	int Inst_Pnl_Light_Knob;
	on_off_type	Inst_Pnl_Light_Off_Switch; //add 19.01.13
	on_off_type	Light_Test_Switch;
	int UFC_Light_Knob;
	on_off_type	Stby_Comp_Switch;
	int Chart_Light_Knob;
	DAY_NIGHT_TYPE Dislplay_Switch;
	int Caution_Light_Knob;
	on_off_type Caution_Light_Reset;
	int Storm_Flood_Light_Knob;
	on_off_type Storm_Flood_Brt_Switch; //add 19.01.17
	//AERP PANEL 

	//HMD CONTROL PANEL 
	int HMD_Control_Knob;
	on_off_type HMD_Power;

	//CANOPY CONTROL HANDLE
	CANOPY_CONTROL_TYPE Canopy_Control_Switch;

}RIGHT_PANEL_TYPE;

typedef struct MAIN_PANEL_TYPE
{
	//UPFROUNT CONTROL PANEL 
	UFC_BUTTON_TYPE UFC_Panel;

	//MASTER CAUTION LIGHT
	on_off_type Master_Caution_Btn;

	//FIRE WARNING/ EXTINGUISHING PANEL
	DISCHARGE_TYPE	Discharge_Switch;
	on_off_type AMAD_Fire_Btn;
	on_off_type Left_Engine_Fire_Btn;
	on_off_type Right_Engine_Fire_Btn;

	//MULTI-PURPOSE DISPLAY, LEFT
	MPD_BUTTON_TYPE Left_MPD;

	//MULTI-PURPOSE DISPLAY, RIGHT
	MPD_BUTTON_TYPE Right_MPD;

	//HEAD UP DISPLAY CONTROL PANEL
	int Symbol_Brt_Knob;
	SYM_DECLUTTER_TYPE Symbol_Declutter_Switch;
	DAY_NIGHT_TYPE Day_Night_Switch;
	on_off_type Test_Btn;
	int Video_Brt_Knob;
	int Video_Cont_Knob;
	UFC_MODE_TYPE UFC_Mode_Button;

	//MULTI - PURPOSE COLOR DISPLAY
	MPD_BUTTON_TYPE MPCD;

	//ARMAMENT CONTROL PANEL 
	ARMT_CONTROL_TYPE	ARMT_Control_Switch;
	on_off_type			ARMT_JETT_Switch;  // add 2019.01.02
	ARMT_TYPE			ARMT_Gun_Switch;
	ARMT_TYPE			ARMT_Master_Switch;

	//EMERGENCY JETTISON BUTTON
	on_off_type Emergency_Jettison_Btn;

	//DATA TRANSFER MODULE RECEPTACLE
	on_off_type DTM_Receptacle;

	//ARRESTING HOOK CONTROL SWITCH
	UP_DOWN_TYPE Arresting_Hook_Switch;

	//LANDING GEAR CONTROL HANDLE
	UP_DOWN_TYPE LDG_Gear_Switch;
	on_off_type Warn_Tone_Sil_Btn;
	on_off_type LDG_Nose_Switch;//add 19. 01. 13
	on_off_type LDG_Left_Switch;//add 19. 01. 13
	on_off_type LDG_Right_Switch;//add 19. 01. 13

	//EMERGENCY LANDING GEAR HANDLE
	PULL_PUSH_TYPE Emerg_LDG_Switch;

	//PITCH RATIO SELECT SWITCH
	AUTO_EMERG_TYPE	Pitch_Ratio_Switch;

	//JET FUEL STARTER CONTROL HANDLE/ BRAKE HOLD SWITCH
	JET_STARTER_TYPE JET_Fuel_Starter_Switch;
	on_off_type	Brake_Hold_Switch;

	//EMERGENCY VENT CONTROL HANDLE 
	PULL_PUSH_TYPE Emerg_Vent_Switch;

	//EMERGENCY BRAKE/ STEERING CONTROL HANDLE 
	PULL_PUSH_TYPE Emerg_Brake_Steer_Switch;

	//CIRCUIT BREAKER PANEL
	Circuit_Breaker_Type Center_CB[FWD_TOTAL];
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
	STICK_POSITION_TYPE Stick_Position;
	CASTLE_TYPE Castle_Switch;
	TRIM_TYPE Trim_Switch;
	AUTO_ACQUISITION_TYPE Auto_Acquisition_Switch;
	on_off_type Weapon_Release_Btn;
	on_off_type Nose_Gear_Steering_Btn;
	//on_off_type Air_Refueling; //remove 2019.01.14
	on_off_type Paddle_Switch;
	STICK_TRIGGER_TYPE Stick_Trigger_Btn;
	on_off_type Stick_Trim_Complete; //add 19.01.13

	//RUDDER PEDAL
	int Rudder_Pedal;
	on_off_type Left_Brake_Pedal;
	on_off_type Right_Brake_Pedal;
	on_off_type Rudder_Trim_Complete; //add 19.01.13

	//INDICATOR
	INDICATOR_TYPE Indicator;

	UP_DOWN_TYPE Left_Ejection_Handle;
	UP_DOWN_TYPE Right_Ejection_Handle;

	//on_off_type MC_Receptacle;	//2019.01.11

}MAIN_PANEL_TYPE;

typedef struct COCKPIT_TO_HOST_TYPE
{
	LEFT_PANEL_TYPE Left_Panel;
	MAIN_PANEL_TYPE Main_Panel;
	RIGHT_PANEL_TYPE Right_Panel;

} COCKPIT_TO_HOST_TYPE;
#pragma pack(pop)