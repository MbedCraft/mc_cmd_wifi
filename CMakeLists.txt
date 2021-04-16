idf_component_register( SRCS "mc_cmd_wifi.c"
                        INCLUDE_DIRS "include"
                        PRIV_REQUIRES
                                        console
                                        nvs_flash

                                        mc_assert
                                        mc_wifi
                                        )
