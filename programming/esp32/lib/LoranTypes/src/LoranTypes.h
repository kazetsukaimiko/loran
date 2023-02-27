
#define NuvoA (0xB4 >> 1)   // root address, second unit is at 0xB6.  Note that the Wire library has a 0-7F range, not a skipped 0-FF range.
#define NuvoB (0xB6 >> 1)

typedef union {
	struct {
		unsigned char P1 :1;
		unsigned char P2 :1;
		unsigned char P3 :1;
		unsigned char P4 :1;
		unsigned char P5 :1;
		unsigned char P6 :1;
		unsigned char Px :2;
	};
	struct {
		unsigned char All;
	};
} chBitflags;
