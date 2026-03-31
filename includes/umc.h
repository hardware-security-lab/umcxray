#ifndef UMC_H
#define UMC_H

#define NUM_BANK_BITS 4
#define NUM_COL_BITS 5
#define NUM_SID_BITS 2

struct atl_xor_bits {
	bool	xor_enable;
	u16	col_xor;
	u32	row_xor;
};

struct atl_addr_hash {
    struct atl_xor_bits bank[NUM_BANK_BITS];
    struct atl_xor_bits pc;
    u8 bank_xor;
};

struct atl_bit_shifts {
	u8 bank[NUM_BANK_BITS];
	u8 col[NUM_COL_BITS];
	u8 sid[NUM_SID_BITS];
	u8 num_row_lo;
	u8 num_row_hi;
	u8 row_lo;
	u8 row_hi;
	u8 pc;
};

typedef int (*get_umc_info_mi300_t)(void);


#endif // UMC_H
