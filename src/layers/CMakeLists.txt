cmake_minimum_required(VERSION 3.0)

cmake_policy(SET CMP0076 NEW)

target_sources(guimp_cmake PUBLIC
        add_layer.c
        clear_layers.c
        del_layer.c
        )
