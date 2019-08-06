SDL_HOME=$(shell brew --prefix SDL)

MACOSX_DEPLOYMENT_TARGET=10.14
# 可以通过bash自动检测，没实现
PLATFORM=MACOS

CFLAGS=-fPIC -I$(SDL_HOME)/include -L$(SDL_HOME)/lib -lsdl 
CXXFLAGS=-fPIC
# 假如这些参数后，体积会变大10倍
#OBFUSCATE=-mllvm -bcf -mllvm -bcf_loop=4 -mllvm -bcf_prob=100 -mllvm -sub -mllvm -sub_loop=2
# 发现“-mllvm -bcf”参数有bug 
#OBFUSCATE=-mllvm -fla -mllvm -sub -mllvm -bcf -mllvm -seed=0x$(SEED) -mllvm -sobf 
#OBFUSCATE=-mllvm -fla -mllvm -sub  -mllvm -bcf -mllvm -sobf -mllvm -seed=0x$(SEED) 

OBJS=ekt_input_method_pinyin.o etk.o etk_app.o etk_bitmap.o etk_button.o etk_canvas.o etk_color.o etk_display.o etk_display_sdl.o etk_entry.o etk_event.o etk_font.o etk_gconf.o etk_global.o etk_image_bmp_decoder.o etk_image_decoder.o etk_image_jpeg_decoder.o etk_input_method.o etk_input_method_manager.o etk_main_loop.o etk_malloc.o etk_menu.o etk_menu_item.o etk_pipe.o etk_platform.o etk_rect.o etk_source.o etk_source_default.o etk_source_sdl.o etk_source_timer.o etk_sources_manager.o etk_stack.o etk_text_buffer.o etk_util.o etk_widget.o etk_window.o etk_wnd_manager.o jcomapi.o jdapimin.o jdapistd.o jdcoefct.o jdcolor.o jddctmgr.o jdhuff.o jdinput.o jdmainct.o jdmarker.o jdmaster.o jdmerge.o jdphuff.o jdpostct.o jdsample.o jdtrans.o jerror.o jfdctflt.o jfdctfst.o jfdctint.o jidctflt.o jidctfst.o jidctint.o jidctred.o jmemmgr.o jmemsysextern.o jquant1.o jquant2.o jutils.o main.o

ifeq ($(PLATFORM),WIN32)
	OBJS += etk_win32.o
else
	OBJS += etk_unix.o
endif

TARGET=etk_gui

GCC=clang

.m.o:
	$(GCC) -c -o $@ $<
%.o: %.c
	$(GCC) -c -o $@ $<
.c.o:
	$(GCC) -c -o $@ $<


all: $(TARGET)

$(TARGET): $(OBJS)
	$(GCC) $(CFLAGS) -o $@  -lz $^

clean:
	rm -rf $(OBJS) $(TARGET)
