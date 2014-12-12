// This file is automatically generated.
// Do not edit it
// open gen_param_struct.py, edit struct definition and run it to generate new file
#define ONBOARD_PARAM_CNT 151

/*
 * volatile array of parameters in RAM
 */
static param_union_t gp_val[ONBOARD_PARAM_CNT] __attribute__((section(".ccm")));

/**
 *
 */
const GlobalParam_t ParamRegistry::param_db[] = {
{"SYS_id", {.u32 = 1}, {.u32 = 20}, {.u32 = 255}, &gp_val[0], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, "System ID.\n This value MUST BE FIRST in param structure. Value 0 reserved for ground station."},
{"SYS_mavtype", {.u32 = 0}, {.u32 = 10}, {.u32 = 16}, &gp_val[1], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, "Autopilot type (0 - generic, 1 - fixed wing, 10 - ground rover).\nOther types you can found in enum MAV_TYPE \nNOTE! You MUST REBOOT device after changing it."},
{"SH_over_radio", {.u32 = 0}, {.u32 = 0}, {.u32 = 1}, &gp_val[2], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, "When 1 than drop shell on xbee channel and telemetry on USB_CDC and vice versa."},
{"AHRS_accweight", {.f32 = 0.000000}, {.f32 = 0.005000}, {.f32 = 0.500000}, &gp_val[3], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    NULL},
{"AHRS_magweight", {.f32 = 0.000000}, {.f32 = 0.050000}, {.f32 = 0.900000}, &gp_val[4], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    NULL},
{"AHRS_gpsweight", {.f32 = 0.000000}, {.f32 = 0.050000}, {.f32 = 0.500000}, &gp_val[5], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    NULL},
{"AHRS_beta", {.f32 = 0.000000}, {.f32 = 1.000000}, {.f32 = 20.000000}, &gp_val[6], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    "Error rate of gyro in degrees"},
{"AHRS_zeta", {.f32 = 0.000000}, {.f32 = 1.000000}, {.f32 = 20.000000}, &gp_val[7], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    NULL},
{"AHRS_mode", {.u32 = 0}, {.u32 = 0}, {.u32 = 3}, &gp_val[8], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, "0 - Starlino, 1 - Madgwick, 2 - Adis, 3 - Kalman"},
{"MARG_acc_src", {.u32 = 0}, {.u32 = 0}, {.u32 = 2}, &gp_val[9], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, "Accelerometer measurement source for MARG (see enum acc_src_t)"},
{"MARG_gyr_src", {.u32 = 0}, {.u32 = 0}, {.u32 = 1}, &gp_val[10], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, "Angular rate measurement source for MARG (see enum gyr_src_t)"},
{"MARG_mag_src", {.u32 = 0}, {.u32 = 0}, {.u32 = 2}, &gp_val[11], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, "Magnetometer measurement source for MARG (see enum mag_src_t)"},
{"LSMM_gain", {.u32 = 0}, {.u32 = 0}, {.u32 = 7}, &gp_val[12], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, "LSM magnetometer gain (see enum mag_sens_t)"},
{"LSMM_xoffset", {.f32 = -500.000000}, {.f32 = 0.000000}, {.f32 = 500.000000}, &gp_val[13], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    NULL},
{"LSMM_yoffset", {.f32 = -500.000000}, {.f32 = 0.000000}, {.f32 = 500.000000}, &gp_val[14], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    NULL},
{"LSMM_zoffset", {.f32 = -500.000000}, {.f32 = 0.000000}, {.f32 = 500.000000}, &gp_val[15], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    NULL},
{"LSMM_vectorlen", {.f32 = 0.000000}, {.f32 = 10.000000}, {.f32 = 512.000000}, &gp_val[16], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    "Length of magnetic flux vector in uT acquired during sphere offset calculation"},
{"LSMM_xsens", {.f32 = 0.900000}, {.f32 = 1.000000}, {.f32 = 1.100000}, &gp_val[17], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    NULL},
{"LSMM_ysens", {.f32 = 0.900000}, {.f32 = 1.000000}, {.f32 = 1.100000}, &gp_val[18], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    NULL},
{"LSMM_zsens", {.f32 = 0.900000}, {.f32 = 1.000000}, {.f32 = 1.100000}, &gp_val[19], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    NULL},
{"LSMM_xpol", {.i32 = -1}, {.i32 = 1}, {.i32 = 1}, &gp_val[20], PARAM_POLARITY, MAVLINK_TYPE_INT32_T,  NULL},
{"LSMM_ypol", {.i32 = -1}, {.i32 = 1}, {.i32 = 1}, &gp_val[21], PARAM_POLARITY, MAVLINK_TYPE_INT32_T,  NULL},
{"LSMM_zpol", {.i32 = -1}, {.i32 = 1}, {.i32 = 1}, &gp_val[22], PARAM_POLARITY, MAVLINK_TYPE_INT32_T,  NULL},
{"LSMM_sortmtrx", {.u32 = 0}, {.u32 = 273}, {.u32 = 1}, &gp_val[23], PARAM_SORT_MTRX, MAVLINK_TYPE_UINT32_T, "Sorting matrix for acquired gyro values\nto correspond with real device axis"},
{"LSMM_calmode", {.u32 = 0}, {.u32 = 0}, {.u32 = 1}, &gp_val[24], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, "0 - simple spherical shift, 1 - egg compensate"},
{"LSMM_ellip1", {.f32 = -5.000000}, {.f32 = 1.000000}, {.f32 = 5.000000}, &gp_val[25], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    "ellipsoid correction coefficient"},
{"LSMM_ellip2", {.f32 = -5.000000}, {.f32 = 1.000000}, {.f32 = 5.000000}, &gp_val[26], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    "ellipsoid correction coefficient"},
{"LSMM_ellip3", {.f32 = -5.000000}, {.f32 = 1.000000}, {.f32 = 5.000000}, &gp_val[27], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    "ellipsoid correction coefficient"},
{"LSMM_ellip4", {.f32 = -5.000000}, {.f32 = 0.000000}, {.f32 = 5.000000}, &gp_val[28], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    "ellipsoid correction coefficient"},
{"LSMM_ellip5", {.f32 = -5.000000}, {.f32 = 0.000000}, {.f32 = 5.000000}, &gp_val[29], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    "ellipsoid correction coefficient"},
{"LSMM_ellip6", {.f32 = -5.000000}, {.f32 = 0.000000}, {.f32 = 5.000000}, &gp_val[30], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    "ellipsoid correction coefficient"},
{"MAG_declinate", {.f32 = -90.000000}, {.f32 = 7.000000}, {.f32 = 90.000000}, &gp_val[31], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    "Magnetic declination. \nThe declination is positive when the magnetic north is east of true north. \nhttp://www.ngdc.noaa.gov/geomagmodels/Declination.jsp"},
{"MAG_still_thr", {.f32 = 0.000000}, {.f32 = 1.000000}, {.f32 = 20.000000}, &gp_val[32], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    "Device immobility threshold in parrots"},
{"MAG_still_flen", {.i32 = 1}, {.i32 = 256}, {.i32 = 2048}, &gp_val[33], PARAM_DEFAULT, MAVLINK_TYPE_INT32_T,  "Length of filter used in immobility detector"},
{"MAG_zeroflen", {.i32 = 1}, {.i32 = 256}, {.i32 = 2048}, &gp_val[34], PARAM_DEFAULT, MAVLINK_TYPE_INT32_T,  "Length of filter used in immobility detector"},
{"MAG_zerocnt", {.u32 = 256}, {.u32 = 512}, {.u32 = 4096}, &gp_val[35], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, NULL},
{"ADIS_smplrtdiv", {.u32 = 12}, {.u32 = 24}, {.u32 = 246}, &gp_val[36], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, "Divider for ADIS's 2460Hz sample rate"},
{"MPU_dlpf", {.u32 = 0}, {.u32 = 5}, {.u32 = 6}, &gp_val[37], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, "If dlpf>0 than use internal LPF and internal sample rate divider.Otherwise use 1kHz sample rate with external FIR and external decimator"},
{"MPU_smplrtdiv", {.u32 = 1}, {.u32 = 10}, {.u32 = 50}, &gp_val[38], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, "Divider for MPU's 1kHz sample rate"},
{"MPU_fir_f", {.i32 = -1}, {.i32 = 0}, {.i32 = 6}, &gp_val[39], PARAM_DEFAULT, MAVLINK_TYPE_INT32_T,  "Cut off frequency of the external FIR filter (F = 2^N). Set -1 to disable filter at all."},
{"MPU_gyr_fs", {.u32 = 0}, {.u32 = 1}, {.u32 = 3}, &gp_val[40], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, "MPU gyroscope full scale (0 - 250, 1 - 500, 2 - 1000, 3 - 2000) deg/s"},
{"MPU_acc_fs", {.u32 = 0}, {.u32 = 3}, {.u32 = 3}, &gp_val[41], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, "MPU accelerometer full scale (0 - 2, 1 - 4, 2 - 8, 3 - 16) g"},
{"MPUG_xt_c0", {.f32 = -1000.000000}, {.f32 = 0.000000}, {.f32 = 1000.000000}, &gp_val[42], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    "Coefficient for thermal zero compensation polynomial"},
{"MPUG_xt_c1", {.f32 = -1000.000000}, {.f32 = 0.000000}, {.f32 = 1000.000000}, &gp_val[43], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    "Coefficient for thermal zero compensation polynomial"},
{"MPUG_xt_c2", {.f32 = -1000.000000}, {.f32 = 0.000000}, {.f32 = 1000.000000}, &gp_val[44], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    "Coefficient for thermal zero compensation polynomial"},
{"MPUG_yt_c0", {.f32 = -1000.000000}, {.f32 = 0.000000}, {.f32 = 1000.000000}, &gp_val[45], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    "Coefficient for thermal zero compensation polynomial"},
{"MPUG_yt_c1", {.f32 = -1000.000000}, {.f32 = 0.000000}, {.f32 = 1000.000000}, &gp_val[46], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    "Coefficient for thermal zero compensation polynomial"},
{"MPUG_yt_c2", {.f32 = -1000.000000}, {.f32 = 0.000000}, {.f32 = 1000.000000}, &gp_val[47], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    "Coefficient for thermal zero compensation polynomial"},
{"MPUG_zt_c0", {.f32 = -1000.000000}, {.f32 = 0.000000}, {.f32 = 1000.000000}, &gp_val[48], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    "Coefficient for thermal zero compensation polynomial"},
{"MPUG_zt_c1", {.f32 = -1000.000000}, {.f32 = 0.000000}, {.f32 = 1000.000000}, &gp_val[49], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    "Coefficient for thermal zero compensation polynomial"},
{"MPUG_zt_c2", {.f32 = -1000.000000}, {.f32 = 0.000000}, {.f32 = 1000.000000}, &gp_val[50], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    "Coefficient for thermal zero compensation polynomial"},
{"MPUG_xsens", {.f32 = 0.900000}, {.f32 = 1.000000}, {.f32 = 1.100000}, &gp_val[51], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    "Sensitivity correction"},
{"MPUG_ysens", {.f32 = 0.900000}, {.f32 = 1.000000}, {.f32 = 1.100000}, &gp_val[52], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    "Sensitivity correction"},
{"MPUG_zsens", {.f32 = 0.900000}, {.f32 = 1.000000}, {.f32 = 1.100000}, &gp_val[53], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    "Sensitivity correction"},
{"MPUG_xpol", {.i32 = -1}, {.i32 = 1}, {.i32 = 1}, &gp_val[54], PARAM_POLARITY, MAVLINK_TYPE_INT32_T,  NULL},
{"MPUG_ypol", {.i32 = -1}, {.i32 = 1}, {.i32 = 1}, &gp_val[55], PARAM_POLARITY, MAVLINK_TYPE_INT32_T,  NULL},
{"MPUG_zpol", {.i32 = -1}, {.i32 = 1}, {.i32 = 1}, &gp_val[56], PARAM_POLARITY, MAVLINK_TYPE_INT32_T,  NULL},
{"MPUG_sortmtrx", {.u32 = 0}, {.u32 = 273}, {.u32 = 1}, &gp_val[57], PARAM_SORT_MTRX, MAVLINK_TYPE_UINT32_T, "Sorting matrix for acquired gyro values\nto correspond with real device axis"},
{"MPUG_zerocnt", {.i32 = 512}, {.i32 = 2048}, {.i32 = 16384}, &gp_val[58], PARAM_DEFAULT, MAVLINK_TYPE_INT32_T,  "Sample count for zeroing procedure"},
{"MPUG_zeroflen", {.i32 = 2}, {.i32 = 512}, {.i32 = 2048}, &gp_val[59], PARAM_DEFAULT, MAVLINK_TYPE_INT32_T,  "Filter length used in zero calibration routine"},
{"MPUG_stillthr", {.f32 = 0.000000}, {.f32 = 0.100000}, {.f32 = 1.000000}, &gp_val[60], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    "Stillness threshold Rad/S"},
{"ACC_xoffset", {.i32 = -100}, {.i32 = 0}, {.i32 = 100}, &gp_val[61], PARAM_DEFAULT, MAVLINK_TYPE_INT32_T,  NULL},
{"ACC_yoffset", {.i32 = -100}, {.i32 = 0}, {.i32 = 100}, &gp_val[62], PARAM_DEFAULT, MAVLINK_TYPE_INT32_T,  NULL},
{"ACC_zoffset", {.i32 = -100}, {.i32 = 0}, {.i32 = 100}, &gp_val[63], PARAM_DEFAULT, MAVLINK_TYPE_INT32_T,  NULL},
{"ACC_xsens", {.i32 = 1000}, {.i32 = 8192}, {.i32 = 27000}, &gp_val[64], PARAM_DEFAULT, MAVLINK_TYPE_INT32_T,  "sens LSB/g, nominals: 4096, 8192, 16384"},
{"ACC_ysens", {.i32 = 1000}, {.i32 = 8192}, {.i32 = 27000}, &gp_val[65], PARAM_DEFAULT, MAVLINK_TYPE_INT32_T,  "sens LSB/g, nominals: 4096, 8192, 16384"},
{"ACC_zsens", {.i32 = 1000}, {.i32 = 8192}, {.i32 = 27000}, &gp_val[66], PARAM_DEFAULT, MAVLINK_TYPE_INT32_T,  "sens LSB/g, nominals: 4096, 8192, 16384"},
{"ACC_xpol", {.i32 = -1}, {.i32 = 1}, {.i32 = 1}, &gp_val[67], PARAM_POLARITY, MAVLINK_TYPE_INT32_T,  NULL},
{"ACC_ypol", {.i32 = -1}, {.i32 = 1}, {.i32 = 1}, &gp_val[68], PARAM_POLARITY, MAVLINK_TYPE_INT32_T,  NULL},
{"ACC_zpol", {.i32 = -1}, {.i32 = 1}, {.i32 = 1}, &gp_val[69], PARAM_POLARITY, MAVLINK_TYPE_INT32_T,  NULL},
{"ACC_sortmtrx", {.u32 = 0}, {.u32 = 273}, {.u32 = 1}, &gp_val[70], PARAM_SORT_MTRX, MAVLINK_TYPE_UINT32_T, "Sorting matrix for acquired gyro values\nto correspond with real device axis"},
{"ACC_still_thr", {.f32 = 0.000000}, {.f32 = 0.006000}, {.f32 = 0.100000}, &gp_val[71], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    "Device immobility threshold in g"},
{"ACC_still_flen", {.i32 = 1}, {.i32 = 256}, {.i32 = 2048}, &gp_val[72], PARAM_DEFAULT, MAVLINK_TYPE_INT32_T,  "Length of filter used in immobility detector"},
{"PMU_above_msl", {.i32 = -200}, {.i32 = 255}, {.i32 = 4000}, &gp_val[73], PARAM_DEFAULT, MAVLINK_TYPE_INT32_T,  "Height of barometric sensor above sea level in meters"},
{"PMU_reserved1", {.i32 = -2000000}, {.i32 = 0}, {.i32 = 2000000}, &gp_val[74], PARAM_DEFAULT, MAVLINK_TYPE_INT32_T,  NULL},
{"ADC_car_I_k", {.i32 = -1000000}, {.i32 = 0}, {.i32 = 1000000}, &gp_val[75], PARAM_DEFAULT, MAVLINK_TYPE_INT32_T,  "k coefficient for calculation from ADC values to uA using formulae y=kx+b\nfor ground rover"},
{"ADC_car_I_b", {.i32 = -1000000}, {.i32 = 0}, {.i32 = 1000000}, &gp_val[76], PARAM_DEFAULT, MAVLINK_TYPE_INT32_T,  "b coefficient for calculation from ADC values to uA using formulae y=kx+b\nfor ground rover"},
{"ADC_SV_gain", {.u32 = 0}, {.u32 = 0}, {.u32 = 122400}, &gp_val[77], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, NULL},
{"ADC_MV_gain", {.u32 = 0}, {.u32 = 0}, {.u32 = 122400}, &gp_val[78], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, NULL},
{"ADC_plane_I_k", {.i32 = -1000000}, {.i32 = 0}, {.i32 = 1000000}, &gp_val[79], PARAM_DEFAULT, MAVLINK_TYPE_INT32_T,  "k coefficient for calculation from ADC values to uA using formulae y=kx+b\nfor fixed wing"},
{"ADC_plane_I_b", {.i32 = -1000000}, {.i32 = 0}, {.i32 = 1000000}, &gp_val[80], PARAM_DEFAULT, MAVLINK_TYPE_INT32_T,  "b coefficient for calculation from ADC values to uA using formulae y=kx+b\nfor fixed wing"},
{"BAT_cap", {.u32 = 0}, {.u32 = 3000}, {.u32 = 11000}, &gp_val[81], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, "Battery capacitance (mAh)"},
{"BAT_fill", {.u32 = 0}, {.u32 = 0}, {.u32 = 100}, &gp_val[82], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, "Start battery filling in percents"},
{"SERVO_0_min", {.u32 = 1000}, {.u32 = 1500}, {.u32 = 2000}, &gp_val[83], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, NULL},
{"SERVO_0_max", {.u32 = 1000}, {.u32 = 1500}, {.u32 = 2000}, &gp_val[84], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, NULL},
{"SERVO_0_neutr", {.u32 = 1000}, {.u32 = 1500}, {.u32 = 2000}, &gp_val[85], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, NULL},
{"SERVO_1_min", {.u32 = 1000}, {.u32 = 1500}, {.u32 = 2000}, &gp_val[86], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, NULL},
{"SERVO_1_max", {.u32 = 1000}, {.u32 = 1500}, {.u32 = 2000}, &gp_val[87], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, NULL},
{"SERVO_1_neutr", {.u32 = 1000}, {.u32 = 1500}, {.u32 = 2000}, &gp_val[88], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, NULL},
{"SERVO_2_min", {.u32 = 1000}, {.u32 = 1500}, {.u32 = 2000}, &gp_val[89], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, NULL},
{"SERVO_2_max", {.u32 = 1000}, {.u32 = 1500}, {.u32 = 2000}, &gp_val[90], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, NULL},
{"SERVO_2_neutr", {.u32 = 1000}, {.u32 = 1500}, {.u32 = 2000}, &gp_val[91], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, NULL},
{"SERVO_3_min", {.u32 = 1000}, {.u32 = 1500}, {.u32 = 2000}, &gp_val[92], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, NULL},
{"SERVO_3_max", {.u32 = 1000}, {.u32 = 1500}, {.u32 = 2000}, &gp_val[93], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, NULL},
{"SERVO_3_neutr", {.u32 = 1000}, {.u32 = 1500}, {.u32 = 2000}, &gp_val[94], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, NULL},
{"SERVO_4_min", {.u32 = 1000}, {.u32 = 1500}, {.u32 = 2000}, &gp_val[95], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, NULL},
{"SERVO_4_max", {.u32 = 1000}, {.u32 = 1500}, {.u32 = 2000}, &gp_val[96], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, NULL},
{"SERVO_4_neutr", {.u32 = 1000}, {.u32 = 1500}, {.u32 = 2000}, &gp_val[97], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, NULL},
{"SERVO_5_min", {.u32 = 1000}, {.u32 = 1500}, {.u32 = 2000}, &gp_val[98], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, NULL},
{"SERVO_5_max", {.u32 = 1000}, {.u32 = 1500}, {.u32 = 2000}, &gp_val[99], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, NULL},
{"SERVO_5_neutr", {.u32 = 1000}, {.u32 = 1500}, {.u32 = 2000}, &gp_val[100], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, NULL},
{"SERVO_6_min", {.u32 = 1000}, {.u32 = 1500}, {.u32 = 2000}, &gp_val[101], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, NULL},
{"SERVO_6_max", {.u32 = 1000}, {.u32 = 1500}, {.u32 = 2000}, &gp_val[102], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, NULL},
{"SERVO_6_neutr", {.u32 = 1000}, {.u32 = 1500}, {.u32 = 2000}, &gp_val[103], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, NULL},
{"SERVO_7_min", {.u32 = 1000}, {.u32 = 1500}, {.u32 = 2000}, &gp_val[104], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, NULL},
{"SERVO_7_max", {.u32 = 1000}, {.u32 = 1500}, {.u32 = 2000}, &gp_val[105], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, NULL},
{"SERVO_7_neutr", {.u32 = 1000}, {.u32 = 1500}, {.u32 = 2000}, &gp_val[106], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, NULL},
{"SERVO_car_max", {.u32 = 1}, {.u32 = 1500}, {.u32 = 2000}, &gp_val[107], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, NULL},
{"SERVO_car_dz", {.u32 = 1}, {.u32 = 16}, {.u32 = 64}, &gp_val[108], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, NULL},
{"T_raw_imu", {.u32 = 10}, {.u32 = 0}, {.u32 = 5000}, &gp_val[109], PARAM_SEND_TMO, MAVLINK_TYPE_UINT32_T, "Interval of sending this data in milliseconds.\nSet it to 0 for disabling"},
{"T_scal_imu", {.u32 = 10}, {.u32 = 0}, {.u32 = 5000}, &gp_val[110], PARAM_SEND_TMO, MAVLINK_TYPE_UINT32_T, NULL},
{"T_highres_imu", {.u32 = 10}, {.u32 = 0}, {.u32 = 5000}, &gp_val[111], PARAM_SEND_TMO, MAVLINK_TYPE_UINT32_T, NULL},
{"T_raw_press", {.u32 = 10}, {.u32 = 0}, {.u32 = 5000}, &gp_val[112], PARAM_SEND_TMO, MAVLINK_TYPE_UINT32_T, NULL},
{"T_scal_press", {.u32 = 10}, {.u32 = 0}, {.u32 = 5000}, &gp_val[113], PARAM_SEND_TMO, MAVLINK_TYPE_UINT32_T, NULL},
{"T_attitude", {.u32 = 10}, {.u32 = 0}, {.u32 = 5000}, &gp_val[114], PARAM_SEND_TMO, MAVLINK_TYPE_UINT32_T, NULL},
{"T_vfr_hud", {.u32 = 10}, {.u32 = 0}, {.u32 = 5000}, &gp_val[115], PARAM_SEND_TMO, MAVLINK_TYPE_UINT32_T, NULL},
{"T_gps_int", {.u32 = 10}, {.u32 = 0}, {.u32 = 5000}, &gp_val[116], PARAM_SEND_TMO, MAVLINK_TYPE_UINT32_T, NULL},
{"T_sys_status", {.u32 = 10}, {.u32 = 0}, {.u32 = 5000}, &gp_val[117], PARAM_SEND_TMO, MAVLINK_TYPE_UINT32_T, NULL},
{"T_position_ned", {.u32 = 10}, {.u32 = 0}, {.u32 = 5000}, &gp_val[118], PARAM_SEND_TMO, MAVLINK_TYPE_UINT32_T, NULL},
{"T_nav_output", {.u32 = 10}, {.u32 = 0}, {.u32 = 5000}, &gp_val[119], PARAM_SEND_TMO, MAVLINK_TYPE_UINT32_T, NULL},
{"TIME_zone", {.i32 = -24}, {.i32 = 0}, {.i32 = 24}, &gp_val[120], PARAM_DEFAULT, MAVLINK_TYPE_INT32_T,  "Simple offset in hours."},
{"FLEN_adc", {.i32 = 1}, {.i32 = 16}, {.i32 = 32768}, &gp_val[121], PARAM_DEFAULT, MAVLINK_TYPE_INT32_T,  NULL},
{"FLEN_pres_dyn", {.i32 = 1}, {.i32 = 16}, {.i32 = 32768}, &gp_val[122], PARAM_DEFAULT, MAVLINK_TYPE_INT32_T,  NULL},
{"FLEN_pres_stat", {.i32 = 1}, {.i32 = 16}, {.i32 = 32768}, &gp_val[123], PARAM_DEFAULT, MAVLINK_TYPE_INT32_T,  NULL},
{"FLEN_climb", {.i32 = 1}, {.i32 = 16}, {.i32 = 32768}, &gp_val[124], PARAM_DEFAULT, MAVLINK_TYPE_INT32_T,  NULL},
{"FLEN_gnd_speed", {.i32 = 1}, {.i32 = 16}, {.i32 = 32768}, &gp_val[125], PARAM_DEFAULT, MAVLINK_TYPE_INT32_T,  NULL},
{"FLEN_reserved2", {.i32 = 1}, {.i32 = 16}, {.i32 = 32768}, &gp_val[126], PARAM_DEFAULT, MAVLINK_TYPE_INT32_T,  NULL},
{"FLEN_reserved3", {.i32 = 1}, {.i32 = 16}, {.i32 = 32768}, &gp_val[127], PARAM_DEFAULT, MAVLINK_TYPE_INT32_T,  NULL},
{"FLEN_reserved4", {.i32 = 1}, {.i32 = 16}, {.i32 = 32768}, &gp_val[128], PARAM_DEFAULT, MAVLINK_TYPE_INT32_T,  NULL},
{"SPD_pulse2m", {.f32 = 0.000000}, {.f32 = 0.055556}, {.f32 = 1.000000}, &gp_val[129], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    "Multiply odometer pulses count by this coefficient to get\ntrip in meters. Coarse value is 0.05555555"},
{"SPD_iGain", {.f32 = -1.000000}, {.f32 = 0.000000}, {.f32 = 1.000000}, &gp_val[130], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    NULL},
{"SPD_pGain", {.f32 = -200.000000}, {.f32 = 0.000000}, {.f32 = 200.000000}, &gp_val[131], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    NULL},
{"SPD_dGain", {.f32 = -10000.000000}, {.f32 = 0.000000}, {.f32 = 10000.000000}, &gp_val[132], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    NULL},
{"SPD_iMin", {.f32 = -10000.000000}, {.f32 = 0.000000}, {.f32 = 10000.000000}, &gp_val[133], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    NULL},
{"SPD_iMax", {.f32 = -10000.000000}, {.f32 = 0.000000}, {.f32 = 10000.000000}, &gp_val[134], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    NULL},
{"HDG_iGain", {.f32 = -1.000000}, {.f32 = 0.000000}, {.f32 = 1.000000}, &gp_val[135], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    NULL},
{"HDG_pGain", {.f32 = -200.000000}, {.f32 = 0.000000}, {.f32 = 200.000000}, &gp_val[136], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    NULL},
{"HDG_dGain", {.f32 = -10000.000000}, {.f32 = 0.000000}, {.f32 = 10000.000000}, &gp_val[137], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    NULL},
{"HDG_iMin", {.f32 = -10000.000000}, {.f32 = 0.000000}, {.f32 = 10000.000000}, &gp_val[138], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    NULL},
{"HDG_iMax", {.f32 = -10000.000000}, {.f32 = 0.000000}, {.f32 = 10000.000000}, &gp_val[139], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    NULL},
{"SPD_speed", {.f32 = 0.000000}, {.f32 = 0.000000}, {.f32 = 60.000000}, &gp_val[140], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    NULL},
{"SPD_speed_max", {.f32 = 0.000000}, {.f32 = 0.000000}, {.f32 = 60.000000}, &gp_val[141], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    NULL},
{"XTRACK_iGain", {.f32 = -1.000000}, {.f32 = 0.000000}, {.f32 = 1.000000}, &gp_val[142], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    NULL},
{"XTRACK_pGain", {.f32 = -200.000000}, {.f32 = 0.000000}, {.f32 = 200.000000}, &gp_val[143], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    NULL},
{"XTRACK_dGain", {.f32 = -10000.000000}, {.f32 = 0.000000}, {.f32 = 10000.000000}, &gp_val[144], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    NULL},
{"XTRACK_iMin", {.f32 = -10000.000000}, {.f32 = 0.000000}, {.f32 = 10000.000000}, &gp_val[145], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    NULL},
{"XTRACK_iMax", {.f32 = -10000.000000}, {.f32 = 0.000000}, {.f32 = 10000.000000}, &gp_val[146], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    NULL},
{"DBG_lat", {.f32 = -360.000000}, {.f32 = 0.000000}, {.f32 = 360.000000}, &gp_val[147], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    NULL},
{"DBG_lon", {.f32 = -360.000000}, {.f32 = 0.000000}, {.f32 = 360.000000}, &gp_val[148], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    NULL},
{"DBG_reserved2", {.f32 = 0.000000}, {.f32 = 0.000000}, {.f32 = 10000.000000}, &gp_val[149], PARAM_DEFAULT, MAVLINK_TYPE_FLOAT,    NULL},
{"param_end_mark", {.u32 = 0}, {.u32 = 0}, {.u32 = 1224}, &gp_val[150], PARAM_DEFAULT, MAVLINK_TYPE_UINT32_T, "Fake parameter with maximum allowable name length"},
};
