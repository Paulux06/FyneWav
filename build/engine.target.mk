# This file is generated by gyp; do not edit.

TOOLSET := target
TARGET := engine
DEFS_Debug := \
	'-DNODE_GYP_MODULE_NAME=engine' \
	'-DUSING_UV_SHARED=1' \
	'-DUSING_V8_SHARED=1' \
	'-DV8_DEPRECATION_WARNINGS=1' \
	'-DV8_DEPRECATION_WARNINGS' \
	'-DV8_IMMINENT_DEPRECATION_WARNINGS' \
	'-D_LARGEFILE_SOURCE' \
	'-D_FILE_OFFSET_BITS=64' \
	'-DV8_COMPRESS_POINTERS' \
	'-DV8_31BIT_SMIS_ON_64BIT_ARCH' \
	'-D__STDC_FORMAT_MACROS' \
	'-DOPENSSL_NO_PINSHARED' \
	'-DOPENSSL_THREADS' \
	'-D__LITTLE_ENDIAN__' \
	'-D__LINUX_ALSA__' \
	'-DBUILDING_NODE_EXTENSION' \
	'-DDEBUG' \
	'-D_DEBUG' \
	'-DV8_ENABLE_CHECKS'

# Flags passed to all source files.
CFLAGS_Debug := \
	-fPIC \
	-pthread \
	-Wall \
	-Wextra \
	-Wno-unused-parameter \
	-m64 \
	-g \
	-O0

# Flags passed to only C files.
CFLAGS_C_Debug :=

# Flags passed to only C++ files.
CFLAGS_CC_Debug := \
	-fno-rtti \
	-fno-exceptions \
	-std=gnu++1y \
	-fexceptions

INCS_Debug := \
	-I/home/paulux/Documents/Code/FyneWav/FyneWav/10.1.5/include/node \
	-I/home/paulux/Documents/Code/FyneWav/FyneWav/10.1.5/src \
	-I/home/paulux/Documents/Code/FyneWav/FyneWav/10.1.5/deps/openssl/config \
	-I/home/paulux/Documents/Code/FyneWav/FyneWav/10.1.5/deps/openssl/openssl/include \
	-I/home/paulux/Documents/Code/FyneWav/FyneWav/10.1.5/deps/uv/include \
	-I/home/paulux/Documents/Code/FyneWav/FyneWav/10.1.5/deps/zlib \
	-I/home/paulux/Documents/Code/FyneWav/FyneWav/10.1.5/deps/v8/include \
	-I/home/paulux/Documents/Code/FyneWav/FyneWav/engine/include \
	-I/home/paulux/Documents/Code/FyneWav/FyneWav/engine

DEFS_Release := \
	'-DNODE_GYP_MODULE_NAME=engine' \
	'-DUSING_UV_SHARED=1' \
	'-DUSING_V8_SHARED=1' \
	'-DV8_DEPRECATION_WARNINGS=1' \
	'-DV8_DEPRECATION_WARNINGS' \
	'-DV8_IMMINENT_DEPRECATION_WARNINGS' \
	'-D_LARGEFILE_SOURCE' \
	'-D_FILE_OFFSET_BITS=64' \
	'-DV8_COMPRESS_POINTERS' \
	'-DV8_31BIT_SMIS_ON_64BIT_ARCH' \
	'-D__STDC_FORMAT_MACROS' \
	'-DOPENSSL_NO_PINSHARED' \
	'-DOPENSSL_THREADS' \
	'-D__LITTLE_ENDIAN__' \
	'-D__LINUX_ALSA__' \
	'-DBUILDING_NODE_EXTENSION'

# Flags passed to all source files.
CFLAGS_Release := \
	-fPIC \
	-pthread \
	-Wall \
	-Wextra \
	-Wno-unused-parameter \
	-m64 \
	-O3 \
	-fno-omit-frame-pointer

# Flags passed to only C files.
CFLAGS_C_Release :=

# Flags passed to only C++ files.
CFLAGS_CC_Release := \
	-fno-rtti \
	-fno-exceptions \
	-std=gnu++1y \
	-fexceptions

INCS_Release := \
	-I/home/paulux/Documents/Code/FyneWav/FyneWav/10.1.5/include/node \
	-I/home/paulux/Documents/Code/FyneWav/FyneWav/10.1.5/src \
	-I/home/paulux/Documents/Code/FyneWav/FyneWav/10.1.5/deps/openssl/config \
	-I/home/paulux/Documents/Code/FyneWav/FyneWav/10.1.5/deps/openssl/openssl/include \
	-I/home/paulux/Documents/Code/FyneWav/FyneWav/10.1.5/deps/uv/include \
	-I/home/paulux/Documents/Code/FyneWav/FyneWav/10.1.5/deps/zlib \
	-I/home/paulux/Documents/Code/FyneWav/FyneWav/10.1.5/deps/v8/include \
	-I/home/paulux/Documents/Code/FyneWav/FyneWav/engine/include \
	-I/home/paulux/Documents/Code/FyneWav/FyneWav/engine

OBJS := \
	$(obj).target/$(TARGET)/engine/wrapper.o

# Add to the list of files we specially track dependencies for.
all_deps += $(OBJS)

# CFLAGS et al overrides must be target-local.
# See "Target-specific Variable Values" in the GNU Make manual.
$(OBJS): TOOLSET := $(TOOLSET)
$(OBJS): GYP_CFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_C_$(BUILDTYPE))
$(OBJS): GYP_CXXFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_CC_$(BUILDTYPE))

# Suffix rules, putting all outputs into $(obj).

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(srcdir)/%.cpp FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

# Try building from generated source, too.

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj).$(TOOLSET)/%.cpp FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj)/%.cpp FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

# End of this set of suffix rules
### Rules for final target.
LDFLAGS_Debug := \
	-pthread \
	-rdynamic \
	-m64

LDFLAGS_Release := \
	-pthread \
	-rdynamic \
	-m64

LIBS := \
	-L/home/paulux/Documents/Code/FyneWav/FyneWav/engine/lib \
	-lstk \
	-lasound \
	-lpthread \
	-lm

$(obj).target/engine.node: GYP_LDFLAGS := $(LDFLAGS_$(BUILDTYPE))
$(obj).target/engine.node: LIBS := $(LIBS)
$(obj).target/engine.node: TOOLSET := $(TOOLSET)
$(obj).target/engine.node: $(OBJS) FORCE_DO_CMD
	$(call do_cmd,solink_module)

all_deps += $(obj).target/engine.node
# Add target alias
.PHONY: engine
engine: $(builddir)/engine.node

# Copy this to the executable output path.
$(builddir)/engine.node: TOOLSET := $(TOOLSET)
$(builddir)/engine.node: $(obj).target/engine.node FORCE_DO_CMD
	$(call do_cmd,copy)

all_deps += $(builddir)/engine.node
# Short alias for building this executable.
.PHONY: engine.node
engine.node: $(obj).target/engine.node $(builddir)/engine.node

# Add executable to "all" target.
.PHONY: all
all: $(builddir)/engine.node

