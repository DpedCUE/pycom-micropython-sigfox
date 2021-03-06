/*
 * Copyright (c) 2016, Pycom Limited.
 *
 * This software is licensed under the GNU GPL version 3 or any
 * later version, with permitted additional terms. For more information
 * see the Pycom Licence v1.0 document supplied with this file, or
 * available at https://www.pycom.io/opensource/licensing
 */

#ifndef MODWLAN_H_
#define MODWLAN_H_

/******************************************************************************
 DEFINE CONSTANTS
 ******************************************************************************/
#define SIMPLELINK_SPAWN_TASK_PRIORITY              3
#define SIMPLELINK_TASK_STACK_SIZE                  2048
#define SL_STOP_TIMEOUT                             35
#define SL_STOP_TIMEOUT_LONG                        575

#define MODWLAN_WIFI_EVENT_ANY                      0x01

#define MODWLAN_SSID_LEN_MAX                        32

/******************************************************************************
 DEFINE TYPES
 ******************************************************************************/
typedef struct _wlan_wpa2_ent_obj_t {
    const char *ca_certs_path;
    const char *client_key_path;
    const char *client_cert_path;
    const char *identity;
    const char *username;
} wlan_wpa2_ent_obj_t;

typedef struct _wlan_obj_t {
    mp_obj_base_t           base;
    wlan_wpa2_ent_obj_t     wpa2_ent;
    vstr_t                  vstr_ca;
    vstr_t                  vstr_cert;
    vstr_t                  vstr_key;

    uint32_t                status;

    uint32_t                ip;

    int8_t                  mode;
    uint8_t                 auth;
    uint8_t                 channel;
    uint8_t                 antenna;

    // my own ssid, key and mac
    uint8_t                 ssid[(MODWLAN_SSID_LEN_MAX + 1)];
    uint8_t                 key[65];
    uint8_t                 mac[6];

    // the sssid (or name) and mac of the other device
    uint8_t                 ssid_o[33];
    uint8_t                 bssid[6];
    uint8_t                 irq_flags;
    bool                    irq_enabled;
    bool                    enable_servers;
    bool                    disconnected;
    bool                    pwrsave;
    bool                    started;
} wlan_obj_t;

/******************************************************************************
 DECLARE PUBLIC DATA
 ******************************************************************************/
//extern _SlLockObj_t wlan_LockObj;

/******************************************************************************
 DECLARE PUBLIC FUNCTIONS
 ******************************************************************************/
extern void wlan_pre_init (void);
extern void wlan_setup (int32_t mode, const char *ssid, uint32_t auth, const char *key, uint32_t channel, uint32_t antenna, bool add_mac);
extern void wlan_update(void);
extern void wlan_get_mac (uint8_t *macAddress);
extern void wlan_get_ip (uint32_t *ip);
extern bool wlan_is_connected (void);
extern void wlan_set_current_time (uint32_t seconds_since_2000);
extern void wlan_off_on (void);
extern mp_obj_t wlan_deinit(mp_obj_t self_in);

#endif /* MODWLAN_H_ */
