cmd_Release/engine.node := ln -f "Release/obj.target/engine.node" "Release/engine.node" 2>/dev/null || (rm -rf "Release/engine.node" && cp -af "Release/obj.target/engine.node" "Release/engine.node")
