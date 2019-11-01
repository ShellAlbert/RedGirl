#ifndef OA_PARAMETER_H
#define OA_PARAMETER_H
/**
 * const URL define.
 */
const char *str_url_login = "http://119.10.114.11:8080/logincheck.php";
const char *str_url_logininfo = "http://119.10.114.11:8080/general/login_info.php";
const char *str_url_attendance_table = "http://119.10.114.11:8080/general/attendance/personal/duty/";
const char *str_url_auto_on = "http://119.10.114.11:8080/general/attendance/personal/duty/submit.php?REGISTER_TYPE=1";
const char *str_url_auto_off = "http://119.10.114.11:8080/general/attendance/personal/duty/submit.php?REGISTER_TYPE=2";

/**
 * gb2312 encoding string in hex format.
 */
/**
 * xitongdenglu gb2312 encoding hex string.
 */
const unsigned char flag_gb2312_xitongdenglu[] =
{ 0xcf, 0xb5, 0xcd, 0xb3, 0xb5, 0xc7, 0xc2, 0xbc, '\0' };
/**
 * yonghuminghuomimacuowu gb2312 encoding hex string.
 */
const unsigned char flag_gb2312_yonghuminghuomimacuowu[] =
{ 0xd3, 0xc3, 0xbb, 0xa7, 0xc3, 0xfb, 0xbb, 0xf2, 0xc3, 0xdc, 0xc2, 0xeb, 0xb4, 0xed, 0xce, 0xf3, '\0' };

/**
 * nizhengzaishiyongdadiwenhuanchuanmenjituan gb2312 encoding hex string.
 */
const unsigned char flag_gb2312_nizhengzaishiyongdadiwenhuanchuanmenjituan[] =
{ 0xc4, 0xfa, 0xd5, 0xfd, 0xd4, 0xda, 0xca, 0xb9, 0xd3, 0xc3, 0xb4, 0xf3, 0xb5, 0xd8, ///<
  0xce, 0xc4, 0xbb, 0xaf, 0xb4, 0xab, 0xb2, 0xa5, 0xbc, 0xaf, 0xcd, 0xc5, '\0' };

/**
 * querenyaozhuxiaoma gb2312 encoding hex string.
 */
const unsigned char flag_gb2312_querenyaozhuxiaoma[] =
{ 0xc8, 0xb7, 0xc8, 0xcf, 0xd2, 0xaa, 0xd7, 0xa2, 0xcf, 0xfa, 0xc3, 0xb4, '\0' };

/**
 * zhuomian gb2312 encoding hex string.
 */
const unsigned char flag_gb2312_zhuomian[] =
{ 0xd7, 0xc0, 0xc3, 0xe6, '\0' };

/**
 * jiemian gb2312 encoding hex string.
 */
const unsigned char flag_gb2312_jiemian[] =
{ 0xbd, 0xe7, 0xc3, 0xe6, '\0' };

/**
 * tuichuxitong gb2312 encoding hex string.
 */
const unsigned char flag_gb2312_tuichuxitong[] =
{ 0xcd, 0xcb, 0xb3, 0xf6, 0xcf, 0xb5, 0xcd, 0xb3, '\0' };

/**
 * diyicidengji gb2312 encoding hex string.
 */
const unsigned char flag_gb2312_first_register[] =
{ 0xb5, 0xda, 0x31, 0xb4, 0xce, 0xb5, 0xc7, 0xbc, 0xc7, '\0' };
/**
 * diercidengji gb2312 encoding hex string.
 */
const unsigned char flag_gb2312_second_register[] =
{ 0xb5, 0xda, 0x32, 0xb4, 0xce, 0xb5, 0xc7, 0xbc, 0xc7, '\0' };
/**
 * shangbandengji gb2312 encoding hex string.
 */
const unsigned char flag_gb2312_shangbandengji[] =
{ 0xc9, 0xcf, 0xb0, 0xe0, 0xb5, 0xc7, 0xbc, 0xc7, '\0' };
/**
 * xiabandengji gb2312 encoding hex string.
 */
const unsigned char flag_gb2312_xiabandengji[] =
{ 0xcf, 0xc2, 0xb0, 0xe0, 0xb5, 0xc7, 0xbc, 0xc7, '\0' };
/**
 * weidengji gb2312 encoding hex string.
 */
const unsigned char flag_gb2312_weidengji[] =
{ 0xb4, 0xce, 0xb5, 0xc7, 0xbc, 0xc7, '\0' };
/**
 * yikaoqin gb2312 encoding hex string.
 */
const unsigned char flag_gb2312_yikaoqin[] =
{ 0xd2, 0xd1, 0xbf, 0xbc, 0xc7, 0xda, '\0' };
//temporary file for store http result data.
#define TMP_COOKIE_FILE            ".cookie.zsy"
#endif // OA_PARAMETER_H
