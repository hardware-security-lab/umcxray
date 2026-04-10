#ifndef MC_MIN_H
#define MC_MIN_H

/* from illumos-gate: usr/src/uts/intel/sys/mc.h */
typedef struct mc_snapshot_info
{
    uint32_t mcs_size; /* snapshot size */
    uint_t mcs_gen;    /* snapshot generation number */
} mc_snapshot_info_t;

#define MC_IOC (0x4d43 << 16)
#define MC_IOC_SNAPSHOT_INFO (MC_IOC | 1)
#define MC_IOC_SNAPSHOT (MC_IOC | 2)
#define MC_IOC_DECODE_SNAPSHOT_INFO (MC_IOC | 6)
#define MC_IOC_DECODE_SNAPSHOT (MC_IOC | 7)

#endif // MC_MIN_H
