{
    "targets": [
        {
            "target_name": "engine",
            "sources": ["./engine/wrapper.cpp"],
            "cflags_cc" :["-fexceptions"],
            "include_dirs": [
                "/home/paulux/Documents/Code/FyneWav/FyneWav/engine/include",
                "/home/paulux/Documents/Code/FyneWav/FyneWav/engine"
            ],
            'link_settings': {
                "libraries": [
                    "-L/home/paulux/Documents/Code/FyneWav/FyneWav/engine/lib", "-lstk", "-lasound", "-lpthread", "-lm"
                ],
            },
            "defines": [
                "__LITTLE_ENDIAN__", "__LINUX_ALSA__"
            ]
        }
    ]
}