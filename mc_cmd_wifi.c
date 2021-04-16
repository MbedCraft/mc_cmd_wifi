/* Console example — WiFi commands

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "esp_console.h"

#include "argtable3/argtable3.h"
#include "mc_cmd_wifi.h"
#include "mc_wifi.h"

#include "mc_assert.h"

/** Arguments used by 'join' function */
static struct {
    struct arg_int *timeout;
    struct arg_str *ssid;
    struct arg_str *password;
    struct arg_end *end;
} join_args;

static int connect(int argc, char **argv)
{
    const uint8_t * ssid;
    size_t ssid_size;
    const uint8_t * password;
    size_t password_size;

    int nerrors = arg_parse(argc, argv, (void **) &join_args);
    if (nerrors != 0) {
        arg_print_errors(stderr, join_args.end, argv[0]);
        return 1;
    }

    ssid = (uint8_t *) join_args.ssid->sval[0];
    ssid_size = strlen(join_args.ssid->sval[0]);
    password = (uint8_t *) join_args.password->sval[0];
    password_size = strlen(join_args.password->sval[0]);

    mc_wifi_join(
            ssid, ssid_size,
            password, password_size,
            join_args.timeout->ival[0]);

    return 0;
}

void mc_cmd_wifi_register(void)
{
    join_args.timeout = arg_int0(NULL, "timeout", "<t>", "Connection timeout, ms");
    join_args.ssid = arg_str1(NULL, NULL, "<ssid>", "SSID of AP");
    join_args.password = arg_str0(NULL, NULL, "<pass>", "PSK of AP");
    join_args.end = arg_end(2);

    const esp_console_cmd_t join_cmd = {
        .command = "join",
        .help = "Join WiFi AP as a station",
        .hint = NULL,
        .func = &connect,
        .argtable = &join_args
    };

    ESP_ERROR_CHECK( esp_console_cmd_register(&join_cmd) );
}
