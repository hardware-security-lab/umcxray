#include "cforge.h"

#define CC_TAG "[" CF_YELLOW "CC" CF_RESET "] "
#define LD_TAG "[" CF_CYAN "LD" CF_RESET "] "
#define KO_TAG "[" CF_MAGENTA "KO" CF_RESET "] "

#define KMOD_NAME "atlxray.ko"

CF_CONFIG(release) {
    CF_SET_ENV(cflags, "-O2 -Iincludes/");
    CF_SET_ENV(ldflags, "");
}

CF_TARGET(build,
    CF_WITH_CONFIG(release),
    CF_DEPENDS(kmod),
    CF_DEPENDS(reader),
    CF_HELP_STRING("Build the kmod and reader")
) {
    CF_NOP();   
}

CF_TARGET(clean,
    CF_HELP_STRING("Remove the build artifacts")
) {
    CF_REMOVE("build/");
}

CF_TARGET(insert,
    CF_HELP_STRING("Insert kernel module"),
    CF_DEPENDS(remove),
    CF_DEPENDS(kmod)
) {
    printf(KO_TAG "Inserting module: %s\n", KMOD_NAME);
    CF_RUN("sudo insmod build/%s", KMOD_NAME);
}

CF_TARGET(remove,
    CF_HELP_STRING("Remove kernel module")
) {
    const char* lsmod_log = "build/lsmod.log";

    CF_RUN(
        "lsmod | grep \"^%s\" > %s || true \"\"",
        CF_MAP(KMOD_NAME, CF_MAP_EXT("")),
        lsmod_log
    );
    char* ret = CF_READ(lsmod_log);
    if (ret == NULL) {
        CF_MKDIR("build");
        return;
    }

    if (strlen(ret) != 0) {
        printf(KO_TAG "Currently inserted: %s", ret);
        CF_RUN("sudo rmmod %s", KMOD_NAME);
    }
}

CF_TARGET(kmod, CF_HELP_STRING("Build the kernel module")) {
    bool rebuild = false;

    for CF_GLOBS_EACH("src/kmod/*", file) {
        if CF_FILE_NOT_UTD(file) {
            rebuild = true;
            CF_FILE_MARK_UTD(file);
        }
    }

    if CF_FILE_NOT_UTD("build/" KMOD_NAME) {
        rebuild = true;
    }

    if (!rebuild) {
        return;
    }

    printf(KO_TAG "%s\n", KMOD_NAME);
    fflush(stdout);
    CF_MKDIR("build/");
    CF_RUN("cp -r %s %s", "src/kmod/", "build/");
    cf_glob_t glob = CF_GLOB("src/kmod/*.c");
    char** objs = CF_MAPA(glob.p, glob.c, CF_MAP_EXT("o"), CF_MAP_DIRS(""));
    CF_WRITE(
        "build/kmod/Makefile",
        "ccflags-y := -I$(PWD)/includes\nobj-m += %s\natlxray-y := %s",
        CF_MAP(KMOD_NAME, CF_MAP_EXT("o")),
        CF_JOIN(objs, " ", glob.c)
    );
    CF_RUN("make -C /lib/modules/$(uname -r)/build M=$(pwd)/%s modules", "build/kmod");
    CF_RUN("cp %s/%s %s", "build/kmod", KMOD_NAME, "build/");
    CF_FILE_MARK_UTD("build/" KMOD_NAME);
}

CF_TARGET(reader,
    CF_DEPENDS(reader_link),
    CF_HELP_STRING("Build the reader")
) {
    CF_NOP();
}

CF_TARGET(reader_link, CF_DEPENDS(reader_compile), CF_HIDDEN) {
    const char* obj = "build/reader/*.o";
    char* exe = "build/atlxray_reader";

    if CF_FILE_NOT_UTD(exe) {
        CF_BANNER("%s==== Linking reader ====", LD_TAG);
        char* objs = CF_JOIN_GLOB(CF_GLOB(obj), " ");
        printf(LD_TAG "%s\n", objs);
        CF_RUN("cc %s %s -o %s", CF_ENV(ldflags), objs, exe);
        CF_FILE_MARK_UTD(exe);
    }
}

CF_TARGET(reader_compile, CF_HIDDEN) {
    const char* src = "src/reader/*.c";
    const char* bld = "build/reader/";

    CF_MKDIR(bld);
    for CF_GLOBS_EACH(src, in) {
        char* out = CF_MAP(in, CF_MAP_EXT("o"), CF_MAP_PARENT("build"));
        if (CF_FILE_NOT_UTD(in) || CF_FILE_NOT_UTD(out)) {
            CF_BANNER("%s=== Compiling reader ===", CC_TAG);
            printf(CC_TAG "%s\n", in);
            CF_RUNP("cc %s -c %s -o %s",
                CF_ENV(cflags),
                in,
                out
            );
            CF_FILE_MARK_UTDP(in);
            CF_FILE_MARK_UTDP(out);
        }
    }
}
