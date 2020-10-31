{
    "targets": [
        {
            "target_name": "engine",
            "sources": ["./engine/engine.cpp"],
            "cflags_cc" :["-fexceptions"],
            "include_dirs": [
                "/home/paulux/Documents/Code/FyneWav/engine/include",
                "/home/paulux/Documents/Code/FyneWav/engine"
            ],
            'link_settings': {
                "libraries": [
                    "-L/home/paulux/Documents/Code/FyneWav/engine/lib", "-lstk", "-lasound", "-lpthread", "-lm"
                ],
            },
            "defines": [
                "__LITTLE_ENDIAN__", "__LINUX_ALSA__"
            ]
        }
    ]
}